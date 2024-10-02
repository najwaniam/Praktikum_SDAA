#include <iostream>
using namespace std;

struct Pasien {
    int id;
    string nama;
    int umur;
    string dokter;
    string kamar;
    string diagnosa;
    double biaya;
    string penyakit;
    Pasien* next; 
};

Pasien* kepala = nullptr;
int jumlahPasien = 0;

void tambahPasien() {
    Pasien* pasienBaru = new Pasien();
    pasienBaru->id = jumlahPasien + 1;

    cout << "Masukkan nama pasien: ";
    cin.ignore();
    getline(cin, pasienBaru->nama);

    cout << "Masukkan umur pasien: ";
    cin >> pasienBaru->umur;

    cout << "Masukkan nama dokter: ";
    cin.ignore(); 
    getline(cin, pasienBaru->dokter);

    cout << "Masukkan nomor kamar pasien: ";
    getline(cin, pasienBaru->kamar);

    cout << "Masukkan diagnosa pasien: ";
    getline(cin, pasienBaru->diagnosa);

    cout << "Masukkan biaya pengobatan pasien: ";
    cin >> pasienBaru->biaya;

    cout << "Masukkan penyakit pasien (opsional): ";
    cin.ignore(); 
    getline(cin, pasienBaru->penyakit);

    pasienBaru->next = nullptr;

    if (kepala == nullptr) {
        kepala = pasienBaru;
    } else {
        Pasien* temp = kepala;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = pasienBaru;
    }

    jumlahPasien++;
    cout << "Pasien berhasil ditambahkan!" << endl;
}


void lihatPasien() {
    if (kepala == nullptr) {
        cout << "Tidak ada data pasien yang tersedia." << endl;
        return;
    }

    Pasien* temp = kepala;
    cout << "Daftar Pasien:" << endl;
    while (temp != nullptr) {
        cout << "ID: " << temp->id
             << ", Nama: " << temp->nama
             << ", Umur: " << temp->umur
             << ", Dokter: " << temp->dokter
             << ", Kamar: " << temp->kamar
             << ", Diagnosa: " << temp->diagnosa
             << ", Biaya: " << temp->biaya
             << ", Penyakit: " << temp->penyakit << endl;
        temp = temp->next;
    }
}

Pasien* cariPasien(int id) {
    Pasien* temp = kepala;
    while (temp != nullptr) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void perbaruiPasien() {
    int id;
    cout << "Masukkan ID pasien yang akan diperbarui: ";
    cin >> id;

    Pasien* p = cariPasien(id);
    if (p == nullptr) {
        cout << "Pasien dengan ID tersebut tidak ditemukan." << endl;
        return;
    }

    cout << "Memperbarui data pasien dengan ID: " << id << endl;

    cout << "Masukkan nama baru: ";
    cin.ignore(); 
    getline(cin, p->nama);

    cout << "Masukkan umur baru: ";
    cin >> p->umur;

    cout << "Masukkan nama dokter baru: ";
    cin.ignore(); 
    getline(cin, p->dokter);

    cout << "Masukkan nomor kamar baru: ";
    getline(cin, p->kamar);

    cout << "Masukkan diagnosa baru: ";
    getline(cin, p->diagnosa);

    cout << "Masukkan biaya pengobatan baru: ";
    cin >> p->biaya;

    cout << "Masukkan penyakit baru (opsional): ";
    cin.ignore(); 
    getline(cin, p->penyakit);

    cout << "Data pasien berhasil diperbarui!" << endl;
}

void hapusPasien() {
    int id;
    cout << "Masukkan ID pasien yang akan dihapus: ";
    cin >> id;

    if (kepala == nullptr) {
        cout << "Tidak ada pasien dalam database." << endl;
        return;
    }

    if (kepala->id == id) {
        Pasien* temp = kepala;
        kepala = kepala->next;
        delete temp;
        jumlahPasien--;
        cout << "Pasien berhasil dihapus!" << endl;
        return;
    }

    Pasien* temp = kepala;
    while (temp->next != nullptr && temp->next->id != id) {
        temp = temp->next;
    }

    if (temp->next == nullptr) {
        cout << "Pasien dengan ID tersebut tidak ditemukan." << endl;
        return;
    }

    Pasien* untukDihapus = temp->next;
    temp->next = temp->next->next;
    delete untukDihapus;
    jumlahPasien--;

    cout << "Pasien berhasil dihapus!" << endl;
}

void tampilkanMenu() {
    cout << "=== Manajemen Rumah Sakit ===" << endl;
    cout << "1. Tambah Pasien" << endl;
    cout << "2. Tampilkan Semua Pasien" << endl;
    cout << "3. Perbarui Data Pasien" << endl;
    cout << "4. Hapus Pasien" << endl;
    cout << "5. Keluar" << endl;
    cout << "Pilih opsi: ";
}

int main() {
    int pilihan;

    do {
        tampilkanMenu();
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            tambahPasien();
            break;
        case 2:
            lihatPasien();
            break;
        case 3:
            perbaruiPasien();
            break;
        case 4:
            hapusPasien();
            break;
        case 5:
            cout << "Terima kasih telah menggunakan program ini." << endl;
            break;
        default:
            cout << "Opsi tidak valid, silakan coba lagi." << endl;
        }

        cout << endl;
    } while (pilihan != 5);

    return 0;
}
