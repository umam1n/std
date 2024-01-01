#include <iostream>
#include "tubes.h"

using namespace std;

int main() {
    list_users LU;
    list_tranksaksi LT;
    list_gudang LG;
    list_barang LB;

    // Initialize lists
    createListUser(LU);
    createListTranksaksi(LT);
    createListGudang(LG);
    createListBarang(LB);

    mainMenu(LU);

    return 0;
}
