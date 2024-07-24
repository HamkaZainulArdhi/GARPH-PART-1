#include <iostream>
#include <string>
using namespace std;

struct Item {
    string nama;
    int jumlah;
    Item(string n = "", int j = 0) : nama(n), jumlah(j) {}
};

class InventoryStack {
private:
    struct StackNode {
        Item data;
        StackNode *next;
        StackNode(Item d, StackNode *n) : data(d), next(n) {}
    };
    StackNode *topNode = nullptr;

public:
    void push(const Item &item) {
        topNode = new StackNode(item, topNode);
    }

    void pop() {
        if (topNode) {
            StackNode *temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    Item top() {
        return topNode ? topNode->data : Item();
    }

    bool isEmpty() {
        return topNode == nullptr;
    }

    ~InventoryStack() {
        while (!isEmpty()) pop();
    }
};

class InventoryQueue {
private:
    struct QueueNode {
        Item data;
        QueueNode *next;
        QueueNode(Item d) : data(d), next(nullptr) {}
    };
    QueueNode *frontNode = nullptr, *rearNode = nullptr;

public:
    void enqueue(const Item &item) {
        QueueNode *newNode = new QueueNode(item);
        if (isEmpty()) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
    }

    void dequeue() {
        if (!isEmpty()) {
            QueueNode *temp = frontNode;
            frontNode = frontNode->next;
            delete temp;
            if (!frontNode) rearNode = nullptr;
        }
    }

    Item front() {
        return frontNode ? frontNode->data : Item();
    }

    bool isEmpty() {
        return frontNode == nullptr;
    }

    ~InventoryQueue() {
        while (!isEmpty()) dequeue();
    }
};

class InventoryArray {
private:
    static const int MAX_SIZE = 100;
    Item items[MAX_SIZE];
    int currentSize = 0;

public:
    void addItem(const Item &item) {
        if (currentSize < MAX_SIZE) items[currentSize++] = item;
    }

    Item getItem(string name) {
        for (int i = 0; i < currentSize; ++i) {
            if (items[i].nama == name) return items[i];
        }
        return Item();
    }

    int getSize() {
        return currentSize;
    }

    bool isEmpty() {
        return currentSize == 0;
    }

    void listItems() {
        if (isEmpty()) {
            cout << "Tidak ada barang dalam inventaris.\n";
        } else {
            cout << "\nDaftar Barang dalam Inventaris:\n";
            for (int i = 0; i < currentSize; ++i) {
                cout << "Nama Barang: " << items[i].nama << ", Jumlah: " << items[i].jumlah << "\n";
            }
        }
    }
};


void displayMenu() {
    cout <<endl<<endl;
    cout << "====================================================\n";
    cout << "        sistem manajemen inventaris kampus\n";
    cout << "====================================================\n\n";
    cout << "1. Meminjam barang\n";
    cout << "2. Mengembalikan barang\n";
    cout << "3. Laporan (laporan kehilangan, perpanjang peminjaman)\n";
    cout << "4. Lihat daftar barang\n";
    cout << "5. Informasi umum\n";
    cout << "6. Keluar\n";
    cout << "Pilihan Anda: ";
}

int main() {
    InventoryStack stack;
    InventoryQueue queue;
    InventoryArray array;
    string namaBarang, tglPengembalian;

    // menambahahkan barang ke daftar inventarsi
    array.addItem(Item("Laptop", 10));
    array.addItem(Item("Proyektor", 5));
    array.addItem(Item("Kabel HDMI", 20));
    array.addItem(Item("Meja", 15));
    array.addItem(Item("Kursi", 30));
    array.addItem(Item("Ruang Kelas Rek.301", 1));
    array.addItem(Item("Kamera", 5));
    string nama, instansi;
    cout << "====================================================\n";
    cout << "Selamat datang di sistem manajemen inventaris kampus\n";
    cout << "====================================================\n\n";
    cout << "Nama: ";
    cin >> nama;
    cout << "Instansi: ";
    cin >> instansi;

    int pilih;
    do {
        displayMenu();
        cin >> pilih;

        switch (pilih) {
        case 1: {
            cout << "Barang apa yang ingin dipinjam: ";
            cin >> namaBarang;

            bool available = false;
            for (int i = 0; i < array.getSize(); ++i) {
                if (array.getItem(namaBarang).nama == namaBarang) {
                    available = true;
                    break;
                }
            }

            if (available) {
                cout << "Barang tersedia\n";
                string tglPeminjaman;
                cout << "Tanggal peminjaman (YYYY-MM-DD): ";
                cin >> tglPeminjaman;
                cout << "Tanggal pengembalian (YYYY-MM-DD): ";
                cin >> tglPengembalian;

                cout << "---- Barang berhasil dipinjam ----\n";
                cout << "====================================================\n";
                cout << "Kebijakan dan ketentuan peminjaman barang:\n";
                cout << "1. Inventaris Jangan hilang\n";
                cout << "2. inventaris Jangan rusak\n";
                cout << "3. Harus dikembalikan tepat waktu\n";
                cout << "====================================================\n";
                cout << "Ketik y untuk verifikasi persetujuan: ";
                char verifikasi;
                cin >> verifikasi;
                if (verifikasi == 'y' || verifikasi == 'Y' ) {
                    cout << "Peminjaman berhasil...\n";
                } else {
                    cout << "Peminjaman dibatalkan !\n";
                }
            } else {
                cout << "Barang tidak tersedia\n";
            }
            break;
        }
        case 2: {
            string namaBarang;
            cout << "Nama barang yang ingin dikembalikan: ";
            cin >> namaBarang;

            bool found = false;
            for (int i = 0; i < array.getSize(); ++i) {
                if (array.getItem(namaBarang).nama == namaBarang) {
                    found = true;
                    break;
                }
            }

            if (found) {
                cout << "Barang berhasil dikembalikan\n";
            } else {
                cout << "Barang tidak ditemukan dalam inventaris\n";
            }
            break;
        }
        case 3: {
            int reportpilih;
            cout << "\n1. Laporan kehilangan\n";
            cout << "2. Perpanjang peminjaman\n";
            cout << "Pilihan Anda: ";
            cin >> reportpilih;

            if (reportpilih == 1) {
                string namaPeminjam, nim, namaBarang, tglKehilangan;
                cout << "Nama peminjam: ";
                cin >> namaPeminjam;
                cout << "NIM: ";
                cin >> nim;
                cout << "Nama barang: ";
                cin >> namaBarang;
                cout << "Tanggal kehilangan (YYYY-MM-DD): ";
                cin >> tglKehilangan;

                cout << "\nLaporan kehilangan berhasil dicatat.\n";
                cout << "Sanksi:\nMengganti barang yang sejenis dengan barang yang hilang, dan diharapkan untuk mengembalikan ke logistik\n";
            } else if (reportpilih == 2) {
                string namaBarang, tglPengembalianLama, tglPengembalianBaru;
                cout << "Nama barang: ";
                cin >> namaBarang;
                cout << "Tanggal pengembalian awal (YYYY-MM-DD): ";
                cin >> tglPengembalianLama;
                cout << "Perpanjangan pengembalian (YYYY-MM-DD): ";
                cin >> tglPengembalianBaru;

                cout << "\nPeminjaman diperpanjang hingga " << tglPengembalianBaru << "\n";
                 cout << "====================================================\n";
                cout << "Kebijakan dan ketentuan peminjaman barang:\n";
                cout << "1. Inventaris Jangan hilang\n";
                cout << "2. inventaris Jangan rusak\n";
                cout << "3. Harus dikembalikan tepat waktu\n";
                cout << "====================================================\n";
                cout << "Ketik y untuk verifikasi persetujuan: ";
                char verifikasi;
                cin >> verifikasi;
                if (verifikasi == 'y' ) {
                    cout << "Perpanjangan peminjaman berhasil\n";
                } else {
                    cout << "Perpanjangan peminjaman dibatalkan\n";
                }
            }
            break;
        }
        case 4: {
            array.listItems();
            break;
        }

        case 5 : {
            cout << namaBarang << " dipinjam oleh " << nama << " dari intansi " << instansi << " sampai "<< tglPengembalian <<endl;
            break;
        }
        case 6: {
            cout << "Terima kasih telah menggunakan sistem manajemen inventaris kampus.\n";
            break;
        }
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
            break;
        }
    } while (pilih != 6);

    return 0;
}
