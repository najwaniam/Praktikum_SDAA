#include <iostream>
using namespace std;

void menara(int n, char sumber, char tujuan, char sementara) {
    if (n == 1) {
        cout << "Pindahkan piringan 1 dari " << sumber << " ke " << tujuan << endl;
        return;
    }
    
    menara(n - 1, sumber, sementara, tujuan);
    cout << "Pindahkan piringan " << n << " dari " << sumber << " ke " << tujuan << endl;
    menara(n - 1, sementara, tujuan, sumber);
}

int main() {
    cout << "Kasus 1: Memindahkan 3 piringan dari A ke C menggunakan B:" << endl;
    menara(3, 'A', 'C', 'B');
    cout << endl;

    cout << "Kasus 2: Memindahkan 3 piringan dari C ke B menggunakan A:" << endl;
    menara(3, 'C', 'B', 'A');
    cout << endl;

    cout << "Kasus 3: Memindahkan 3 piringan dari B ke A menggunakan C:" << endl;
    menara(3, 'B', 'A', 'C');
    cout << endl;

    return 0;
}
