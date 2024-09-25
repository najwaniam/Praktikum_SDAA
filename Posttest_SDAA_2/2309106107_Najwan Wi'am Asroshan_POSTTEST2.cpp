#include <iostream>
using namespace std;

int BatasPasien = 100; 
struct Pasien {
    int id;
    string nama;
    int umur;
    string dokter;
    string kamar;
    string diagnosis;    
    double biaya;
    string sakit;
};

Pasien Pasiens[100];
int JumlahPasien = 0;

void addPasien() {
    if (JumlahPasien >= BatasPasien) {
        cout << "Database penuh, tidak bisa menambahkan pasien baru." << endl;
        return;
    }

    Pasien* newPasien = &Pasiens[JumlahPasien];
    newPasien->id = JumlahPasien + 1;

    cout << "Masukkan nama pasien: ";
    cin.ignore(); 
    getline(cin, newPasien->nama);

    cout << "Masukkan umur pasien: ";
    cin >> newPasien->umur;

    cout << "Masukkan nama dokter: ";
    cin.ignore(); 
    getline(cin, newPasien->dokter);

    cout << "Masukkan nomor kamar pasien: ";
    getline(cin, newPasien->kamar);

    cout << "Masukkan diagnosa pasien: ";
    getline(cin, newPasien->diagnosis);

    cout << "Masukkan biaya pengobatan pasien: ";
    cin >> newPasien->biaya;

    cout << "Masukkan penyakit pasien (opsional): ";
    cin.ignore(); 
    getline(cin, newPasien->sakit);

    JumlahPasien++;
    cout << "Pasien berhasil ditambahkan!" << endl;
}

void viewPasiens() {
    if (JumlahPasien == 0) {
        cout << "Tidak ada data pasien yang tersedia." << endl;
        return;
    }

    cout << "Daftar Pasien:" << endl;
    for (int i = 0; i < JumlahPasien; i++) {
        Pasien* p = &Pasiens[i];
        cout << "ID: " << p->id 
             << ", Nama: " << p->nama
             << ", Umur: " << p->umur 
             << ", Dokter: " << p->dokter 
             << ", Kamar: " << p->kamar 
             << ", Diagnosa: " << p->diagnosis 
             << ", Biaya: " << p->biaya 
             << ", Penyakit: " << p->sakit << endl;
    }
}

Pasien* CariPasien(int id) {
    for (int i = 0; i < JumlahPasien; i++) {
        if (Pasiens[i].id == id) {
            return &Pasiens[i];
        }
    }
    return nullptr;
}

void UpdatePasien() {
    int id;
    cout << "Masukkan ID pasien yang akan diperbarui: ";
    cin >> id;

    Pasien* p = CariPasien(id);
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
    getline(cin, p->diagnosis);

    cout << "Masukkan biaya pengobatan baru: ";
    cin >> p->biaya;

    cout << "Masukkan penyakit baru (opsional): ";
    cin.ignore(); 
    getline(cin, p->sakit);

    cout << "Data pasien berhasil diperbarui!" << endl;
}

void HapusPasien() {
    int id;
    cout << "Masukkan ID pasien yang akan dihapus: ";
    cin >> id;

    Pasien* p = CariPasien(id);
    if (p == nullptr) {
        cout << "Pasien dengan ID tersebut tidak ditemukan." << endl;
        return;
    }

    for (int i = id - 1; i < JumlahPasien - 1; i++) {
        Pasiens[i] = Pasiens[i + 1];
    }
    JumlahPasien--;

    cout << "Pasien berhasil dihapus!" << endl;
}

void menu() {
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
        menu();
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            addPasien();
            break;
        case 2:
            viewPasiens();
            break;
        case 3:
            UpdatePasien();
            break;
        case 4:
            HapusPasien();
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
