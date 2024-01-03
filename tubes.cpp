#include "inventori.h"

void createListUser(list_users &LU){
    first(LU)= nil;
    last(LU)= nil;
}

void createListGudang(list_gudang &LG){
    first(LG)= nil;
}

void createListBarang(list_barang &LB){
    first(LB)= nil;
}
void createListTranksaksi(list_tranksaksi &LT){
    first(LT)= nil;
}

adrUser allocateUser(infotypeUser dataUser){
    adrUser newUser = new elemuser;
    infoU(newUser) = dataUser;
    //infoU(newUser).id = dataUser.id;
    //infoU(newUser).password = dataUser.password;
    nextG(newUser) = NULL;
    prevU(newUser) = NULL;
    //firstT(newUser) = NULL;
    return newUser;
}

adrGud allocateGud(infotypeGud dataGudang){
    adrGud newGudang = new elemgud;
    infoG(newGudang)= dataGudang;
    nextG(newGudang)= NULL;
    return newGudang;
}

adrTrank allocateTrank(infotypeTrank dataTranksaksi){
    adrTrank newTrank = new elemtrank;
    infoT(newTrank)= dataTranksaksi;
    nextG(newTrank)= NULL;
    nextU(newTrank)= NULL;
    return newTrank;
}

adrBar allocateBarang(infotypeBar dataBarang) {
    adrBar newBarang = new elembar;
    infoB(newBarang) = dataBarang;
    nextB(newBarang) = NULL;
    firstB(newBarang) = NULL;

    return newBarang;
}

void insertUser(list_users &LU, infotypeUser dataUser) {
    adrUser newUser = allocateUser(dataUser);

    if (first(LU) == NULL) {
        // If the list is empty, make the new user the first and last user
        first(LU) = last(LU) = newUser;
        nextG(newUser) = prevU(newUser) = newUser; // Circular connections
    } else {
        // Insert the new user at the end
        nextG(last(LU)) = newUser;
        prevU(newUser) = last(LU);
        nextG(newUser) = first(LU); // Make it circular
        prevU(first(LU)) = newUser; // Update the previous of the first user
        last(LU) = newUser;
    }
}

void deleteUser(list_users &LU, int userIdToDelete) {
    if (first(LU) != NULL) {
        adrUser currentUser = first(LU);
        adrUser prevUser = NULL;

        // Find the user to delete
        while (currentUser != NULL && infoU(currentUser).id != userIdToDelete) {
            prevUser = currentUser;
            currentUser = nextG(currentUser);
        }

        if (currentUser != NULL) {
            // If the user is found

            // Update the next and prev pointers of adjacent nodes
            if (nextG(currentUser) != currentUser) {
                if (prevUser != NULL) {
                    nextG(prevUser) = nextG(currentUser);
                } else {
                    // The user is at the beginning of the list
                    first(LU) = nextG(currentUser);
                }

                prevU(nextG(currentUser)) = prevU(currentUser);

                // Update the first and last pointers if necessary
                if (last(LU) == currentUser) {
                    last(LU) = prevU(currentUser);
                }
            } else {
                // If there is only one user in the list
                first(LU) = last(LU) = NULL;
            }

            // Set the pointer to NULL instead of using delete
            currentUser = NULL;
        }
    }
}


void printUser(list_users &listUsers) {
    if (first(listUsers) == NULL) {
        cout << "No users to display." << endl;
        return;
    }

    adrUser current = first(listUsers);
    do {
        cout << "ID: " << infoU(current).id << endl;
        cout << "Nama: " << infoU(current).nama << endl;
        cout << "Password: " << infoU(current).password << endl;
        cout << "-----------------------------" << endl;
        current = nextG(current);
    } while (current != first(listUsers) && current != NULL);
}


void insertFirstGudang(list_gudang &listGudang, infotypeGud dataGudang) {
    adrGud newGudang = allocateGud(dataGudang);

    if (newGudang != NULL) {
        nextG(newGudang) = first(listGudang);
        first(listGudang) = newGudang;
    } else {
        cout << "Memory allocation failed for the new gudang." << endl;
    }
}

