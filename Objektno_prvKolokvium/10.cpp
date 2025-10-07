#include<iostream>
using namespace std;

struct Igrac{
    char ime[15];
    int nivo;
    int poeni;
};
struct KompjuterskaIgra{
    char imeIgra[20];
    Igrac igraci[30];
    int n;
};

void najdobarIgrac(KompjuterskaIgra *lista, int n){
    int indexmaxIgr=0;

    for(int i=0;i<n;i++){
        if(lista[i].n > lista[indexmaxIgr].n){
            indexmaxIgr=i;
        }
    }
    KompjuterskaIgra najpopularna = lista[indexmaxIgr];
    int indexmax=0;
    for(int i=0;i<najpopularna.n;i++){
        if(najpopularna.igraci[i].poeni > najpopularna.igraci[indexmax].poeni){
            indexmax=i;
        }
        else if(najpopularna.igraci[i].poeni == najpopularna.igraci[indexmax].poeni){
            if(najpopularna.igraci[i].nivo > najpopularna.igraci[indexmax].nivo){
                indexmax=i;
            }
        }
    }
    cout<<"Najdobar igrac e igracot so korisnicko ime "<<najpopularna.igraci[indexmax].ime;
    cout<<" koj ja igra igrata "<<najpopularna.imeIgra;


}

int main() {
    int n,m;
    char ime[20];
    cin>>n;
    KompjuterskaIgra poleigri[100];
    for (int i=0; i<n; i++) {
        KompjuterskaIgra nova;
        cin>>nova.imeIgra>>nova.n;
        Igrac pole[30];
        for (int j=0; j<nova.n; j++) {
            Igrac nov;
            cin>>nov.ime>>nov.nivo>>nov.poeni;
            nova.igraci[j]=nov;
        }
        poleigri[i]=nova;
    }

    najdobarIgrac(poleigri,n);
    return 0;
}
