import streamlit as st
import yfinance as yf
import pandas as pd
import numpy as np
import time
from sklearn.preprocessing import MinMaxScaler
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import LSTM, Dense, Dropout
import matplotlib.pyplot as plt

# Set UI config
st.set_page_config(layout="wide")
st.title("📈 Dashboard Prediksi Saham BBRI, TLKM, ANTM")

# Input: Stock selection and prediction days
stock_choice = st.selectbox("📌 Pilih Saham:", ["BBRI", "TLKM", "ANTM"])
predict_days = st.slider("🧮 Jumlah hari yang ingin diprediksi:", 30, 100, 60)

# Ticker mapping
ticker_map = {
    "BBRI": "BBRI.JK",
    "TLKM": "TLKM.JK",
    "ANTM": "ANTM.JK"
}
tickers = ["BBRI.JK", "TLKM.JK", "ANTM.JK"]
selected_ticker = ticker_map[stock_choice]
selected_index = tickers.index(selected_ticker)

# Download data
@st.cache_data
def get_data():
    df = pd.DataFrame()
    for ticker in tickers:
        try:
            data = yf.download(ticker, start="2021-01-01", end="2025-05-01", auto_adjust=False)
            df[ticker] = data['Close']
            time.sleep(2)
        except Exception as e:
            st.error(f"Gagal mengunduh data untuk {ticker}: {e}")
    return df.dropna()

df_close = get_data()

# Preprocessing
scaler = MinMaxScaler()
scaled_data = scaler.fit_transform(df_close)

# Sequence preparation
def create_sequences(data, time_steps=50):
    X, y = [], []
    for i in range(len(data) - time_steps):
        X.append(data[i:i+time_steps])
        y.append(data[i+time_steps])
    return np.array(X), np.array(y)

time_steps = 50
X, y = create_sequences(scaled_data, time_steps)
X = X.reshape((X.shape[0], X.shape[1], len(tickers)))

# Train-test split
split_idx = int(len(X) * 0.8)
X_train, X_test = X[:split_idx], X[split_idx:]
y_train, y_test = y[:split_idx], y[split_idx:]

# Build model
model = Sequential([
    LSTM(50, return_sequences=True, input_shape=(time_steps, len(tickers))),
    Dropout(0.2),
    LSTM(50, return_sequences=True),
    Dropout(0.2),
    LSTM(50),
    Dropout(0.2),
    Dense(25),
    Dense(len(tickers))
])
model.compile(optimizer='adam', loss='mean_squared_error')
with st.spinner("🚀 Melatih model..."):
    model.fit(X_train, y_train, epochs=20, batch_size=32, verbose=0)

# Predict future
future_input = scaled_data[-time_steps:]
future_input = np.reshape(future_input, (1, time_steps, len(tickers)))

future_predictions = []
for _ in range(predict_days):
    pred = model.predict(future_input, verbose=0)
    future_predictions.append(pred[0])
    future_input = np.append(future_input[:, 1:, :], [[pred[0]]], axis=1)

future_predictions = scaler.inverse_transform(np.array(future_predictions))
future_df = pd.DataFrame(future_predictions, columns=tickers)
future_dates = pd.date_range(start=df_close.index[-1] + pd.Timedelta(days=1), periods=predict_days, freq='B')

# Combine actual + predicted
combined_df = pd.concat([df_close[[selected_ticker]].iloc[-100:], pd.DataFrame(
    {selected_ticker: future_df[selected_ticker].values}, index=future_dates)])

# Plot
st.subheader(f"📊 Grafik Harga dan Prediksi ({stock_choice})")
st.line_chart(combined_df)

# Prediction change %
start_price = combined_df[selected_ticker].iloc[-predict_days - 1]
end_price = combined_df[selected_ticker].iloc[-1]
pct_change = ((end_price - start_price) / start_price) * 100
st.metric("📈 Persentase Prediksi Kenaikan", f"{pct_change:.2f} %")

# Dummy Sentiment Table
st.subheader("🧾 Sentimen 7 Hari Terakhir (simulasi)")
sentiment_df = pd.DataFrame({
    "Tanggal": pd.date_range(end=pd.Timestamp.today(), periods=7, freq='B'),
    "Sentimen": np.random.choice(["Positif", "Netral", "Negatif"], size=7),
    "Sumber": np.random.choice(["Twitter", "News"], size=7)
})
st.dataframe(sentiment_df, use_container_width=True)

# Recommendation
st.subheader("✅ Rekomendasi")
if pct_change > 5:
    st.success("Rekomendasi: **BUY** - Prediksi naik signifikan 📈")
elif pct_change < -5:
    st.error("Rekomendasi: **SELL** - Prediksi turun signifikan 📉")
else:
    st.warning("Rekomendasi: **HOLD** - Pergerakan stabil 🔄")
