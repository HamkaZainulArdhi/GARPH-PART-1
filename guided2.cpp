#include <iostream>
#include <string>

using namespace std;

int jumlahSimpul = 5;
string *dataSimpul;
int **dataBusur;
bool cekMatrik = false;
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

void hitungJarakTerdekat(){
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
    cout<<"Silahkan masukkan jumlah kota : ";
    cin>>jumlahSimpul;
    buatMatriks();
    tampilMatriks();
    cout<<endl<<endl;
    hitungJarakTerdekat();
    return 0;
}