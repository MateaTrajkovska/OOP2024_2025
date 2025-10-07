#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

enum tip{smartphone,computer};
class Device{
protected:
    char model[100];
    tip t;
    static float casovi;
    int godina;
public:
    Device(){}

    Device(const char *model,tip t=smartphone,int godina=2000){
        strcpy(this->model,model);
        this->t=t;
        this->godina=godina;
    }

    static void setPocetniCasovi(int c){
        casovi=c;
    }

    float dopCasovi(){
        float dopCas=Device::casovi;
        if(godina>2015){
            dopCas+=2;
        }
        if(t==computer){
            dopCas+=2;
        }
        return dopCas;
    }

    friend ostream & operator<<(ostream &out,Device &d){
        out<<d.model<<endl;
        if(d.t==smartphone){
            out<<"Mobilen ";
        }else{
            out<<"Laptop ";
        }
        out<<d.dopCasovi()<<endl;
        return out;
    }
    int getGodina(){
        return godina;
    }

};

float Device::casovi=1;

class InvalidProductionDate{
public:
    void print(){
        cout<<"Невалидна година на производство"<<endl;
    }
};

class MobileServis{
private:
    char adresa[100];
    Device *nizaUredi;
    int n;// broj uredi
public:
    MobileServis(){}

    MobileServis(const char *adresa){
        strcpy(this->adresa,adresa);
        this->n=0;
        this->nizaUredi= nullptr;
    }

    ~MobileServis(){
        delete[]nizaUredi;
    }

    MobileServis(const MobileServis &ms){
        strcpy(this->adresa,ms.adresa);
        this->n=ms.n;
        this->nizaUredi= new Device[n];
        for(int i=0;i<n;i++){
            nizaUredi[i]=ms.nizaUredi[i];
        }
    }

    MobileServis &operator+=(Device &d){
        if(d.getGodina()>2019 || d.getGodina()<2000){
            throw InvalidProductionDate();
        }
        Device *tmp= new Device[n+1];
        for(int i=0;i<n;i++){
            tmp[i]=nizaUredi[i];
        }
        tmp[n++]=d;
        delete[]nizaUredi;
        nizaUredi=tmp;
        return *this;
    }

    void pecatiCasovi(){
        cout<<"Ime: "<<adresa<<endl;
        for(int i=0;i<n;i++){
            cout<<nizaUredi[i];
        }
    }
};

int main()
{
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
        MobileServis t(ime);
        cout<<ig;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }catch(InvalidProductionDate & e){
                e.print();
            }

        }
        t.pecatiCasovi();
    }
    if (testCase == 3){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }catch(InvalidProductionDate & e){
                e.print();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4){
        cout <<"===== Testiranje na konstruktori ======"<<endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }catch(InvalidProductionDate & e){
                e.print();
            }

        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5){
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }catch(InvalidProductionDate & e){
                e.print();
            }

        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6){
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }catch(InvalidProductionDate & e){
                e.print();
            }

        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}

