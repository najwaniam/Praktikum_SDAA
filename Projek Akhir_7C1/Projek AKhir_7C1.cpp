#include <iostream>
#include <cmath>
#include <stdexcept>
#include <unordered_set>
#include <limits>
#include <sstream>
using namespace std;


// Struktur untuk data history hewan
struct History
{
    string entry;
    History *next;
};


// Struktur untuk data hewan
struct Hewan
{
    string nama;
    string spesies;
    int umur;
    string status_kesehatan;
    Hewan *berikutnya;
    History *history; // Menyimpan sejarah hewan masuk ke habitat, diganti menjadi linked list
};

// Struktur untuk data habitat
struct Habitat
{
    int id_habitat; // Mengubah ID habitat menjadi integer
    string jenis;   // akuatik, terestrial, kandang burung, dll.
    int kapasitas;
     Hewan *daftar_hewan; // untuk menyimpan hewan dalam habitat
    Habitat *berikutnya;
};

void mergeSort(Hewan *arr[], int left, int right);
void quickSort(Hewan *arr[], int low, int high);
int partition(Hewan *arr[], int low, int high);

// Fungsi untuk menambah hewan
void tambahHewan(Hewan *&daftarHewan, string nama, string spesies, int umur, string kesehatan)
{
    Hewan *hewanBaru = new Hewan();
    hewanBaru->nama = nama;
    hewanBaru->spesies = spesies;
    hewanBaru->umur = umur;
    hewanBaru->status_kesehatan = kesehatan;
    hewanBaru->berikutnya = NULL;
    hewanBaru->history = NULL;

    if (daftarHewan == NULL)
    {
        daftarHewan = hewanBaru;
    }
    else
    {
        Hewan *temp = daftarHewan;
        while (temp->berikutnya != NULL)
        {
            temp = temp->berikutnya;
        }
        temp->berikutnya = hewanBaru;
    }
}

// Fungsi untuk menambah habitat
void tambahHabitat(Habitat *&daftarHabitat, int &idHabitatCounter, string jenis, int kapasitas)
{
    Habitat *habitatBaru = new Habitat();
    habitatBaru->id_habitat = idHabitatCounter++;
    habitatBaru->jenis = jenis;
    habitatBaru->kapasitas = kapasitas;
    habitatBaru->daftar_hewan = NULL;
    habitatBaru->berikutnya = NULL;

    if (daftarHabitat == NULL)
    {
        daftarHabitat = habitatBaru;
    }
    else
    {
        Habitat *temp = daftarHabitat;
        while (temp->berikutnya != NULL)
        {
            temp = temp->berikutnya;
        }
        temp->berikutnya = habitatBaru;
    }
    cout << "Habitat dengan ID " << habitatBaru->id_habitat << " telah ditambahkan." << endl;
}

// Fungsi untuk mencari hewan
Hewan *cariHewan(Hewan *daftarHewan, string nama)
{
    Hewan *temp = daftarHewan;
    while (temp != NULL)
    {
        if (temp->nama == nama)
        {
            cout << "Hewan ditemukan: " << endl;
            cout << "Nama: " << temp->nama << ", Spesies: " << temp->spesies
                 << ", Umur: " << temp->umur << ", Status Kesehatan: " << temp->status_kesehatan << endl;
            return temp;
        }
        temp = temp->berikutnya;
    }
    cout << "Hewan dengan nama " << nama << " tidak ditemukan." << endl;
    return NULL;
}

// Fungsi untuk menghapus hewan
void hapusHewan(Hewan *&daftarHewan, string nama)
{
    Hewan *temp = daftarHewan;
    Hewan *prev = NULL;

    while (temp != NULL)
    {
        if (temp->nama == nama)
        {
            if (prev == NULL)
            {
                daftarHewan = temp->berikutnya;
            }
            else
            {
                prev->berikutnya = temp->berikutnya;
            }
            delete temp;
            cout << "Hewan " << nama << " telah dihapus." << endl;
            return;
        }
        prev = temp;
        temp = temp->berikutnya;
    }
    cout << "Hewan dengan nama " << nama << " tidak ditemukan untuk dihapus." << endl;
}

// Fungsi untuk mengedit umur hewan
void editUmurHewan(Hewan *daftarHewan, string nama, int umurBaru)
{
    Hewan *hewan = cariHewan(daftarHewan, nama);
    if (hewan != NULL)
    {
        hewan->umur = umurBaru;
        cout << "Umur hewan " << hewan->nama << " telah diperbarui menjadi " << umurBaru << "." << endl;
    }
}

