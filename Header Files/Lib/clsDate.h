#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <string>
#include "clsString.h"
#include <string>

class clsDate {
private:
    short _Day;
    short _Month;
    short _Year;


public:
    clsDate() {
        time_t t = time(0);
        tm* now = localtime(&t);
        _Day = now->tm_mday;
        _Month = now->tm_mon + 1;
        _Year = now->tm_year + 1900;

    }
    clsDate(std::string sDate) {
        std::vector<std::string> vDate = clsString::Split(sDate, "/");

        _Day = stoi(vDate[0]);
        _Month = stoi(vDate[1]);
        _Year = stoi(vDate[2]);
    }
    clsDate(short Day, short Month, short Year) {
        _Day = Day;
        _Month = Month;
        _Year = Year;
    }
    clsDate(short DateOrderInYear, short Year) {
        //This will construct a date by date order in year
        clsDate Date = GetTodaysDate(Year, DateOrderInYear);
        _Day = Date.Day();
        _Month = Date.Month();
        _Year = Date.Year();

    }

    // set & get Day.
    void setDay(short Day) {
        _Day = Day;
    }
    short Day() {
        return _Day;
    }

    // set & get Month
    void setMonth(short Month) {
        _Month = Month;
    }
    short Month() {
        return _Month;
    }

    // set & get Year
    void setYear(short Year) {
        _Year = Year;
    }
    short Year() {
        return _Year;
    }


    static short ReadYear() {
        short Num;
        std::cout << "Please enter a Year? ";
        std::cin >> Num;
        return Num;
    }
    static short ReadMonth() {
        short Num;
        do {
            std::cout << "Please enter a Month? ";
            std::cin >> Num;
        } while (!(Num > 0 && Num < 13));

        return Num;
    }
    static short ReadDay() {
        short Num;
        do {
            std::cout << "Please enter a day? ";
            std::cin >> Num;
        } while (Num < 1 || Num > 31);

        return Num;
    }
    static clsDate ReadDate() {
         return clsDate(ReadDay(), ReadMonth(), ReadYear());
    }

    // =================================================================================

    static clsDate GetSystemDate() {
        // SystemDate
        time_t t = time(0);
        tm* now = localtime(&t);

        short Day, Month, Year;
        Day = now->tm_mday;
        Month = now->tm_mon + 1;
        Year = now->tm_year + 1900;

        return clsDate(Day, Month, Year);
    }

    static std::string GetSystemDateTimeString(){

        // system datetime string
        time_t t = time(0);
        tm* now = localtime(&t);

        short Day, Month, Year, Hour, Minute, Second;

        Day = now->tm_mday;
        Month = now->tm_mon + 1;
        Year = now->tm_year + 1900;
        Hour = now->tm_hour;
        Minute = now->tm_min;
        Second = now->tm_sec;


        return (std::to_string(Day) + "/" + std::to_string(Month) + "/" + std::to_string(Year) + " - "
            + std::to_string(Hour) + ":" + std::to_string(Minute) + ":" + std::to_string(Second));
    }

    // =================================================================================

    static bool isLeapYear(short Year) {
        return (Year % 400 == 0) || ((Year % 4 == 0) && (Year % 100 != 0));;
    }
    bool isLeapYear() {
        return isLeapYear(_Year);
    }

    // =================================================================================

    static int NumberOfDaysInYear(short Year) {
        return (isLeapYear(Year)) ? 365 : 366;
    }
    static int NumberOfHoursInYear(short Year) {
        return NumberOfDaysInYear(Year) * 24;
    }
    static int NumberOfMinutesInYear(short Year) {
        return NumberOfHoursInYear(Year) * 60;
    }
    static int NumberOfSecondsInYear(short Year) {
        return NumberOfMinutesInYear(Year) * 60;
    }
    int NumberOfDaysInYear() {
        return NumberOfDaysInYear(_Year);
    }
    int NumberOfHoursInYear() {
        return NumberOfHoursInYear(_Year);
    }
    int NumberOfMinutesInYear() {
        return NumberOfMinutesInYear(_Year);
    }
    int NumberOfSecondsInYear() {
        return NumberOfSecondsInYear(_Year);
    }

