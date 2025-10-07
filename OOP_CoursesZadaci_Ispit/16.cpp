#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;


// вашиот код треба да биде тука

class Transport{
protected:
    char destinacija[100];
    int cena;
    int rastojanie;
public:
    Transport(){}

    Transport(const char *destinacija,int cena, int rastojanie){
        strcpy(this->destinacija,destinacija);
        this->cena=cena;
        this->rastojanie=rastojanie;
    }
    virtual ~Transport(){}
    virtual int cenaTransport()=0;

    int getCena(){
        return cena;
    }

    char *getDestinacija(){
        return destinacija;
    }
    int getRastojanie(){
        return rastojanie;
    }

    friend bool operator <(const Transport &t1, const Transport &t2){
        return (t1.rastojanie<t2.rastojanie);
    }
};

class AvtomobilTransport : public Transport {
private:
    bool daliShofer;
public:
    AvtomobilTransport(const char *destinacija,int cena, int rastojanie,bool shofer=true)
            : Transport(destinacija,cena,rastojanie){
        this->daliShofer=shofer;
    }

    virtual int cenaTransport() override{
        int cenaA=Transport::cena;
        if(daliShofer){
            cenaA*=1.20;
        }
        return cenaA;
    }

};

class KombeTransport : public Transport {
private:
    int patnici;
public:
    KombeTransport(const char *destinacija,int cena, int rastojanie,int patnici)
            : Transport(destinacija,cena,rastojanie){
        this->patnici=patnici;
    }

    virtual int cenaTransport() override{
        int cenaK=Transport::cena;

        cenaK-= patnici*200;
        return cenaK;
    }

};

int pecatiPoloshiPonudi(Transport **ponudi,int n, Transport &t){

    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(*ponudi[j]<*ponudi[i]){
                Transport *pom=ponudi[i];
                ponudi[i]=ponudi[j];
                ponudi[j]=pom;
            }
        }
    }
    for(int i=0;i<n;i++){
        if(ponudi[i]->cenaTransport()>t.cenaTransport()){
            cout << ponudi[i]->getDestinacija() << " ";
            cout << ponudi[i]->getRastojanie() << " ";
            cout << ponudi[i]->cenaTransport() << endl;
        }
    }
}

int main(){

    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }


    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}
