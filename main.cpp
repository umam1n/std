#include <iostream>
#include "inventori.h"

using namespace std;

int main()
{
    list_users LU;
    list_gudang LG;
    list_barang LB;
    list_tranksaksi LT;

    createListUser(LU);
    createListGudang(LG);
    createListBarang(LB);
    createListTranksaksi(LT);

    adrUser U;
    adrGud G;
    adrBar B;
    adrTrank T;

    //Deklarasi Variabel Data Pelanggan
    infotypeUser DU;

    //Deklarasi Variabel Data Barang
    infotypeGud DG;
    infotypeBar DB;

    int pilihan = selectMenu();
    while (pilihan != 0 ) {
        switch(pilihan) {
        case 1:
            {
            cout << "Tambahkan Data User" << endl;
            cout << "Nama    : ";
            cin >> DU.nama;
            cout << "ID      : ";
            cin >> DU.id;
            cout << "Password: ";
            cin >> DU.password;
            insertUser(LU,DU);
            }
            break;
        case 2:
            {
            cout <<"MENAMPILKAN SELURUH DATA USER"<<endl;
            printUser(LU);
            }
            break;
        case 3:
            {
            int idUser;
            cout << "HAPUS DATA USER" <<endl;
            cout << "ID : ";
            cin >> idUser;
            deleteUserWithTransactions(LU, LT, idUser);
            }
            break;
        case 4:
            {
            string namaUser;
            adrUser found;
            cout << "Mencari Data User" <<endl;
            cout <<"Masukkan Nama User: ";
            cin >> namaUser;
            found = searchUser(LU,namaUser);
            if (found != nil) {
                cout << endl <<"Data Yang Dicari: "<<endl;
                cout << "Nama          : " << infoU(found).nama <<endl;
                cout << "ID            : " << infoU(found).id<<endl;
                cout << "Password      : "<<infoU(found).password<<endl;
            } else {
                cout << "===================================="<<endl;
                cout << "|  DATA PELANGGAN TIDAK DITEMUKAN   |"<<endl;
                cout << "===================================="<<endl;
            }
            }
            break;
        case 5:
            {
            cout << "Tambahkan Data Gudang" <<endl;
            cout << "Nama Gudang       : ";
            cin >> DG.nama;
            cout << "Limit Gudang      : ";
            cin >> DG.limit;
            cout << "Terisi sekarang   : ";
            cin >> DG.isi;
            insertFirstGudang(LG,DG);
            }
            break;
        case 6:
            {
            string namaGudang;
            adrGud found;
            cout << "Mencari Data Gudang" <<endl;
            cout <<"Masukkan Nama Gudang: ";
            cin >> namaGudang;
            found = searchGudang(LG,namaGudang);
            if (found != nil) {
                cout << endl <<"Data Yang Dicari: "<<endl;
                cout << "Nama Gudang         : " << infoG(found).nama <<endl;
                cout << "Limit Gudang        : " << infoG(found).limit<<endl;
                cout << "Terisi sekarang     : " <<infoG(found).isi<<endl;
            } else {
                cout << "===================================="<<endl;
                cout << "|  DATA GUDANG TIDAK DITEMUKAN   |"<<endl;
                cout << "===================================="<<endl;
            }
            }
            break;
        case 7:
            {
            string namaUser, namaGudang;
            cout<< "Hubungkan User dengan Data Gudang"<<endl;
            cout << "Nama User untuk Dihubungkan: ";
            cin >>namaUser;
            cout << "Nama Gudang                   : ";
            cin >> namaGudang;
            connectUserToGudang(LU, LG, namaUser, namaGudang);
            }
            break;
        case 8:
            {
            string namaUser, namaGudang, tanggalTranksaksi, jenisTranksaksi;
            int jumlahTranksaksi;
            cout << "Buat Tranksaksi Baru" << endl;
            cout << "Nama User : ";
            cin >> namaUser;
            cout << "Nama Gudang ";
            cin >> namaGudang;
            cout << "Tanggal Tranksaksi : ";
            cin >> tanggalTranksaksi;
            cout << "Jenis Tranksaksi : ";
            cin >> jenisTranksaksi;
            cout << "Jumlah Tranksaksi: ";
            cin >> jumlahTranksaksi;
            connectUserToGudangWithTranksaksi(LU,LT,LG,namaUser,namaGudang, tanggalTranksaksi, jenisTranksaksi, jumlahTranksaksi);
            }
            break;
        case 9:
            {
                    printTranksaksi(LT, LU, LG);
            }
            break;
        case 10:
            {
            string namaBarang, namaGudang;
            int jumlahbarang;
            cout << "Tambah Barang ke Gudang" << endl;
            cout << "Nama Barang : ";
            cin >> namaBarang;
            cout << "Nama Gudang : ";
            cin >> namaGudang;
            cout << "jumlah barang yang ingin ditambahkan :";
            cin >> jumlahbarang;
            addBarangToGudang(LG, namaBarang, namaGudang, jumlahbarang);
            }
        case 11:
            {
                // Implement your logic to search Gudang for a specific User
            }
            break;
        case 12:
            {
                // Implement your logic to delete Gudang for a specific User
            }
            break;
        case 13:
            {
                // Implement your logic to count the number of Barang from a specific User
            }
            break;


        }

        pilihan = selectMenu();
        }
    cout<<"|-------------------------------------------------|"<<endl;
    cout<<"|=========ANDA TELAH KELUAR DARI PROGRAM==========|"<<endl;
    cout<<"|-------------------------------------------------|"<<endl;

    return 0;
}
