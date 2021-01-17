#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// order_ids: od 1 do 667800
// order ids od 10.02.2020 do października 2020: 462001 do 667800

// 30 pierwszych wierszy z reservable_tables: stoliki do rezerwacji przed restrykcjami epidemicznymi
// restrykcje: kolejne stoliki od 31 do 59

int main(){
    ofstream fileResult;
    fileResult.open ("result.sql");
    ifstream customers ("customer-ids.txt");
    ifstream orderDates ("order-dates.txt");
    ifstream collectionDates ("collection-dates.txt");
    string line;
    string ordLine;
    string colLine;
    int order_id = 462001;
    int table_id = 31;
    string temp;
    string hour="";
    string str = "INSERT INTO reservations(customer_id, table_id, date_start_time, date_end_time, is_accepted) VALUES(";
    if (customers.is_open() && orderDates.is_open() && collectionDates.is_open()){
        while(order_id<667801){
            if(table_id>59){table_id=31;}
            for(int i=0; i<500; i++){
                getline(customers, line);
                getline(orderDates, ordLine);
                getline(collectionDates, colLine);
                order_id++;
            } // przy restrykcjach co 500 zamówienie ma przypisaną rezerwację
            temp = colLine;
            colLine = "";
            hour = "";
            for(int i=0; i<11; i++){
                colLine += temp[i];
            }
            hour += temp[11];
            hour += temp[12];
            int hourLater = stoi(hour) + 2; // zakładamy, że rezerwacja kończy się dwie godziny po odbiorze zamówienia
            colLine += to_string(hourLater);
            colLine += ":00:00.000";
            fileResult << str << line << ", " << table_id << ", '" << ordLine << "', '" << colLine << "', 1);\n";
            order_id++;
            table_id++;
        }
        customers.close();
        orderDates.close();
        collectionDates.close();
    } else cout<<"Unable to open a file!\n";
    fileResult.close();
    return 0;
}