    // ==============================================================================

    static int NumberOfDaysInMonth(short Month, short Year) {

        if (Month > 12 || Month < 1) {
            return 0;
        }

        short arrDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        return ((Month == 2) ? (isLeapYear(Year) ? 29 : 28) : (arrDays[Month - 1]));
    }
    int NumberOfDaysInMonth() {
        return NumberOfDaysInMonth(_Month, _Year);
    }


    static int NumberOfHoursInMonth(short Month, short Year) {
        return NumberOfDaysInMonth(Month, Year) * 24;
    }
    int NumberOfHoursInMonth() {
        return NumberOfHoursInMonth(_Month, _Year);
    }


    static int NumberOfMinutesInMonth(short Month, short Year) {
        return NumberOfHoursInMonth(Month, Year) * 60;
    }
    int NumberOfMinutesInMonth() {
        return NumberOfMinutesInMonth(_Month, _Year);
    }


    static int NumberOfSecondsInMonth(short Month, short Year) {
        return NumberOfMinutesInMonth(Month, Year) * 60;
    }
    int NumberOfSecondsInMonth() {
        return NumberOfSecondsInMonth(_Month, _Year);
    }

    // =============================================================================

    static std::string GetDayName(int DayOfWeekOrder) {
        std::string arr[] = {
            "Sunday", "Monday", "Tuesday",
            "Wednesday", "Thursday", "Friday",
            "Saturday"
        };
        return arr[DayOfWeekOrder];
    }
    static std::string GetDayName(short Day, short Month, short Year) {
        std::string arr[] = {
            "Sunday", "Monday", "Tuesday",
            "Wednesday", "Thursday", "Friday",
            "Saturday"
        };
        return arr[DayOfWeekOrder(Year, Month, Day)];
    }
    std::string GetDayName() {
        return GetDayName(_Day, _Month, _Year);
    }

    // =============================================================================

    static std::string GetDayShortName(int DayOfWeekOrder) {
        std::string arr[] = {
            "Sun", "Mon", "Tue",
            "Wed", "Thu", "Fri",
            "Sat"
        };
        return arr[DayOfWeekOrder];
    }
    static std::string GetDayShortName(int Day, int Month, int Year) {
        std::string arr[] = {
            "Sun", "Mon", "Tue",
            "Wed", "Thu", "Fri",
            "Sat"
        };
        return arr[DayOfWeekOrder(Year, Month, Day)];
    }
    std::string GetDayShortName() {
        return GetDayShortName(_Day, _Month, _Year);
    }

    // =============================================================================

    static std::string GetMonthName(int MonthNumber) {
        std::string arr[] = {
            "January", "February", "March",
            "April", "May", "June",
            "July", "August", "September",
            "October", "November", "December"
        };
        return arr[MonthNumber-1];
    }
    std::string GetMonthName() {
        return GetMonthName(_Month);
    }

    // =============================================================================

    static std::string GetMonthShortName(int MonthNumber) {
        std::string arr[] = {
            "Jan", "Feb", "Mar", "Apr",
            "May", "Jun", "Jul", "Aug",
            "Sep", "Oct", "Nov", "Dec"
        };
        return arr[MonthNumber-1];
    }
    std::string GetMonthShortName() {
        return GetMonthShortName(_Month);
    }

    // =============================================================================

    static bool isDate1BeforeDate2(clsDate Date1, clsDate Date2) {
        return  (Date1.Year() < Date2.Year()) ? true :
        ((Date1.Year() == Date2.Year()) ? (Date1.Month() < Date2.Month() ? true :
            (Date1.Month() == Date2.Month() ? Date1.Day() < Date2.Day() : false)) : false);
    }
    static bool isDate1EqualDate2(clsDate Date1, clsDate Date2) {
        return Date1.Year() == Date2.Year() && Date1.Month() == Date2.Month() &&
            Date1.Day() == Date2.Day();
    }
    static bool isDate1AfterDate2(clsDate Date1, clsDate Date2) {
        return (!isDate1BeforeDate2(Date1, Date2) && !isDate1EqualDate2(Date1, Date2));
    }

