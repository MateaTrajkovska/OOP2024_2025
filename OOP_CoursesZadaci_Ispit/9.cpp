////
//// Created by Matea Trajkovska on 25.1.25.
////
//#include <iostream>
//#include <cstring>
//#include <fstream>
//using namespace std;
//
//class Exception{
//public:
//    void print(){
//        cout << "Ne moze da se vnese dadeniot trud" << endl;
//    }
//};
//
//class Trud{
//private:
//    char tip;
//    int god;
//public:
//    Trud(const char tip = 'C', int god = 0){
//        this->tip = toupper(tip);
//        this->god = god;
//    }
//    int getGod(){
//        return god;
//    }
//    char getTip(){
//        return tip;
//    }
//
//    friend istream& operator>>(istream& in, Trud &t){
//        in >> t.tip >> t.god;
//        return in;
//    }
//};
//
//class Student{
//private:
//    char ime[30];
//    int indeks;
//    int god;
//    int oceni[50];
//    int n;
//public:
//    Student(){}
//    Student(const char* ime, int indeks, int god, int *oceni, int n){
//        strcpy(this->ime, ime);
//        this->indeks = indeks;
//        this->god = god;
//        this->n = n;
//        for (int i = 0; i < n; i++)
//            this->oceni[i] = oceni[i];
//    }
//
//    int getGod(){
//        return god;
//    }
//
//    int getIndeks(){
//        return indeks;
//    }
//
//    virtual float rang(){
//        int suma = 0;
//        for (int i = 0; i < n; i++)
//            suma += oceni[i];
//        return (float)suma / n;
//    }
//
//    friend ostream& operator<< (ostream& o, Student& st)
//    {
//        o << st.indeks << " " << st.ime << " " << st.god << " " << st.rang() << endl;
//        return o;
//    }
//    virtual ~Student(){}
//};
//
//class PhDStudent : public Student{
//private:
//    Trud *t;
//    int nt;
//    static int conf;
//    static int journal;
//public:
//    PhDStudent(const char* ime, int indeks, int god, int *oceni, int n, Trud* t, int nt) :Student(ime, indeks, god, oceni, n){
//        //this->nt = nt;
//        this->t = new Trud[100];
//        int ok=0;
//        for (int i = 0; i < nt; i++){
//            try{
//                if (this->getGod() > t[i].getGod()) throw Exception();
//                this->t[ok] = t[i];
//                ok++;
//            }
//            catch (Exception e){
//                e.print();
//                //this->nt--;
//
//            }
//        }
//        this->nt = ok;
//
//    }
//
//    float rang(){
//        int suma = 0;
//        for (int i = 0; i < nt; i++){
//            if (t[i].getTip() == 'C')
//                suma += conf;
//            else
//                suma += journal;
//        }
//        return Student::rang() + suma;
//    }
//
//    static void setConf(int c){
//        PhDStudent::conf = c;
//    }
//
//    static void setJournal(int j){
//        PhDStudent::journal = j;
//    }
//
//    void operator+=(Trud &tr){
//        if (this->getGod() > tr.getGod()) throw Exception();
//        this->t[nt] = tr;
//        this->nt++;
//    }
//
//    ~PhDStudent(){
//        delete[] t;
//    }
//
//};
//int PhDStudent::conf = 1;
//int PhDStudent::journal = 3;
//
//int main(){
//    int testCase;
//    cin >> testCase;
//
//    int god, indeks, n, god_tr, m, n_tr;
//    int izbor; //0 za Student, 1 za PhDStudent
//    char ime[30];
//    int oceni[50];
//    char tip;
//    Trud trud[50];
//
//    if (testCase == 1){
//        cout << "===== Testiranje na klasite ======" << endl;
//        cin >> ime;
//        cin >> indeks;
//        cin >> god;
//        cin >> n;
//        for (int j = 0; j < n; j++)
//            cin >> oceni[j];
//        Student s(ime, indeks, god, oceni, n);
//        cout << s;
//
//        cin >> ime;
//        cin >> indeks;
//        cin >> god;
//        cin >> n;
//        for (int j = 0; j < n; j++)
//            cin >> oceni[j];
//        cin >> n_tr;
//        for (int j = 0; j < n_tr; j++){
//            cin >> tip;
//            cin >> god_tr;
//            Trud t(tip, god_tr);
//            trud[j] = t;
//        }
//        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
//        cout << phd;
//    }
//    if (testCase == 2){
//        cout << "===== Testiranje na operatorot += ======" << endl;
//        Student **niza;
//        cin >> m;
//        niza = new Student *[m];
//        for (int i = 0; i<m; i++){
//            cin >> izbor;
//            cin >> ime;
//            cin >> indeks;
//            cin >> god;
//            cin >> n;
//            for (int j = 0; j < n; j++)
//                cin >> oceni[j];
//
//            if (izbor == 0){
//                niza[i] = new Student(ime, indeks, god, oceni, n);
//            }
//            else{
//                cin >> n_tr;
//                for (int j = 0; j < n_tr; j++){
//                    cin >> tip;
//                    cin >> god_tr;
//                    Trud t(tip, god_tr);
//                    trud[j] = t;
//                }
//                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
//            }
//        }
//        // pecatenje na site studenti
//        cout << "\nLista na site studenti:\n";
//        for (int i = 0; i < m; i++)
//            cout << *niza[i];
//
//        // dodavanje nov trud za PhD student spored indeks
//        Trud t;
//        cin >> indeks;
//        cin >> t;
//        int flag = 1;
//        for (int i = 0; i < m; i++){
//            if ((*niza[i]).getIndeks() == indeks) {
//                PhDStudent* nov = dynamic_cast<PhDStudent*>(niza[i]);
//                if (nov != 0){
//                    (*nov) += t;
//                    flag = 0;
//                    break;
//                }
//            }
//        }
//        if (flag)
//            cout << "Ne postoi PhD student so indeks " << indeks << endl;
//
//
//        // pecatenje na site studenti
//        cout << "\nLista na site studenti:\n";
//        for (int i = 0; i < m; i++)
//            cout << *niza[i];
//    }
//    if (testCase == 3){
//        cout << "===== Testiranje na operatorot += ======" << endl;
//        Student **niza;
//        cin >> m;
//        niza = new Student *[m];
//        for (int i = 0; i<m; i++){
//            cin >> izbor;
//            cin >> ime;
//            cin >> indeks;
//            cin >> god;
//            cin >> n;
//            for (int j = 0; j < n; j++)
//                cin >> oceni[j];
//
//            if (izbor == 0){
//                niza[i] = new Student(ime, indeks, god, oceni, n);
//            }
//            else{
//                cin >> n_tr;
//                for (int j = 0; j < n_tr; j++){
//                    cin >> tip;
//                    cin >> god_tr;
//                    Trud t(tip, god_tr);
//                    trud[j] = t;
//                }
//                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
//            }
//        }
//        // pecatenje na site studenti
//        cout << "\nLista na site studenti:\n";
//        for (int i = 0; i < m; i++)
//            cout << *niza[i];
//
//        // dodavanje nov trud za PhD student spored indeks
//        Trud t;
//        cin >> indeks;
//        cin >> t;
//        int flag = 1;
//        for (int i = 0; i < m; i++){
//            if ((*niza[i]).getIndeks() == indeks) {
//                PhDStudent* nov = dynamic_cast<PhDStudent*>(niza[i]);
//                if (nov != 0){
//                    (*nov) += t;
//                    flag = 0;
//                    break;
//                }
//            }
//        }
//        if (flag)
//            cout << "Ne postoi PhD student so indeks " << indeks << endl;
//
//
//        // pecatenje na site studenti
//        cout << "\nLista na site studenti:\n";
//        for (int i = 0; i < m; i++)
//            cout << *niza[i];
//    }
//    if (testCase == 4){
//        cout << "===== Testiranje na isklucoci ======" << endl;
//        cin >> ime;
//        cin >> indeks;
//        cin >> god;
//        cin >> n;
//        for (int j = 0; j < n; j++)
//            cin >> oceni[j];
//        cin >> n_tr;
//        for (int j = 0; j < n_tr; j++){
//            cin >> tip;
//            cin >> god_tr;
//            Trud t(tip, god_tr);
//            trud[j] = t;
//        }
//        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
//        cout << phd;
//    }
//    if (testCase == 5){
//        cout << "===== Testiranje na isklucoci ======" << endl;
//        Student **niza;
//        cin >> m;
//        niza = new Student *[m];
//        for (int i = 0; i<m; i++){
//            cin >> izbor;
//            cin >> ime;
//            cin >> indeks;
//            cin >> god;
//            cin >> n;
//            for (int j = 0; j < n; j++)
//                cin >> oceni[j];
//
//            if (izbor == 0){
//                niza[i] = new Student(ime, indeks, god, oceni, n);
//            }
//            else{
//                cin >> n_tr;
//                for (int j = 0; j < n_tr; j++){
//                    cin >> tip;
//                    cin >> god_tr;
//                    Trud t(tip, god_tr);
//                    trud[j] = t;
//                }
//                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
//            }
//        }
//        // pecatenje na site studenti
//        cout << "\nLista na site studenti:\n";
//        for (int i = 0; i < m; i++)
//            cout << *niza[i];
//
//        // dodavanje nov trud za PhD student spored indeks
//        Trud t;
//        cin >> indeks;
//        cin >> t;
//        int flag = 1;
//        for (int i = 0; i < m; i++){
//            if ((*niza[i]).getIndeks() == indeks) {
//                PhDStudent* nov = dynamic_cast<PhDStudent*>(niza[i]);
//                if (nov != 0){
//                    try{
//                        flag = 0;
//                        (*nov) += t;
//                        break;
//                    }
//                    catch (Exception e){
//                        e.print();
//                    }
//                }
//            }
//        }
//        if (flag)
//            cout << "Ne postoi PhD student so indeks " << indeks << endl;
//
//
//        // pecatenje na site studenti
//        cout << "\nLista na site studenti:\n";
//        for (int i = 0; i < m; i++)
//            cout << *niza[i];
//    }
//    if (testCase == 6){
//        cout << "===== Testiranje na static clenovi ======" << endl;
//        Student **niza;
//        cin >> m;
//        niza = new Student *[m];
//        for (int i = 0; i<m; i++){
//            cin >> izbor;
//            cin >> ime;
//            cin >> indeks;
//            cin >> god;
//            cin >> n;
//            for (int j = 0; j < n; j++)
//                cin >> oceni[j];
//
//            if (izbor == 0){
//                niza[i] = new Student(ime, indeks, god, oceni, n);
//            }
//            else{
//                cin >> n_tr;
//                for (int j = 0; j < n_tr; j++){
//                    cin >> tip;
//                    cin >> god_tr;
//                    Trud t(tip, god_tr);
//                    trud[j] = t;
//                }
//                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
//            }
//        }
//        // pecatenje na site studenti
//        cout << "\nLista na site studenti:\n";
//        for (int i = 0; i < m; i++)
//            cout << *niza[i];
//
//        int conf, journal;
//        cin >> conf;
//        cin >> journal;
//        PhDStudent::setConf(conf);
//        PhDStudent::setJournal(journal);
//
//        // pecatenje na site studenti
//        cout << "\nLista na site studenti:\n";
//        for (int i = 0; i < m; i++)
//            cout << *niza[i];
//    }
//
//    return 0;
//}

