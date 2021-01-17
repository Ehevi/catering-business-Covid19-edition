#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

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
            myfileRESULT << str << table_id << ", " << line << ", DATEFROMPARTS(2018, 1, 1), DATEFROMPARTS(2020, 2, 9));\n";
            // od początku (2018) do 9. lutego 2020 wszystkie stoliki można rezerwować z maksymalną dostępną liczbą miejsc
            table_id++;
        }
        max_seats_no.close();
        myfileRESULT.close();
    }
    else cout << "Unable to open file";
    return 0;
}