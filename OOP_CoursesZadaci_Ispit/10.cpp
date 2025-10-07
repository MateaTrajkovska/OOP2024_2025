#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

//место за вашиот код

class Oglas{
protected:
    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
public:
    Oglas(){}

    Oglas(const char *naslov, const char *kategorija, const char *opis, float cena){
        strcpy(this->naslov,naslov);
        strcpy(this->kategorija,kategorija);
        strcpy(this->opis,opis);
        this->cena=cena;
    }
    friend ostream & operator<<(ostream &out,Oglas &o){
        out<<o.naslov<<endl;
        out<<o.opis<<endl;
        out<<o.cena<<" evra"<<endl;
        return out;
    }
    friend bool operator >(const Oglas &o1, const Oglas &o2){
        return (o1.cena>o2.cena);
    }

    float getCena(){
        return cena;
    }

    char *getKat(){
        return kategorija;
    }
};

class NegativnaVrednost{
public:
    void print(){
        cout<<"Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!"<<endl;
    }
};

class Oglasnik {
private:
    char ime[20];
    Oglas *oglasi;
    int n;
public:
    Oglasnik(const char *ime){
        strcpy(this->ime,ime);
        this->n=0;
        this->oglasi= new Oglas[n];
    }
    ~Oglasnik(){
        delete[]oglasi;
    }

    Oglasnik & operator +=(Oglas &o){
        if(o.getCena()<0){
            throw NegativnaVrednost();
        }
        Oglas *tmp=new Oglas[n+1];
        for(int i=0;i<n;i++){
            tmp[i]=oglasi[i];
        }
        tmp[n++]=o;
        delete[]oglasi;
        oglasi=tmp;
        return *this;
    }

    friend ostream & operator<<(ostream &out, Oglasnik &o){
        out<<o.ime<<endl;
        for(int i=0;i<o.n;i++){
            out<<o.oglasi[i];
            out<<endl;
        }
        return out;
    }

    void oglasiOdKategorija(const char *k){
        for(int i=0;i<n;i++){
            if(!strcmp(oglasi[i].getKat(),k)){
                cout<<oglasi[i]<<endl;
            }
        }
    }

    void najniskaCena(){
        Oglas min=oglasi[0];
        for(int i=1;i<n;i++){
            if(min>oglasi[i]){
                min=oglasi[i];
            }
        }
        cout<<min;
    }
};


int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
        cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }catch (NegativnaVrednost & e){
                e.print();
            }

        }
        cout<<ogl;
    }
    else if (tip==4){
        cout<<"-----Test oglasOdKategorija -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
        cout<<"-----Test Exception -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }catch (NegativnaVrednost & e){
                e.print();
            }

        }
        cout<<ogl;

    }
    else if (tip==6){
        cout<<"-----Test najniskaCena -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }catch (NegativnaVrednost & e){
                e.print();
            }

        }
        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }
    else if (tip==7){
        cout<<"-----Test All -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            try{
                ogl+=o;
            }catch (NegativnaVrednost & e){
                e.print();
            }

        }
        cout<<ogl;

        cin.get();
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }

    return 0;
}
