#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

// vashiot kod ovde


class Vozac{
protected:
    char ime[50];
    int vozrast;
    int trki;
    bool veteran;
public:
    Vozac(){}

    Vozac(const char *ime,int vozrast, int trki, bool vet ){
        strcpy(this->ime,ime);
        this->vozrast=vozrast;
        this->trki=trki;
        this->veteran=vet;
    }

    friend ostream & operator << (ostream &out, Vozac &v){
        out<<v.ime<<endl;
        out<<v.vozrast<<endl;
        out<<v.trki<<endl;
        if(v.veteran==true){
            out<<"VETERAN"<<endl;
        }
        return out;
    }
    virtual double zarabotuvackaPoTrka()=0;
    virtual double danok()=0;

    bool operator == (Vozac &v){
        return zarabotuvackaPoTrka()==v.zarabotuvackaPoTrka();
    }
};

class Avtomobilist : public Vozac{
private:
    float cena;
public:
    Avtomobilist(const char *ime,int vozrast, int trki, bool vet,float cena)
            : Vozac(ime,vozrast,trki,vet) {
        this->cena = cena;
    }

    virtual double zarabotuvackaPoTrka()override{
        return cena/5;
    }
    virtual double danok()override{
        if(trki>10){
            return zarabotuvackaPoTrka()*0.15;
        }
        else{
            return zarabotuvackaPoTrka()*0.10;
        }
    }
};

class Motociklist : public Vozac{
private:
    int motor;
public:
    Motociklist(const char *ime,int vozrast, int trki, bool vet,int motor)
            : Vozac(ime,vozrast,trki,vet){
        this->motor=motor;
    }

    virtual double zarabotuvackaPoTrka()override{
        return motor*20;
    }
    virtual double danok()override{
        if(veteran){
            return zarabotuvackaPoTrka()*0.25;
        }
        else{
            return zarabotuvackaPoTrka()*0.20;
        }
    }
};

int soIstaZarabotuvachka(Vozac **v,int n,Vozac *vz){
    int brVozaci=0;
    for(int i=0;i<n;i++){
        if(*v[i]==*vz){
            brVozaci++;
        }
    }
    return brVozaci;
}

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}