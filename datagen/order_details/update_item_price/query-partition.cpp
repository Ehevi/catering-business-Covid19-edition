#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(){
    ofstream myfilePART1;
    ofstream myfilePART2;
    ofstream myfilePART3;
    ofstream myfilePART4;
    ofstream myfilePART5;
    ofstream myfilePART6;
    ofstream myfilePART7;
    ofstream myfilePART8;
    ofstream myfilePART9;
    ofstream myfilePART10;
    ofstream myfilePART11;
    ofstream myfilePART12;
    ofstream myfilePART13;
    ofstream myfilePART14;
    ofstream myfilePART15;
    ofstream myfilePART16;
    ofstream myfilePART17;
    ofstream myfilePART18;
    ofstream myfilePART19;
    ofstream myfilePART20;
    myfilePART1.open ("part1.sql");
    myfilePART2.open ("part2.sql");
    myfilePART3.open ("part3.sql");
    myfilePART4.open ("part4.sql");
    myfilePART5.open ("part5.sql");
    myfilePART6.open ("part6.sql");
    myfilePART7.open ("part7.sql");
    myfilePART8.open ("part8.sql");
    myfilePART9.open ("part9.sql");
    myfilePART10.open ("part10.sql");
    myfilePART11.open ("part11.sql");
    myfilePART12.open ("part12.sql");
    myfilePART13.open ("part13.sql");
    myfilePART14.open ("part14.sql");
    myfilePART15.open ("part15.sql");
    myfilePART16.open ("part16.sql");
    myfilePART17.open ("part17.sql");
    myfilePART18.open ("part18.sql");
    myfilePART19.open ("part19.sql");
    myfilePART20.open ("part20.sql");
    
    string line;
    ifstream from ("result.sql");
    
    int no=1;
    while(no<50000){
        getline(from, line);
        myfilePART1 << line <<"\n";
        no++;
    }
    
    no=1;
    while(no<50000){
        getline(from, line);
        myfilePART2 << line <<"\n";
        no++;
    }

    no=1;
    while(no<50000){
        getline(from, line);
        myfilePART3 << line <<"\n";
        no++;
    }

    no=1;
    while(no<50000){
        getline(from, line);
        myfilePART4 << line <<"\n";
        no++;
    }

    no=1;
    while(no<50000){
        getline(from, line);
        myfilePART5 << line <<"\n";
        no++;
    }

    no=1;
    while(no<50000){
        getline(from, line);
        myfilePART6 << line <<"\n";
        no++;
    }

    no=1;
    while(no<50000){
        getline(from, line);
        myfilePART7 << line <<"\n";
        no++;
    }

    no=1;
    while(no<50000){
        getline(from, line);
        myfilePART8 << line <<"\n";
        no++;
    }

    no=1;
    while(no<50000){
        getline(from, line);
        myfilePART9 << line <<"\n";
        no++;
    }

    no=1;
    while(no<50000){
        getline(from, line);
        myfilePART10 << line <<"\n";
        no++;
    }

    no=1;
    while(no<50000){
        getline(from, line);
        myfilePART11 << line <<"\n";
        no++;
    }

    no=1;
    while(no<50000){
        getline(from, line);
        myfilePART12 << line <<"\n";
        no++;
    }

    no=1;
    while(no<50000){
        getline(from, line);
        myfilePART13 << line <<"\n";
        no++;
    }

    no=1;
    while(no<50000){
        getline(from, line);
        myfilePART14 << line <<"\n";
        no++;
    }

    no=1;
    while(no<50000){
        getline(from, line);
        myfilePART15 << line <<"\n";
        no++;
    }

    no=1;
    while(no<50000){
        getline(from, line);
        myfilePART16 << line <<"\n";
        no++;
    }

    no=1;
    while(no<50000){
        getline(from, line);
        myfilePART17 << line <<"\n";
        no++;
    }

    no=1;
    while(no<50000){
        getline(from, line);
        myfilePART18 << line <<"\n";
        no++;
    }

    no=1;
    while(no<50000){
        getline(from, line);
        myfilePART19 << line <<"\n";
        no++;
    }

    no=1;
    while(no<50000){
        getline(from, line);
        myfilePART20 << line <<"\n";
        no++;
    }

    myfilePART1.close();
    myfilePART2.close();
    myfilePART3.close();
    myfilePART4.close();
    myfilePART5.close();
    myfilePART6.close();
    myfilePART7.close();
    myfilePART8.close();
    myfilePART9.close();
    myfilePART10.close();
    myfilePART11.close();
    myfilePART12.close();
    myfilePART13.close();
    myfilePART14.close();
    myfilePART15.close();
    myfilePART16.close();
    myfilePART17.close();
    myfilePART18.close();
    myfilePART19.close();
    myfilePART20.close();
    from.close();
    return 0;
}