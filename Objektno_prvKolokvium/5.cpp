#include <iostream>
#include <cstring>
using namespace std;

class Gitara{
private:
    char seriski[25];
    float cena;
    int godina;
    char tip[40];
public:
    Gitara (){}
    Gitara(char *tip,char *seriski, int godina,float cena){
        strcpy(this->tip,tip);
        strcpy(this->seriski,seriski);
        this->godina=godina;
        this->cena=cena;
    }

    bool daliIsti(Gitara &g){
        for(int i=0;i< strlen(seriski);i++){
            if(seriski[i]!=g.seriski[i]){
                return false;
            }
        }
        return true;
    }

    void pecati(){
        cout<<seriski<<" "<<tip<<" "<<cena<<endl;
    }

    const char *getSeriski() const {
        return seriski;
    }

    float getNabavna() const {
        return cena;
    }

    int getGodina() const {
        return godina;
    }

    const char *getTip() const {
        return tip;
    }
};

class Magacin{
private:
    char ime[30];
    char lokacija[60];
    Gitara *gitari;
    int n;
    int godinaOtvaranje;
public:
    Magacin(char *ime=" ", char *lokacija=" ", int godinaOtvaranje=0){ //arguments const.
        strcpy(this->ime,ime);
        strcpy(this->lokacija,lokacija);
        this->godinaOtvaranje=godinaOtvaranje;
        n=0;
        gitari= nullptr;
    }

    Magacin (const Magacin & m){ //copy
        strcpy(this->ime,m.ime);
        strcpy(this->lokacija,m.lokacija);
        this->godinaOtvaranje=m.godinaOtvaranje;
        n=m.n;
        gitari= new Gitara[n+1];
        for(int i=0;i<n;i++){
            gitari[i]=m.gitari[i];
        }

    }

    Magacin & operator =(const Magacin &m){ //operator =
        if (this!=&m){
            delete[] gitari;
            strcpy(this->ime,m.ime);
            strcpy(this->lokacija,m.lokacija);
            this->godinaOtvaranje=m.godinaOtvaranje;
            n=m.n;
            gitari= new Gitara[n+1];
            for(int i=0;i<n;i++){
                gitari[i]=m.gitari[i];
            }

        }
        return *this;
    }

    ~Magacin(){
        delete[]gitari;
    }

    double vrednost(){
        double vrednost=0.0;
        for(int i=0;i<n;i++){
            vrednost+=gitari[i].getNabavna();
        }
        return vrednost;
    }

    void dodadi(Gitara d){
        Gitara *tmp=new Gitara [n+1];
        for(int i=0;i<n;i++){
            tmp[i]=gitari[i];
        }
        tmp[n++]=d;
        delete[]gitari;
        gitari=tmp;
    }

    void prodadi(Gitara p){

        int newSize=0;
        for(int i=0;i<n;i++){
            if(gitari[i].daliIsti(p)==false){
                newSize++;
            }
        }
        Gitara *tmp= new Gitara[newSize];
        int j=0;
        for(int i=0;i<n;i++){
            if(gitari[i].daliIsti(p)==false){
                tmp[j]=gitari[i];
                j++;
            }
        }
        delete[]gitari;
        gitari=tmp;
        n=newSize;
    }
    void pecati(bool daliNovi){
        cout<<ime<<" "<<lokacija<<endl;
        for(int i=0;i<n;i++){
            if(daliNovi==true && gitari[i].getGodina()>godinaOtvaranje){
                gitari[i].pecati();
            }
            else if(daliNovi==false){
                gitari[i].pecati();
            }
        }
    }
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, godina;
    float cena;
    char seriski[50],tip[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin>>tip;
        cin>>seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip,seriski, godina,cena);
        cout<<g.getTip()<<endl;
        cout<<g.getSeriski()<<endl;
        cout<<g.getGodina()<<endl;
        cout<<g.getNabavna()<<endl;
    } else if(testCase == 2){
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
        Magacin kb("Magacin1","Lokacija1");
        kb.pecati(false);
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2005);
        cin>>n;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;
            Gitara g(tip,seriski, godina,cena);
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
    }

    else if(testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2012);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    }
    else if(testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        Magacin kb3;
        kb3=kb;
        kb3.pecati(true);
    }
    else if(testCase ==6)
    {
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            kb.dodadi(g);
        }
        cout<<kb.vrednost()<<endl;
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        cout<<kb.vrednost();
        Magacin kb3;
        kb3=kb;
    }
    return 0;
}
