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

int main(){
    ofstream fileResult;
    date printdate;
    printdate.day = 1;
    printdate.month = 1;
    printdate.year = 2018;
    fileResult.open ("result.sql");
    string str = "INSERT INTO menu(since_date, due_date) VALUES(";
    // generowanie dat co dwa tygodnie od 01.01.2018 do 25.01.2021 - gdzie następną byłaby 08.02.2021: warunek stopu
    while (printdate.year < 2021 || printdate.month < 2 || printdate.day < 8){
        fileResult << str;
        fileResult << "DATEFROMPARTS("<< printdate.year <<", " << printdate.month << ", " << printdate.day <<"),";
        printdate = twoWeeksLater(printdate);
        fileResult << "DATEFROMPARTS("<< printdate.year <<", " << printdate.month << ", " << printdate.day <<"));\n";
        printdate = nextDay(printdate);
    }
    fileResult.close();
    return 0;
}