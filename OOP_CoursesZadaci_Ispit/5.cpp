#include <iostream>
#include <cstring>
#include <fstream>
#define MAX 50
using namespace std;

class UserExistsException{
public :
    void print(){
        cout<<"The user already exists in the list!"<<endl;
    }
};

enum typeC{standard,loyal,vip};

class Customer{
protected:
    char name[MAX];
    char email[MAX];
    typeC tC;
    static int discount1;
    static const int discount2;
    int numProducts;
public:
    Customer(){}

    Customer(const char *name, const char *email,typeC tC=standard,int num=0){
        strcpy(this->name,name);
        strcpy(this->email,email);
        this->tC=tC;
        this->numProducts=num;
    }

    static void setDiscount1(int n){
        Customer::discount1=n;
    }

    friend ostream& operator<<(ostream &out,Customer &c){
        out<<c.name<<endl;
        out<<c.email<<endl;
        out<<c.numProducts<<endl;
        if(c.tC==standard){
            out<<"standard ";
        }else if(c.tC==loyal){
            out<<"loyal ";
        }else if(c.tC==vip){
            out<<"vip ";}
        out<<c.calcDiscound()<<endl;
        return out;
    }
    int calcDiscound(){
        int disc;
        if(tC==standard){
            disc=0;
        }else if(tC==loyal){
            disc=discount1;
        }
        else if(tC==vip){
            disc=discount1+discount2;
        }
        return disc;
    }
    char* getEmail(){
        return email;
    }

    typeC getType(){
        return tC;
    }

    void setType(typeC t){
        tC=t;
    }

    int getNumProducts(){
        return numProducts;
    }

    ~Customer() {}


};
int Customer::discount1=10;
const int Customer::discount2=20;

class FINKI_bookstore{
private:
    Customer *customers;
    int n;
public:
    FINKI_bookstore(){
        this->n=0;
        this->customers= new Customer[n];
    }
    FINKI_bookstore(const FINKI_bookstore & fb){
        this->n=fb.n;
        for(int i=0;i<n;i++){
            customers[i]=fb.customers[i];
        }
    }
    FINKI_bookstore & operator = (const FINKI_bookstore &fb){
        if(this!=&fb){
            delete[]customers;
            this->n=fb.n;
            for(int i=0;i<n;i++){
                customers[i]=fb.customers[i];
            }
        }
        return *this;
    }
    ~FINKI_bookstore(){
        delete[]customers;
    }

    FINKI_bookstore & operator+=(Customer c){
        for(int i=0;i<n;i++){
            if(strcmp(customers[i].getEmail(),c.getEmail())==0){
                throw UserExistsException();
            }
        }

        Customer *tmp=new Customer[n+1];
        for(int i=0;i<n;i++){
            tmp[i]=customers[i];
        }
        tmp[n++]=c;
        delete[]customers;
        customers=tmp;
        return *this;
    }

//    void update(){
//        for(int i=0;i<n;i++){
//            if(customers[i].getType()==standard && customers[i].getNumProducts()>5){
//                customers[i].setType(loyal);
//            }
//            if(customers[i].getType()==loyal && customers[i].getNumProducts()>10){
//                customers[i].setType(vip);
//            }
//        }
//    }
    void update() {
        for (int i = 0; i < n; ++i) {
            switch(customers[i].getType()){
                case standard:
                    if(customers[i].getNumProducts()>5)
                        customers[i].setType(loyal); break;
                case loyal:
                    if(customers[i].getNumProducts()>10)
                        customers[i].setType(vip); break;
                default: break;
            }
        }
    }

    friend ostream &operator<<(ostream &out,FINKI_bookstore &fb){
        for(int i=0;i<fb.n;i++){
            out<<fb.customers[i];
        }
        return out;
    }

    void setCustomers(Customer *c, int n){
        delete[] customers;
        this->n = n;
        customers= new Customer[n];
        for(int i=0;i<n;i++){
            customers[i]=c[i];
        }
    }

};

int main(){
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1){
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2){
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3){
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc <<endl;
    }

    if (testCase == 4){
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        fc+=c;

        cout << fc;
    }

    if (testCase == 5){
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        try{
            fc+=c;
        }catch (UserExistsException &e){
            e.print();
        }


        cout << fc;
    }

    if (testCase == 6){
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}
