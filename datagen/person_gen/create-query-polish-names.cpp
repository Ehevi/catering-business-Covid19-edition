#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

string getRandDigit(){
    string result="";
    int number;
    number = (rand() % 10 ); //losowa cyfra
    return to_string(number);
}

string getRandPhone(){
    string result="";
    for(int i=0; i<9; i++){
        result+=getRandDigit();
    }
    return result;
}

int main(){
    srand( time( NULL ) );
    ofstream myfileRESULT;
    myfileRESULT.open ("result-polish-names.sql");
    string line;
    ifstream name ("polish-firstnames.txt");
    ifstream surname ("polish-surnames.txt");
    int number;
    int address_id=0;
    string email;
    if (name.is_open())
    {
        while ( getline (name, line) )
        {
            string str = "INSERT INTO person(first_name, last_name, email, phone, address_id) VALUES('";
            email=tolower(line[0]);
            int dl = line.length();
            for(int i=1; i<dl; i++){
                if(line[i])
                email+=line[i];
            }
            myfileRESULT << str << line << "', '";
            getline(surname, line);
            myfileRESULT << line << "', '";
            myfileRESULT << email << rand() <<"@randmail.com', '";
            myfileRESULT << getRandPhone() <<"', " << address_id << ");\n";
            address_id++;
        }
        name.close();
        surname.close();
        myfileRESULT.close();
    }

  else cout << "Unable to open file";
  return 0;
}