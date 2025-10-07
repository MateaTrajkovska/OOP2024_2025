//
// Created by Matea Trajkovska on 25.1.25.
//
#include<iostream>
#include<string.h>
using namespace std;

class Karticka{
protected:
    char smetka[16];
    int pin;
    bool povekjePin;
public:
    Karticka(char* smetka,int pin){
        strcpy(this->smetka,smetka);
        this->pin=pin;
        this->povekjePin=false;
    }
    virtual ~Karticka(){}
    Karticka(const Karticka & u){
        strcpy(this->smetka,u.smetka);
        this->pin=u.pin;
        this->povekjePin=u.povekjePin;
    }
    bool getDopolnitelenPin(){return povekjePin;}
    char* getSmetka(){return smetka;}

    virtual int tezinaProbivanje(){
        int broj=0;
        int pompin=pin;
        while (pompin!=0) {
            broj++;
            pompin/=10;
        }
        return broj;
    }
    friend ostream& operator<<(ostream& o,Karticka &u){
        o<<u.smetka<<": "<<u.tezinaProbivanje()<<endl;
        return o;
    }

};
class IndexOutOfBoundException{
public:
    void print(){
        cout<<"Brojot na pin kodovi ne moze da go nadmine dozvolenoto"<<endl;
    }

};
class SpecijalnaKarticka: public Karticka{
private:
    int broj;
    int *poeni;

public:
    const static int M=4;
    ~SpecijalnaKarticka()
    {
        delete []poeni;
    }
    SpecijalnaKarticka(char* ime,int finalenIspit):Karticka(ime,finalenIspit){
        this->povekjePin=true;
        broj=0;
        poeni=new int[M];
    }
    SpecijalnaKarticka(const SpecijalnaKarticka& u):Karticka(u){
        broj=u.broj;
        poeni=new int[M];
        for (int i=0;i<broj;i++) poeni[i]=u.poeni[i];
    }

