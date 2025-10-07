//
// Created by Matea Trajkovska on 20.3.25.
//
#include <iostream>
#include <cstring>
using namespace std;

class StockRecord{
private:
    char id[12];
    char company[50];
    double price;
    double newPrice;
    int shares;
public:
    StockRecord(){}

    StockRecord(char *id, char *company, double price, int shares){
        strcpy(this->id,id);
        strcpy(this->company,company);
        this->price=price;
//      this->newPrice=newPrice;
        this->shares=shares;
    }

    void setNewPrice(double c){
        newPrice=c;
    }

    double value(){
        double value=shares*newPrice;
        return value;
    }

    double profit() const {
        double profit=shares*(newPrice-price);
        return profit;
    }

    friend ostream & operator << (ostream & out, const StockRecord & sr){
        out<<sr.company<<" "<<sr.shares<<" "<<sr.price<<" "<<sr.newPrice<<" "<<sr.profit()<<endl;
        return out;
    }

};

class Client{
private:
    char clientName[60];
    int companyID;
    StockRecord *companies;
    int n;
public:
    Client(){
        n=0;
        companies= nullptr;
    }
    Client(char *clientName, int companyID){
        strcpy(this->clientName,clientName);
        this->companyID=companyID;
        n=0;
        companies= nullptr;
    }
    ~Client(){
        delete[]companies;
    }
    Client (const Client &c){
        strcpy(this->clientName,c.clientName);
        this->companyID=c.companyID;
        this->n=c.n;
        companies= new StockRecord[n];
        for(int i=0;i<n;i++){
            companies[i]=c.companies[i];
        }
    }
    Client & operator = (const Client &c){
        if (this!=&c){
            delete[]companies;
            strcpy(this->clientName,c.clientName);
            this->companyID=c.companyID;
            this->n=c.n;
            companies= new StockRecord[n];
            for(int i=0;i<n;i++){
                companies[i]=c.companies[i];
            }
        }
        return *this;
    }

    double totalValue() const {
        double total=0.0;
        for(int i=0;i<n;i++){
            total+=companies[i].value();
        }
        return total;
    }

    Client & operator += (StockRecord sr){
        StockRecord *tmp= new StockRecord[n+1];
        for(int i=0;i<n;i++){
            tmp[i]=companies[i];
        }
        tmp[n++]=sr;
        delete[]companies;
        companies=tmp;
        return *this;
    }

    friend ostream & operator<<(ostream &out , const Client c){
        out<<c.companyID<<" "<<c.totalValue()<<endl;
        for(int i=0;i<c.n;i++){
            out<<c.companies[i];
        }
        return out;
    }

};

int main(){

    int test;
    cin >> test;

    if(test == 1){
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if(test == 2){
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for(int i = 0; i < n; ++i){
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    }
    else if(test == 3){
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for(int i = 0; i < n; ++i){
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if(flag){
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}