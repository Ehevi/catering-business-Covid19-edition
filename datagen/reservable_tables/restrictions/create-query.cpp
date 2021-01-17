#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int get50percent(int number){
    return number/2;
}

int main(){
    srand( time( NULL ) );
    ofstream myfileRESULT;
    myfileRESULT.open ("result.sql");
    string line;
    ifstream max_seats_no ("max-seats-no.txt");
    string str = "INSERT INTO reservable_tables(table_id, seats_no, since_date, due_date) VALUES(";
    int table_id = 1; // numery stolików w tabeli tables: od 1 do 30
    if (max_seats_no.is_open())
    {
        while(table_id<31){
            getline(max_seats_no, line);
            if(get50percent(stoi(line))>0){
              myfileRESULT << str << table_id << ", " << get50percent(stoi(line)) << ", DATEFROMPARTS(2020, 10, 2), DATEFROMPARTS(2020, 10, 23));\n";
            // od 10. lutego 2020 do 23. października: 50% miejsc
            // od 24. października do teraz: 0 (tylko na wynos) --- czyli nie ma wpisów w tabeli reservable_tables, bo nie można rezerwować stolików  
            }
            table_id++;
        }
        max_seats_no.close();
        myfileRESULT.close();
    }
    else cout << "Unable to open file";
    return 0;
}