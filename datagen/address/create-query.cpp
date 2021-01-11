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

string getPostalCode(){
    string result="";
    result += getRandDigit();
    result += getRandDigit();
    result += "-";
    for(int i=0; i<3; i++)
    {result += getRandDigit();}
    return result;
}

int main(){
    
    ofstream fileResult;
    fileResult.open ("result.sql");
    string line;
    ifstream fileFrom ("polish-street-names.txt");
    int number;
    int city_id = 2;
    if (fileFrom.is_open())
    {
        while ( getline (fileFrom,line) )
        {
            if(city_id>41){city_id=2;}
            number = (rand() % 100 ) + 7;
            fileResult << "INSERT INTO address(street, postal_code, city_id) values('";
            fileResult << line << number << "', '" << getPostalCode() << "', " << city_id << ");\n";
            city_id++;
        }
        fileFrom.close();
        fileResult.close();
    }
    else cout << "Unable to open file";
    return 0;
}