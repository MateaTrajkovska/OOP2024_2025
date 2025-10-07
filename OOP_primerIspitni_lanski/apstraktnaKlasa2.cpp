//
// Created by Matea Trajkovska on 27.6.24.
//
#include <iostream>
#include <cstring>
using namespace std;

class Museum{
protected:
    string ime;
    string grad;
    double osnovna;
    int rabotniH;
public:
    Museum(){}
    Museum (string &ime, string &grad, double osnovna,int rabotniH){
        this->ime=ime;
        this->grad=grad;
        this->osnovna=osnovna;
        this->rabotniH=rabotniH;
    }

    virtual void printDetail()=0;
    virtual double calculateTicketCost()=0;
};

class ScientificMuseum : public Museum{
protected:
    bool interaktivni;
    int multimedija;
public:
    ScientificMuseum(string &ime, string &grad, double osnovna,int rabotniH, bool i,int m) : Museum(ime,grad,osnovna,rabotniH){
        this->interaktivni=i;
        this->multimedija=m;
    }
    virtual double calculateTicketCost()override{
        double cena = osnovna;
        if(interaktivni){
            cena*= 1.12;
        }
        for(int i=0;i<multimedija;i++)
        {
            cena+=multimedija*6;

        }
        return cena;
    }

    virtual void printDetail()override{
        cout<<ime<<" - (Scientific) "<<grad<<" "<<multimedija<<" "<<calculateTicketCost()<<endl;
    }
};

class ArtMuseum : public Museum{
private:
    bool izlozba;
    int brojUmetnicki;
public:
    ArtMuseum(string &ime, string &grad, double osnovna,int rabotniH, bool i,int b) : Museum(ime,grad,osnovna,rabotniH){
        this->izlozba=i;
        this->brojUmetnicki=b;
    }
    virtual double calculateTicketCost()override{
        double cena = osnovna;
        if(izlozba){
            cena*= 0.82;
        }
        for(int i=0;i<brojUmetnicki;i++)
        {
            cena+=brojUmetnicki*3;
            return cena;
        }
    }
    virtual void printDetail()override{
        cout<<ime<<" - (Art) "<<grad<<" "<<izlozba<<" "<<calculateTicketCost()<<endl;
    }
};

int findCheapestScientificMuseum(Museum **m, int n){
    int index=0;
    int min=999;
    int mintemp=999;
    for(int i=0;i<n;i++){
        ScientificMuseum *sc=dynamic_cast<ScientificMuseum *>(m[i]);
        if(sc)
        {
            if(sc->calculateTicketCost()<min){
                min=sc->calculateTicketCost();
                index=i;
            }
        }
    }
    if(min<mintemp){
        return -1;
    }
    else{
        return index;
    }

}

int main() {
    int n, testCase, type;
    cin >> testCase >> n;
    cin.ignore();

    Museum** m = new Museum*[n];

    for (int i = 0; i < n; ++i) {
        string name;
        string city;
        float base_price;
        int working_hours;

        cin >> type;
        cin.ignore();
        getline(cin, name);
        getline(cin, city);
        cin >> base_price;
        cin.ignore();
        cin >> working_hours;
        cin.ignore();

        if (type == 1) {
            bool interactive_shows;
            int multimedia_pres;

            cin >> interactive_shows >> multimedia_pres;
            cin.ignore();

            m[i] = new ScientificMuseum(name, city, base_price, working_hours, interactive_shows, multimedia_pres);
        } else {
            bool amateur_shows;
            int original_artwork;

            cin >> amateur_shows >> original_artwork;
            cin.ignore();

            m[i] = new ArtMuseum(name, city, base_price, working_hours, amateur_shows, original_artwork);
        }
    }

    if(testCase == 1){
        cout << "Abstract and child classes OK" << endl;
    }
    else if(testCase == 2){
        for(int i = 0; i < n; i++){
            cout << m[i]->calculateTicketCost() << endl;
        }
        cout << "calculateTicketCost method OK" << endl;
    }
    else if(testCase == 3){
        for(int i = 0; i < n; i++){
            m[i]->printDetail();
        }
        cout << "printDetail method OK" << endl;
    }
    else if(testCase == 4){
        int cheapest_sci_museum_index = findCheapestScientificMuseum(m, n);
        if(cheapest_sci_museum_index>=0){
            m[cheapest_sci_museum_index]->printDetail();
        }else{
            cout << "Scientific Museum not found in the array!"<<endl;
        }
        cout << "findCheapestOnlineOrder method OK" << endl;
    }


    for (int i = 0; i < n; ++i) {
        delete m[i];
    }

    delete[] m;

    return 0;
}
