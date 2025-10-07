//
// Created by Matea Trajkovska on 10.4.25.
//
#include <iostream>
#include <cstring>
using namespace std;

enum Genre{
    ACTION,
    DRAMA
};

class Movie{
private:
    char title[50];
    int id;
    Genre genre;
    float price;
    static int objects;
public:
    Movie(){}

    Movie(char title[50],int genre, float price){
        strcpy(this->title,title);
        this->genre= (Genre) genre;
        this->price=price;
        this->id=100000 + objects;
        objects++;
    }

    static void setObjects(int ob){
        objects=ob;
    }

    char getGenre(){
        return genre;
    }

    const char *const getTitle() const {
        return title;
    }

    void print(){
        cout<<id<<" - "<<title<<" ";
        if(genre == ACTION){
            cout<<"action"<<" ";
        }
        else if(genre == DRAMA){
            cout<<"drama"<<" ";
        }
        cout<<price<<endl;
    }

    void increaseTicketPrice(float sum){
        price+=sum;
    }
    float getPrice(){
        return price;
    }
};

class Cinema{
private:
    char name[50];
    Movie niza[100];
    int n;
public:
    Cinema(){}

    Cinema(char *name){
        strcpy(this->name,name);
        this-> n =0;
    }

    void print(){
        cout<<name<<" ";
        for(int i=0;i<n;i++){
            niza[i].print();
        }
    }

    void addMovie(const Movie &m){
        if(n==100){
            return;
        }
        for(int i=0;i<n;i++){
            if(strcmp(niza[i].getTitle(),m.getTitle())==0){
                return;
            }
        }

        niza[n]=m;
        n++;
    }

    bool moreMoviesThan (const Cinema &c){
        return this->n > c.n;
    }

    void applyGenreDiscount(){
        for(int i=0;i<n;i++){
            if(niza[i].getGenre() == ACTION){
                niza[i].increaseTicketPrice(niza[i].getPrice()*0.1);
            }
            else if(niza[i].getGenre() == DRAMA){
                niza[i].increaseTicketPrice(niza[i].getPrice()*0.05);
            }
        }
    }

    int getNumber(){
        return n;
    };
};

Cinema bestCinema(Cinema cinemas[], int n){
    int maxI =0;
    for(int i=0;i<n;i++){
        if(cinemas[i].getNumber()>cinemas[maxI].getNumber()){
            maxI=i;
        }
    }

    return cinemas[maxI];
}


int Movie :: objects = 0;

int main() {
    int testCase;
    cin >> testCase;

    if(testCase == 0) {
        cout << "TESTING MOVIE CONSTRUCTOR" << endl;
        Movie m1("Avengers", 0, 350.0);
        Movie m2("Titanic", 1, 300.0);
        Movie m3("John Wick", 0, 400.0);
        cout << "TEST PASSED" << endl;
    }
    else if(testCase == 1) {
        cout << "TESTING MOVIE print()" << endl;
        Movie m1("Avengers", 0, 350.0);
        m1.print();
        cout << "TEST PASSED" << endl;
    }
    else if(testCase == 2) {
        cout << "TESTING increaseTicketPrice()" << endl;
        Movie m1("Avengers", 0, 350.0);
        m1.increaseTicketPrice(50.0);
        m1.print();
        cout << "TEST PASSED" << endl;
    }
    else if(testCase == 3) {
        cout << "TESTING CINEMA constructor" << endl;
        Cinema c1("Cineplexx");
        c1.print();
        cout << "TEST PASSED" << endl;
    }
    else if(testCase == 4) {
        cout << "TESTING addMovie and print()" << endl;
        Cinema c1("Cineplexx");
        Movie m1("Avengers", 0, 350.0);
        Movie m2("Titanic", 1, 300.0);
        c1.addMovie(m1);
        c1.addMovie(m2);
        c1.print();
        cout << "TEST PASSED" << endl;
    }
    else if(testCase == 5) {
        cout << "TESTING applyGenreDiscount()" << endl;
        Cinema c1("Cineplexx");
        c1.addMovie(Movie("Avengers", 0, 350.0));
        c1.addMovie(Movie("Titanic", 1, 300.0));
        cout << "BEFORE DISCOUNT:" << endl;
        c1.print();
        c1.applyGenreDiscount();
        cout << "AFTER DISCOUNT:" << endl;
        c1.print();
        cout << "TEST PASSED" << endl;
    }
    else if(testCase == 6) {
        cout << "TESTING bestCinema()" << endl;
        int n;
        cin >> n;
        Cinema cinemas[10];
        for(int i = 0; i < n; ++i) {
            char name[30];
            cin.ignore();
            cin.getline(name, 30);
            cinemas[i] = Cinema(name);
            int movieCount;
            cin >> movieCount;
            for(int j = 0; j < movieCount; ++j) {
                char title[50];
                int genre;
                float price;
                cin >> title >> genre >> price;
                Movie m(title, genre, price);
                cinemas[i].addMovie(m);
            }
        }
        bestCinema(cinemas, n).print();
    }

    return 0;
}
