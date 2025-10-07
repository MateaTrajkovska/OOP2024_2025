//
// Created by Matea Trajkovska on 27.1.25.
//
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

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
protected:
    string ime;
    string kategorija;
    int cena;
    int kolicina;
public:
    Product(){}

    Product(string &ime, string &kategorija, int cena,int kolicina){
        this->ime=ime;
        this->kategorija=kategorija;
        this->cena=cena;
        this->kolicina=kolicina;
    }
    int totalPrice(){
        int total=cena*kolicina;
        return total;
    }

    friend ostream & operator <<(ostream & out,Product p)
    {
        out<<p.ime<<" ("<<p.kategorija<<") "<<p.kolicina<<" x "<<p.cena<<" = "<<p.totalPrice()<<endl;
        return out;
    }

    const string &getKategorija()  {
        return kategorija;
    }

    string getIme()
    {
        return ime;
    }};

class NoProductFoundException{
private:
    string cat;
public:
    NoProductFoundException(const string &cat)
    {
        this->cat=cat;
    }

    void message()
    {
        cout<<"No products from category "<<cat<<" were found in the store"<<endl;
    }
};

class Store{
private:
    Product *produkti;
    int n;
public:
    Store(){
        n=0;
        produkti= new Product[n];
    }

    //оператор +=
    Store & operator +=(Product &p)
    {
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

    //оператор -=9
    Store &operator -=(Product &p){
        bool found=false;
        Product *tmp=new Product[n];
        int newSize=0;
        for(int i=0;i<n;i++){
            if(produkti[i].getIme() != p.getIme() ){
                tmp[newSize++]=produkti[i];
            }else{
                found=true;
            }
        }

        if(!found){
            throw NoProductFoundException(p.getIme());
        }
        delete[]produkti;
        produkti=tmp;
        n=newSize;
        return *this;
    }

    friend ostream & operator<<(ostream & out, Store s)
    {
        for(int i=0;i<s.n;i++)
        {
            out<<s.produkti[i];
        }
        return out;
    }
    Store fromCategory (string & category){
        Store results;
        int count=0;
        for(int i=0;i<n;i++)
        {
            if(produkti[i].getKategorija()==category)
            {
                results+=produkti[i];
                count++;
            }
        }
        if(count==0)
        {
            throw NoProductFoundException(category);
        }

        return results;
    }

};


int main() {

    wtf();


    Store s;

    //TODO your code starts here
    //TODO Read the products from the file and add them in the store `s`

    ifstream ifs1("input.txt");
    string ime,kategorija;
    int cena,kolicina;

    while(getline(ifs1,ime)){
        getline(ifs1,kategorija);
        ifs1>>cena;
        ifs1>>kolicina;
        ifs1.ignore();
    }
    ifs1.close();
    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT

    string category;
    cin >> category;

    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT

    //TODO Save the results in the files output1.txt and output2.txt after this line
    ofstream fout1("output1.txt");
    fout1<<s;
    fout1.close();

    ofstream fout2("output2.txt");
    fout2<<s.fromCategory(category);
    fout2.close();

    //DO NOT MODIFY THE CODE BELLOW

    cout << "All products:" << endl;
    rff("output1.txt");
    cout << "Products from category " << category << ": " << endl;
    rff("output2.txt");


    return 0;
}