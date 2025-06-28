#pragma once

#include <iostream>
#include <string>
#include <limits>
#include "clsDate.h"

template<typename T>
class clsInputValidate {
public:

    static bool isNumberBetween(T Number, T From, T To) {
        return (Number >= From && Number <= To);
    }
    // ===================================================================

    static bool isDateBetween(clsDate Date, clsDate DateFrom, clsDate DateTo){
        return (
                       clsDate::isDate1AfterDate2(Date, DateFrom)
                       &&
                       clsDate::isDate1BeforeDate2(Date, DateTo)
               ) || (
                       clsDate::isDate1AfterDate2(Date, DateTo)
                       &&
                       clsDate::isDate1BeforeDate2(Date, DateFrom)
               );
    }
    // ===================================================================

    static T ReadNumber(std::string ErrorMessage="Invalid Number, Enter again\n"){
        T Number;
        while (!(std::cin >> Number)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << ErrorMessage;
        }
        return Number;
    }
    static T ReadNumberBetween(
            T From, T To, std::string ErrorMessage="Number is not within range, Enter again:\n")
    {
        T Number = ReadNumber();
        while (!isNumberBetween(Number, From, To)){
            std::cout << ErrorMessage;
            Number = ReadNumber();
        }
        return Number;
    }

    // =======================================================================

    static bool isValidDate(clsDate Date){
        return clsDate::isValidDate(Date);
    }

    // ========================================================================

    static std::string ReadString() {
        std::string S1;
        getline(std::cin>>std::ws, S1);
        return S1;
    }

};