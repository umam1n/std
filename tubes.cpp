#include "TUBES.h"
#include <iostream>

using namespace std;

void createListUser(list_users &LU){
    first(LU) = nil;
    last(LU) = nil;
}

void createListTranksaksi(list_tranksaksi &LT){
    first(LT) = nil;
    last(LT) = nil;
}

void createListGudang(list_gudang &LG){
    first(LG) = nil;
    last(LG) = nil;
}

void createListBarang(list_barang &LB){
    first(LB) = nil;
    last(LB) = nil;
}
void registerUser(list_users &LU, infotypeUser dataUser) {
    adrUser newUser = new elemuser;
    info(newUser) = dataUser;
    next(newUser) = nil;
    prev(newUser) = nil;

    if (first(LU) == nil) {
        first(LU) = newUser;
        last(LU) = newUser;
    } else {
        next(newUser) = first(LU);
        prev(first(LU)) = newUser;
        first(LU) = newUser;
    }

    cout << "Registration successful. Welcome, " << dataUser.nama << "!" << endl;
}

void login(list_users &LU) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;

    if (isUsernameExist(LU, username)) {
        adrUser user = findUserByUsername(LU, username);

        cout << "Enter password: ";
        cin >> password;

        if (username == "admin" && info(user).password == password) {
            // Admin login successful
            cout << "Welcome, Admin!" << endl;
            // Add additional actions or messages for the admin if needed
        } else if (isPasswordCorrect(user, password)) {
            // Regular user login successful
            printWelcomeMessage(user);
        } else {
            cout << "Incorrect password." << endl;
        }
    } else {
        cout << "User with username " << username << " does not exist." << endl;
    }
}


adrUser findUserByUsername(list_users &LU, const string &username) {
    adrUser P = first(LU);
    while (P != nil && info(P).nama != username) {
        P = next(P);
    }
    return P;
}

bool isUsernameExist(list_users &LU, const string &username) {
    return findUserByUsername(LU, username) != nil;
}

bool isPasswordCorrect(adrUser user, const string &password) {
    return info(user).password == password;
}

