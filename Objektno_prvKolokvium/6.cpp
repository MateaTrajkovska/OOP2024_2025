//
// Created by Matea Trajkovska on 20.3.25.
//
#include<iostream>
#include <cstring>
using namespace std;

struct Voz{
    char relacija[50];
    double kilometri;
    int brPatnici;
};

struct ZeleznickaStanica{
    char grad[25];
    Voz vozovi[30];
    int brVozovi;
};

void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad){
    int minKm=1000, minI = 0, minJ = 0;
    for (int i=0; i<n; i++)
        if(!strcmp(zs[i].grad, grad))
            for (int j=0; j<zs[i].brVozovi; j++)
                if (zs[i].vozovi[j].kilometri <= minKm){
                    minKm=zs[i].vozovi[j].kilometri;
                    minI = i;
                    minJ = j;
                }

    cout<<"Najkratka relacija: ";
    cout<<zs[minI].vozovi[minJ].relacija;
    cout<<" (";
    cout<<minKm;
    cout<<" km)";
}

int main(){

    int n;
    cin>>n; //se cita brojot na zelezlnichki stanici

    ZeleznickaStanica zStanica[100];
    for (int i=0;i<n;i++){
        //se citaat infomracii za n zelezlnichkite stanici i se zacuvuvaat vo poleto zStanica
        cin>>zStanica[i].grad;
        cin>>zStanica[i].brVozovi;

        for(int j=0;j < zStanica[i].brVozovi;j++){
            cin >> zStanica[i].vozovi[j].relacija;
            cin >> zStanica[i].vozovi[j].kilometri;
            cin >> zStanica[i].vozovi[j].brPatnici;
        }
    }

    char grad[25];
    cin>>grad;

    najkratkaRelacija(zStanica,n,grad);
    return 0;
}
