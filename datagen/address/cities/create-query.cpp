#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(){
    
    ofstream fileResult;
    fileResult.open ("cities-result.sql");
    string line;
    ifstream fileFrom ("cities.txt");
    int number;
    int country_id = 2;
    if (fileFrom.is_open())
    {
        while ( getline (fileFrom,line) )
        {
            if(country_id>27){country_id=2;}
            fileResult << "INSERT INTO cities(city_name, country_id) values('";
            fileResult << line << "', " << country_id << ");\n";
            country_id++;
        }
        fileFrom.close();
        fileResult.close();
    }
    else cout << "Unable to open file";
    return 0;
}