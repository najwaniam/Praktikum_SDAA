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

class RiwayatStack {
private:
    static const int MAX_SIZE = 100;
    Pasien* data[MAX_SIZE];
    int top;

public:
    RiwayatStack() {
        top = -1;
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == MAX_SIZE - 1;
    }

    void push(Pasien* pasien) {
        if (!isFull()) {
            data[++top] = pasien;
            cout << "Riwayat pasien " << pasien->nama << " ditambahkan ke stack" << endl;
        } else {
            cout << "Stack penuh!" << endl;
        }
    }

    Pasien* pop() {
        if (!isEmpty()) {
            return data[top--];
        }
        cout << "Stack kosong!" << endl;
        return nullptr;
    }

    void tampilkanRiwayat() {
        if (isEmpty()) {
            cout << "Tidak ada riwayat pasien" << endl;
            return;
        }

        cout << "\n=== Riwayat Pasien ===" << endl;
        for (int i = top; i >= 0; i--) {
            cout << "ID: " << data[i]->id << endl;
            cout << "Nama: " << data[i]->nama << endl;
            cout << "Diagnosa: " << data[i]->diagnosa << endl;
            cout << "------------------------" << endl;
        }
    }
};

class AntrianQueue {
private:
    static const int MAX_SIZE = 100;
    Pasien* data[MAX_SIZE];
    int front, rear;
    int count;

public:
    AntrianQueue() {
        front = 0;
        rear = -1;
        count = 0;
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == MAX_SIZE;
    }

    void enqueue(Pasien* pasien) {
        if (!isFull()) {
            rear = (rear + 1) % MAX_SIZE;
            data[rear] = pasien;
            count++;
            cout << "Pasien " << pasien->nama << " ditambahkan ke antrian" << endl;
        } else {
            cout << "Antrian penuh!" << endl;
        }
    }

    Pasien* dequeue() {
        if (!isEmpty()) {
            Pasien* pasien = data[front];
            front = (front + 1) % MAX_SIZE;
            count--;
            return pasien;
        }
        cout << "Antrian kosong!" << endl;
        return nullptr;
    }

    void tampilkanAntrian() {
        if (isEmpty()) {
            cout << "Tidak ada pasien dalam antrian" << endl;
            return;
        }

        cout << "\n=== Antrian Pasien ===" << endl;
        int index = front;
        for (int i = 0; i < count; i++) {
            cout << "Posisi " << (i + 1) << ":" << endl;
            cout << "ID: " << data[index]->id << endl;
            cout << "Nama: " << data[index]->nama << endl;
            cout << "Dokter: " << data[index]->dokter << endl;
            cout << "------------------------" << endl;
            index = (index + 1) % MAX_SIZE;
        }
    }
};

RiwayatStack riwayat;
AntrianQueue antrian;

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

    antrian.enqueue(pasienBaru);
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

    Pasien* pasienToDelete = cariPasien(id);
    if (pasienToDelete != nullptr) {
        riwayat.push(pasienToDelete);
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

void prosesAntrian() {
    Pasien* p = antrian.dequeue();
    if (p != nullptr) {
        cout << "Memproses pasien: " << p->nama << endl;
        riwayat.push(p);
    }
}

void tampilkanMenu() {
    cout << "\n=== Manajemen Rumah Sakit ===" << endl;
    cout << "1. Tambah Pasien" << endl;
    cout << "2. Tampilkan Semua Pasien" << endl;
    cout << "3. Perbarui Data Pasien" << endl;
    cout << "4. Hapus Pasien" << endl;
    cout << "5. Lihat Antrian" << endl;
    cout << "6. Proses Antrian" << endl;
    cout << "7. Lihat Riwayat" << endl;
    cout << "8. Keluar" << endl;
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
                antrian.tampilkanAntrian();
                break;
            case 6:
                prosesAntrian();
                break;
            case 7:
                riwayat.tampilkanRiwayat();
                break;
            case 8:
                cout << "Terima kasih telah menggunakan program ini." << endl;
                break;
            default:
                cout << "Opsi tidak valid, silakan coba lagi." << endl;
        }

        cout << endl;
    } while (pilihan != 8);

    return 0;
}