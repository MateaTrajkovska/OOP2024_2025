//

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

void wtf() {
    ofstream fout("input.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----"){
            break;
        }
        fout << line << endl;
    }
}

void rff(string path) {
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}

class Student {
protected:
    string indeks;
    string ime;
    string prezime;
    int poeni;
public:
    Student(){}
    Student(string &indeks, string &ime, string &prezime,int poeni )
    {
        this->indeks=indeks;
        this->ime=ime;
        this->prezime=prezime;
        this->poeni=poeni;
    }

    int grade(){
        if(poeni<49){
            return 5;
        }if(poeni>=50 && poeni<=59){
            return 6;
        }if(poeni>=60 && poeni<=69){
            return 7;
        } if(poeni>=70 && poeni<=79){
            return 8;
        } if(poeni>=80 && poeni<=89){
            return 9;
        } if(poeni>=90 && poeni<=100){
            return 10;
        }
    }

    friend ostream & operator <<(ostream & out,Student s){
        out<<s.indeks<<" "<<s.ime<<" "<<s.prezime<<" "<<s.poeni<<" Grade: "<<s.grade()<<endl;
        return out;
    }

    int getPoeni() const {
        return poeni;
    }
    const string getIndeks() const{
        return indeks;
    }

};

class StudentFailedException{
private:
    string id;
public:
    StudentFailedException(const string &id){
        this->id=id;
    }

    void message()
    {
        cout<<"Student with id "<<id<<" failed the course"<<endl;
    }
};

class Results{
private:
    Student *studenti;
    int n;
public:
    Results()
    {
        this->n=0;
        this->studenti= new Student[n];
    }

    Results & operator+=(Student &s)
    {
        if(s.getPoeni()<50)
        {
            throw StudentFailedException(s.getIndeks());
        }
        Student *tmp= new Student[n+1];
        for(int i=0;i<n;i++)
        {
            tmp[i]=studenti[i];
        }
        tmp[n++]=s;
        delete[]studenti;
        studenti=tmp;
        return *this;
    }
    friend ostream & operator <<(ostream & out,Results r){
        for(int i=0;i<r.n;i++)
        {
            out<<r.studenti[i];
        }
        return out;
    }

    Results withGrade(int grade){
        Results r;
        for(int i=0;i<n;i++){
            if(studenti[i].grade()==grade)
            {
                r+=studenti[i];
            }
        }
        return r;
    }
    int getSize(){
        return n;
    }
};



int main() {

    wtf();

    Results results;
    //TODO your code here
    //TODO Read the students from the file and add them in `results`
    ifstream ifs("input.txt");
    string indeks,ime,prezime;
    int poeni;

    while(ifs>>indeks>>ime>>prezime>>poeni)
    {
        Student s(indeks,ime,prezime,poeni);
        try{
            results+=s;
        }catch (StudentFailedException & e)
        {
            e.message();
        }
    }
    ifs.close();

    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT
    int grade;
    cin >> grade;
    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT

    //TODO Save the results in the files output1.txt and output2.txt after this line

    ofstream fout1("output1.txt");
    fout1 << results;
    fout1.close();

    ofstream fout2 ("output2.txt");
    if(results.withGrade(grade).getSize()>0){
        fout2<<results.withGrade(grade)<<endl;
    }
    else{
        fout2<<"None";
    }
    fout2.close();

    //DO NOT MODIFY THE CODE BELLOW

    cout << "All students:" << endl;
    rff("output1.txt");
    cout << "Grade report for grade " << grade << ": " << endl;
    rff("output2.txt");



    return 0;
}