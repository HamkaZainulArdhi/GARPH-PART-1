#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

// Struct untuk barang
struct Barang {
    string nama;
    bool tersedia;
};

// Struct untuk peminjaman
struct Peminjaman {
    string nama_barang;
    string nama_peminjam;
    string instansi;
    string tanggal_pinjam;
    string tanggal_kembali;
    string tanggal_dikembalikan; // Tambahkan field ini
    string password;

    bool operator==(const Peminjaman& other) const {
        return nama_barang == other.nama_barang &&
               nama_peminjam == other.nama_peminjam &&
               instansi == other.instansi &&
               tanggal_pinjam == other.tanggal_pinjam &&
               tanggal_kembali == other.tanggal_kembali &&
               tanggal_dikembalikan == other.tanggal_dikembalikan &&
               password == other.password;
    }
};

// Deklarasi fungsi-fungsi
void menu();
void main_menu();
void login();
void register_user();
void display_barang();
void pinjam_barang();
void kembalikan_barang();
void lihat_log();
void keluar();
string waktu_sekarang(); // Deklarasi fungsi waktu_sekarang

// Map untuk log aktivitas
map<string, string> log_aktivitas;

// Vector untuk daftar barang
vector<Barang> daftar_barang = {
    {"meja", true},
    {"kursi", true},
    {"proyektor", true}
};

// Vector untuk antrian peminjaman
vector<Peminjaman> antrian_peminjaman;

// Pengguna saat ini
Peminjaman pengguna_saat_ini;

// Fungsi untuk menambahkan pengguna ke map
map<string, Peminjaman> database_pengguna;

void tambah_pengguna(string username, string password, string nama, string instansi) {
    Peminjaman user;
    user.nama_peminjam = nama;
    user.password = password;
    user.instansi = instansi;

    database_pengguna[username] = user;

    log_aktivitas[waktu_sekarang()] = "Tambah pengguna: " + username;
}

Peminjaman* cari_pengguna(string username) {
    auto it = database_pengguna.find(username);
    if (it != database_pengguna.end()) {
        return &it->second;
    } else {
        return nullptr;
    }
}

// Fungsi untuk menambahkan log aktivitas
void tambah_log(string aktivitas) {
    log_aktivitas[waktu_sekarang()] = aktivitas;
}

// Fungsi untuk mencari barang
Barang* find_barang(const string& nama_barang) {
    auto it = find_if(daftar_barang.begin(), daftar_barang.end(), [&nama_barang](const Barang& barang) {
        return barang.nama == nama_barang;
    });
    if (it != daftar_barang.end()) {
        return &(*it);
    } else {
        return nullptr;
    }
}

// Fungsi untuk mencari peminjaman
Peminjaman* find_peminjaman(const string& nama_barang) {
    auto it = find_if(antrian_peminjaman.begin(), antrian_peminjaman.end(), [&nama_barang](const Peminjaman& peminjaman) {
        return peminjaman.nama_barang == nama_barang;
    });
    if (it != antrian_peminjaman.end()) {
        return &(*it);
    } else {
        return nullptr;
    }
}

// Fungsi untuk mendapatkan waktu sekarang sebagai string
string waktu_sekarang() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-"
       << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-"
       << setfill('0') << setw(2) << ltm->tm_mday << " "
       << setfill('0') << setw(2) << ltm->tm_hour << ":"
       << setfill('0') << setw(2) << ltm->tm_min << ":"
       << setfill('0') << setw(2) << ltm->tm_sec;
    return ss.str();
}

// Fungsi untuk login
void login() {
    string username;
    string password;

    cout << "==============================================" << endl;
    cout << "            Sistem Manajemen Inventaris       " << endl;
    cout << "==============================================" << endl;
    cout << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    Peminjaman* user = cari_pengguna(username);

    if (user != nullptr && user->password == password) {
        pengguna_saat_ini = *user;
        tambah_log("Login oleh " + username);
        menu();
    } else {
        cout << "Username atau password salah!" << endl;
        main_menu();
    }
}

// Fungsi untuk registrasi
void register_user() {
    string username, password, nama, instansi;

    cout << "==============================================" << endl;
    cout << "            Sistem Manajemen Inventaris       " << endl;
    cout << "==============================================" << endl;
    cout << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    cout << "Nama: ";
    cin >> nama;
    cout << "Instansi: ";
    cin >> instansi;

    // Tambahkan pengguna ke database (misalnya MySQL)
    tambah_pengguna(username, password, nama, instansi);
    tambah_log("Registrasi pengguna baru: " + username);
    cout << "Registrasi berhasil! Silakan login." << endl;
    main_menu();
}

// Fungsi untuk menampilkan daftar barang
void display_barang() {
    cout << "==============================================" << endl;
    cout << "            Daftar Barang Tersedia           " << endl;
    cout << "==============================================" << endl;
    cout << endl;
    cout << setw(15) << "Nama Barang" << setw(20) << "Tersedia" << endl;
    cout << "---------------------------------------------" << endl;
    for (const Barang& barang : daftar_barang) {
        cout << setw(15) << barang.nama << setw(20) << (barang.tersedia ? "Ya" : "Tidak") << endl;
    }
    menu();
}

