#ifndef TUBES_H_INCLUDED
#define TUBES_H_INCLUDED

#include <string>

#define info(P) (P)->info
#define next(P) (P)->next
#define prev(P) (P)->prev
#define first(L) ((L).first)
#define last(L) ((L).last)
#define nil NULL

using namespace std;

typedef struct tranksaksi infotypeTrank;
typedef struct barang infotypeBar;
typedef struct gudang infotypeGud;
typedef struct users infotypeUser;

typedef struct elemuser *adrUser;
typedef struct elemtrank *adrTrank;
typedef struct elembar *adrBar;
typedef struct elemgud *adrGud;


struct users {
    string password;
    string nama;
    int id;
};

struct tranksaksi {
    string tanggal_trank, jenis;
    int jml_trank;
};

struct barang {
    string nama_barang, alamat, tgl_produksi, tgl_kedaluwarsa;
    int jml_barang, hrg_barang;
};

struct gudang {
    string nama;
    int limit;
};

struct elemuser {
    users info;
    adrUser next;
    adrUser prev;
    adrTrank tranksaksi;
};

struct elemtrank {
    tranksaksi info;
    adrTrank next;
    adrTrank prev;
    adrUser user;  // Relasi dengan user
};

struct elembar {
    barang info;
    adrBar next;
    adrBar prev;
    adrGud gudang;  // Relasi dengan gudang
};

struct elemgud {
    gudang info;
    adrGud next;
    adrTrank transaksi;
    adrBar firstBarang;  // List barang sebagai child dari gudang
};

struct list_users {
    adrUser first;
    adrUser last;
};

struct list_tranksaksi {
    adrTrank first;
    adrTrank last;
};

struct list_barang {
    adrBar first;
    adrBar last;
};

struct list_gudang {
    adrGud first;
    adrGud last;
};


void createListUser(list_users &LU);
void createListTranksaksi(list_tranksaksi &LT);
void createListGudang(list_gudang &LG);
void createListBarang(list_barang &LB);

void mainMenu(list_users &LU);
void login(list_users &LU);
void registerUser(list_users &LU, infotypeUser dataUser);
void registerMenu(list_users &LU);
adrUser findUserByUsername(list_users &LU, const string &username);
bool isUsernameExist(list_users &LU, const string &username);
bool isPasswordCorrect(adrUser user, const string &password);


void adminMenu(list_gudang &LG, list_tranksaksi &LT, list_users &LU);
void userMenu(list_gudang &LG, list_tranksaksi &LT, list_users &LU, const string &username);

#endif // TUBES_H_INCLUDED
