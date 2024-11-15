#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <unordered_set>
using namespace std;

struct Hewan
{
    string nama;
    string spesies;
    int umur;
    string status_kesehatan;
    Hewan *berikutnya;
    vector<string> history;
};

struct Habitat
{
    int id_habitat;
    string jenis;  
    int kapasitas;
    vector<Hewan *> daftar_hewan; 
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
    if (temp->daftar_hewan.size() >= temp->kapasitas)
    {
        cout << "Habitat sudah penuh, tidak bisa memasukkan hewan." << endl;
        return;
    }

    temp->daftar_hewan.push_back(hewan);
    hewan->history.push_back("Dimasukkan ke habitat ID " + to_string(idHabitat));
    cout << "Hewan " << hewan->nama << " telah dimasukkan ke habitat " << temp->id_habitat << "." << endl;
}

// Fungsi untuk melihat sejarah hewan
void lihatHistoryHewan(Hewan *daftarHewan, string nama)
{
    Hewan *hewan = cariHewan(daftarHewan, nama);
    if (hewan != NULL)
    {
        cout << "Sejarah hewan " << hewan->nama << ":\n";
        for (const string &entry : hewan->history)
        {
            cout << entry << endl;
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
             << ", Kapasitas: " << temp->kapasitas << ", Jumlah Hewan: " << temp->daftar_hewan.size() << endl;

        cout << "Hewan di habitat ini: ";
        if (temp->daftar_hewan.empty())
        {
            cout << "Tidak ada hewan." << endl;
        }
        else
        {
            for (Hewan *hewan : temp->daftar_hewan)
            {
                cout << hewan->nama << " (" << hewan->spesies << "), ";
            }
            cout << endl;
        }

        temp = temp->berikutnya;
    }
}

void urutkanHewan(Hewan *daftarHewan, bool isMergeSort)
{
    vector<Hewan *> arr;
    Hewan *temp = daftarHewan;
    while (temp != NULL)
    {
        arr.push_back(temp);
        temp = temp->berikutnya;
    }

    if (isMergeSort)
    {
        mergeSort(arr.data(), 0, arr.size() - 1);
    }
    else
    {
        quickSort(arr.data(), 0, arr.size() - 1);
    }

    cout << "Hewan telah diurutkan:\n";
    for (Hewan *hewan : arr)
    {
        cout << "Nama: " << hewan->nama << ", Spesies: " << hewan->spesies
             << ", Umur: " << hewan->umur << ", Status Kesehatan: " << hewan->status_kesehatan << endl;
    }
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
            return 1; 
        }
        temp = temp->berikutnya;
    }
    return -1;
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
        if (arr[j]->nama > pivot) 
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

