#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// rezerwacje: id od 1 do 4575 włącznie

int main(){
    ofstream fileResult;
    fileResult.open ("result.sql");
    ifstream orders ("orders.txt");
    int res_id=1;
    string line;
    string str = "INSERT INTO reservations_orders(reservation_id, order_id) VALUES(";
    if (orders.is_open()){
        while(res_id<4576){
            getline(orders, line);
            fileResult << str << res_id << ", " << line << ");\n";
            res_id++;
        }
        orders.close();
    } else cout<<"Unable to open a file!\n";
    fileResult.close();
    return 0;
}