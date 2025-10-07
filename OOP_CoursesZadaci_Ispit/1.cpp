#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class Book{
protected:
    char isbn[20];
    char title[50];
    char author[30];
    double price;
public:
    Book(){}

    Book(const char *isbn, const char *title,const char *author,double price){
        strcpy(this->isbn,isbn);
        strcpy(this->title,title);
        strcpy(this->author,author);
        this->price=price;
    }

    virtual double bookPrice()=0;
    virtual ~Book(){}

    void setISBN(char *isbn){
        strcpy(this->isbn,isbn);
    }

    friend ostream & operator <<(ostream &out, Book &b){
        out<< b.isbn << ": " << b.title << ", " << b.author << " " << b.bookPrice() << endl;
        return out;
    }

};

bool operator > ( Book & b1,  Book &b2){
    return (b1.bookPrice()> b2.bookPrice());
}


class OnlineBook : public Book{
private:
    char *url;
    int n; //golemina MB
public:
    OnlineBook(const char *isbn,const char *title,const char *author,double price,const char *url,int n) : Book(isbn,title,author,price){
        this->n=n;
        this->url = new char[strlen(url) + 1];
        strcpy(this->url, url);
    }

    OnlineBook(const OnlineBook &ob){
        strcpy(this->isbn,ob.isbn);
        strcpy(this->title,ob.title);
        strcpy(this->author,ob.author);
        this->price=ob.price;
        this->url = new char[strlen(url) + 1];
        strcpy(this->url,ob.url);
        this->n=ob.n;
    }

    OnlineBook & operator =(const OnlineBook &ob){
        if(this!=&ob){
            strcpy(this->isbn,ob.isbn);
            strcpy(this->title,ob.title);
            strcpy(this->author,ob.author);
            this->price=ob.price;
            this->url = new char[strlen(url) + 1];
            strcpy(this->url,ob.url);
            this->n=ob.n;
        }
        return *this;
    }

    ~OnlineBook(){
        delete[]url;
    }

    virtual double bookPrice() override{
        double price= Book :: price;
        if(n>20){
            price*=1.20;
        }
        return price;
    }
};

class PrintBook : public Book{
private:
    float weight;
    bool inStock;
public:
    PrintBook(const char *isbn,const char *title,const char *author,double price,float weight,bool inStock):Book(isbn,title,author,price){
        this->weight=weight;
        this->inStock=inStock;
    }

    virtual double bookPrice() override{
        double price= Book :: price;
        if(weight>0.7){
            price*=1.15;
        }
        return price;
    }
};

void mostExpensiveBook(Book** books, int n)
{
    int obNo = 0;
    int pbNo = 0;

    for (int i = 0; i<n; i++)
    {
        OnlineBook* ob = dynamic_cast<OnlineBook*>(books[i]);
        if (ob != 0)
            obNo++;
        PrintBook* pb = dynamic_cast<PrintBook*>(books[i]);
        if (pb != 0)
            pbNo++;
    }
    cout << "FINKI-Education" << endl;
    cout << "Total number of online books: " << obNo << endl;
    cout << "Total number of print books: " << pbNo << endl;

    Book* max = books[0];
    for (int i = 1; i<n; i++)
        if (*books[i] > *max)
            max = books[i];

    cout << "The most expensive book is: " << endl;
    cout << *max;
}

int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3){
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4){
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i<n; i++) delete books[i];
    delete[] books;
    return 0;
}
