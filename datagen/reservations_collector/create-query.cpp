#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(){
    ofstream fileResult;
    fileResult.open ("result.sql");
    ifstream person ("person_ids.txt");
    ifstream res ("reservation-ids.txt");
    string line;
    string str = "INSERT INTO reservations_collector(reservation_id, person_id) VALUES(";
    if (person.is_open() && res.is_open()){
        while(getline(res, line)){
            fileResult << str << line << ", ";
            getline(person, line);
            fileResult << line << ");\n";
        }
    } else cout<<"Unable to open a file!\n";
    fileResult.close();
    return 0;
}