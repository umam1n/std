#ifndef INVENTORI_H_INCLUDED
#define INVENTORI_H_INCLUDED

#include <string>
#include <iostream>

#define firstU(P) (P)->firstU
#define firstT(P) (P)->firstT
#define firstG(P) (P)->firstG
#define firstB(P) (P)->firstB
#define infoG(P) (P)->infoG
#define infoU(P) (P)->infoU
#define infoT(P) (P)->infoT
#define infoB(P) (P)->infoB
#define nextG(P) (P)->nextG
#define nextU(P) (P)->nextU
#define nextB(P) (P)->nextB
#define nextT(P) (P)->nextT
#define prevU(P) (P)->prevU
#define last(L) ((L).last)
#define first(L) ((L).first)
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
    int isi;
    int limit;
};

struct elemuser {
    infotypeUser infoU;
    adrUser nextU;
    adrUser nextG;
    adrUser prevU;
    adrTrank firstT;
    adrGud firstG;
};

struct elemtrank {
    infotypeTrank infoT;
    adrUser nextU;
    adrTrank nextT;
    adrGud nextG;
};

struct elembar {
    infotypeBar infoB;
    adrBar nextB;
    adrBar firstB;
    adrGud firstG;
    adrGud connectedGud;
};

struct elemgud {
    infotypeGud infoG;
    adrGud nextG;
    adrUser firstG;
    adrBar firstB;
};

struct list_users {
    adrUser first;
    adrUser last;
};

struct list_tranksaksi {
    adrTrank first;
};

struct list_barang {
    adrBar first;
};

struct list_gudang {
    adrGud first;
};

void createListUser(list_users &LU);
void createListGudang(list_gudang &LG);
void createListBarang(list_barang &LB);
void createListTranksaksi(list_tranksaksi &LT);

adrUser allocateUser(infotypeUser dataUser);
adrGud allocateGud(infotypeGud dataGudang);
adrTrank allocateTrank(infotypeTrank dataTranksaksi);
adrBar allocateBarang(infotypeBar dataBarang);

void insertUser(list_users &LU, infotypeUser dataUser);
void deleteUser(list_users &LU, int userIdToDelete);
void printUser(list_users &listUsers);

void insertFirstGudang(list_gudang &listGudang, infotypeGud dataGudang);
void deleteGudang(list_gudang &listGudang, string namaGudang);
adrGud findGudangByUser(list_users &listUsers, string namaUser);

adrUser searchUser(list_users &LU, string namaUser);
adrGud searchGudang(list_gudang &listGudang, string namaGudang);

void connectUserToGudang(list_users &LU, list_gudang &LG, string namaUser, string namaGudang);
void deleteUserWithTransactions(list_users &listUsers, list_tranksaksi &listTranksaksi, string namaUser);
void showUserWithTransactionAndGudang(list_users &listUsers, string namaUser);

void insertBarang(list_barang &listBarang, adrBar newBarang);
adrBar searchBarang(list_barang &LB, string namaBarang);
void connectBarangToGudang(list_barang &LB, list_gudang &LG, string namaBarang, string namaGudang);
int countChildGudang(adrGud gudang);

int selectMenu();
void insertTranksaksi(list_tranksaksi &LT, adrTrank newTranksaksi);
void connectUserToGudangWithTranksaksi(list_users &LU, list_tranksaksi &LT, list_gudang &LG, string namaUser, string namaGudang, string tanggalTranksaksi, string jenisTranksaksi, int jumlahTranksaksi);
void printTranksaksi(list_tranksaksi &LT, list_users &LU, list_gudang &LG);

void addBarangToGudang(list_gudang &LG, string namaBarang, string namaGudang, int jumlahbarang);
void deleteTransactionsWithUser(list_tranksaksi &LT, int userIdToDelete);
void deleteUserWithTransactions(list_users &LU, list_tranksaksi &LT, int userIdToDelete);
#endif // INVENTORI_H_INCLUDED
