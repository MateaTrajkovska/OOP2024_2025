//
// Created by Matea Trajkovska on 21.3.25.
//
#include<iostream>
#include <cstring>
using namespace std;
// vashiot kod ovde

class Ucesnik{
private:
    char *ime;
    bool pol;
    int vozrast;
public:
    Ucesnik (){}
    Ucesnik(char *ime,bool pol, int vozrast){ //default
        this->ime = new char[strlen(ime)+1]; //allocate memory
        strcpy(this->ime,ime); //copy the char
        this->pol=pol;
        this->vozrast = vozrast;
    }
    ~Ucesnik(){ //destructor
        delete[]ime;
    }
    Ucesnik(const Ucesnik & u){ // copy const
        this->ime = new char[strlen(u.ime)+1]; //allocate memory
        strcpy(this->ime,u.ime); //copy the char
        this->pol=u.pol;
        this->vozrast = u.vozrast;
    }
    Ucesnik & operator = (const Ucesnik & u){ //operator =
        if(this!=&u){
            delete[]ime;
            this->ime = new char[strlen(u.ime)+1]; //allocate memory
            strcpy(this->ime,u.ime); //copy the char
            this->pol=u.pol;
            this->vozrast = u.vozrast;
        }
        return *this;
    }

    friend bool operator > (Ucesnik &u1, Ucesnik &u2){
        return u1.vozrast > u2.vozrast;
    }

    friend ostream & operator <<(ostream &out , Ucesnik &u){
        out<<u.ime<<endl;
        out<<(u.pol ? "mashki" : "zhenski") <<endl;
        out<<u.vozrast<<endl;
        return out;
    }

    int getVozrast() const {
        return vozrast;
    }
};

class Maraton{
private:
    char lokacija[100];
    Ucesnik *niza;
    int n;
public:
    Maraton(){
        n=0;
        niza= nullptr;
    }
    Maraton(char *lokacija){
        strcpy(this->lokacija,lokacija);
        n=0;
        niza= nullptr;
    }
    ~Maraton(){
        delete[]niza;
    }

    Maraton & operator += (Ucesnik &u){
        Ucesnik *tmp= new Ucesnik [n+1];
        for(int i=0;i<n;i++){
            tmp[i]=niza[i];
        }
        tmp[n++]=u;
        delete[]niza;
        niza=tmp;
        return *this;
    }
    double prosecnoVozrast(){
        double prosecno=0.0;
        int brojac=0;
        for(int i=0;i<n;i++){
            prosecno+=niza[i].getVozrast();
            brojac++;
        }
        return prosecno/(double)brojac;
    }

    void pecatiPomladi(Ucesnik &u){
        int ucesnikVoz=u.getVozrast();
        for(int i=0;i<n;i++){
            if(niza[i].getVozrast()<ucesnikVoz){
                cout<<niza[i];
            }
        }
    }
};


int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik*[n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
        u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
    m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for(int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete [] u;
    return 0;
}