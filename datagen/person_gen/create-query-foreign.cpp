#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// address_ids: od 323 do 53102
// ( std::rand() % 50 ) + 7; == przedział od 7 do 56
// przedział od 1 do 9 ==> (rand() %9)+1
// cyfra losowa ==> (rand() % 10)
string getRandDigit(){
    string result="";
    int number;
    number = (rand() % 10 ); //losowa cyfra
    return to_string(number);
}

string getRandPhone(){
    string result="";
    for(int i=0; i<10; i++){
        result+=getRandDigit();
    }
    return result;
}
int main(){
    srand( time( NULL ) );
    ofstream myfileRESULT;
    myfileRESULT.open ("result-foreign-names.sql");
    string line;
    ifstream name ("names.txt");
    ifstream surname ("surnames.txt");
    string email;
    int number;
    int address_id=5319;
    if (name.is_open())
    {
        while ( getline (name, line) )
        {
            if(address_id>11407){break;}
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