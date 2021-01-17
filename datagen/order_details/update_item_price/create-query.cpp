#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(){
    srand( time( NULL ) );
    ofstream myfileRESULT;
    myfileRESULT.open ("result.sql");
    string line;
    ifstream items ("item-ids.txt");
    ifstream prices ("item-prices.txt");
    ifstream orders ("order-ids.txt");
    string str = "UPDATE order_details SET item_price=";
    string temp;
    if (items.is_open() && prices.is_open() && orders.is_open())
    {
        int log_id = 1; // 1178103 linii w każdym z plików txt
        while(log_id<1178104){
            getline(prices, line);
            for(int i=0; i<line.length(); i++){
                if(line[i] == ','){
                    temp = line;
                    line = "";
                    for(int j=0; j<i; j++){
                        line += temp[j];
                    }
                }
            }
            myfileRESULT << str << line <<" WHERE item_id=";
            getline(items, line);
            myfileRESULT << line << " and order_id=";
            getline(orders, line);
            myfileRESULT << line <<";\n";
            log_id++;
        }
        items.close();
        prices.close();
        orders.close();
        myfileRESULT.close();
    }
    else cout << "Unable to open file";
    return 0;
}