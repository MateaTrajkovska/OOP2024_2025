//
// Created by Matea Trajkovska on 27.6.24.
//
#include <iostream>
#include <cstring>
#include<fstream>
using namespace std;

//Your code here


void wtf() {
    ofstream fout("input.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----") {
            break;
        }
        fout << line << endl;
    }
}

void rff(string path) {
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}


class Product{
private:
    string ime;
    string kategorija;
    int cena;
    int kolicina;
public:
    Product(){
    }
    Product(string &ime, string &kategorija, int c, int k){
        this->ime=ime;
        this->kategorija=kategorija;
        this->cena=c;
        this->kolicina=k;
    }
    friend ostream & operator<<(ostream & out,  Product p)
    {
        out<<p.ime<<" ("<<p.kategorija<<") "<<p.kolicina<<" x "<<p.cena<<p.totalPrice()<<endl;
        return out;
    }
    int totalPrice(){
        return cena*kolicina;
    }
    string getcat(){
        return kategorija;
    }
};


class NoProductFoundException{
    string cat;
public:
    NoProductFoundException(string &kategorija){
        this->cat=kategorija;
    }
    void print(){
        cout<<"No products found from category ("<<cat<<")"<<endl;
    }
};


class Store{
private:
    Product *produkti;
    int n;
public:
    Store(){
        this->n=0;
        this->produkti= new Product[n];
    }
    Store &operator +=(Product &p){
        Product *tmp=new Product[n+1];
        for(int i=0;i<n;i++)
        {
            tmp[i]=produkti[i];
        }
        tmp[n++]=p;
        delete[]produkti;
        produkti=tmp;
        return *this;
    }

    friend ostream & operator<<(ostream & out,  Store s){
        for(int i=0;i<s.n;i++)
        {
            out<<s.produkti[i];
        }
        return out;
    }
    Store fromCategory(string &category){
        Store s;
        int istacat=0;
        for(int i=0;i<n;i++){
            if(produkti[i].getcat()==category){
                istacat++;
            }
        }
        if(istacat==0){
            throw NoProductFoundException(category);
        }
        for(int i=0;i<n;i++){
            if(produkti[i].getcat()==category){
                s+=produkti[i];
            }
        }
        return s;
    }

}

int main() {

    wtf();


    Store s;

    //TODO your code starts here
    //TODO Read the products from the file and add them in the store `s`
    ifstream ifs1;
    string ime,kategorija;
    int cena,kolicina;
    while(getline(ifs1,ime)) {
        getline(ifs1, kategorija);
        ifs1 >> cena;
        ifs1 >> kolicina;
        ifs1.ignore();
        Product p(ime,kategorija,cena,kolicina);
        s+=p;
    }
    ifs1.close();


    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT

    string category;
    cin >> category;

    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT

    //TODO Save the results in the files output1.txt and output2.txt after this line
    ofstream ofs1;
    ofs1<<s;
    ofs1.close();

    //DO NOT MODIFY THE CODE BELLOW
    ofstream ofs2;
    try{
        ofs2<<s.fromCategory(category);
    }catch(NoProductFoundException &np){
        np.print();
    }
    ofs2.close();
    cout << "All products:" << endl;
    rff("output1.txt");
    cout << "Products from category " << category << ": " << endl;
    rff("output2.txt");


    return 0;
}