#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(){
    ofstream fileResult;
    fileResult.open ("result.sql");
    string line;
    ifstream fileFrom ("file.txt");
    if (fileFrom.is_open())
    {
        while ( getline (fileFrom,line) )
        {
            fileResult << "INSERT INTO tables(max_seats_no) values(";
            fileResult << line << ");\n";
        }
        fileFrom.close();
        fileResult.close();
    }
    else cout << "Unable to open file";
    return 0;
}