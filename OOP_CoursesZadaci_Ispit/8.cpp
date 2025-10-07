#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class Koncert{
private:
    char naziv[20];
    char lokacija[20];
    static float sezonskiPopust;
    float cenaBilet;
public:
    Koncert(){}

    Koncert(const char *naziv, const char *lokacija,float cena){
        strcpy(this->naziv,naziv);
        strcpy(this->lokacija,lokacija);
        this->cenaBilet=cena;
    }

    virtual float cena(){
        return cenaBilet*(1-sezonskiPopust);
    }

    static void setSezonskiPopust(float p){
        sezonskiPopust=p;
    }

    static float getSezonskiPopust(){
        return sezonskiPopust;
    }

    virtual ~ Koncert(){}

    char *getNaziv(){
        return naziv;
    }
};

float Koncert::sezonskiPopust=0.2;

class ElektronskiKoncert : public Koncert {
private:
    char imeDJ[100];
    float casovi;
    bool denNokj;
public:
    ElektronskiKoncert(const char *naziv, const char *lokacija,float cena,const char*ime,float vreme, bool denNokj=false)
            : Koncert(naziv,lokacija,cena){
        strcpy(this->imeDJ,ime);
        this->casovi=vreme;
        this->denNokj=denNokj;
    }
    virtual float cena()override{
        float total=Koncert::cena();
        if(casovi>7){
            total+=360;
        }else if(casovi>5){
            total+=150;
        }
        if(denNokj)//dnevna
        {
            total-=50;
        }else{
            total+=100;
        }
        return total;
    }
};

void najskapKoncert(Koncert ** koncerti, int n){
    float maxCena=0;
    int maxI=0;
    int elektronski=0;
    for(int i=0;i<n;i++){
        if(koncerti[i]->cena()>maxCena){
            maxCena=koncerti[i]->cena();
            maxI=i;
        }

        if(dynamic_cast<ElektronskiKoncert *>(koncerti[i])!=0){
            elektronski++;
        }
    }
    cout<<"Najskap koncert: "<<koncerti[maxI]->getNaziv()<<" "<<maxCena<<endl;
    cout<<"Elektronski koncerti: "<<elektronski<<" od vkupno "<<n;
}

bool prebarajKoncert(Koncert ** koncerti, int n, char * naziv, bool elektronski){

    bool found=false;

    for(int i=0;i<n;i++){
        if(elektronski==true && dynamic_cast<ElektronskiKoncert *>(koncerti[i])!=0 && strcmp(koncerti[i]->getNaziv(),naziv)==0){
            found =true;
            cout<<koncerti[i]->getNaziv()<<" "<<koncerti[i]->cena()<<endl;
        }
        else {
            if(elektronski==false && strcmp(koncerti[i]->getNaziv(),naziv)==0){
                found = true;
                cout<<koncerti[i]->getNaziv()<<" "<<koncerti[i]->cena()<<endl;
            }
        }

        return found;
    }
}

int main(){

    int tip,n,novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

    cin>>tip;
    if (tip==1){//Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
    }
    else if (tip==2){//cena - Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
    }
    else if (tip==3){//ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
    }
    else if (tip==4){//cena - ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
    }
    else if (tip==5) {//najskapKoncert

    }
    else if (tip==6) {//prebarajKoncert
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        najskapKoncert(koncerti,5);
    }
    else if (tip==7){//prebaraj
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        bool elektronski;
        cin>>elektronski;
        if(prebarajKoncert(koncerti,5, "Area",elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

        if(prebarajKoncert(koncerti,5, "Area",!elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

    }
    else if (tip==8){//smeni cena
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[2] -> setSezonskiPopust(0.9);
        najskapKoncert(koncerti,4);
    }

    return 0;
}
