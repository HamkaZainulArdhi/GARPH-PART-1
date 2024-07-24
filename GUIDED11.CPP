#include <iostream>  // Library untuk operasi input-output
#include <string>    // Library untuk operasi string

using namespace std;  // Menggunakan namespace standar agar tidak perlu menulis std:: di depan fungsi standar

int jumlahSimpul = 5;  // Variabel untuk menyimpan jumlah simpul (vertex), diinisialisasi dengan 5
string *dataSimpul;    // Pointer untuk mengalokasikan array nama simpul secara dinamis
int **dataBusur;       // Pointer untuk mengalokasikan array 2D untuk bobot busur secara dinamis
bool cekMatrik = false;  // Boolean untuk memeriksa apakah matriks telah dibuat
int indeksPosisi, simpulSaatIni, simpulAsal, simpulTujuan, jarakSaatIni, jarakLama, jarakBaru; // Variabel untuk operasi algoritma
int dikunjungi = 1;  // Konstanta untuk mewakili simpul yang telah dikunjungi
int belumDikunjungi = 0;  // Konstanta untuk mewakili simpul yang belum dikunjungi
int *jarakDiketahui;  // Pointer untuk mengalokasikan array jarak terdekat yang diketahui secara dinamis
int *kunjungan;  // Pointer untuk mengalokasikan array status kunjungan secara dinamis

// Fungsi untuk membuat matriks bobot busur antar simpul
void buatMatriks(){
    dataSimpul = new string[jumlahSimpul];  // Alokasi array nama simpul
    dataBusur = new int*[jumlahSimpul];     // Alokasi array pointer untuk baris-baris dalam matriks
    dataBusur[0] = new int[jumlahSimpul * jumlahSimpul];  // Alokasi semua elemen matriks dalam satu baris memori besar

    for(int i = 1; i < jumlahSimpul; i++){
        dataBusur[i] = dataBusur[i-1] + jumlahSimpul;  // Mengatur pointer untuk setiap baris
    }

    cout << "Silahkan masukkan nama simpul " << endl;
    for(int i = 0; i < jumlahSimpul; i++){
        cout << "Kota " << i+1 << " : ";
        cin >> dataSimpul[i];  // Input nama simpul dari pengguna
    }

    cout << "Silahkan masukkan bobot antar simpul " << endl;
    for(int baris = 0; baris < jumlahSimpul; baris++){
        for(int kolom = 0; kolom < jumlahSimpul; kolom++){
            cout << dataSimpul[baris] << " --> " << dataSimpul[kolom] << " : ";
            cin >> dataBusur[baris][kolom];  // Input bobot busur antara simpul dari pengguna
        }
    }
    cekMatrik = true;  // Menandai bahwa matriks telah dibuat
}

// Fungsi untuk menghitung jarak terdekat menggunakan algoritma Dijkstra
void hitungJarakTerdekat(){
    if(cekMatrik){  // Mengecek apakah matriks telah dibuat
        jarakDiketahui = new int[jumlahSimpul];  // Alokasi array untuk menyimpan jarak terdekat yang diketahui
        kunjungan = new int[jumlahSimpul];  // Alokasi array untuk status kunjungan simpul
        for(int i = 0; i < jumlahSimpul; i++){
            jarakDiketahui[i] = 999; // Nilai 999 dianggap sebagai infinity atau tak hingga
            kunjungan[i] = belumDikunjungi;  // Semua simpul awalnya belum dikunjungi
        }

        kunjungan[simpulAsal] = dikunjungi;  // Tandai simpul asal sebagai dikunjungi
        jarakDiketahui[simpulAsal] = 0;  // Jarak dari simpul asal ke dirinya sendiri adalah 0
        simpulSaatIni = simpulAsal;  // Inisialisasi simpul saat ini dengan simpul asal

        // Algoritma Dijkstra untuk mencari jalur terpendek
        while(simpulSaatIni != simpulTujuan){
            jarakLama = 999;  // Inisialisasi jarak terdekat sementara sebagai infinity
            jarakSaatIni = jarakDiketahui[simpulSaatIni];  // Dapatkan jarak terdekat dari simpul saat ini
            for(int i = 0; i < jumlahSimpul; i++){
                if(kunjungan[i] == belumDikunjungi){  // Jika simpul belum dikunjungi
                    jarakBaru = jarakSaatIni + dataBusur[simpulSaatIni][i];  // Hitung jarak baru
                    if(jarakBaru < jarakDiketahui[i]){
                        jarakDiketahui[i] = jarakBaru;  // Perbarui jarak terdekat jika jarak baru lebih kecil
                    }
                    if(jarakDiketahui[i] < jarakLama){
                        jarakLama = jarakDiketahui[i];  // Perbarui jarak terdekat sementara
                        indeksPosisi = i;  // Simpan indeks posisi simpul dengan jarak terdekat baru
                    }
                }
            }
            simpulSaatIni = indeksPosisi;  // Pindah ke simpul berikutnya dengan jarak terdekat
            kunjungan[simpulSaatIni] = dikunjungi;  // Tandai simpul saat ini sebagai dikunjungi
        }
        cout << "Jarak terdekat dari " << dataSimpul[simpulAsal] << " ke " << dataSimpul[simpulTujuan] << " adalah " << jarakDiketahui[simpulTujuan] << endl;
        delete[] jarakDiketahui;  // Dealokasi memori array jarak terdekat
        delete[] kunjungan;  // Dealokasi memori array kunjungan
    }
}

// Fungsi untuk menampilkan matriks bobot busur
void tampilMatriks(){
    if(cekMatrik){  // Mengecek apakah matriks telah dibuat
        for(int i = 0; i < jumlahSimpul; i++){
            cout << dataSimpul[i] << " ";  // Tampilkan nama simpul
        }
        cout << endl;
        for(int baris = 0; baris < jumlahSimpul; baris++){
            for(int kolom = 0; kolom < jumlahSimpul; kolom++){
                cout << dataBusur[baris][kolom] << " ";  // Tampilkan bobot busur antar simpul
            }
            cout << endl;
        }
    } else {
        cout << "Tidak ada matriks" << endl;  // Pesan jika matriks belum dibuat
    }
}

int main(){
    char keluar;  // Variabel untuk menyimpan pilihan pengguna apakah akan keluar atau tidak
    cout << "Silahkan masukkan jumlah kota (angka) : ";
    cin >> jumlahSimpul;  // Input jumlah simpul dari pengguna
    buatMatriks();  // Panggil fungsi untuk membuat matriks
    tampilMatriks();  // Panggil fungsi untuk menampilkan matriks

    do{
        cout << "Silahkan masukkan simpul asal (0 - " << jumlahSimpul-1 << ") : ";
        cin >> simpulAsal;  // Input simpul asal dari pengguna
        cout << "Silahkan masukkan simpul tujuan (0 - " << jumlahSimpul-1 << ") : ";
        cin >> simpulTujuan;  // Input simpul tujuan dari pengguna
        hitungJarakTerdekat();  // Panggil fungsi untuk menghitung jarak terdekat

        cout << endl << endl;
        cout << "Keluar (y/t) ? : ";
        cin >> keluar;  // Input apakah akan keluar atau tidak

        if(tolower(keluar) != 'y'){  // Jika tidak memilih keluar
            system("cls");  // Bersihkan layar (fungsi ini hanya berfungsi di Windows)
        }
    } while(tolower(keluar) != 'y');  // Ulangi sampai pengguna memilih keluar

    return 0;  // Akhiri program
}