#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class Exception{
public:
    void print(){
        cout<<"Ne moze da se vnese dadeniot trud"<<endl;
    }
};

class Trud{
protected:
    char tip;
    int godina;
public:
    Trud(const char tip='C', int god=0) {
        this->tip = toupper(tip);
        this->godina = god;
    }
    char getTip(){
        return tip;
    }
    int getGod(){
        return godina;
    }

    friend istream & operator >> (istream &in, Trud &t){
        in>>t.tip>>t.godina;
        return in;
    }

};

class Student{
protected:
    char ime[30];
    int indeks;
    int godUpis;
    int listaOceni[50];
    int polozeni;
public:
    Student(){}

    Student(const char *ime, int indeks, int godUpis, int *oceni, int polozeni){
        strcpy(this->ime,ime);
        this->indeks=indeks;
        this->godUpis=godUpis;
        this->polozeni=polozeni;
        for(int i=0;i<polozeni;i++){
            this->listaOceni[i]=oceni[i];
        }
    }

    virtual float rang(){
        float sum=0;
        for(int i=0;i<polozeni;i++){
            sum+=listaOceni[i];
        }
        return sum/(float)polozeni;
    }
    virtual ~Student(){}

    friend ostream & operator << (ostream & out, Student &s){
        out<<s.indeks<<" "<<s.ime<<" "<<s.godUpis<<" "<<s.rang()<<endl;
        return out;
    }