void deleteGudang(list_gudang &listGudang, string namaGudang) {
    adrGud current = first(listGudang);
    adrGud prev = NULL;

    // Search for the gudang to be deleted
    while (current != NULL && infoG(current).nama != namaGudang) {
        prev = current;
        current = nextG(current);
    }

    // Check if the gudang is found
    if (current != NULL) {
        // Remove the gudang from the list
        if (prev != NULL) {
            nextG(prev) = nextG(current);
        } else {
            // The gudang is at the beginning of the list
            first(listGudang) = nextG(current);
        }

        // Set the pointer to NULL instead of using delete
        current = NULL;

        cout << "Gudang '" << namaGudang << "' has been deleted." << endl;
    } else {
        cout << "Gudang '" << namaGudang << "' not found." << endl;
    }
}


// Function to search for a user by name
adrUser searchUser(list_users &LU, string namaUser) {
    adrUser currentUser = first(LU);

    while (currentUser != NULL) {
        if (infoU(currentUser).nama == namaUser) {
            return currentUser; // Found the user
        }
        currentUser = nextG(currentUser);
    }

    return NULL; // User not found
}


// Function to search for a gudang by name
adrGud searchGudang(list_gudang &listGudang, string namaGudang) {
    adrGud currentGudang = first(listGudang);

    while (currentGudang != NULL) {
        if (infoG(currentGudang).nama == namaGudang) {
            return currentGudang; // Found the gudang
        }
        currentGudang = nextG(currentGudang);
    }

    return NULL; // Gudang not found
}

void connectUserToGudang(list_users &LU, list_gudang &LG, string namaUser, string namaGudang) {
    adrUser user = searchUser(LU, namaUser);
    adrGud gudang = searchGudang(LG, namaGudang);

    if (user != NULL && gudang != NULL) {
        if (firstG(gudang) == NULL) {
            firstG(gudang) = user;
        } else {
            nextG(user) = firstG(gudang);

            // Tidak perlu variabel sementara karena firstG(gudang) dapat diubah
            prevU(firstG(gudang)) = user;

            firstG(gudang) = user;
        }
    } else {
        cout << "Data User atau Gudang tidak ditemukan." << endl;
    }
}

adrGud findGudangByUser(list_users &listUsers, string namaUser) {
    adrUser currentUser = first(listUsers);

    // Cari user
    while (currentUser != NULL && infoU(currentUser).nama != namaUser) {
        currentUser = nextG(currentUser);
    }

    // Periksa apakah user ditemukan
    if (currentUser != NULL) {
        // Dapatkan gudang yang terkait dengan user
        adrGud associatedGudang = firstG(currentUser);
        return associatedGudang;
    } else {
        cout << "User '" << namaUser << "' tidak ditemukan." << endl;
        return NULL; // User tidak ditemukan
    }
}

void insertBarang(list_barang &listBarang, adrBar newBarang) {
    if (first(listBarang) == NULL) {
        first(listBarang) = newBarang;
    } else {
        adrBar currentBarang = first(listBarang);
        while (nextB(currentBarang) != NULL) {
            currentBarang = nextB(currentBarang);
        }
        nextB(currentBarang) = newBarang;
    }
}

// Function to search for a barang in list_barang
adrBar searchBarang(list_barang &LB, string namaBarang) {
    adrBar currentBarang = first(LB);

    while (currentBarang != NULL) {
        // Assuming the barang has a member function or data member called nama_barang
        if (infoB(currentBarang).nama_barang == namaBarang) {
            return currentBarang; // Found the barang
        }

        currentBarang = nextB(currentBarang);
    }

    return NULL; // Barang not found
}

void insertTranksaksi(list_tranksaksi &LT, adrTrank newTranksaksi) {
    if (first(LT) == nil) {
        first(LT) = newTranksaksi;
    } else {
        adrTrank currentTranksaksi = first(LT);
        while (nextT(currentTranksaksi) != nil) {
            currentTranksaksi = nextT(currentTranksaksi);
        }
        nextT(currentTranksaksi) = newTranksaksi;
    }
}

