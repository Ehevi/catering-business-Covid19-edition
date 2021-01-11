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
string getAddressId(){
    int number=(rand()% 52700)+323;
    return to_string(number);
}


int main(){
    srand( time( NULL ) );
    ofstream myfileRESULT;
    myfileRESULT.open ("polish-male-names-insert.txt");
    string line;
    ifstream name ("polish_female_firstnames.txt");
    ifstream surname ("polish_surnames.txt");
    ifstream phone ("phones.txt");
    string email;
    int number;
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
            getline(phone, line);
            myfileRESULT << line <<"', " << getAddressId() << ");\n";
        }
        name.close();
        surname.close();
        phone.close();
        myfileRESULT.close();
    }

  else cout << "Unable to open file";
  return 0;
}