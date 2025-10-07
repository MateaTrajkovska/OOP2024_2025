//
// Created by Matea Trajkovska on 30.3.25.
//
#include <iostream>
using namespace std;

class Temperature{
private:
    float temp;
public:
    Temperature(){
        temp=0;
    }
    void set(float t){
        temp=t;
    }

    void changeTemp(){
        if(temp<0){
            temp+=1;
        }else if(temp>=0){
            temp-=1;
        }
    }

    void print(){
        cout<<temp<<endl;
    }
};

int main() {
    Temperature obj;
    int n;
    cin >> n;
    int cmd;
    float k;
    for (int i = 0; i < n; i++) {
        cin >> cmd;
        switch (cmd) {
            case 1: {
                cin >> k;
                obj.set(k);
                obj.print();
                break;
            }
            case 2: {
                obj.changeTemp();
                obj.print();
                break;
            }
            case 3: {
                Temperature obj3;
                cin >> k;
                obj3.set(k);
                obj3.changeTemp();
                obj3.print();
                break;
            }
            default: {
                obj.print();
                break;
            }
        }
    }
}