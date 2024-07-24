#include <iostream>
#include <string>

using namespace std;

int jumlahSimpul = 5;
string *dataSimpul;
int **dataBusur;
bool cekMatrik = false;
int indeksPosisi, simpulSaatIni, simpulAsal, simpulTujuan, jarakSaatIni, jarakLama, jarakBaru;
int dikunjungi = 1;
int belumDikunjungi = 0;
int *jarakDiketahui;
int *kunjungan;
int **jalurTerdekat;

void buatMatriks(){
    dataSimpul = new string[jumlahSimpul];
    dataBusur = new int*[jumlahSimpul];
    dataBusur[0] = new int[jumlahSimpul * jumlahSimpul];

    for(int i = 1; i < jumlahSimpul; i++){
        dataBusur[i] = dataBusur[i-1] + jumlahSimpul;
    }

    cout<<"Silahkan masukkan nama simpul "<<endl;
    for(int i = 0; i < jumlahSimpul; i++){
        cout<<"Kota "<<i+1<<" : ";
        cin>>dataSimpul[i];
    }

    cout<<"Silahkan masukkan bobot antar simpul "<<endl;
    for(int baris = 0; baris < jumlahSimpul; baris++){
        for(int kolom = 0; kolom < jumlahSimpul; kolom++){
            cout<<dataSimpul[baris]<<" --> "<<dataSimpul[kolom]<<" : ";
            cin>> dataBusur[baris][kolom];
        }
    }
    cekMatrik = true;
}

void hitungJarakTerdekatdjistra(){
    if(cekMatrik){
        jarakDiketahui = new int[jumlahSimpul];
        kunjungan = new int[jumlahSimpul];
        for(int i = 0; i < jumlahSimpul; i++){
            jarakDiketahui[i] = 999; //Nilai 999 dianggap sebagai infinity atau tak hingga
            kunjungan[i] = belumDikunjungi;
        }

        kunjungan[simpulAsal] = dikunjungi;
        jarakDiketahui[simpulAsal] = 0;
        simpulSaatIni = simpulAsal;

        while(simpulSaatIni != simpulTujuan){
            jarakLama = 999;
            jarakSaatIni = jarakDiketahui[simpulSaatIni];
            for(int i = 0; i < jumlahSimpul; i++){
                if(kunjungan[i] == belumDikunjungi){
                    jarakBaru = jarakSaatIni + dataBusur[simpulSaatIni][i];
                    if(jarakBaru < jarakDiketahui[i]){
                        jarakDiketahui[i] = jarakBaru;
                    }
                    if(jarakDiketahui[i] < jarakLama){
                        jarakLama = jarakDiketahui[i];
                        indeksPosisi = i;
                    }
                }
            }
            simpulSaatIni = indeksPosisi;
            kunjungan[simpulSaatIni] = dikunjungi;
        }
        cout<<"Jarak terdekat dari "<<simpulAsal<<" ke "<<simpulTujuan<<" adalah "<<jarakDiketahui[simpulTujuan]<<endl;
        delete jarakDiketahui;
        delete kunjungan;
    }
}

void hitungJarakTerdekatwarshall(){
    if(cekMatrik){
        //Membuat matrik yang sama dengan matrik dataBusur
        jalurTerdekat = new int*[jumlahSimpul];
        jalurTerdekat[0] = new int[jumlahSimpul * jumlahSimpul];
        for(int i = 1; i < jumlahSimpul; i++){
            jalurTerdekat[i] = jalurTerdekat[i-1] + jumlahSimpul;
        }

        //Duplikasi isi matrik dataBusur kedalam matrik jalurTerdekat
        for(int baris = 0; baris < jumlahSimpul; baris++){
            for(int kolom = 0; kolom < jumlahSimpul; kolom++){
                jalurTerdekat[baris][kolom] = dataBusur[baris][kolom];
            }
        }

        //Pencarian jalur terdekat dengan algoritma Flyod Warshall
        for(int k = 0; k < jumlahSimpul; k++){
            for(int baris = 0; baris < jumlahSimpul; baris++){
                for(int kolom = 0; kolom < jumlahSimpul; kolom++){
                    if(jalurTerdekat[baris][k] + jalurTerdekat[k][kolom] < jalurTerdekat[baris][kolom]){
                        jalurTerdekat[baris][kolom] = jalurTerdekat[baris][k] + jalurTerdekat[k][kolom];
                    }
                }
            }
        }

        //Tampilkan hasil
        cout<<" --- ";
        for(int kolom = 0; kolom < jumlahSimpul; kolom++){
            cout<<dataSimpul[kolom]<<" ";
        }
        cout<<endl;

        for(int baris = 0; baris < jumlahSimpul; baris++){
            cout<<dataSimpul[baris]<<" | ";
            for(int kolom = 0; kolom < jumlahSimpul; kolom++){
                cout<<jalurTerdekat[baris][kolom]<<" ";
            }
            cout<<endl;
        }
    }
}


void tampilMatriks(){
    if(cekMatrik){
        for(int i = 0; i < jumlahSimpul; i++){
            cout<<dataSimpul[i]<<" ";
        }
        cout<<endl;
        for(int baris = 0; baris < jumlahSimpul; baris++){
            for(int kolom = 0; kolom < jumlahSimpul; kolom++){
                cout<<dataBusur[baris][kolom]<<" ";
            }
            cout<<endl;
        }
    }else{
        cout<<"Tidak ada matriks"<<endl;
    }
}

int main(){
    char keluar;
    cout<<"Silahkan masukkan jumlah kota (angka) : ";
    cin>>jumlahSimpul;
    buatMatriks();
    tampilMatriks();
    cout<<endl<<endl;
    cout<<"ini adalah algoritma flody-warshall" << endl;
    hitungJarakTerdekatwarshall();
    cout<<endl;

    do{
        cout<<"ini adalah algoritma djistra" << endl;
        cout<<"Silahkan masukkan simpul asal (0 - "<<jumlahSimpul-1<<") : ";
        cin>>simpulAsal;
        cout<<"Silahkan masukkan simpul tujuan (0 - "<<jumlahSimpul-1<<") : ";
        cin>>simpulTujuan;
        hitungJarakTerdekatdjistra();
       

        cout<<endl<<endl;
        cout<<"Keluar (y/t) ? : ";
        cin>>keluar;

        if(tolower(keluar) != 'y'){
            system("cls");
        }
    }while(tolower(keluar) != 'y');

    return 0;
}