int main()
{
    Hewan *daftarHewan = NULL;
    Habitat *daftarHabitat = NULL;
    int idHabitatCounter = 1;
    int pilihan;

    while (true)
    {
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
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
        {
            string nama, spesies, kesehatan;
            int umur;
            cout << "Masukkan nama hewan: ";
            cin >> nama;
            cout << "Masukkan spesies: ";
            cin >> spesies;
            cout << "Masukkan umur: ";
            cin >> umur;
            cout << "Masukkan status kesehatan: ";
            cin >> kesehatan;
            tambahHewan(daftarHewan, nama, spesies, umur, kesehatan);
            break;
        }
        case 2:
        {
            string jenis;
            int kapasitas;
            cout << "Masukkan jenis habitat (akuatik/terestrial): ";
            cin >> jenis;
            cout << "Masukkan kapasitas habitat: ";
            cin >> kapasitas;
            tambahHabitat(daftarHabitat, idHabitatCounter, jenis, kapasitas);
            break;
        }
        case 3:
        {
            string namaHewan;
            int idHabitat;
            cout << "Masukkan nama hewan: ";
            cin >> namaHewan;
            cout << "Masukkan ID habitat: ";
            cin >> idHabitat;
            masukkanHewanKeHabitat(daftarHewan, daftarHabitat, namaHewan, idHabitat);
            break;
        }
        case 4:
        {
            cout << "Daftar Semua Hewan:\n";
            Hewan *temp = daftarHewan;
            while (temp != NULL)
            {
                cout << "Nama: " << temp->nama << ", Spesies: " << temp->spesies
                     << ", Umur: " << temp->umur << ", Status Kesehatan: " << temp->status_kesehatan << endl;
                temp = temp->berikutnya;
            }
            break;
        }
        case 5:
        {
            cout << "Daftar Semua Habitat:\n";
            lihatSemuaHabitat(daftarHabitat);
            break;
        }
        case 6:
        {
            string namaHewan;
            cout << "Masukkan nama hewan yang dicari: ";
            cin >> namaHewan;
            cout << "1. Pencarian Fibonacci\n";
            cout << "2. Pencarian Jump\n";
            cout << "3. Pencarian Boyer-Moore\n";
            cout << "Pilih metode pencarian: ";
            int metode;
            cin >> metode;

            Hewan *temp = daftarHewan;
            vector<Hewan *> arr;
            while (temp != NULL)
            {
                arr.push_back(temp);
                temp = temp->berikutnya;
            }

            int index = -1;
            switch (metode)
            {
            case 1:
                index = fibonacciSearch(arr.data(), arr.size(), namaHewan);
                break;
            case 2:
                index = jumpSearch(arr.data(), arr.size(), namaHewan);
                break;
            case 3:
                index = boyerMooreSearch(daftarHewan, namaHewan);
                break;
            default:
                cout << "Metode pencarian tidak valid.\n";
            }

            if (index != -1)
            {
                cout << "Hewan ditemukan: " << arr[index]->nama << ", Spesies: " << arr[index]->spesies
                     << ", Umur: " << arr[index]->umur << ", Status Kesehatan: " << arr[index]->status_kesehatan << endl;
            }
            else
            {
                cout << "Hewan tidak ditemukan.\n";
            }
            break;
        }
        case 7:
        {
            string namaHewan;
            int umurBaru;
            cout << "Masukkan nama hewan yang ingin diedit: ";
            cin >> namaHewan;
            cout << "Masukkan umur baru: ";
            cin >> umurBaru;
            editUmurHewan(daftarHewan, namaHewan, umurBaru);
            break;
        }
        case 8:
        {
            string namaHewan;
            cout << "Masukkan nama hewan yang ingin dihapus: ";
            cin >> namaHewan;
            hapusHewan(daftarHewan, namaHewan);
            break;
        }
        case 9:
        {
            string namaHewan;
            cout << "Masukkan nama hewan untuk melihat history: ";
            cin >> namaHewan;
            lihatHistoryHewan(daftarHewan, namaHewan);
            break;
        }
        case 10:
        {
            cout << "1. Merge Sort\n";
            cout << "2. Quick Sort\n";
            cout << "Pilih metode pengurutan: ";
            int metode;
            cin >> metode;

            Hewan *temp = daftarHewan;
            vector<Hewan *> arr;
            while (temp != NULL)
            {
                arr.push_back(temp);
                temp = temp->berikutnya;
            }

            if (metode == 1)
            {
                mergeSort(arr.data(), 0, arr.size() - 1);
            }
            else if (metode == 2)
            {
                quickSort(arr.data(), 0, arr.size() - 1);
            }
            else
            {
                cout << "Metode pengurutan tidak valid.\n";
                break;
            }

            cout << "Hewan telah diurutkan:\n";
            for (Hewan *hewan : arr)
            {
                cout << "Nama: " << hewan->nama << ", Spesies: " << hewan->spesies
                     << ", Umur: " << hewan->umur << ", Status Kesehatan: " << hewan->status_kesehatan << endl;
            }
            break;
        }
        case 11:
        {
            cout << "Keluar dari program,Terima Kasih.\n";
            return 0; 
        }
        default:
        {
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
            break;
        }
        }
    }

    return 0;
}
