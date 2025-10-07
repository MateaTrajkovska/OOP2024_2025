#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

//место за вашиот код

class Delo{
protected:
    char ime[50];
    int god;
    char zemja[50];
public:
    Delo(){}
    Delo(const char *ime, int god, const char *zemja){
        strcpy(this->ime,ime);
        this->god=god;
        strcpy(this->zemja,zemja);
    }

    friend bool operator == (const Delo &d1,const Delo &d2){
        return strcmp(d1.ime,d2.ime)==0;
    }
    int getGod(){
        return god;
    }
    char *getZemja(){
        return zemja;
    }
    char *getIme(){
        return ime;
    }
};

class Pretstava{
protected:
    Delo delo;
    int karti;
    char data[15];
public:
    Pretstava(){}

    Pretstava(Delo delo,int karti,const char *data){
        this->delo=delo;
        this->karti=karti;
        strcpy(this->data,data);
    }

    virtual float cena(){
        float total=0;
        float m=0,n=0;
        if(delo.getGod()>1901 && delo.getGod()<2100){
            m+=50;
        }else if(delo.getGod()>1801 && delo.getGod()<1901){
            m+=75;
        }
        else{
            if(delo.getGod()<1801){
                m+=100;
            }
        }
        if(strcmp(delo.getZemja(),"Italija")==0){
            n+=100;
        }else if(strcmp(delo.getZemja(),"Rusija")==0){
            n+=150;
        }else{
            n+=80;
        }

        total=m+n;
        return total;
    }

    Delo getDelo(){
        return delo;
    }

    int getKarti(){
        return karti;
    }

};

class Opera : public Pretstava{
public:
    Opera(Delo delo,int karti,const char *data): Pretstava(delo,karti,data){}
};
class Balet : public Pretstava{
private:
    static int dopolnitelen;
public:
    Balet(Delo delo,int karti,const char *data): Pretstava(delo,karti,data){}

    static void setCenaBalet(int n){
        dopolnitelen=n;
    }

    float cena()override{
        return Pretstava::cena()+dopolnitelen;
    }
};

int Balet::dopolnitelen=150;

int prihod(Pretstava **p,int n){
    int prihod=0;
    for(int i=0;i<n;i++){
        prihod+=p[i]->cena()*p[i]->getKarti();
    }
    return prihod;
}

int brojPretstaviNaDelo(Pretstava **pr,int n,Delo d){
    int br=0;
    for(int i=0;i<n;i++){
        if(pr[i]->getDelo()==d){
            br++;
        }
    }
    return br;
}

//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout<<"======TEST CASE 1======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->getDelo().getIme()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->getDelo().getIme()<<endl;
        }break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout<<"======TEST CASE 2======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->cena()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->cena()<<endl;
        }break;

        case 3:
            //Testiranje na operator ==
        {
            cout<<"======TEST CASE 3======="<<endl;
            Delo f1=readDelo();
            Delo f2=readDelo();
            Delo f3=readDelo();

            if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
            if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

        }break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout<<"======TEST CASE 4======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();

            }
            cout<<prihod(pole,n);
        }break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout<<"======TEST CASE 5======="<<endl;
            int cenaBalet;
            cin>>cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }
            cout<<prihod(pole,n);
        }break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout<<"======TEST CASE 6======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }

            Delo f=readDelo();
            cout<<brojPretstaviNaDelo(pole,n,f);
        }break;

    };


    return 0;
}
