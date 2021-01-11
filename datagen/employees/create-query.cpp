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
    string str = "INSERT INTO employees(person_id) VALUES('";
    for(int i=2; i<=50; i++){
        fileResult << str << i << "');\n";
    }
    fileResult.close();
    return 0;
}