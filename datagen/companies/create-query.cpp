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

string getRandNIP(){
    string result="";
    for(int i=0; i<10; i++){
        result+=getRandDigit();
    }
    return result;
}

int main(){
    srand( time( NULL ) );
    ofstream myfileRESULT;
    myfileRESULT.open ("companies-result.sql");
    string line;
    ifstream name ("company-names.txt");
    ifstream address ("company-addresses.txt");
    string email;
    char space = ' ';
    int number;
    int customer_id=1;
    if (name.is_open())
    {
        while ( getline (name, line) )
        {
            string str = "INSERT INTO companies(customer_id, company_name, address_id, phone, email, NIP) VALUES(";
            email=tolower(line[0]);
            int dl = line.length();
            for(int i=1; i<dl; i++){
                if(line[i] && line[i] != space && line[i] != '&')
                email+=tolower(line[i]);
            }
            myfileRESULT << str << customer_id << ", '" << line << "', ";
            getline(address, line);
            myfileRESULT << line << ", '";
            myfileRESULT << getRandPhone() << "', '" <<email << rand() <<"@randmail.com', '";
            myfileRESULT << getRandNIP() << "');\n";
            customer_id++;
        }
        name.close();
        address.close();
        myfileRESULT.close();
    }

  else cout << "Unable to open file";
  return 0;
}