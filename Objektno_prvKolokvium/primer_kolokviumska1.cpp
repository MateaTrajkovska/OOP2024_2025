//
// Created by Matea Trajkovska on 3.4.25.
//

// kodot na onenote
#include <iostream>
#include<cstring>
#include<iomanip>
using namespace std;

class Date{
private:
    int day;
    int month;
    int year;
public:
    Date(){}

    Date(int day, int mont, int year){
        this->day=day;
        this->month=month;
        this->year=year;
    }

    bool isAfter(Date & other){
        if(year > other.year){
            return true;
        }else if(year < other.year){
            return false;
        }else{
            if(month > other.month){
                return true;
            }else if(month <other.month){
                return false;
            }else{
                if(day > other.day){
                    return true;
                }else{
                    return false;
                }
            }
        }

    }

    void print () {
        cout << setfill('0') << setw(2) << day << "/" << setfill('0') << setw(2) << month << "/" << year;
    }
};

class SMS{
    Date date;
    char content[150];
    char sender[11];
    char reciver[11];
public:
    SMS(){}
    SMS(Date date,char content[150], char sender[11],char reciver[11]){
        this->date=date;
        strcpy(this->content,content);
        strcpy(this->sender,sender);
        strcpy(this->reciver,reciver);
    }

    void print(){
        date.print();
        cout << content<<" "<<sender<<" "<<reciver<<endl;
    }

    friend void filterMessages(SMS messages[],int n,Date filter);
};

void filterMessages(SMS messages[],int n,Date filter){
    int flag=0;
    for(int i=0;i<n;i++){
        if(strlen(messages[i].content)>70 && messages[i].date.isAfter(filter)){
            messages[i].print();
            flag=1;
        }
    }

    if(flag==0){
        cout<<"No SMS satisfy the given condition."<<endl;
    }
}

int main(){
    int n;
    cin>>n;

    int day;
    int month;
    int year;
    char content[150];
    char sender[11];
    char reciver[11];

    SMS messages[100];

    for(int i=0;i<n;i++){ // mora da e vo for ciklus
        cin>>day>>month>>year>>sender>>reciver;
        cin.ignore();
        cin.getline(content,150);
        Date date(day,month,year); // za date konstruktor
        messages[i]= SMS (date, content, sender,reciver); // za sms konstruktor so argumenti
    }

    cin>>day>>month>>year;
    Date filter (day,month,year); // noviot datum

    filterMessages(messages,n,filter); // za filtriranje void
    return 0;

}