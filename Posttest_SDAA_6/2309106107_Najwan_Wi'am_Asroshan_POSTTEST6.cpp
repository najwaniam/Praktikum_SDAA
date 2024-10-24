#include <iostream>
#include <algorithm>
#include <cmath> 
#include <vector> 
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

int partitionAsc(Pasien* arr[], int low, int high) {
    int pivot = arr[high]->id;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j]->id < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSortAsc(Pasien* arr[], int low, int high) {
    if (low < high) {
        int pi = partitionAsc(arr, low, high);
        quickSortAsc(arr, low, pi - 1);
        quickSortAsc(arr, pi + 1, high);
    }
}

void shellSortDesc(Pasien* arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            Pasien* temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap]->id < temp->id; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

Pasien** linkedListToArray(Pasien* head, int& size) {
    size = 0;
    Pasien* current = head;
    while (current != nullptr) {
        size++;
        current = current->next;
    }

    Pasien** arr = new Pasien*[size];
    current = head;
    for (int i = 0; i < size; i++) {
        arr[i] = current;
        current = current->next;
    }

    return arr;
}

void arrayToLinkedList(Pasien** arr, int size) {
    kepala = arr[0];
    for (int i = 0; i < size - 1; i++) {
        arr[i]->next = arr[i + 1];
    }
    arr[size - 1]->next = nullptr;
}

void displaySortedPatients(Pasien** arr, int size, string order) {
    cout << "\nDaftar Pasien (diurutkan " << order << " berdasarkan ID):" << endl;
    for (int i = 0; i < size; i++) {
        cout << "ID: " << arr[i]->id
             << ", Nama: " << arr[i]->nama
             << ", Umur: " << arr[i]->umur
             << ", Dokter: " << arr[i]->dokter
             << ", Kamar: " << arr[i]->kamar
             << ", Diagnosa: " << arr[i]->diagnosa
             << ", Biaya: " << arr[i]->biaya
             << ", Penyakit: " << arr[i]->penyakit << endl;
    }
}

void sortPasiensAscending() {
    if (kepala == nullptr || kepala->next == nullptr) {
        cout << "Tidak ada pasien atau hanya ada satu pasien. Pengurutan tidak diperlukan." << endl;
        return;
    }

    int size;
    Pasien** arr = linkedListToArray(kepala, size);
    quickSortAsc(arr, 0, size - 1);
    
    displaySortedPatients(arr, size, "ascending");
    
    arrayToLinkedList(arr, size);
    delete[] arr;
    cout << "Pasien telah diurutkan secara ascending berdasarkan ID." << endl;
}

void sortPasiensDescending() {
    if (kepala == nullptr || kepala->next == nullptr) {
        cout << "Tidak ada pasien atau hanya ada satu pasien. Pengurutan tidak diperlukan." << endl;
        return;
    }

    int size;
    Pasien** arr = linkedListToArray(kepala, size);
    shellSortDesc(arr, size);
    
    displaySortedPatients(arr, size, "descending");
    
    arrayToLinkedList(arr, size);
    delete[] arr;
    cout << "Pasien telah diurutkan secara descending berdasarkan ID." << endl;
}

int fibonacciSearch(Pasien** arr, int n, int x) {
    int fib2 = 0;
    int fib1 = 1;
    int fib = fib2 + fib1;

    while (fib < n) {
        fib2 = fib1;
        fib1 = fib;
        fib = fib2 + fib1;
    }

    int offset = -1;

    while (fib > 1) {
        int i = min(offset + fib2, n - 1);

        if (arr[i]->id < x) {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        } else if (arr[i]->id > x) {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        } else {
            return i;
        }
    }

    if (fib1 && arr[offset + 1]->id == x) {
        return offset + 1;
    }

    return -1;
}

int jumpSearch(Pasien** arr, int n, int x) {
    int step = sqrt(n);
    int prev = 0;

    while (arr[min(step, n) - 1]->id < x) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            return -1;
        }
    }

    while (arr[prev]->id < x) {
        prev++;
        if (prev == min(step, n)) {
            return -1;
        }
    }

    if (arr[prev]->id == x) {
        return prev;
    }

    return -1;
}

int boyerMooreSearch(const string& text, const string& pattern) {
    int m = pattern.size();
    int n = text.size();

    vector<int> badChar(256, -1);

    for (int i = 0; i < m; i++) {
        badChar[(int)pattern[i]] = i;
    }

    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }

        if (j < 0) {
            return s;
        } else {
            s += max(1, j - badChar[text[s + j]]);
        }
    }

    return -1;
}

void cariPasienDenganFibonacci() {
    if (kepala == nullptr) {
        cout << "Error: Tidak ada pasien dalam sistem." << endl;
        return;
    }

    int id;
    cout << "Masukkan ID pasien yang ingin dicari (Fibonacci Search): ";
    cin >> id;

    int size;
    Pasien** arr = linkedListToArray(kepala, size);
    
    int hasil = fibonacciSearch(arr, size, id);
    if (hasil == -1) {
        cout << "Pasien dengan ID " << id << " tidak ditemukan." << endl;
    } else {
        cout << "Pasien ditemukan! Nama: " << arr[hasil]->nama << endl;
    }

    delete[] arr;
}


void cariPasienDenganJump() {
    if (kepala == nullptr) {
        cout << "Error: Tidak ada pasien dalam sistem." << endl;
        return;
    }

    int id;
    cout << "Masukkan ID pasien yang ingin dicari (Jump Search): ";
    cin >> id;

    int size;
    Pasien** arr = linkedListToArray(kepala, size);

    int hasil = jumpSearch(arr, size, id);
    if (hasil == -1) {
        cout << "Pasien dengan ID " << id << " tidak ditemukan." << endl;
    } else {
        cout << "Pasien ditemukan! Nama: " << arr[hasil]->nama << endl;
    }

    delete[] arr;
}


void cariPasienDenganBoyerMoore() {
    if (kepala == nullptr) {
        cout << "Error: Tidak ada pasien dalam sistem." << endl;
        return;
    }

    string nama;
    cout << "Masukkan nama pasien yang ingin dicari (Boyer-Moore Search): ";
    cin.ignore();
    getline(cin, nama);

    Pasien* temp = kepala;
    bool ditemukan = false;

    while (temp != nullptr) {
        if (boyerMooreSearch(temp->nama, nama) != -1) {
            cout << "Pasien ditemukan! ID: " << temp->id << ", Nama: " << temp->nama << endl;
            ditemukan = true;
            break;
        }
        temp = temp->next;
    }

    if (!ditemukan) {
        cout << "Pasien dengan nama " << nama << " tidak ditemukan." << endl;
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
    cout << "8. Urutkan Pasien (Ascending)" << endl;
    cout << "9. Urutkan Pasien (Descending)" << endl;
    cout << "10. Cari Pasien dengan Fibonacci Search" << endl;
    cout << "11. Cari Pasien dengan Jump Search" << endl;
    cout << "12. Cari Pasien dengan Boyer-Moore Search" << endl;
    cout << "13. Keluar" << endl;
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
                sortPasiensAscending();
                break;
            case 9:
                sortPasiensDescending();
                break;
            case 10:
                cariPasienDenganFibonacci();
                break;
            case 11:
                cariPasienDenganJump();
                break;
            case 12:
                cariPasienDenganBoyerMoore();
                break;
            case 13:
                cout << "Keluar dari program..." << endl;
                return 0;
            default:
                cout << "Pilihan tidak valid. Coba lagi." << endl;
        }
    } while (pilihan != 13);  

    return 0;
}