    int getIndeks(){
        return indeks;
    }
};


class PhDStudent : public Student {
private:
    Trud *listaTrudovi;
    int n;
    static int konf;
    static int spis;
public:
    PhDStudent(const char *ime, int indeks, int godUpis, int *oceni, int polozeni,Trud *trud,int n)
            : Student(ime,indeks,godUpis,oceni,polozeni){
        this->n=0;
        this->listaTrudovi= new Trud [n];
    }

    ~PhDStudent(){
        delete[]listaTrudovi;
    }

    static void setKonf(int k){
        PhDStudent::konf=k;
    }

    static void setSpis(int s){
        PhDStudent::spis=s;
    }

    virtual float rang()override{
        int sum2=0;
        for(int i=0;i<n;i++){
            if(listaTrudovi->getTip()=='C'){
                sum2+=konf;
            }else{
                sum2=spis;
            }
        }
        return rang()+sum2;
    }

    void operator +=(Trud &t){
        if(t.getGod()>this->godUpis){
            throw Exception();
        }
        Trud *tmp= new Trud[n+1];
        for(int i=0;i<n;i++){
            tmp[i]=listaTrudovi[i];
        }
        tmp[n++]=t;
        delete[]listaTrudovi;
        listaTrudovi=tmp;
    }

};

