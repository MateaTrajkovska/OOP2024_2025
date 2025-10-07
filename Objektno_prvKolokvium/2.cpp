//
// Created by Matea Trajkovska on 15.3.25.
//
#include <iostream>
#include <cstring>
using namespace std;

class List{
private:
    int *broj;
    int n;
public:
    List(){

    }

    List (int *broj, int n){
        this->broj= new int [n];
        for(int i=0;i<n;i++){
            this->broj[i]= broj[i];
        }
        this->n=n;
    }
    ~List(){
        delete[] broj;
    }

    List (const List &l){ // copy const
        n=l.n;
        broj= new int[n];
        for(int i=0;i<n;i++){
            this->broj[i]= l.broj[i];
        }
    }
    List & operator =(const List &l){
        if(this != &l){
            delete[]broj;
            n=l.n;
            broj= new int [n];
            for(int i=0;i<n;i++){
                this->broj[i]= l.broj[i];
            }
        }
        return *this;
    }

    int sum(){
        int suma=0;
        for(int i=0;i<n;i++){
            suma+=broj[i];
        }
        return suma;
    }

    double average(){
        int suma=0;
        for(int i=0;i<n;i++){
            suma+=broj[i];
        }
        double prosek=(double)suma/n;
        return prosek;
    }

    void print(){
        cout<<n<<": ";
        for(int i=0;i<n;i++){
            cout<<broj[i]<<" ";
        }
        cout<<"sum: "<<sum()<<" average: "<<average()<<endl;
    }

    int getN() const {
        return n;
    }

};

class ListContainer{
private:
    List *listi;
    int n;
    int brObidi;
public:
    ListContainer(){
        listi= nullptr;
        n=0;
        brObidi=0;
    }

    ListContainer(const ListContainer & lc){
        n=lc.n;
        brObidi=lc.brObidi;
        listi = new List[n];
        for(int i = 0; i < n ; i++){
            listi[i]=lc.listi[i];
        }
    }

    ListContainer & operator = (const ListContainer &lc){
        if(this != &lc){
            delete[]listi;
            n=lc.n;
            brObidi=lc.brObidi;
            listi = new List[n];
            for(int i=0;i<n;i++){
                listi[i]=lc.listi[i];
            }
        }
        return *this;
    }

    ~ListContainer(){
        delete[]listi;
    }

    void print(){
        if (n==0){
            cout<<"The list is empty"<<endl;
            return;
        }
        for(int i=0;i<n;i++){
            cout<<"List number: "<< i+1<< " List info: ";
            listi[i].print();
        }
        cout<<"Sum: "<<sum()<<" Average: "<<average()<<endl;
        cout << "Successful attempts: " << n << " Failed attempts: " << (brObidi - n) << endl;

    }

    void addNewList(List l){
        brObidi++;
        for(int i=0;i<n;i++){
            if(listi[i].sum() == l.sum()){
                return;
            }
        }
        List *tmp= new List[n+1];
        for(int i=0;i<n;i++){
            tmp[i]=listi[i];
        }
        tmp[n++]=l;
        delete[]listi;
        listi=tmp;

    }

    int sum(){
        int suma=0;
        for(int i=0;i<n;i++){
            suma+= listi[i].sum();
        }
        return suma;
    }

    double average(){
        double prosek=0.0;
        int brEl=0;
        for(int i=0;i<n;i++){
            brEl+=listi[i].getN();
        }
        prosek=(double)sum()/brEl;
        return prosek;
    }
};
int main() {

    ListContainer lc;
    int N;
    cin>>N;

    for (int i=0;i<N;i++) {
        int n;
        int niza[100];

        cin>>n;

        for (int j=0;j<n;j++){
            cin>>niza[j];

        }

        List l=List(niza,n);

        lc.addNewList(l);
    }


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.print();
    }
}