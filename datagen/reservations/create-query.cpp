#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

struct date{
    int year;
    int month;
    int day;
};

int numberOfDays (int monthNumber, int year) 
{ 
    // Styczeń
    if (monthNumber == 1) 
        return (31); 
  
    // Luty
    if (monthNumber == 2) 
    { 
        // jeśli rok jest przestępny, to luty ma 29 dni
        if (year % 400 == 0 || 
                (year % 4 == 0 && year % 100 != 0)) 
            return (29); 
        else
            return (28); 
    } 
  
    // Marzec 
    if (monthNumber == 3) 
        return (31); 
  
    // Kwiecień
    if (monthNumber == 4) 
        return (30); 
  
    // Maj
    if (monthNumber == 5) 
        return (31); 
  
    // Czerwiec
    if (monthNumber == 6) 
        return (30); 
  
    // Lipiec
    if (monthNumber == 7) 
        return (31); 
  
    // Sierpień
    if (monthNumber == 8) 
        return (31); 
  
    // Wrzesień
    if (monthNumber == 9) 
        return (30); 
  
    // Październik
    if (monthNumber == 10) 
        return (31); 
  
    // Listopad
    if (monthNumber == 11) 
        return (30); 
  
    // Grudzień
    if (monthNumber == 12) 
        return (31); 
}

date twoWeeksLater(date from){
    date result;
    if (from.day + 13 <= numberOfDays(from.month, from.year)) {
        result.day = from.day + 13;
        result.month = from.month;
        result.year = from.year;
    }
    else if (from.month != 12){
        result.day = from.day + 13 - numberOfDays(from.month, from.year);
        result.month = from.month + 1;
        result.year = from.year;
    }
    else {
        result.day = from.day + 13 - 31;
        result.month = 1;
        result.year = from.year + 1;
    }
    return result;
}

date nextDay(date from){
    date result;
    if (from.day + 1 <= numberOfDays(from.month, from.year)) {
        result.day = from.day + 1;
        result.month = from.month;
        result.year = from.year;
    }
    else if (from.month != 12){
        result.day = from.day + 1 - numberOfDays(from.month, from.year);
        result.month = from.month + 1;
        result.year = from.year;
    }
    else {
        result.day = from.day + 1 - 31;
        result.month = 1;
        result.year = from.year + 1;
    }
    return result;
}

// order_ids: od 1 do 667800
// order ids od początku do 09.02.2020: od 1 do 462000

// 30 pierwszych wierszy z reservable_tables: stoliki do rezerwacji przed restrykcjami epidemicznymi

int main(){
    ofstream fileResult;
    date printdate;
    printdate.day = 1;
    printdate.month = 1;
    printdate.year = 2018;
    fileResult.open ("result.sql");
    ifstream customers ("customer-ids.txt");
    ifstream orderDates ("order-dates.txt");
    ifstream collectionDates ("collection-dates.txt");
    string line;
    string ordLine;
    string colLine;
    int order_id = 1;
    int table_id = 1;
    string temp;
    string hour="";
    string str = "INSERT INTO reservations(customer_id, table_id, date_start_time, date_end_time, is_accepted) VALUES(";
    if (customers.is_open() && orderDates.is_open() && collectionDates.is_open()){
        while(order_id<462001){
            if(table_id>30){table_id=1;}
            for(int i=0; i<100; i++){
                getline(customers, line);
                getline(orderDates, ordLine);
                getline(collectionDates, colLine);
                order_id++;
            } // co 100 zamówienie ma przypisaną rezerwację
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