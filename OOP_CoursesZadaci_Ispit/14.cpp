//
// Created by Matea Trajkovska on 26.1.25.
//
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class SMS{
protected:
    float cena;
    char tel[16];
public:
    SMS(){}

    SMS(const char *tel, float cena){
        strcpy(this->tel,tel);
        this->cena=cena;
    }
    virtual ~SMS(){}

    virtual float SMS_cena()=0;

    friend ostream & operator<<(ostream &out,SMS &s){
        out<<"Tel: "<<s.tel<<" - cena: "<<s.SMS_cena()<<"den."<<endl;
        return out;
    }
    float getCena(){
        return cena;
    }
};

class RegularSMS : public SMS{
private:
    char *msg;
    bool roaming;
    static int r_procent;
    const static int danok;
public:
    RegularSMS(const char *tel, float cena,const char* msg,bool roaming)
            : SMS(tel,cena){
        this->msg=new char[strlen(msg)+1];
        strcpy(this->msg,msg);
        this->roaming=roaming;
    }

    ~RegularSMS(){
        delete[]msg;
    }

    virtual float SMS_cena()override{
        if(roaming){
            return getCena()*((strlen(msg)/160+1)*(1+r_procent/100.0));
        }else{
            return getCena()*((strlen(msg)/160+1)*(1+danok/100.0));
        }
    }

    static void set_rProcent(int r){
        r_procent=r;
    }

};

int RegularSMS::r_procent=300;
const int RegularSMS::danok=18;

class SpecialSMS : public SMS{
private:
    bool humanitarni;
    static int procent;
public:
    SpecialSMS(const char *tel, float cena,bool humanitarni)
            : SMS(tel,cena){
        this->humanitarni=humanitarni;
    }

    virtual float SMS_cena()override{
        if(humanitarni){
            return getCena();
        }else{
            return getCena()*(1+procent/100.0);
        }
    }

    static void set_sProcent(int s){
        procent=s;
    }
};
int SpecialSMS::procent=150;

void vkupno_SMS(SMS** poraka, int n){
    float vkupnoReg=0;
    float vkupna1=0;
    float vkupnoSpec=0.0;
    float vkupna2=0.0;

    for(int i=0;i<n;i++){
        RegularSMS* ob1 = dynamic_cast<RegularSMS *>(poraka[i]);
        if(ob1!=0){
            vkupnoReg++;
            vkupna1+=ob1->SMS_cena();
        }
        SpecialSMS* ob2 = dynamic_cast<SpecialSMS *>(poraka[i]);
        if(ob2!=0){
            vkupnoSpec++;
            vkupna2+=ob2->SMS_cena();
        }
    }
    cout << "Vkupno ima " << vkupnoReg<< " regularni SMS poraki i nivnata cena e: " << vkupna1 << endl;
    cout << "Vkupno ima " << vkupnoSpec<< " specijalni SMS poraki i nivnata cena e: " << vkupna2 << endl;

}

int main(){

    char tel[20], msg[1000];
    float cena;
    float price;
    int p;
    bool roam, hum;
    SMS  **sms;
    int n;
    int tip;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing RegularSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new RegularSMS(tel, cena, msg, roam);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 2){
        cout << "====== Testing SpecialSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new SpecialSMS(tel, cena, hum);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 3){
        cout << "====== Testing method vkupno_SMS() ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i<n; i++){

            cin >> tip;
            cin >> tel;
            cin >> cena;
            if (tip == 1) {

                cin.get();
                cin.getline(msg, 1000);
                cin >> roam;

                sms[i] = new RegularSMS(tel, cena, msg, roam);

            }
            else {
                cin >> hum;

                sms[i] = new SpecialSMS(tel, cena, hum);
            }
        }

        vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 4){
        cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        sms1 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        cin >> p;
        RegularSMS::set_rProcent(p);
        sms2 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms2;

        delete sms1, sms2;
    }
    if (testCase == 5){
        cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin >> hum;
        sms1 = new SpecialSMS(tel, cena, hum);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin >> hum;
        cin >> p;
        SpecialSMS::set_sProcent(p);
        sms2 = new SpecialSMS(tel, cena, hum);
        cout << *sms2;

        delete sms1, sms2;
    }

    return 0;
}