// Fungsi untuk meminjam barang
void pinjam_barang() {
    string nama_barang;

    cout << "==============================================" << endl;
    cout << "            Formulir Peminjaman Barang       " << endl;
    cout << "==============================================" << endl;
    cout << endl;
    cout << "Nama Barang: ";
    cin >> nama_barang;

    // Cari barang dalam daftar barang
    Barang* barang = find_barang(nama_barang);

    if (barang != nullptr && barang->tersedia) {
        barang->tersedia = false;
        Peminjaman peminjaman;
        peminjaman.nama_barang = nama_barang;
        peminjaman.nama_peminjam = pengguna_saat_ini.nama_peminjam;
        peminjaman.instansi = pengguna_saat_ini.instansi;

        // Input tanggal pinjam dan tanggal kembali
        cout << "Tanggal Pinjam (YYYY-MM-DD): ";
        cin >> peminjaman.tanggal_pinjam;
        cout << "Tanggal Kembali (YYYY-MM-DD): ";
        cin >> peminjaman.tanggal_kembali;

        antrian_peminjaman.push_back(peminjaman);
        tambah_log("Peminjaman barang: " + nama_barang + " oleh " + pengguna_saat_ini.nama_peminjam);
        cout << "Peminjaman barang berhasil!" << endl;
    } else {
        cout << "Barang tidak tersedia atau tidak ditemukan." << endl;
    }

    menu();
}

// Fungsi untuk mengembalikan barang
void kembalikan_barang() {
    string nama_barang;

    cout << "==============================================" << endl;
    cout << "            Formulir Pengembalian Barang     " << endl;
    cout << "==============================================" << endl;
    cout << endl;
    cout << "Nama Barang: ";
    cin >> nama_barang;

    // Cari barang dalam daftar barang dan antrian peminjaman
    Barang* barang = find_barang(nama_barang);
    Peminjaman* peminjaman = find_peminjaman(nama_barang);

    if (barang != nullptr && peminjaman != nullptr) {
        barang->tersedia = true;

        // Input tanggal dikembalikan
        cout << "Tanggal Dikembalikan (YYYY-MM-DD): ";
        cin >> peminjaman->tanggal_dikembalikan;

        // Cek apakah tanggal dikembalikan melebihi tanggal kembali yang dijadwalkan
        if (peminjaman->tanggal_dikembalikan > peminjaman->tanggal_kembali) {
            cout << "Anda telat mengembalikan barang." << endl;
        }

        antrian_peminjaman.erase(remove(antrian_peminjaman.begin(), antrian_peminjaman.end(), *peminjaman), antrian_peminjaman.end());
        tambah_log("Pengembalian barang: " + nama_barang + " oleh " + pengguna_saat_ini.nama_peminjam);
        cout << "Pengembalian barang berhasil!" << endl;
    } else {
        cout << "Barang tidak dipinjam atau tidak ditemukan." << endl;
    }

    menu();
}

// Fungsi untuk melihat log aktivitas
// Fungsi untuk melihat log aktivitas
void lihat_log() {
  cout << "==============================================" << endl;
  cout << "            Log Aktivitas Sistem              " << endl;
  cout << "==============================================" << endl;
  cout << endl;

  for (const auto& [timestamp, aktivitas] : log_aktivitas) {
    cout << timestamp << " - " << aktivitas << endl;
  }
    menu();
}

// Fungsi untuk keluar
void keluar() {
    char pilihan;
    cout << "Apakah Anda yakin ingin keluar? (y/n): ";
    cin >> pilihan;

    if (pilihan == 'y' || pilihan == 'Y') {
        cout << "Terima kasih telah menggunakan sistem manajemen inventaris!" << endl;
        exit(0);
    } else {
        menu();
    }
}

// Fungsi menu utama
void menu() {
    cout << "==============================================" << endl;
    cout << "            Menu Utama Sistem               " << endl;
    cout << "==============================================" << endl;
    cout << endl;
    cout << "1. Lihat Daftar Barang" << endl;
    cout << "2. Pinjam Barang" << endl;
    cout << "3. Kembalikan Barang" << endl;
    cout << "4. Lihat Log Aktivitas" << endl;
    cout << "5. Keluar" << endl;
    cout << endl;
    cout << "Pilihan Anda: ";

    int pilihan;
    cin >> pilihan;

    switch (pilihan) {
        case 1:
            display_barang();
            break;
        case 2:
            pinjam_barang();
            break;
        case 3:
            kembalikan_barang();
            break;
        case 4:
            lihat_log();
            break;
        case 5:
            keluar();
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            menu();
            break;
    }
}

void main_menu() {
    cout << "==============================================" << endl;
    cout << "            Sistem Manajemen Inventaris       " << endl;
    cout << "==============================================" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "Pilihan Anda: ";
    
    int pilihan;
    cin >> pilihan;

    switch (pilihan) {
        case 1:
            login();
            break;
        case 2:
            register_user();
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            main_menu();
            break;
    }
}

int main() {
    main_menu();
}
