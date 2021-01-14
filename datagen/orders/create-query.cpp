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

int getSeconds(){
    int result = (rand()% 60);
    return result;
}

int getEmployeeId(int log_id){
    int result=(log_id%50)+1; //czyli zakres 1 do 50
    while(result==50 || result==46){
        result=(rand()%50)+1;
    }
    // bo id pracowników to od 1 do 45, potem 47, 48, 49
    return result;
}

struct myTime{
    int hour;
    int minute;
};

myTime minuteLater(myTime from){
    myTime result;
    if (from.minute == 59){
        result.minute = 0;
        result.hour = from.hour + 1;
    } else {
        result.minute = from.minute + 1;
        result.hour = from.hour;
    }
    return result;
}

myTime fiveMinutesLater(myTime from){
    myTime result;
    if (from.minute > 54){
        result.minute = from.minute - 55;
        result.hour = from.hour + 1;
    } else {
        result.minute = from.minute + 5;
        result.hour = from.hour;
    }
    return result;
}

myTime randMoreWait(myTime from){
    int result = (rand()% 5);
    for(int i=0; i<result; i++){
        from = minuteLater(from);
    }
    return from;
}

myTime randWait(myTime from){
    int waitTime = (rand()%4) + 1; // 1, 2, 3 lub 4
    for(int i=0; i<waitTime; i++){
        from = fiveMinutesLater(from);
    }
    randMoreWait(from);
    return from;
}

int getStatus(int log_id){
    if(log_id%500 == 0){
        return 5;
    } // co 500 zamówienie anulowane
    return 4; // pozostałe w stanie zapłacone && odebrane
}

int main(){
    ofstream fileResult;
    ifstream c_ids ("customer-ids.txt");
    string line;
    date printdate;
    myTime printTime;
    printdate.day = 1;
    printdate.month = 1;
    printdate.year = 2018;
    fileResult.open ("result.sql");
    string str = "INSERT INTO orders(customer_id, employee_id, order_date, collection_date, status) VALUES(";
    int log_id = 1;
    // zapełniamy bazę zamówieniami od 01.01.2018 do 18.01.2021
    while (printdate.year < 2021 || printdate.day < 18){
        printTime.hour = 10;  
        printTime.minute = 0;
        while(printTime.hour < 20){
            fileResult << str;
            getline (c_ids, line);
            fileResult << line << ", " << getEmployeeId(log_id);
            if(line == "2940"){
                c_ids.clear();
                c_ids.seekg (0, ios::beg);
            } // 2940 to ostatni customer_id, trzeba wrócić na początek
            fileResult << ", DATETIMEFROMPARTS("<< printdate.year <<", " << printdate.month << ", " << printdate.day;
            fileResult << ", " << printTime.hour << ", " << printTime.minute << ", " << getSeconds() << ", 0), ";
            fileResult << "DATETIMEFROMPARTS("<< printdate.year <<", " << printdate.month << ", " << printdate.day;
            myTime wait = randWait(printTime);
            fileResult << ", " << wait.hour << ", " << wait.minute << ", " << getSeconds() << ", 0), " << getStatus(log_id) << ");\n";
            printTime = minuteLater(printTime);
            log_id++;
        }
        printdate = nextDay(printdate);
    }
    fileResult.close();
    c_ids.close();
    return 0;
}