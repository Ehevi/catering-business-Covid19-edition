#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int getRandItem(){
    int number = (rand() % 156 );
    return number;
    // plik items.txt ma 156 linii
}

int getRandQuantity(){
    int number = (rand()%100);
    if(number<30) return 1;
    if(number<45) return 2;
    if(number<55) return 3;
    if(number<63) return 4;
    if(number<70) return 5;
    if(number<74) return 6;
    if(number<79) return 7;
    if(number<83) return 8;
    if(number<90) return 9;
    if(number<92) return 10;
    if(number<94) return 11;
    if(number<96) return 12;
    if(number<98) return 13;
    return 17;
}

// order_id dla menu_id:1 => od 1 do 8400 włącznie, 1 już zostało wpisane ręcznie

int main(){
    srand( time( NULL ) );
    ofstream myfileRESULT;
    myfileRESULT.open ("result.sql");
    string line;
    ifstream items ("items.txt");
    string str = "INSERT INTO order_details(order_id, item_id, item_price, item_quantity) VALUES(";
    if (items.is_open())
    {
        int order_id=33601;
        while(order_id<42001){
           for(int counter=0; counter<getRandQuantity(); counter++){
                myfileRESULT << str << order_id <<", ";
                for(int i=0; i<getRandItem(); i++){
                    getline(items, line);
                    if(line == "645"){
                        items.clear();
                        items.seekg (0, ios::beg);
                    } // 645 to ostatnia linia pliku, trzeba wrócić na początek
                }
                myfileRESULT << line << ", 1, " << getRandQuantity() << ");\n";
            }
            order_id++;
        }
        items.close();
        myfileRESULT.close();
    }
    else cout << "Unable to open file";
    return 0;
}