    bool isDateBeforeDate2(clsDate Date2) {
        return isDate1BeforeDate2(*this, Date2);
    }
    bool isDateEqualDate2(clsDate Date2) {
        return isDate1EqualDate2(*this, Date2);
    }
    bool isDateAfterDate2(clsDate Date2) {
        return isDate1AfterDate2(*this, Date2);
    }

    // =============================================================================

    static short DayOfWeekOrder(int Year, int Month, int Day) {
        int a = (14 - Month) / 12;
        int y = Year - a;
        int m = Month + 12 * a - 2;

        // Gregorian:
        //0:sun, 1:Mon, 2:Tue...etc
        int d;
        d = (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;

        return d;
    }
    static short DayOfWeekOrder(clsDate Date) {
        int a = (14 - Date.Month()) / 12;
        int y = Date.Year() - a;
        int m = Date.Month() + 12 * a - 2;

        // Gregorian:
        //0:sun, 1:Mon, 2:Tue...etc
        int d;
        d = (Date.Day() + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;

        return d;
    }
    short DayOfWeekOrder() {
        return DayOfWeekOrder(_Year, _Month, _Day);
    }

    // ==============================================================================

    static short GetTodayCountInYear(short Year, short Month, short Day) {
        short Counter = 0;
        for (short i = 1; i <= Month - 1; i++) {
            Counter += NumberOfDaysInMonth(i, Year);
        }
        return Counter + Day;
    }
    static short GetTodayCountInYear(clsDate Date) {
        short Counter = 0;
        for (short i = 1; i < Date.Month() - 1; i++) {
            Counter += NumberOfDaysInMonth(Date.Year(),  i);
        }
        return Counter + Date.Day();
    }
    short GetTodayCountInYear() {
        return GetTodayCountInYear(_Year, _Month, _Day);
    }

    // =============================================================================

    static clsDate GetTodaysDate(short Year, short Days) {
        clsDate Date;
        short DayCount;
        short ThisMonth = 1;
        while (Days >= (DayCount = NumberOfDaysInMonth(ThisMonth, Year))) {
            Days -= DayCount;
            ThisMonth++;
        }
        Date.setDay(Days);
        Date.setMonth(ThisMonth);
        Date.setYear(Year);
        return Date;
    }
    clsDate GetTodaysDate() {
        return GetTodaysDate(_Year, GetTodayCountInYear(_Year, _Month, _Day));
    }

    // ==============================================================================

    static bool isLastDayInMonth(short Year, short Month, short Day) {
        return (NumberOfDaysInMonth(Month, Year) == Day);
    }
    static bool isLastMonthInYear(short Month) {
        return Month == 12;
    }
    bool isLastDayInMonth() {
        return isLastDayInMonth(_Year, _Month, _Day);
    }
    bool isLastMonthInYear() {
        return isLastMonthInYear(_Month);
    }

    // ==============================================================================

    static void IncreaseDayByOne(clsDate& Date){
        if (isLastDayInMonth(Date.Year(), Date.Month(), Date.Day())){
            if (isLastMonthInYear(Date.Month())){
                Date.setYear(Date.Year() + 1);
                Date.setMonth(1);
            }
            else {
                Date.setMonth(Date.Month() + 1);
            }
            Date.setDay(1);
        }
        else {
            Date.setDay(Date.Day() + 1);
        }
    }
    void IncreaseDayByOne() {
        IncreaseDayByOne(*this);
    }


    static void IncreaseDateByXDays(clsDate& D, short Add) {
        for (short i = 1; i <= Add; i++) {
            IncreaseDayByOne(D);
        }
    }
    void IncreaseDateByXDays(short Add) {
        IncreaseDateByXDays(*this, Add);
    }


    static void IncreaseDateByOneWeek(clsDate& D) {
        for (short i = 1; i <= 7; i++) {
            IncreaseDayByOne(D);
        }
    }
    void IncreaseDateByOneWeek() {
        return IncreaseDateByOneWeek(*this);
    }


    static void IncreaseDateByXWeeks(clsDate& D, short Weeks) {
        for (short i = 1; i <= Weeks; i++) {
            IncreaseDateByOneWeek(D);
        }
    }
    void IncreaseDateByXWeeks(short Weeks) {
        IncreaseDateByXWeeks(*this, Weeks);
    }


    static void IncreaseDateByOneMonth(clsDate& D) {

        if (D.Month() == 12) {
            D.setYear(D.Year() + 1);
            D.setMonth(1);
        }
        else {
            D.setMonth(D.Month() + 1);
        }

        short DaysInCurrectMonth = NumberOfDaysInMonth(D.Month(), D.Year());
        if (D.Day() > DaysInCurrectMonth) {
            D.setDay(DaysInCurrectMonth);
        }

    }
    void IncreaseDateByOneMonth() {
        IncreaseDateByOneMonth(*this);
    }


    static void IncreaseDateByXMonths(clsDate& D, short Months) {
        for (short i = 1; i <= Months; i++) {
            IncreaseDateByOneMonth(D);
        }
    }
    void IncreaseDateByXMonths(short Months) {
        IncreaseDateByXMonths(*this, Months);
    }


    static void IncreaseDateByOneYear(clsDate& D) {
        D.setYear(D.Year() +1);
    }
    void IncreaseDateByOneYear() {
        IncreaseDateByOneYear(*this);
    }


    static void IncreaseDateByXYears(clsDate& D, short Year) {
        D.setYear(D.Year() + Year);
    }
    void IncreaseDateByXYears(short Year) {
        IncreaseDateByXYears(*this, Year);
    }


    static void IncreaseDateByOneDecade(clsDate& D) {
        D.setYear(D.Year() + 10);
    }
    void IncreaseDateByOneDecade() {
        IncreaseDateByOneDecade(*this);
    }


    static void IncreaseDateByXDecades(clsDate& D, short Decade) {
        D.setYear(D.Year() + (10 * Decade));
    }
    void IncreaseDateByXDecades(short Decade) {
        IncreaseDateByXDecades(*this, Decade);
    }


    static void IncreaseDateByOneCentury(clsDate& D) {
        D.setYear(D.Year() + 100);
    }
    void IncreaseDateByOneCentury() {
        IncreaseDateByOneCentury(*this);
    }


    static void IncreaseDateByOneMillennium(clsDate& D) {
        D.setYear(D.Year() + 1000);
    }
    void IncreaseDateByOneMillennium() {
        IncreaseDateByOneMillennium(*this);
    }
    // =============================================================================

    static void DecreaseDateByOneDay(clsDate& Date) {
        // Check if day is the first day of the month
        if (Date.Day() == 1) {
            // if it's january 1st go to december 31st of the previos year
            if (Date.Month() == 1) {
                Date.setYear(Date.Year() - 1);
                Date.setMonth(12);
            }
            else {
                // Move to last day of the previos month
                Date.setMonth(Date.Month() - 1);
            }

            Date.setDay(NumberOfDaysInMonth(Date.Month(), Date.Year()));
        }
        else {
            Date.setDay(Date.Day() - 1);
        }
    }
    void DecreaseDateByOneDay() {
        DecreaseDateByOneDay(*this);
    }


    static void DecreaseDateByXDays(clsDate& Date, short Day) {
        for (short i = 0; i < Day; i++) {
            DecreaseDateByOneDay(Date);
        }
    }
    void DecreaseDateByXDays(short Day) {
        DecreaseDateByXDays(*this, Day);
    }


    static void DecreaseDateByOneWeek(clsDate& Date) {
        for (short i = 0; i < 7; i++) {
            DecreaseDateByOneDay(Date);
        }
    }
    void DecreaseDateByOneWeek() {
        DecreaseDateByOneWeek(*this);
    }


    static void DecreaseDateByXWeeks(clsDate& Date, short Week) {
        for (short i = 0; i < Week; i++) {
            DecreaseDateByOneWeek(Date);
        }
    }
    void DecreaseDateByXWeeks(short Week) {
        DecreaseDateByXWeeks(*this, Week);
    }


    static void DecreaseDateByOneMonth(clsDate& Date) {
        if (Date.Month() == 1) {
            Date.setYear(Date.Year() - 1);
            Date.setMonth(12);
        }
        else {
            Date.setMonth(Date.Month() - 1);
        }

        short Max = NumberOfDaysInMonth(Date.Month(), Date.Year());
        if (Date.Day() > Max) {
            Date.setDay(Max);
        }
    }
    void DecreaseDateByOneMonth() {
        DecreaseDateByOneMonth(*this);
    }


    static void DecreaseDateByXMonths(clsDate& Date, short Month) {
        for (short i = 0; i < Month; i++) {
            DecreaseDateByOneMonth(Date);
        }
    }
    void DecreaseDateByXMonths(short Month) {
        DecreaseDateByXMonths(*this, Month);
    }


    static void DecreaseDateByOneYear(clsDate& Date) {
        Date.setYear(Date.Year() - 1);
    }
    void DecreaseDateByOneYear() {
        DecreaseDateByOneYear(*this);
    }


    static void DecreaseDateByXYears(clsDate& Date, short Year) {
        Date.setYear(Date.Year() - Year);
    }
    void DecreaseDateByXYears(short Year) {
        DecreaseDateByXYears(*this, Year);
    }


    static void DecreaseDateByOneDecades(clsDate& Date) {
        Date.setYear(Date.Year() - 10);
    }
    void DecreaseDateByOneDecades() {
        DecreaseDateByOneDecades(*this);
    }


    static void DecreaseDateByXDecades(clsDate& Date, short Decade) {
        Date.setYear(Date.Year() - Decade * 10);
    }
    void DecreaseDateByXDecades(short Decade) {
        DecreaseDateByXDecades(*this, Decade);
    }


    static void DecreaseDateByOneCentury(clsDate& Date) {
        Date.setYear(Date.Year() - 100);
    }
    void DecreaseDateByOneCentury() {
        DecreaseDateByOneCentury(*this);
    }


    static void DecreaseDateByOneMillennium(clsDate& Date) {
        Date.setYear(Date.Year() - 1000);
    }
    void DecreaseDateByOneMillennium() {
        DecreaseDateByOneMillennium(*this);
    }

    // =============================================================================

    static int GetUserAge(clsDate Date){
        clsDate Date2 = GetSystemDate();
        int Day = 0;

        while (!isDate1EqualDate2(Date, Date2)){
            IncreaseDayByOne(Date);
            Day++;
        }
        return Day;
    }
    int GetUserAge() {
        return GetUserAge(*this);
    }

    // ============================================================================

    static void SwapDates(clsDate& Date1, clsDate& Date2) {
        clsDate TempDate;

        TempDate = Date1;
        Date1 = Date2;
        Date2 = TempDate;
    }
    void SwapDates(clsDate& Date2){
        SwapDates(*this, Date2);
    }

    // ============================================================================

    static short GetDifferenceCount(clsDate Date1, clsDate Date2, bool IncludeEndDay = false){
        short Counter = 0;
        int SwapFlagValue = 1;

        if (isDate1AfterDate2(Date1, Date2)){
            SwapDates(Date1, Date2);
            SwapFlagValue = -1;
        }
        while (!isDate1EqualDate2(Date1, Date2)){
            Counter++;
            IncreaseDayByOne(Date1);
        }
        return (SwapFlagValue) * ((IncludeEndDay) ? ++Counter : Counter);
    }
    short GetDifferenceCount(clsDate Date2, bool IncludeEndDay = false) {
        return GetDifferenceCount(*this, Date2, IncludeEndDay);
    }

    // ==============================================================================

    static short CalculateMyAgeInDays(clsDate DateOfBirth) {
        return GetDifferenceCount(DateOfBirth, GetSystemDate(), true);
    }
    short CalculateMyAgeInDays() {
        return CalculateMyAgeInDays(*this);
    }
    //above no need to have nonstatic function for the object because it
    //does not depend on any data from it.

    // ==============================================================================

    static bool isEndOfWeek(clsDate Date) {
        short TodayCount = DayOfWeekOrder(Date);
        return (TodayCount == 0);
    }
    static bool isWeekEnd(clsDate Date) {
        short TodayCount = DayOfWeekOrder(Date);
        return (TodayCount == 0 || TodayCount == 6);
    }
    static bool isWorkDay(clsDate Date) {
        return !isWeekEnd(Date);
    }
    bool isEndOfWeek() {
        return isEndOfWeek(*this);
    }
    bool isWeekEnd() {
        return isWeekEnd(*this);
    }
    bool isWorkDay() {
        return isWorkDay(*this);
    }

    // ==============================================================================

    static short DaysUntilTheEndOfWeek(clsDate Date) {
        short TodayCount = DayOfWeekOrder(Date);
        return 7 - TodayCount;
    }
    short DaysUntilTheEndOfWeek() {
        return DaysUntilTheEndOfWeek(*this);
    }


    static short DaysUntilTheEndOfMonth(clsDate Date) {
        // stDate End;
        // End.Day = GetDayCountInMonth(Date.Month, Date.Year);
        // End.Month = Date.Month;
        // End.Year = Date.Year;
        //
        // return GetDifferenceCount(Date, End, true);
        return NumberOfDaysInMonth(Date.Month(), Date.Year()) - Date.Day();
    }
    short DaysUntilTheEndOfMonth() {
        return DaysUntilTheEndOfMonth(*this);
    }


    static short DaysUntilTheEndOfYear(clsDate Date) {
        clsDate EndYear;
        EndYear.setDay(31);
        EndYear.setMonth(12);
        EndYear.setYear(Date.Year());

        short Counter = 0;
        while (isDate1AfterDate2(EndYear, Date)) {
            IncreaseDayByOne(Date);
            Counter++;
        }
        return Counter;
    }
    short DaysUntilTheEndOfYear() {
        return DaysUntilTheEndOfYear(*this);
    }

    // =============================================================================

    static short CalculateWorkDays(clsDate DateFrom, clsDate DateTo) {
        short Days = 0;
        while (isDate1BeforeDate2(DateFrom, DateTo)) {
            if (isWorkDay(DateFrom)) {
                Days++;
            }
            IncreaseDayByOne(DateFrom);
        }
        return Days;
    }
    short CalculateWorkDays(clsDate DateTo) {
        return CalculateWorkDays(*this, DateTo);
    }

    // =============================================================================

    static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo) {
        return CalculateWorkDays(DateFrom, DateTo);
    }
    short CalculateVacationDays(clsDate DateTo) {
        return CalculateVacationDays(*this, DateTo);
    }

    // =============================================================================

    static clsDate CalculateVacationReturnDate(clsDate From, short VacationDays) {

        // in case the data is weekend keep adding one day until you reach business
        // we get rid of all weekends before the first business day
        while (isWeekEnd(From)) {
            IncreaseDayByOne(From);
        }

        //here we increase the vacation dates to add all weekends to it.
        short WeekEndCounter = 0;
        for (short i = 1; i <= VacationDays + WeekEndCounter; i++) {

            if (isWeekEnd(From)) {
                WeekEndCounter++;
            }

            IncreaseDayByOne(From);
        }

        //in case the return date is week end keep adding one day until you reach business day
        while (isWeekEnd(From)) {
            IncreaseDayByOne(From);
        }

        return From;
    }
    clsDate CalculateVacationReturnDate(short VacationDays) {
        return CalculateVacationReturnDate(*this, VacationDays);
    }

    // ================================================================================

    static short ActualVacationDays(clsDate From, clsDate To) {
        short Counter = 0;
        while (isDate1BeforeDate2(From, To)) {
            if (isWorkDay(From)) {
                Counter++;
            }
            IncreaseDayByOne(From);
        }
        return Counter;
    }
    short ActualVacationDays(clsDate To) {
        return ActualVacationDays(*this, To);
    }

    // =================================================================================

    enum enDateCompare{Before = -1, Equal = 0, After = 1};

    static enDateCompare CompareDates(clsDate Date1, clsDate Date2) {
        if (isDate1BeforeDate2(Date1, Date2)) {
            return enDateCompare::Before;
        }
        if (isDate1EqualDate2(Date1, Date2)) {
            return enDateCompare::Equal;
        }
        return enDateCompare::After;

    }
    enDateCompare CompareDates(clsDate Date2) {
        return CompareDates(*this, Date2);
    }

    static std::string GetDateCompare(enDateCompare D){
        switch (D){
            case enDateCompare::After:{
                return "After";
            }
            case enDateCompare::Equal:{
                return "Equal";
            }
            case enDateCompare::Before:{
                return "Before";
            }
        }
    }

    // =====================================================================================

    static bool isValidDate(clsDate Date) {
        if (Date.Day() > NumberOfDaysInMonth(Date.Month(), Date.Year()) || Date.Day() < 1) {
            return false;
        }

        if (Date.Month() > 12 || Date.Month() < 1) {
            return false;
        }

        if (Date.Year() < 1) {
            return false;
        }

        return true;
    }
    bool isValidDate() {
        return isValidDate(*this);
    }

    // =====================================================================================

    static clsDate StringToDate(std::string sDate) {
        std::vector<std::string> vString = clsString::Split(sDate, "/");

        clsDate Date;

        Date.setDay(stoi(vString[0]));
        Date.setMonth(stoi(vString[1]));
        Date.setYear(stoi(vString[2]));

        return Date;
    }


    static std::string DateToString(clsDate Date) {
        std::string sDate;
        sDate += std::to_string(Date.Day()) + "/";
        sDate += std::to_string(Date.Month()) + "/";
        sDate += std::to_string(Date.Year());
        return sDate;
    }
    std::string DateToString() {
        return DateToString(*this);
    }

    // =====================================================================================

    static std::string FormatDate(clsDate Date, std::string FormatedDate = "dd/mm/yyyy") {

        FormatedDate = clsString::ReplaceWord(FormatedDate, "dd", std::to_string(Date.Day()));
        FormatedDate = clsString::ReplaceWord(FormatedDate, "mm", std::to_string(Date.Month()));
        FormatedDate = clsString::ReplaceWord(FormatedDate, "yyyy", std::to_string(Date.Year()));

        return FormatedDate;
    }
    std::string FormatDate(std::string FormatedDate = "dd/mm/yyyy") {
        return FormatDate(*this, FormatedDate);
    }

    // =====================================================================================

    static std::string PrintDate(clsDate D) {
        return std::to_string(D.Day()) + "/" + std::to_string(D.Month()) + "/" + std::to_string(D.Year());
    }
    std::string PrintDate() {
        return PrintDate(*this);
    }

    // =====================================================================================

    static void PrintMonthCalender(short Year, short Month) {

        int NumberOfDays = NumberOfDaysInMonth(Month, Year);
        int ThisMonth = DayOfWeekOrder(Year, Month, 1);

        std::cout << "________________" << GetMonthShortName(Month) << "__________________\n\n";
        std::cout << std::setw(5) << "Sun";
        std::cout << std::setw(5) << "Mon";
        std::cout << std::setw(5) << "Tue";
        std::cout << std::setw(5) << "Wed";
        std::cout << std::setw(5) << "Thu";
        std::cout << std::setw(5) << "Fri";
        std::cout << std::setw(5) << "Sat";
        std::cout << "\n";

        int i;
        for (i = 0; i < ThisMonth; i++) {
            std::cout << std::setw(5) << "";
        }

        for (short j = 0; j < NumberOfDays; j++) {
            std::cout << std::setw(5) << j + 1;

            if (++i == 7) {
                i = 0;
                std::cout << "\n";
            }
        }
        std::cout << "\n_____________________________________\n\n";
    }
    void PrintMonthCalender() {
        PrintMonthCalender(_Year, _Month);
    }

    // ==================================================================================

    static void PrintYearCalender(short Year) {

        std::cout << "\n_____________________________________\n\n";
        std::cout << "           Calender - " << Year << "\n";
        std::cout << "_____________________________________\n\n";

        for (short i = 1; i <= 12; i++) {

            PrintMonthCalender(Year, i);

        }
    }
    void PrintYearCalender() {
        PrintYearCalender(_Year);
    }

    // ==================================================================================

    static void Print(clsDate Date1) {
        std::cout << DateToString(Date1) << std::endl;
    }
    void Print(){
        Print(*this);
    }

    // ==================================================================================


};