void connectUserToGudangWithTranksaksi(list_users &LU, list_tranksaksi &LT, list_gudang &LG, string namaUser, string namaGudang, string tanggalTranksaksi, string jenisTranksaksi, int jumlahTranksaksi) {
    adrUser user = searchUser(LU, namaUser);
    adrGud gudang = searchGudang(LG, namaGudang);

    if (user != NULL && gudang != NULL) {
        // Membuat transaksi baru
        infotypeTrank dataTranksaksi;
        dataTranksaksi.tanggal_trank = tanggalTranksaksi;
        dataTranksaksi.jenis = jenisTranksaksi;
        dataTranksaksi.jml_trank = jumlahTranksaksi;

        adrTrank newTranksaksi = allocateTrank(dataTranksaksi);
        insertTranksaksi(LT, newTranksaksi);

        // Menghubungkan transaksi dengan user dan gudang
        nextU(newTranksaksi) = user;
        nextG(newTranksaksi) = gudang;

        cout << "User '" << namaUser << "' berhasil terhubung dengan Gudang '" << namaGudang << "' melalui transaksi." << endl;
    } else {
        cout << "Data User atau Gudang tidak ditemukan atau transaksi tidak dapat dibuat." << endl;
    }
}

void addBarangToGudang(list_gudang &LG, string namaBarang, string namaGudang) {
    adrGud gudang = searchGudang(LG, namaGudang);

    if (gudang != NULL) {
        // Create a new barang and connect it to the gudang
        infotypeBar dataBarang;
        dataBarang.nama_barang = namaBarang;

        adrBar newBarang = allocateBarang(dataBarang);

        if (firstB(gudang) == NULL) {
            firstB(gudang) = newBarang;
        } else {
            nextB(newBarang) = firstB(gudang);
            firstB(gudang) = newBarang;
        }

        cout << "Barang '" << namaBarang << "' berhasil ditambahkan ke Gudang '" << namaGudang << "'." << endl;
    } else {
        cout << "Gudang '" << namaGudang << "' tidak ditemukan." << endl;
    }
}


int countChildGudang(adrGud gudang) {
    int child = 0;
    adrBar currentBarang = firstB(gudang);

    while (currentBarang != NULL) {
        child++;
        currentBarang = nextB(currentBarang);
    }

    return child;
}

void printTranksaksi(list_tranksaksi &LT, list_users &LU, list_gudang &LG) {
    adrTrank currentTranksaksi = first(LT);

    if (currentTranksaksi == NULL) {
        cout << "Tidak ada transaksi saat ini." << endl;
        return;
    }

    cout << "Daftar Transaksi:" << endl;
    while (currentTranksaksi != nil) {
        cout << "Tanggal Transaksi : " << infoT(currentTranksaksi).tanggal_trank << endl;
        cout << "Jenis Transaksi   : " << infoT(currentTranksaksi).jenis << endl;
        cout << "Jumlah Transaksi  : " << infoT(currentTranksaksi).jml_trank << endl;

        // Check if currentTranksaksi is not nil before accessing nextU and nextG
        if (nextU(currentTranksaksi) != nil && nextG(currentTranksaksi) != nil) {
            cout << "User   : " << infoU(nextU(currentTranksaksi)).nama << endl;
            cout << "Gudang : " << infoG(nextG(currentTranksaksi)).nama << endl;
        }

        cout << "-----------------------------" << endl;

        currentTranksaksi = nextT(currentTranksaksi);
    }
}



