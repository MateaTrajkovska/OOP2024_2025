#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

#include <cstring>
#include <iostream>
using namespace std;

// Your Code goes here
class Pizza{
protected:
    char ime[20];
    char sostojki[100];
    double cena;
public:
    Pizza(){}

    Pizza(const char *ime,const char *sostojki,double cena){
        strcpy(this->ime,ime);
        strcpy(this->sostojki,sostojki);
        this->cena=cena;
    }

    virtual double price()=0;
    virtual ~Pizza(){}
};

bool operator < ( Pizza &p1,  Pizza &p2){
    return (p1.price()<p2.price());
}

enum Size {
    mala,golema,familijarna
};

class FlatPizza : public Pizza{
private:
    Size s;
public:
    FlatPizza(const char *ime,const char *sostojki,double cena,Size s=mala) : Pizza(ime,sostojki,cena)
    {
        this->s=s;
    }

    virtual double price()override{
        if(s==mala){
            return cena*1.10;
        }
        if(s==golema){
            return cena*1.20;
        }
        if(s==familijarna){
            return cena*1.30;
        }
    }

    friend ostream & operator << (ostream &out, FlatPizza &fp){
        out<<fp.ime<<": "<<fp.sostojki<<", ";
        if(fp.s==mala)
        {
            out<<"small - ";
        }
        if(fp.s==golema)
        {
            out<<"big - ";
        }
        if(fp.s==familijarna)
        {
            out<<"family - ";
        }
        out<<fp.price()<<endl;
        return out;
    }
};
class FoldedPizza : public Pizza{
private:
    bool beloBrashno;
public:
    FoldedPizza(const char *ime,const char *sostojki,double cena,bool beloBrashno=true) : Pizza(ime,sostojki,cena)
    {
        this->beloBrashno=beloBrashno;
    }

    virtual double price()override{
        double cena= Pizza :: cena;
        if(beloBrashno){
            cena*=1.10;
        }
        else{
            cena*=1.30;
        }
        return cena;
    }
    friend ostream & operator << (ostream &out, FoldedPizza &fp){
        out<<fp.ime<<": "<<fp.sostojki<<", ";
        if(fp.beloBrashno){
            out<<"wf - ";
        }
        else{
            out<<"nwf - ";
        }
        out<<fp.price()<<endl;
        return out;
    }
    void setWhiteFlour(bool wf){
        beloBrashno=wf;
    }
};

int expensivePizza(Pizza **p,int n){
    float maxCena=p[0]->price();
    int maxI=0;

    for(int i=1;i<n;i++){
        if(p[i]->price()>maxCena){
            maxCena=p[i]->price();
            maxI=i;
        }
    }

    FlatPizza *p1= dynamic_cast<FlatPizza *>(p[maxI]);
    if(p1){
        cout<<*p1;
    }

    FoldedPizza *p2= dynamic_cast<FoldedPizza *>(p[maxI]);
    if(p2){
        cout<<*p2;
    }
}
// Testing

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza fp(name, ingredients, inPrice, (Size)s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp1;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp2;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout<<"Lower price: "<<endl;
        if(*fp1<*fp2)
            cout<<fp1->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp1<*fp3)
            cout<<fp1->price()<<endl;
        else cout<<fp3->price()<<endl;

        if(*fp4<*fp2)
            cout<<fp4->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp3<*fp4)
            cout<<fp3->price()<<endl;
        else cout<<fp4->price()<<endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name,20);

                cin.getline(ingredients,100);
                cin >> inPrice;
                int s;
                cin>>s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name,20);
                cin.getline(ingredients,100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza (name, ingredients, inPrice);
                if(j%2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi,num_p);


    }
    return 0;
}
