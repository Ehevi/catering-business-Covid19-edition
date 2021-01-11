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
    ifstream c_ids ("customer-ids.txt");
    ifstream p_ids ("person-ids.txt");
    if (c_ids.is_open() && p_ids.is_open() )
    {
        while ( getline (p_ids, line) )
        {
            string str = "INSERT INTO individual(person_id, customer_id) VALUES(";
            myfileRESULT << str << line << ", ";
            getline(c_ids, line);
            myfileRESULT << line << ");\n ";
        }
        p_ids.close();
        c_ids.close();
        myfileRESULT.close();
    }
  else cout << "Unable to open file";
  return 0;
}