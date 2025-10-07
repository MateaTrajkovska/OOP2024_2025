#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

enum tip{POP,RAP,ROK};

class Pesna{
private:
    char *ime;
    int minuti;
    tip kojtip;
public:
    Pesna(){
        ime= nullptr;
        minuti=0;
        kojtip=POP;
    }
    Pesna(const char *ime,int minuti, tip kojtip){
        this->ime= new char[strlen(ime)+1]; // dinamicka alokacija
        strcpy(this->ime,ime);
        this->minuti=minuti;
        this->kojtip=kojtip;
    }

    Pesna(const Pesna &p){
        ime= new char[strlen(p.ime)+1]; // copy const za din.
        strcpy(this->ime,p.ime);
        minuti=p.minuti;
        kojtip=p.kojtip;
    }

    Pesna &operator =(const Pesna &p){
        if(this!= &p){
            delete[] ime;
            ime= new char[strlen(p.ime)+1]; // operator = za din.
            strcpy(this->ime,p.ime);
            minuti=p.minuti;
            kojtip=p.kojtip;
        }
        return *this;
    }

    ~Pesna(){
        delete[]ime;  // dinamicka alokacija mora destructor
    }

    void pecati(){
        cout<<"\""<<ime<<"\"-"<<minuti<<"min"<<endl;
    }

    int getMinuti() const {
        return minuti;
    }

    tip getKojtip() const {
        return kojtip;
    }
};

class CD{
private:
    Pesna pesni[10];
    int brPesni;
    int vremetraenje;
public:
    CD(int vremetraenje){
        this->brPesni=0;
        this->vremetraenje=vremetraenje;
    }
    void dodadiPesna(Pesna p){
        int vkupnovreme=0;
        for(int i=0;i<brPesni;i++){
            vkupnovreme+=pesni[i].getMinuti();
        }

        if(brPesni<10 && vkupnovreme + p.getMinuti() <=vremetraenje){
            pesni[brPesni++]=p; // dodavame plus ushte edna pesna
        }
    }

    void pecatiPesniPoTip(tip t){
        for(int i=0;i<brPesni;i++){
            if(pesni[i].getKojtip()==t){
                pesni[i].pecati();
            }
        }
    }

    Pesna getPesna(int index)  {
        return pesni[index];
    }

    int getBroj() const {
        return brPesni;
    }

};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, minuti, kojtip;
    char ime[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
        p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<n; i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<omileno.getBroj(); i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

    return 0;
}