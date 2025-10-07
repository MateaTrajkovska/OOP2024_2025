//
// Created by Matea Trajkovska on 25.1.25.
//
#include <iostream>
#include <cstring>

using namespace std;

class ExistingGame{
private:
    char msg[256];

public:
    ExistingGame(char msg_txt[]){
        strncpy(this->msg, msg_txt, 255);
        this->msg[255] = '\0';
    }

    void message(){
        std::cout<<this->msg<<std::endl;
    }
};

class Game {

protected:
    char name[100];
    float price;
    bool on_sale;
public:
    Game(){
        name[0] = '\0';
    }
    Game(char *n, float p, bool s=false){
        strncpy(name, n, 99);
        this->name[99] = '\0';

        price = p;

        on_sale = s;
    }

    virtual float get_price(){
        if (on_sale){
            return price * 0.3F;
        }

        return price;
    }

    bool operator==(Game& g){
        return !strcmp(this->name, g.name);
    }

    friend ostream & operator<<(ostream & o, const Game& g);
    friend istream & operator>>(istream & i, Game& g);
};

class SubscriptionGame : public Game {
protected:
    float monthly_fee;
    int month, year;

public:
    SubscriptionGame(){
        name[0] = '\0';
    }

    SubscriptionGame(char *n, float p, bool s, float mf, int m, int y):
            Game(n, p, s),
            monthly_fee(mf),
            month(m),
            year(y) { }

    float get_price(){
        float price = Game::get_price();

        int months=0;
        if (year<2018){
            months = (12 - this->month) + (2017 - year)*12 + 5;
        }
        else {
            months = 5 - this->month;
        }

        price += months * monthly_fee;

        return price;
    }

    friend ostream & operator<<(ostream & o, SubscriptionGame& sg);
    friend istream & operator>>(istream & i, SubscriptionGame& g);

};

ostream & operator<<(ostream & o, const Game& g) {
    o<<"Game: "<< g.name <<", regular price: $" << g.price;

    if (g.on_sale){
        o<<", bought on sale";
    }
    return o;
}

ostream & operator<<(ostream & o, SubscriptionGame& sg) {

    Game * tmp = dynamic_cast<Game*>(&sg);

    o << *tmp;

    o<<", monthly fee: $"<< sg.monthly_fee
     <<", purchased: "<< sg.month << "-" << sg.year<<std::endl;

    return o;
}

istream & operator>>(istream & is, Game &g){

    is.get();
    is.getline(g.name,100);
    is>>g.price>>g.on_sale;

    return is;
}

istream & operator>>(istream & is, SubscriptionGame &g){
    is.get();
    is.getline(g.name,100);
    is>>g.price>>g.on_sale;
    is>>g.monthly_fee >> g.month >> g.year;
    return is;
}

class User {
private:
    void obj_copy(const User * orig, User * cpy){
        strcpy(cpy->username, orig->username);
        cpy->num_games = orig->num_games;

        cpy->games = new Game*[cpy->num_games];

        for (int i=0; i< cpy->num_games; ++i){
            cpy->games[i] = new Game(*(orig->games[i]));
        }
    }

protected:
    char username[100];
    Game ** games;
    int num_games;
public:
    User (char const * const un="") {
        strncpy(this->username, un, 99);
        this->username[99] = '\0';
        games = 0;
        num_games = 0;
    }

    User (const User& orig){
        obj_copy(&orig,this);
    }

    ~User(){
        for (int i=0; i < this->num_games; ++i){
            delete this->games[i];
        }
        delete [] games;
    }

    User& operator=(User & orig){
        if (&orig != this){

            for (int i=0; i < this->num_games; ++i){
                delete orig.games[i];
            }

            delete [] orig.games;

            obj_copy(&orig, this);
        }
        return *this;
    }

    User& operator+=(Game&g){

        Game ** new_games = new Game*[this->num_games+1];

        for (int i=0; i < (this->num_games); ++i) {
            if ( (*(this->games[i])) == g){
                throw ExistingGame("The game is already in the collection");
            }

            new_games[i] = games[i];
        }

        for (int i=0; i < (this->num_games); ++i) {
            new_games[i] = games[i];
        }

        SubscriptionGame * sg = dynamic_cast< SubscriptionGame* >(&g);

        if(sg){

            new_games[num_games] = new SubscriptionGame(*sg);
        }
        else {
            //cout<<"Game"<<endl;
            new_games[num_games] = new Game(g);
        }

        delete [] this->games;
        this->games = new_games;
        this->num_games++;

        return *this;
    }


    Game& get_game(int i){
        return (*(this->games[i]));
    }

    float total_spent(){
        float sum = 0.0f;
        for (int i=0; i<this->num_games; ++i){
            sum += games[i]->get_price();
        }
        return sum;
    }

    char const * const get_username(){
        return this->username;
    }

    int get_games_number(){
        return this->num_games;
    }

};

ostream & operator<<(ostream & o, User& u) {

    o<<"\nUser: "<<u.get_username()<<"\n";

    for (int i=0; i < u.get_games_number(); ++i){
        Game * g;
        SubscriptionGame * sg;
        g = &(u.get_game(i));

        sg = dynamic_cast<SubscriptionGame *> (g);

        if (sg){
            cout<<"- "<<(*sg);
        }
        else {
            cout<<"- "<<(*g);
        }
        cout<<"\n";
    }
    return o;
}