//
// Created by Matea Trajkovska on 26.1.25.
//
#include<iostream>
#include<string.h>
using namespace std;

class StudentKurs{
protected:
    char ime[30];
    int ocenka;
    bool daliUsno;

public:
    static int M;


    static void setMAX(int m){
        M = m;
    }

    StudentKurs(char* ime,int finalenIspit){
        strcpy(this->ime,ime);
        this->ocenka=finalenIspit;
        this->daliUsno=false;
    }
    //дополни ја класата

    virtual ~StudentKurs(){}

    StudentKurs(const StudentKurs & sk)
    {
        strcpy(this->ime,sk.ime);
        this->ocenka=sk.ocenka;
        this->daliUsno=sk.daliUsno;
    }

    bool getDaliUsno() const{
        return daliUsno;
    }

    virtual int osvoeniPoeni() const{
        return ocenka;
    }

    friend ostream & operator <<(ostream & out,StudentKurs & sk)
    {
        out<<sk.ime<<" --- "<<sk.osvoeniPoeni()<<endl;
        return out;
    }

    const char *getIme() const {
        return ime;
    }

};

int StudentKurs :: M=10;

class BadInputException{
public:
    void message()
    {
        cout<<"Greshna opisna ocenka"<<endl;
    }
};

//вметни го кодот за StudentKursUsno
class StudentKursUsno : public StudentKurs {
private:
    char *opisnaOcena;
public:
    ~StudentKursUsno(){
        delete []opisnaOcena;
    }

    StudentKursUsno (char* ime,int finalenIspit) : StudentKurs(ime,finalenIspit)
    {
        this->daliUsno=true;
        opisnaOcena= new char[0];
    }

    StudentKursUsno (const StudentKursUsno & sku) : StudentKurs(sku){
        opisnaOcena= new char[strlen(sku.opisnaOcena)+1];
        strcpy(this->opisnaOcena,sku.opisnaOcena);
    }

    int osvoeniPoeni() const override
    {
        if(strcmp(opisnaOcena,"odlicen")==0 && StudentKurs::osvoeniPoeni()<M-1 )
        {
            return StudentKurs::osvoeniPoeni()+2;
        }
        if(strcmp(opisnaOcena,"odlicen")==0 && StudentKurs::osvoeniPoeni()==M-1 )
        {
            return StudentKurs::osvoeniPoeni()+1;
        }
        if(strcmp(opisnaOcena,"dobro")==0 && StudentKurs::osvoeniPoeni()<M )
        {
            return StudentKurs::osvoeniPoeni()+1;
        }
        if(strcmp(opisnaOcena,"losho")==0 && StudentKurs::osvoeniPoeni()<=M )
        {
            return StudentKurs::osvoeniPoeni()-1;
        }
        return StudentKurs::osvoeniPoeni();

    }

    friend void operator +=(StudentKursUsno & sku, char *nova){
        bool daliznak=false;
        for(int i=0;i< strlen(nova);i++)
        {
            if(!isalpha(nova[i])){
                daliznak=true;
                break;
            }
        }
        if(daliznak==true){
            throw BadInputException();
        }
        delete[]sku.opisnaOcena;
        sku.opisnaOcena= new char [strlen(nova)+1];
        strcpy(sku.opisnaOcena,nova);

    }


};

class KursFakultet{
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;
    static const int MINOCENKA=6;

public:
    KursFakultet(char *naziv, StudentKurs** studenti,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako studentot ima usno isprashuvanje
            if (studenti[i]->getDaliUsno()){
                this->studenti[i]=new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
            }
            else this->studenti[i]=new StudentKurs(*studenti[i]);
        }
        this->broj=broj;
    }
    ~KursFakultet(){
        for (int i=0;i<broj;i++) delete studenti[i];
    }

    //дополни ја класата

    void pecatiStudenti(){
        cout<<"Kursot "<<naziv<<" go polozile: "<<endl;
        for(int i=0;i<broj;i++)
        {
            if(studenti[i]->osvoeniPoeni()>=MINOCENKA)
            {
                cout<<(*studenti[i]);
            }
        }
    }

    void postaviOpisnaOcenka(char * ime, char* opisnaOcenka){
        for(int i=0;i<broj;i++)
        {
            if(strcmp(studenti[i]->getIme(),ime)==0)
            {
                StudentKursUsno* nov=dynamic_cast<StudentKursUsno *>(studenti[i]);
                if(nov!=0)
                {
                    (*nov)+=opisnaOcenka;
                }
            }
        }
    }

};

int main(){

    StudentKurs **niza;
    int n,m,ocenka;
    char ime[30],opisna[10];
    bool daliUsno;
    cin>>n;
    niza=new StudentKurs*[n];
    for (int i=0;i<n;i++){
        cin>>ime;
        cin>>ocenka;
        cin>>daliUsno;
        if (!daliUsno)
            niza[i]=new StudentKurs(ime,ocenka);
        else
            niza[i]=new StudentKursUsno(ime,ocenka);
    }

    KursFakultet programiranje("OOP",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;

    for (int i=0;i<m;i++){
        cin>>ime>>opisna;
        try{
            programiranje.postaviOpisnaOcenka(ime,opisna); //imam

        }catch(BadInputException &e)
        {
            char nova[10];
            int k=0;
            for(int i=0;i< strlen(opisna);i++)
            {
                if(isalpha(opisna[i])){
                    nova[k++]=opisna[i];
                }
                nova[k]=0;
            }
            programiranje.postaviOpisnaOcenka(ime,nova);
            e.message();
        }

    }

    StudentKurs::setMAX(9);

    programiranje.pecatiStudenti();

}
