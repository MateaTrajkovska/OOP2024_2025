//
// Created by Matea Trajkovska on 10.4.25.
//
#include <iostream>
#include<cstring>
#include<iomanip>
using namespace std;

class Book{
private:
    char title[100];
    char author[50];
    int pages;
public:
    Book(){}

    Book(char *title, char *author, int pages){
        strcpy(this->title,title);
        strcpy(this->author,author);
        this->pages=pages;
    }
    void print(){
        cout << title << " by " << author << " (" << pages << " pages)" << endl;
    }

    int getPages() const {
        return pages;
    }
};

void printBooks(Book books[], int n, int minPages) {
    bool found = false;
    cout << "Books with more than " << minPages << " pages:" << endl;
    for (int i = 0; i < n; i++) {
        if (books[i].getPages() > minPages) {
            books[i].print();
            found = true;
        }
    }
    if (!found) {
        cout << "No books with more than " << minPages << " pages." << endl;
    }
}

int main(){
    int n;
    cin>>n;
    char title[100];
    char author[50];
    int pages;

    Book books[100];

    for(int i=0;i<n;i++){
        cin.ignore();
        cin.getline(title,100);
        cin>>author>>pages;
        books[i]=Book (title,author,pages);
    }

    int minPages;
    cin>>minPages;

    printBooks(books,n,minPages);

    return 0;
}