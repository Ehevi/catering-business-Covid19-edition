#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

string getRandPrice(){
    string result="";
    int number;
    number = (rand() % 30 ) + 10;
    return to_string(number);
}

int main(){
    srand( time( NULL ) );
    ofstream myfileRESULT;
    myfileRESULT.open ("result.sql");
    string line;
    ifstream i_ids ("item-ids.txt");
    ifstream m_ids ("menu-ids.txt");
    if (i_ids.is_open() && m_ids.is_open())
    {
        while ( getline (m_ids, line) )
        {
            string str = "INSERT INTO menu_details(menu_id, item_id, is_available, item_price) VALUES(";
            myfileRESULT << str << line << ", ";
            getline(i_ids, line);
            myfileRESULT << line << ", 1, " << getRandPrice() << ");\n";
        }
        i_ids.close();
        m_ids.close();
        myfileRESULT.close();
    }

  else cout << "Unable to open file";
  return 0;
}