// Fungsi untuk memasukkan hewan ke habitat
void masukkanHewanKeHabitat(Hewan *daftarHewan, Habitat *&daftarHabitat, string namaHewan, int idHabitat)
{
    Hewan *hewan = cariHewan(daftarHewan, namaHewan);
    Habitat *temp = daftarHabitat;

    while (temp != NULL && temp->id_habitat != idHabitat)
    {
        temp = temp->berikutnya;
    }

    if (hewan == NULL)
    {
        cout << "Hewan dengan nama " << namaHewan << " tidak ditemukan." << endl;
        return;
    }
    if (temp == NULL)
    {
        cout << "Habitat dengan ID " << idHabitat << " tidak ditemukan." << endl;
        return;
    }
    if (temp->daftar_hewan == NULL) // Jika daftar hewan kosong
    {
        temp->daftar_hewan = hewan;
    }
    else
    {
        Hewan *last = temp->daftar_hewan;
        while (last->berikutnya != NULL)
        {
            last = last->berikutnya;
        }
        last->berikutnya = hewan;
    }
    hewan->history = new History{"Dimasukkan ke habitat ID " + to_string(idHabitat), nullptr};
    cout << "Hewan " << hewan->nama << " telah dimasukkan ke habitat " << temp->id_habitat << "." << endl;
}

// Fungsi untuk melihat sejarah hewan
void lihatHistoryHewan(Hewan *daftarHewan, string nama)
{
    Hewan *hewan = cariHewan(daftarHewan, nama);
    if (hewan != NULL)
    {
        cout << "Sejarah hewan " << hewan->nama << ":\n";
        History *history = hewan->history;
        while (history != NULL)
        {
            cout << history->entry << endl;
            history = history->next;
        }
    }
}


// Fungsi untuk melihat semua habitat
void lihatSemuaHabitat(Habitat *daftarHabitat)
{
    Habitat *temp = daftarHabitat;
    while (temp != NULL)
    {
        cout << "ID Habitat: " << temp->id_habitat << ", Jenis: " << temp->jenis
             << ", Kapasitas: " << temp->kapasitas << ", Jumlah Hewan: ";

        Hewan *hewanTemp = temp->daftar_hewan;
        int jumlahHewan = 0;
        while (hewanTemp != NULL)
        {
            jumlahHewan++;
            hewanTemp = hewanTemp->berikutnya;
        }
        cout << jumlahHewan << endl;

        // Menampilkan hewan yang ada di habitat
        cout << "Hewan di habitat ini: ";
        if (temp->daftar_hewan == NULL)
        {
            cout << "Tidak ada hewan." << endl;
        }
        else
        {
            hewanTemp = temp->daftar_hewan;
            while (hewanTemp != NULL)
            {
                cout << hewanTemp->nama << " (" << hewanTemp->spesies << "), ";
                hewanTemp = hewanTemp->berikutnya;
            }
            cout << endl;
        }

        temp = temp->berikutnya;
    }
}

void urutkanHewan(Hewan *daftarHewan, bool isMergeSort)
{
    // Hitung jumlah hewan
    int count = 0;
    Hewan *temp = daftarHewan;
    while (temp != NULL)
    {
        count++;
        temp = temp->berikutnya;
    }

    // Gunakan array statis atau array pointer
    Hewan **arr = new Hewan *[count];
    temp = daftarHewan;
    for (int i = 0; i < count; i++)
    {
        arr[i] = temp;
        temp = temp->berikutnya;
    }

    // Proses sorting
    if (isMergeSort)
    {
        mergeSort(arr, 0, count - 1);
    }
    else
    {
        quickSort(arr, 0, count - 1);
    }

    // Menampilkan hasil
    cout << "Hewan telah diurutkan:\n";
    for (int i = 0; i < count; i++)
    {
        cout << "Nama: " << arr[i]->nama << ", Spesies: " << arr[i]->spesies
             << ", Umur: " << arr[i]->umur << ", Status Kesehatan: " << arr[i]->status_kesehatan << endl;
    }

    delete[] arr;
}

// Fungsi pencarian Fibonacci
int fibonacciSearch(Hewan *arr[], int n, string x)
{
    int fibM2 = 0;            
    int fibM1 = 1;            
    int fibM = fibM1 + fibM2; 

    while (fibM < n)
    {
        fibM2 = fibM1;
        fibM1 = fibM;
        fibM = fibM1 + fibM2;
    }

    int offset = -1;

    while (fibM > 1)
    {
        int i = min(offset + fibM2, n - 1);

        if (arr[i]->nama < x)
        {
            fibM = fibM1;
            fibM1 = fibM2;
            fibM2 = fibM - fibM1;
            offset = i;
        }
        else if (arr[i]->nama > x)
        {
            fibM = fibM2;
            fibM1 = fibM1 - fibM2;
            fibM2 = fibM - fibM1;
        }
        else
        {
            return i;
        }
    }

    if (fibM1 && offset + 1 < n && arr[offset + 1]->nama == x)
    {
        return offset + 1;
    }

    return -1;
}

