#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

/* wspisze do pliku result.sql polecenia sql tworzące id klientów: od 1 do 100000 */
/* dla każdego wiersza wklejono osobne polecenie INSERT, ponieważ w jednorazowym poleceniu można wpisać tylko do 1000 wartości */

int main(){
    ofstream fileResult;
    fileResult.open ("result.sql");
    string str = "INSERT INTO customers(customer_id) VALUES('";
    for(int i=1; i<=100000; i++){
        fileResult << str << i << "');\n";
    }
    fileResult.close();
    return 0;
}