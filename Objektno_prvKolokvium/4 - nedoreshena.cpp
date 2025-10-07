#include<iostream>
#include<cstring>
using namespace std;

class Patnik{
private:
    char ime[100];
    int klasa;
    bool velosiped;
public:
    Patnik (){}
    Patnik(char *ime, int klasa, bool velosiped){
        strcpy(this->ime,ime);
        this->klasa=klasa;
        this->velosiped=velosiped;
    }
    friend ostream & operator << (ostream & out, Patnik p){
        out<<p.ime<<endl;
        out<<p.klasa<<endl;
        if(p.velosiped){
            out<<"1"<<endl;
        }
        else{
            out<<"0"<<endl;
        }
        return out;
    }
    bool hasBicycle() const {
        return velosiped;
    }

    int getKlasa() const {
        return klasa;
    }
};

class Voz{
private:
    char destinacija[100];
    Patnik *patnici;
    int n;
    int maxV;
public:
    Voz(){
        n=0;
        patnici= nullptr;
    }

    Voz(char *destinacija,int maxV){
        strcpy(this->destinacija,destinacija);
        this->maxV=maxV;
        n=0;
        patnici= nullptr;
    }
    Voz(const Voz &v) {
        strcpy(this->destinacija, v.destinacija);
        this->maxV = v.maxV;
        this->n = v.n;
        this->patnici = new Patnik[n];
        for (int i = 0; i < n; i++) {
            this->patnici[i] = v.patnici[i];
        }
    }
    Voz &operator=(const Voz &v) {
        if (this != &v) {
            delete[] patnici;

            strcpy(this->destinacija, v.destinacija);
            this->maxV = v.maxV;
            this->n = v.n;
            this->patnici = new Patnik[n];
            for (int i = 0; i < n; i++) {
                this->patnici[i] = v.patnici[i];
            }
        }
        return *this;
    }


    ~Voz(){
        delete[]patnici;
    }

    Voz & operator +=(const Patnik &p){
        if(p.hasBicycle()){
            int brojac=0;
            for(int i=0;i<n;i++){
                if(patnici[i].hasBicycle()){
                    brojac++;
                }
            }
            if(brojac>=maxV){
                return *this;
            }
        }
        Patnik *tmp = new Patnik[n+1];
        for(int i=0;i<n;i++){
            tmp[i]=patnici[i];
        }
        tmp[n++]=p;
        delete[]patnici;
        patnici=tmp;
        return *this;
    }

    friend ostream & operator << (ostream & out, Voz v){
        out<<v.destinacija<<endl;
        for(int i=0;i<v.n;i++){
            out<<v.patnici[i]<<endl;
        }
        return out;
    }

    void patniciNemaMesto(){
        int prva=0, vtora=0;
        int dozvoleni = maxV;

        for (int i = 0; i < n; i++) {
            if (patnici[i].hasBicycle()) { // Ако патникот има велосипед
                if (patnici[i].getKlasa() == 1) {
                    prva++;
                } else {
                    vtora++;
                }
            }
        }

        int izbrishani1 = (prva > dozvoleni) ? prva - dozvoleni : 0;
        dozvoleni -= (prva > dozvoleni) ? dozvoleni : prva; // Намалување на дозволени места

        int izbrishani2 = (vtora > dozvoleni) ? vtora - dozvoleni : 0;
        dozvoleni -= (vtora > dozvoleni) ? dozvoleni : vtora; // Намалување на дозволени места

        cout << "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: " << izbrishani1 << endl;
        cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " << izbrishani2 << endl;
    }

};


int main()
{
    Patnik p;
    char ime[100], destinacija[100];
    int n;
    bool velosiped;
    int klasa;
    int maxv;
    cin >> destinacija >> maxv;
    cin >> n;
    Voz v(destinacija, maxv);
    //cout<<v<<endl;
    for (int i = 0; i < n; i++){
        cin >> ime >> klasa >> velosiped;
        Patnik p(ime, klasa, velosiped);
        //cout<<p<<endl;
        v += p;
    }
    cout << v;
    v.patniciNemaMesto();

    return 0;
}