    int tezinaProbivanje(){

        return broj+ Karticka::tezinaProbivanje();
    }
    friend void operator +=(SpecijalnaKarticka &u,int novi){
        if (u.broj==u.M) throw IndexOutOfBoundException();
        u.poeni[u.broj++]=novi;
    }
};
class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    int static P;
public:
    Banka(char *naziv, Karticka** karticki,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako kartickata ima dopolnitelni pin kodovi
            //cout<<karticki[i]->getDopolnitelenPin()<<endl;
            if (karticki[i]->getDopolnitelenPin()){
                this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
            }
            else this->karticki[i]=new Karticka(*karticki[i]);
        }
        this->broj=broj;
    }
    ~Banka(){
        for (int i=0;i<broj;i++) delete karticki[i];
    }

    //da se dopolni
    static void setLIMIT(int novoP){
        P=novoP;
    }
    void pecatiKarticki(){
        cout<<"Vo bankata "<<naziv<<" moze da se probijat kartickite:"<<endl;
        for (int i=0;i<broj;i++)
            if (karticki[i]->tezinaProbivanje()<=P) cout<<(*karticki[i]);
    }
    void dodadiDopolnitelenPin(char *ime,int poeniA){
        for (int i=0;i<broj;i++)
            if (strcmp(karticki[i]->getSmetka(),ime)==0)
            {
                SpecijalnaKarticka* nov=dynamic_cast<SpecijalnaKarticka*>(karticki[i]);
                if (nov!=0){
                    //cout<<"a"<<endl;
                    (*nov)+=poeniA;
                }

            }
    }
};
int Banka::P=7;
int main(){

    Karticka **niza;
    int n,m,pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin>>n;
    niza=new Karticka*[n];
    for (int i=0;i<n;i++){
        cin>>smetka;
        cin>>pin;
        cin>>daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i]=new Karticka(smetka,pin);
        else
            niza[i]=new SpecijalnaKarticka(smetka,pin);
        //cout<<"main: "<<niza[i]->getDopolnitelenPin()<<endl;
    }

    Banka komercijalna("Komercijalna",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;
    for (int i=0;i<m;i++){
        cin>>smetka>>pin;
        try{
            komercijalna.dodadiDopolnitelenPin(smetka,pin);
        }
        catch(IndexOutOfBoundException i){
            i.print();
        }
    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();

}

//#include <iostream>
//#include <cstring>
//#include <fstream>
//using namespace std;
//
//class Karticka{
//protected:
//    char smetka[16];
//    int pin;
//    bool povekjePin;
//public:
//    Karticka(char* smetka,int pin){
//        strcpy(this->smetka,smetka);
//        this->pin=pin;
//        this->povekjePin=false;
//    }
//    // дополниете ја класата
//    Karticka (const Karticka & k){
//        strcpy(this->smetka,k.smetka);
//        this->pin=k.pin;
//        this->povekjePin=k.povekjePin;
//    }
//    virtual ~Karticka(){}
//
//    friend ostream & operator <<(ostream &out,Karticka k){
//        out<<k.smetka<<": "<<k.tezinaProbivanje()<<endl;
//    }
//
//    virtual int tezinaProbivanje(){
//        int broj=0;
//        int pompin=pin;
//        while(pompin!=0){
//            broj++;
//            pompin/10;
//        }
//        return broj;
//    }
//};
//
//class OutOfBoundException{
//public:
//    void print(){
//        cout<<"Brojot na pin kodovi ne moze da go nadmine dozvolenoto"<<endl;
//    }
//};
////вметнете го кодот за SpecijalnaKarticka
//
//class SpecijalnaKaricka : public Karticka{
//private:
//    int *poeni; //dopolnitelen pin
//    int broj;// broj na pin kodovi
//public:
//    const static int M=4;
//
//    SpecijalnaKaricka(char* smetka,int pin): Karticka(smetka,pin){
//        this->povekjePin=true;
//        this->broj=0;
//        this->poeni=new int[M];
//    }
//
//    SpecijalnaKaricka(const SpecijalnaKaricka & k) : Karticka(k){
//        this->broj=k.broj;
//        for(int i=0;i<broj;i++){
//            poeni[i]=k.poeni[i];
//        }
//    }
//    ~SpecijalnaKaricka(){
//        delete[]poeni;
//    }
//
//    virtual int tezinaProbivanje() override{
//        return broj+Karticka::tezinaProbivanje();
//    }
//
//
//
//};
//
//
//class Banka {
//private:
//    char naziv[30];
//    Karticka *karticki[20];
//    int broj;
//public:
//    Banka(char *naziv, Karticka** karticki,int broj ){
//        strcpy(this->naziv,naziv);
//        for (int i=0;i<broj;i++){
//            //ako kartickata ima dopolnitelni pin kodovi
//            if (karticki[i]->getDopolnitelenPin()){
//                this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
//            }
//            else this->karticki[i]=new Karticka(*karticki[i]);
//        }
//        this->broj=broj;
//    }
//    ~Banka(){
//        for (int i=0;i<broj;i++) delete karticki[i];
//    }
//
//    //да се дополни класата
//
//};
//
//
//
//int main(){
//
//    Karticka **niza;
//    int n,m,pin;
//    char smetka[16];
//    bool daliDopolnitelniPin;
//    cin>>n;
//    niza=new Karticka*[n];
//    for (int i=0;i<n;i++){
//        cin>>smetka;
//        cin>>pin;
//        cin>>daliDopolnitelniPin;
//        if (!daliDopolnitelniPin)
//            niza[i]=new Karticka(smetka,pin);
//        else
//            niza[i]=new SpecijalnaKarticka(smetka,pin);
//    }
//
//    Banka komercijalna("Komercijalna",niza,n);
//    for (int i=0;i<n;i++) delete niza[i];
//    delete [] niza;
//    cin>>m;
//    for (int i=0;i<m;i++){
//        cin>>smetka>>pin;
//
//        komercijalna.dodadiDopolnitelenPin(smetka,pin);
//
//    }
//
//    Banka::setLIMIT(5);
//
//    komercijalna.pecatiKarticki();
//
//}