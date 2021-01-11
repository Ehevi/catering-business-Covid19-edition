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
    for(int i=0; i<6; i++)
    {result += getRandDigit();}
    return result;
}

int main(){
    
    ofstream fileResult;
    fileResult.open ("foreign-result.sql");
    string line;
    ifstream fileFrom ("foreign-street-names.txt");
    int number;
    int city_id = 42;
    if (fileFrom.is_open())
    {
        while ( getline (fileFrom,line) )
        {
            if(city_id>356){city_id=42;}
            number = (rand() % 100 ) + 7;
            fileResult << "INSERT INTO address(street, postal_code, city_id) values('";
            fileResult << line << " " << number << "', '" << getPostalCode() << "', " << city_id << ");\n";
            city_id++;
        }
        fileFrom.close();
        fileResult.close();
    }
    else cout << "Unable to open file";
    return 0;
}