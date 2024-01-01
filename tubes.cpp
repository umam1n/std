#include "TUBES.h"
#include <iostream>

using namespace std;

    list_users LU;
    list_tranksaksi LT;
    list_gudang LG;
    list_barang LB;

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

void mainMenu(list_users &LU) {
    int choice;
    do {
        cout << "Main Menu:\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                login(LU);
                break;
            case 2:
                registerMenu(LU);
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 3);
}

void registerMenu(list_users &LU) {
    infotypeUser newUser; // Creating a variable to store user information

    cout << "Registration Menu:\n";

    // Getting user input for full name
    cout << "Enter your name: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, newUser.nama);

    // Check if the entered user ID already exists
    while (isUsernameExist(LU, newUser.nama)) {
        cout << "User name already exists. Please enter a different username: ";
        cin >> newUser.nama;
    }

    // Getting user input for password
    cout << "Enter your password: ";
    cin >> newUser.password;

    // Call the registerUser function to add the user to the list
    registerUser(LU, newUser);
    cout << "Registration successful!\n";
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
           adminMenu(LG, LT, LU);
        } else if (isPasswordCorrect(user, password)) {
            // Regular user login successful
            userMenu(LG, LT, LU, username);
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

void adminMenu(list_gudang &LG, list_tranksaksi &LT, list_users &LU) {
    int choice;
    do {
        cout << "Admin Menu:\n";
        cout << "1. View Inventory\n";
        cout << "2. Add Item to Inventory\n";
        cout << "3. View All Transactions\n";
        cout << "4. View All Users\n";
        cout << "5. View Transactions by User\n";
        cout << "6. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // viewInventory(LG);
                break;
            case 2:
                // addItemToInventory(LG);
                break;
            case 3:
                // viewAllTransactions(LT);
                break;
            case 4:
                // viewAllUsers(LU);
                break;
            case 5:
                // viewTransactionsByUser(LT);
                break;
            case 6:
                cout << "Logging out...\n";
                mainMenu(LU);
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 6);
}

void userMenu(list_gudang &LG, list_tranksaksi &LT, list_users &LU, const string &username) {
    int choice;
    do {
        cout << "User Menu:\n";
        cout << "1. View Available Items\n";
        cout << "2. Buy Items\n";
        cout << "3. View My Transactions\n";
        cout << "4. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // viewInventory(LG);
                break;
            case 2:
                // makeTransaction(LG, LT, username);
                break;
            case 3:
                // viewUserTransactions(LT, username);
                break;
            case 4:
                cout << "Logging out...\n";
                mainMenu(LU);
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 4);
}