int selectMenu() {
    cout<<endl<<endl;
    cout << "    *********************** SELAMAT DATANG **********************"<<endl;
    cout << "    *                           MENU                            *"<<endl;
    cout << "    * 1. Tambahkan Data User                                    *"<<endl;
    cout << "    * 2. Menampilkan Semua Data User                            *"<<endl;
    cout << "    * 3. Mengahapus Data User serta Tranksaksi                  *"<<endl;
    cout << "    * 4. Mencari Data User                                      *"<<endl;
    cout << "    * 5. Tambahkan Data Gudang                                  *"<<endl;
    cout << "    * 6. Mencari Data Gudang                                    *"<<endl;
    cout << "    * 7. Hubungkan User dengan Gudang                           *"<<endl;
    cout << "    * 8. Tambahkan Tranksaksi                                   *"<<endl;
    cout << "    * 9. Menampilkan Tranksaksi                                 *"<<endl;
    cout << "    * 10. Tambahkan Barang ke dalam Gudang                      *"<<endl;
    cout << "    * 11. Mencari Data Gudang pada User Tertentu                *"<<endl;
    cout << "    * 12. Hapus Data Gudang pada User Tertentu                  *"<<endl;
    cout << "    * 13. Menghitung Jumlah Data Barang dari Pelanggan Tertentu *"<<endl;
    cout << "    * 0. Exit                                                   *"<<endl;
    cout << "    *************************************************************"<<endl;
    cout << ">>  Masukkan menu: ";

    int input = 0;
    cin>> input;

    if (input != 0 && input > 11) {
        cout<<"    >>>MAAF MENU TIDAK TERSEDIA<<<";
    }

    return input;
}

void deleteTransactionsWithUser(list_tranksaksi &LT, int userIdToDelete) {
    adrTrank currentTranksaksi = first(LT);
    adrTrank prevTranksaksi = NULL;

    while (currentTranksaksi != NULL) {
        if (nextU(currentTranksaksi) != NULL && infoU(nextU(currentTranksaksi)).id == userIdToDelete) {
            // Remove the transaction from the list
            if (prevTranksaksi != NULL) {
                nextT(prevTranksaksi) = nextT(currentTranksaksi);
            } else {
                // The transaction is at the beginning of the list
                first(LT) = nextT(currentTranksaksi);
            }

            // Move to the next transaction
            adrTrank temp = currentTranksaksi;
            currentTranksaksi = nextT(currentTranksaksi);

            // Set the pointer to NULL instead of using delete
            temp = NULL;
        } else {
            // Move to the next transaction
            prevTranksaksi = currentTranksaksi;
            currentTranksaksi = nextT(currentTranksaksi);
        }
    }
}

// Pemanggilan dari fungsi deleteTransactionsWithUser diperbaiki
void deleteUserWithTransactions(list_users &LU, list_tranksaksi &LT, int userIdToDelete) {
    adrUser currentUser = first(LU), toDelete = NULL;
    adrUser prevUser = NULL;

    // If list is empty or single user who is not the target
    if (first(LU) == NULL || (nextG(first(LU)) == first(LU) && infoU(first(LU)).id != userIdToDelete)) {
        cout << "User with ID " << userIdToDelete << " not found." << endl;
        return;
    }

    // Find the user to delete
    do {
        if (infoU(currentUser).id == userIdToDelete) {
            toDelete = currentUser;
            break;
        }
        prevUser = currentUser;
        currentUser = nextG(currentUser);
    } while (currentUser != first(LU));

    if (toDelete != NULL) {
        // Update links for adjacent nodes
        if (nextG(toDelete) == toDelete) {  // Single element case
            first(LU) = last(LU) = NULL;
        } else {
            if (toDelete == first(LU)) {
                first(LU) = nextG(toDelete);
            }
            if (toDelete == last(LU)) {
                last(LU) = prevUser;
            }
            nextG(prevUser) = nextG(toDelete);
            prevU(nextG(toDelete)) = prevUser;
        }

        // Delete transactions associated with the user
        deleteTransactionsWithUser(LT, userIdToDelete);

        // Finally, delete the user
        delete toDelete;
        cout << "User with ID " << userIdToDelete << " and all associated transactions have been deleted." << endl;
    } else {
        cout << "User with ID " << userIdToDelete << " not found." << endl;
    }
}

