#include <iostream>

using namespace std;

//Your code here

class Library{
protected:
    string ime;
    string grad;
    double cena;
    bool vikend;
public:
    Library(){}

    Library(string &ime,string &grad,double cena,bool vikend){
        this->ime=ime;
        this->grad=grad;
        this->cena=cena;
        this->vikend=vikend;
    }

    virtual void printDetail()=0;
    virtual double calculateMembershipCardCost()=0;
};

class AcademicLibrary : public Library{
private:
    bool moznosti;
    int kolekcii;
public:
    AcademicLibrary(string &ime,string &grad,double cena,bool vikend,bool moznosti, int kolekcii): Library(ime,grad,cena,vikend){
        this->moznosti=moznosti;
        this->kolekcii=kolekcii;
    }

    virtual double calculateMembershipCardCost()override{
        double totalCena=cena;
        if(moznosti){
            totalCena*=1.24;
        }
        for(int i=0;i<kolekcii;i++){
            totalCena+=6;
        }
        return totalCena;
    }

    virtual void printDetail()override{
        cout<<ime<<" - (Academic) "<<grad<<" "<<kolekcii<<" "<<calculateMembershipCardCost()<<endl;
    }
};

class NationalLibrary : public Library {
private:
    bool edukativni;
    int rakopisi;
public:

    NationalLibrary(string &ime,string &grad,double cena,bool vikend,bool edukativni,int rakopisi) : Library(ime,grad,cena,vikend){
        this->edukativni=edukativni;
        this->rakopisi=rakopisi;
    }

    virtual double calculateMembershipCardCost()override{
        double cena=Library::cena;
        if(edukativni){
            cena*=0.93;
        }
        for(int i=0;i<rakopisi;i++)
        {
            cena+=15;
        }
        return cena;
    }
    virtual void printDetail()override{
        cout<<ime<<" - (National) "<<grad<<" "<<rakopisi<<" "<<calculateMembershipCardCost()<<endl;
    }
};

int findMostExpensiveNationalLibrary(Library **l, int n){
    int max=-1;
    int indeks=0;
    for(int i=0;i<n;i++){
        NationalLibrary *nl= dynamic_cast<NationalLibrary *>(l[i]);
        if(nl){
            if(nl->calculateMembershipCardCost()>max){
                max=nl->calculateMembershipCardCost();
                indeks=i;
            }
        }
    }
    if(max==-1){
        return max;
    }else{
        return indeks;
    }
}


int main() {
    int n, testCase, type;
    cin >> testCase >> n;
    cin.ignore();

    Library** m = new Library*[n];

    for (int i = 0; i < n; ++i) {
        string name;
        string city;
        float base_price;
        bool weekend_working;

        cin >> type;
        cin.ignore();
        getline(cin, name);
        getline(cin, city);
        cin >> base_price;
        cin.ignore();
        cin >> weekend_working;
        cin.ignore();

        if (type == 1) {
            bool open_cooperation;
            int specialized_articles;

            cin >> open_cooperation >> specialized_articles;
            cin.ignore();

            m[i] = new AcademicLibrary(name, city, base_price, weekend_working, open_cooperation, specialized_articles);
        } else {
            bool cultural_program;
            int national_articles;

            cin >> cultural_program >> national_articles;
            cin.ignore();

            m[i] = new NationalLibrary(name, city, base_price, weekend_working, cultural_program, national_articles);
        }
    }

    if(testCase == 1){
        cout << "Abstract and child classes OK" << endl;
    }
    else if(testCase == 2){
        for(int i = 0; i < n; i++){
            cout << m[i]->calculateMembershipCardCost() << endl;
        }
        cout << "calculateMembershipCardCost method OK" << endl;
    }
    else if(testCase == 3){
        for(int i = 0; i < n; i++){
            m[i]->printDetail();
        }
        cout << "printDetail method OK" << endl;
    }
    else if(testCase == 4){
        int most_expensive_nat_lib_index = findMostExpensiveNationalLibrary(m, n);
        if(most_expensive_nat_lib_index>=0){
            m[most_expensive_nat_lib_index]->printDetail();
        }else{
            cout << "National Library not found in the array!"<<endl;
        }
        cout << "findMostExpensiveNationalLibrary method OK" << endl;
    }


    for (int i = 0; i < n; ++i) {
        delete m[i];
    }

    delete[] m;

    return 0;
}
