#include <iostream>
#include <cstring>
using namespace std;

struct Laptop{
    char firma[100];
    float goleminaMonitor;
    bool daliTouch;
    int cena;
};

struct ITStore{
    char ime[100];
    char lokacija[100];
    Laptop laptopi[100];
    int n;

    void print();
};
void ITStore ::  print(){
    cout<<ime<<" "<<lokacija<<endl;
    for(int i=0;i<n;i++){
        cout<<laptopi[i].firma<<" "<<laptopi[i].goleminaMonitor<<" "<<laptopi[i].cena<<endl;
    }
}

int najmalaCena (ITStore its){
    int min , f=0;
    for(int i=0;i<its.n;i++){
        if(its.laptopi[i].daliTouch){
            if(!f){
                min=its.laptopi[i].cena;
                f=1;
            }
            else if (its.laptopi[i].cena<min){
                min=its.laptopi[i].cena;
            }
        }
    }
    return min;
}

void najeftina_ponuda(ITStore its[], int n){
    int minCena= najmalaCena(its[0]);
    int minI=0;
    for(int i=0;i<n;i++){
        if(najmalaCena(its[i])<minCena){
            minCena= najmalaCena(its[i]);
            minI=i;
        }
    }

    cout<<"Najeftina ponuda ima prodavnicata: "<<endl;
    cout<<its[minI].ime<<" "<<its[minI].lokacija<<endl;
    cout<<"Najniskata cena iznesuva: "<<najmalaCena(its[minI])<<endl;
}
int main() {
    ITStore s[100];
    int n;
    cin>>n; //broj na IT prodavnici

    //vnesuvanje na prodavnicite edna po edna, zaedno so raspolozlivite laptopvi vo niv
    for(int i=0;i<n;i++){
        cin>>s[i].ime;
        cin>>s[i].lokacija;
        cin>>s[i].n;
        for(int j=0;j<s[i].n;j++){
            cin>>s[i].laptopi[j].firma;
            cin>>s[i].laptopi[j].goleminaMonitor;
            cin>>s[i].laptopi[j].daliTouch;
            cin>>s[i].laptopi[j].cena;
        }
    }
    //pecatenje na site prodavnici
    for(int i=0;i<n;i++){
        s[i].print();
    }
    //povik na glavnata metoda
    najeftina_ponuda(s, n);

    return 0;
}