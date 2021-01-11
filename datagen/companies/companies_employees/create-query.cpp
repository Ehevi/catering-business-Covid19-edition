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
    ifstream c_ids ("company-ids.txt");
    int person_id=51;
    if (c_ids.is_open())
    {
        while ( getline (c_ids, line) && person_id<8500 )
        {
            string str = "INSERT INTO companies_employees(person_id, company_id) VALUES(";
            myfileRESULT << str << person_id << ", " << line << ");\n ";
            person_id++;
        }
        c_ids.close();
        myfileRESULT.close();
    }
  else cout << "Unable to open file";
  return 0;
}