int PhDStudent::konf=1;
int PhDStudent::spis=3;

int main(){
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        Trud listaTrudovi;
        cin >> indeks;
        cin >> t;
        int flag = 1;
        for (int i = 0; i < m; i++){
            if ((*niza[i]).getIndeks() == indeks) {
                PhDStudent* nov = dynamic_cast<PhDStudent*>(niza[i]);
                if (nov != 0){
                    (*nov) += t;
                    flag = 0;
                    break;
                }
            }
        }
        if (flag)
            cout << "Ne postoi PhD student so indeks " << indeks << endl;


        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks


        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2


        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 5){
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot


        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6){
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi
        int konf, spis;
        cin >> konf;
        cin >> spis;
        PhDStudent::setKonf(konf);
        PhDStudent::setSpis(spis);

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}

//#include <iostream>
//#include <cstring>
//#include <fstream>
//using namespace std;
//
//class Exception {
//public:
//    void print() {
//        cout << "Ne moze da se vnese dadeniot trud" << endl;
//    }
//};
//
//class Trud {
//protected:
//    char tip;
//    int godina;
//
//public:
//    Trud(const char tip = 'C', int god = 0) {
//        this->tip = toupper(tip);
//        this->godina = god;
//    }
//
//    char getTip() {
//        return tip;
//    }
//
//    int getGod() {
//        return godina;
//    }
//
//    friend istream &operator>>(istream &in, Trud &t) {
//        in >> t.tip >> t.godina;
//        return in;
//    }
//};
//
//class Student {
//protected:
//    char ime[30];
//    int indeks;
//    int godUpis;
//    int listaOceni[50];
//    int polozeni;
//
//public:
//    Student() {}
//
//    Student(const char *ime, int indeks, int godUpis, int *oceni, int polozeni) {
//        strcpy(this->ime, ime);
//        this->indeks = indeks;
//        this->godUpis = godUpis;
//        this->polozeni = polozeni;
//        for (int i = 0; i < polozeni; i++) {
//            this->listaOceni[i] = oceni[i];
//        }
//    }
//
//    virtual float rang() {
//        float sum = 0;
//        for (int i = 0; i < polozeni; i++) {
//            sum += listaOceni[i];
//        }
//        return sum / (float)polozeni;
//    }
//
//    virtual ~Student() {}
//
//    friend ostream &operator<<(ostream &out, Student &s) {
//        out << s.indeks << " " << s.ime << " " << s.godUpis << " " << s.rang() << endl;
//        return out;
//    }
//
//    int getIndeks() {
//        return indeks;
//    }
//};
//
//class PhDStudent : public Student {
//private:
//    Trud *listaTrudovi;
//    int n;
//    static int konf;
//    static int spis;
//
//public:
//    PhDStudent(const char *ime, int indeks, int godUpis, int *oceni, int polozeni, Trud *trud, int n)
//        : Student(ime, indeks, godUpis, oceni, polozeni) {
//        this->n = n;
//        this->listaTrudovi = new Trud[n];
//        for (int i = 0; i < n; i++) {
//            this->listaTrudovi[i] = trud[i];
//        }
//    }
//
//    ~PhDStudent() {
//        delete[] listaTrudovi;
//    }
//
//    static void setKonf(int k) {
//        PhDStudent::konf = k;
//    }
//
//    static void setSpis(int s) {
//        PhDStudent::spis = s;
//    }
//
//    float rang() override {
//        int sum2 = 0;
//        for (int i = 0; i < n; i++) {
//            if (listaTrudovi[i].getTip() == 'C') {
//                sum2 += konf;
//            } else {
//                sum2 += spis;
//            }
//        }
//        return Student::rang() + sum2;
//    }
//
//    void operator+=(Trud &t) {
//        if (t.getGod() < this->godUpis) {
//            throw Exception();
//        }
//        Trud *tmp = new Trud[n + 1];
//        for (int i = 0; i < n; i++) {
//            tmp[i] = listaTrudovi[i];
//        }
//        tmp[n++] = t;
//        delete[] listaTrudovi;
//        listaTrudovi = tmp;
//    }
//};
//
//int PhDStudent::konf = 1;
//int PhDStudent::spis = 3;
//
//int main() {
//    int testCase;
//    cin >> testCase;
//
//    int god, indeks, n, god_tr, m, n_tr;
//    int izbor; // 0 za Student, 1 za PhDStudent
//    char ime[30];
//    int oceni[50];
//    char tip;
//    Trud trud[50];
//
//    if (testCase == 1) {
//        cout << "===== Testiranje na klasite ======" << endl;
//        cin >> ime;
//        cin >> indeks;
//        cin >> god;
//        cin >> n;
//        for (int j = 0; j < n; j++)
//            cin >> oceni[j];
//        Student s(ime, indeks, god, oceni, n);
//        cout << s;
//
//        cin >> ime;
//        cin >> indeks;
//        cin >> god;
//        cin >> n;
//        for (int j = 0; j < n; j++)
//            cin >> oceni[j];
//        cin >> n_tr;
//        for (int j = 0; j < n_tr; j++) {
//            cin >> tip;
//            cin >> god_tr;
//            Trud t(tip, god_tr);
//            trud[j] = t;
//        }
//        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
//        cout << phd;
//    }
//
//    if (testCase == 2 || testCase == 3) {
//        cout << "===== Testiranje na operatorot += ======" << endl;
//        Student **niza;
//        cin >> m;
//        niza = new Student *[m];
//        for (int i = 0; i < m; i++) {
//            cin >> izbor;
//            cin >> ime;
//            cin >> indeks;
//            cin >> god;
//            cin >> n;
//            for (int j = 0; j < n; j++)
//                cin >> oceni[j];
//
//            if (izbor == 0) {
//                niza[i] = new Student(ime, indeks, god, oceni, n);
//            } else {
//                cin >> n_tr;
//                for (int j = 0; j < n_tr; j++) {
//                    cin >> tip;
//                    cin >> god_tr;
//                    Trud t(tip, god_tr);
//                    trud[j] = t;
//                }
//                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
//            }
//        }
//
//        cout << "\nLista na site studenti:\n";
//        for (int i = 0; i < m; i++)
//            cout << *niza[i];
//
//        Trud t;
//        cin >> indeks;
//        cin >> t;
//
//        bool flag = true;
//        for (int i = 0; i < m; i++) {
//            if (niza[i]->getIndeks() == indeks) {
//                PhDStudent *phd = dynamic_cast<PhDStudent *>(niza[i]);
//                if (phd) {
//                    try {
//                        *phd += t;
//                        flag = false;
//                    } catch (Exception &e) {
//                        e.print();
//                    }
//                    break;
//                }
//            }
//        }
//
//        if (flag)
//            cout << "Ne postoi PhD student so indeks " << indeks << endl;
//
//        cout << "\nLista na site studenti:\n";
//        for (int i = 0; i < m; i++)
//            cout << *niza[i];
//
//        for (int i = 0; i < m; i++) {
//            delete niza[i];
//        }
//        delete[] niza;
//    }
//
//    if (testCase == 6) {
//        cout << "===== Testiranje na static clenovi ======" << endl;
//        Student **niza;
//        cin >> m;
//        niza = new Student *[m];
//        for (int i = 0; i < m; i++) {
//            cin >> izbor;
//            cin >> ime;
//            cin >> indeks;
//            cin >> god;
//            cin >> n;
//            for (int j = 0; j < n; j++)
//                cin >> oceni[j];
//
//            if (izbor == 0) {
//                niza[i] = new Student(ime, indeks, god, oceni, n);
//            } else {
//                cin >> n_tr;
//                for (int j = 0; j < n_tr; j++) {
//                    cin >> tip;
//                    cin >> god_tr;
//                    Trud t(tip, god_tr);
//                    trud[j] = t;
//                }
//                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
//            }
//        }
//
//        cout << "\nLista na site studenti:\n";
//        for (int i = 0; i < m; i++)
//            cout << *niza[i];
//
//        int conf, journal;
//        cin >> conf >> journal;
//        PhDStudent::setKonf(conf);
//        PhDStudent::setSpis(journal);
//
//        cout << "\nLista na site studenti:\n";
//        for (int i = 0; i < m; i++)
//            cout << *niza[i];
//
//        for (int i = 0; i < m; i++) {
//            delete niza[i];
//        }
//        delete[] niza;
//    }
//
//    return 0;
//}