// Fungsi pencarian Jump
int jumpSearch(Hewan *arr[], int n, string x)
{
    int step = sqrt(n);
    int prev = 0;

    while (arr[min(step, n) - 1]->nama < x)
    {
        prev = step;
        step += sqrt(n);
        if (prev >= n)
            return -1;
    }

    while (arr[prev]->nama < x)
    {
        prev++;
        if (prev == min(step, n))
            return -1;
    }

    if (arr[prev]->nama == x)
        return prev;

    return -1;
}

int boyerMooreSearch(Hewan *daftarHewan, string x)
{
    Hewan *temp = daftarHewan;
    while (temp != NULL)
    {
        if (temp->nama == x)
        {
            cout << "Hewan ditemukan: " << temp->nama << ", Spesies: " << temp->spesies
                 << ", Umur: " << temp->umur << ", Status Kesehatan: " << temp->status_kesehatan << endl;
            return 1; // Ditemukan
        }
        temp = temp->berikutnya;
    }
    return -1; // Tidak ditemukan
}

// Fungsi untuk mengurutkan hewan menggunakan Merge Sort
void merge(Hewan *arr[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Hewan **L = new Hewan *[n1];
    Hewan **R = new Hewan *[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        if (L[i]->nama <= R[j]->nama)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(Hewan *arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void quickSort(Hewan *arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(Hewan *arr[], int low, int high)
{
    string pivot = arr[high]->nama;
    int i = (low - 1);

    for (int j = low; j < high; j++)
    {
        // Mengubah kondisi untuk descending
        if (arr[j]->nama > pivot) // Mengubah '<' menjadi '>'
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

int main(){
    Hewan *daftarHewan = NULL;
    Habitat *daftarHabitat = NULL;
    int idHabitatCounter = 1;
    int pilihan;

    while (true){
        cout << "\nSistem Manajemen Kebun Binatang\n";
        cout << "1. Tambah Hewan\n";
        cout << "2. Tambah Habitat\n";
        cout << "3. Masukkan Hewan ke Habitat\n";
        cout << "4. Lihat Semua Hewan\n";
        cout << "5. Lihat Semua Habitat\n";
        cout << "6. Cari Hewan\n";
        cout << "7. Edit Umur Hewan\n";
        cout << "8. Hapus Hewan\n";
        cout << "9. Lihat History Hewan\n";
        cout << "10. Urutkan Hewan\n";
        cout << "11. Keluar\n";
        cout << "Masukkan pilihan Anda: ";
        while (true) {
            cout << "Masukkan pilihan Anda: ";
            cin >> pilihan;
        
            if (cin.fail()) {  // Jika input bukan angka
                cin.clear();  // Membersihkan status error pada cin
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Mengabaikan input yang salah
                cout << "Inputan Anda salah. Harap masukkan angka yang valid.\n";
            } else {
                break;  // Jika input valid, keluar dari loop
            }
        }
        switch (pilihan){
            
        case 1: {
            string nama, spesies, kesehatan;
            int umur;
        
            // Input untuk nama hewan (String)
            cout << "Masukkan nama hewan: ";
            cin.ignore();  // Mengabaikan newline sebelumnya
            getline(cin, nama);  // Menggunakan getline untuk menerima input dengan spasi
            while (nama.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos) {
                cout << "Nama hewan hanya boleh berisi huruf dan spasi. Masukkan nama hewan yang valid: ";
                getline(cin, nama);
            }
        
            // Input untuk spesies hewan (String)
            cout << "Masukkan spesies: ";
            getline(cin, spesies);  // Menggunakan getline untuk menerima input dengan spasi
            while (spesies.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos) {
                cout << "Spesies hanya boleh berisi huruf dan spasi. Masukkan spesies yang valid: ";
                getline(cin, spesies);
            }
        
            // Input untuk umur (Integer)
            cout << "Masukkan umur: ";
            while (true) {
                cin >> umur;
                if (cin.fail()) {  // Jika input bukan angka
                    cin.clear();  // Membersihkan status error pada cin
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Mengabaikan input yang salah
                    cout << "Input tidak valid. Masukkan umur yang valid: ";
                } else {
                    break;  // Jika input valid, keluar dari loop
                }
            }
        
            // Input untuk status kesehatan (String)
            cout << "Masukkan status kesehatan: ";
            cin.ignore();  // Mengabaikan newline sebelumnya
            getline(cin, kesehatan);  // Menggunakan getline untuk menerima input dengan spasi
            while (kesehatan.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos) {
                cout << "Status kesehatan hanya boleh berisi huruf dan spasi. Masukkan status kesehatan yang valid: ";
                getline(cin, kesehatan);
            }
        
            tambahHewan(daftarHewan, nama, spesies, umur, kesehatan);
            break;
        }

        case 2: {
            string jenis;
            int kapasitas;
            cout << "Masukkan jenis habitat (akuatik/terestrial): ";
            cin >> jenis;
            // Validasi hanya menerima string untuk jenis habitat
            while (jenis.empty() || jenis.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos) {
                cout << "Jenis habitat hanya boleh berisi huruf dan tidak boleh kosong. Masukkan jenis habitat yang valid: ";
                cin >> jenis;
            }
            
            cout << "Masukkan kapasitas habitat: ";
            while (true) {
                cin >> kapasitas;
                if (cin.fail()) {  // Jika input bukan angka
                    cin.clear();  // Membersihkan status error pada cin
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Mengabaikan input yang salah
                    cout << "Input tidak valid. Masukkan kapasitas yang valid: ";
                } else {
                    break;  // Jika input valid, keluar dari loop
                }
            }
            tambahHabitat(daftarHabitat, idHabitatCounter, jenis, kapasitas);
            break;
        }
        
        case 3: {
            string namaHewan;
            int idHabitat;
            cout << "Masukkan nama hewan: ";
            cin >> namaHewan;
            // Validasi hanya menerima string untuk nama hewan
            while (namaHewan.empty() || namaHewan.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos) {
                cout << "Nama hewan hanya boleh berisi huruf dan tidak boleh kosong. Masukkan nama hewan yang valid: ";
                cin >> namaHewan;
            }
        
            cout << "Masukkan ID habitat: ";
            while (true) {
                cin >> idHabitat;
                if (cin.fail()) {  // Jika input bukan angka
                    cin.clear();  // Membersihkan status error pada cin
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Mengabaikan input yang salah
                    cout << "Input tidak valid. Masukkan ID habitat yang valid: ";
                } else {
                    break;  // Jika input valid, keluar dari loop
                }
            }
            masukkanHewanKeHabitat(daftarHewan, daftarHabitat, namaHewan, idHabitat);
            break;
        }

        case 4:{
            cout << "Daftar Semua Hewan:\n";
            Hewan *temp = daftarHewan;
            while (temp != NULL){
                cout << "Nama: " << temp->nama << ", Spesies: " << temp->spesies
                     << ", Umur: " << temp->umur << ", Status Kesehatan: " << temp->status_kesehatan << endl;
                temp = temp->berikutnya;
            }
            break;
        }
        case 5:{
            cout << "Daftar Semua Habitat:\n";
            lihatSemuaHabitat(daftarHabitat);
            break;
        }
        case 6: {
            int metode;
            string namaHewan;
            cout << "Masukkan nama hewan yang dicari: ";
            cin >> namaHewan;
            // Validasi hanya menerima string untuk nama hewan
            while (namaHewan.empty() || namaHewan.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos) {
                cout << "Nama hewan hanya boleh berisi huruf dan tidak boleh kosong. Masukkan nama hewan yang valid: ";
                cin >> namaHewan;
            }
        
            cout << "1. Pencarian Fibonacci\n";
            cout << "2. Pencarian Jump\n";
            cout << "3. Pencarian Boyer-Moore\n";
            cout << "Pilih metode pencarian: ";
            while (true) {
                cin >> metode;
                if (cin.fail()) {  // Jika input bukan angka
                    cin.clear();  // Membersihkan status error pada cin
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Mengabaikan input yang salah
                    cout << "Input tidak valid. Masukkan metode pencarian yang valid: ";
                } else {
                    break;  // Jika input valid, keluar dari loop
                }
            }
        
            Hewan *temp = daftarHewan;
            int count = 0;
            // Menghitung jumlah hewan
            while (temp != NULL) {
                count++;
                temp = temp->berikutnya;
            }
        
            // Membuat array pointer untuk menyimpan daftar hewan
            Hewan **arr = new Hewan*[count];
            temp = daftarHewan;
            int i = 0;
            while (temp != NULL) {
                arr[i] = temp;
                temp = temp->berikutnya;
                i++;
            }
        
            int index = -1;
            switch (metode) {
            case 1:
                index = fibonacciSearch(arr, count, namaHewan);
                break;
            case 2:
                index = jumpSearch(arr, count, namaHewan);
                break;
            case 3:
                index = boyerMooreSearch(daftarHewan, namaHewan);
                break;
            default:
                cout << "Metode pencarian tidak valid.\n";
            }
        
            if (index != -1) {
                cout << "Hewan ditemukan: " << arr[index]->nama << ", Spesies: " << arr[index]->spesies
                     << ", Umur: " << arr[index]->umur << ", Status Kesehatan: " << arr[index]->status_kesehatan << endl;
            }
            else {
                cout << "Hewan tidak ditemukan.\n";
            }
        
            // Menghapus array yang sudah dibuat
            delete[] arr;
            break;
        }
        
        case 7: {
            string namaHewan;
            int umurBaru;
            cout << "Masukkan nama hewan yang ingin diedit: ";
            cin >> namaHewan;
            // Validasi hanya menerima string untuk nama hewan
            while (namaHewan.empty() || namaHewan.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos) {
                cout << "Nama hewan hanya boleh berisi huruf dan tidak boleh kosong. Masukkan nama hewan yang valid: ";
                cin >> namaHewan;
            }
        
            cout << "Masukkan umur baru: ";
            while (true) {
                cin >> umurBaru;
                if (cin.fail()) {  // Jika input bukan angka
                    cin.clear();  // Membersihkan status error pada cin
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Mengabaikan input yang salah
                    cout << "Input tidak valid. Masukkan umur yang valid: ";
                } else {
                    break;  // Jika input valid, keluar dari loop
                }
            }
            editUmurHewan(daftarHewan, namaHewan, umurBaru);
            break;
        }
        
        case 8: {
            string namaHewan;
            cout << "Masukkan nama hewan yang ingin dihapus: ";
            cin >> namaHewan;
            // Validasi hanya menerima string untuk nama hewan
            while (namaHewan.empty() || namaHewan.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos) {
                cout << "Nama hewan hanya boleh berisi huruf dan tidak boleh kosong. Masukkan nama hewan yang valid: ";
                cin >> namaHewan;
            }
        
            hapusHewan(daftarHewan, namaHewan);
            break;
        }
        
        case 9: {
            string namaHewan;
            cout << "Masukkan nama hewan untuk melihat history: ";
            cin >> namaHewan;
            // Validasi hanya menerima string untuk nama hewan
            while (namaHewan.empty() || namaHewan.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos) {
                cout << "Nama hewan hanya boleh berisi huruf dan tidak boleh kosong. Masukkan nama hewan yang valid: ";
                cin >> namaHewan;
            }
        
            lihatHistoryHewan(daftarHewan, namaHewan);
            break;
        }
        case 10: {
            int metode;
            cout << "1. Merge Sort\n";
            cout << "2. Quick Sort\n";
            cout << "Pilih metode pengurutan: ";
            while (true) {
                cin >> metode;
                if (cin.fail()) {  // Jika input bukan angka
                    cin.clear();  // Membersihkan status error pada cin
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Mengabaikan input yang salah
                    cout << "Input tidak valid. Masukkan umur yang valid: ";
                } else {
                    break;  // Jika input valid, keluar dari loop
                }
            }
        
            // Menghitung jumlah hewan
            Hewan *temp = daftarHewan;
            int count = 0;
            while (temp != NULL) {
                count++;
                temp = temp->berikutnya;
            }
        
            // Membuat array pointer untuk menyimpan daftar hewan
            Hewan **arr = new Hewan*[count];
            temp = daftarHewan;
            int i = 0;
            while (temp != NULL) {
                arr[i] = temp;
                temp = temp->berikutnya;
                i++;
            }
        
            if (metode == 1) {
                mergeSort(arr, 0, count - 1);
            }
            else if (metode == 2) {
                quickSort(arr, 0, count - 1);
            }
            else {
                cout << "Metode pengurutan tidak valid.\n";
                break;
            }
        
            cout << "Hewan telah diurutkan:\n";
            for (int i = 0; i < count; i++) {
                cout << "Nama: " << arr[i]->nama << ", Spesies: " << arr[i]->spesies
                     << ", Umur: " << arr[i]->umur << ", Status Kesehatan: " << arr[i]->status_kesehatan << endl;
            }
        
            // Menghapus array yang sudah dibuat
            delete[] arr;
            break;
        }

        case 11:{
            cout << "Keluar dari program...\n";
            return 0; // Keluar dari program
        }
        default:{
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
            break;
        }
        }
    }while (pilihan != 11);
    return 0;
}