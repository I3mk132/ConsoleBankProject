#pragma once
#include <iostream>
#include "../../clsScreen.h"
#include "../../Core/clsCurrency.h"
#include "../../Lib/clsInputValidate.h"
#include "clsCurrencyExchangeScreen.h"

class clsFindCurrencyScreen : protected clsScreen {
private:
    static void _PrintCurrency(clsCurrency Currency){
        std::cout << "\n\t\tCurrency Card: \n";
        std::cout << "\t\t_________________________________\n";
        std::cout << "\n\t\tCountry      : " << Currency.Country();
        std::cout << "\n\t\tCode         : " << Currency.CurrencyCode();
        std::cout << "\n\t\tName         : " << Currency.CurrencyName();
        std::cout << "\n\t\tRate(1$)=    : " << Currency.Rate();
        std::cout << "\n\t\t_________________________________\n";

    }

    static void _ShowResult(clsCurrency Currency){

        if (!Currency.isEmpty()){
            std::cout << "\nCurrency Found :-)\n";
            _PrintCurrency(Currency);
        }
        else {
            std::cout << "\nCurrency Was not Found :-( \n";
        }

    }


public:
    static void ShowFindCurrencyScreen(){

        std::cout << "\nFind By: [1] Code or [2] Country ? ";
        short Choice = clsInputValidate<short>::ReadNumberBetween(1, 2, "Enter [1] or [2]? ");


        if (Choice == 2){

            std::cout << "\nPlease Enter Country Name: ";
            std::string Country = clsInputValidate<std::string>::ReadString();
             clsCurrency Currency = clsCurrency::FindByCountry(Country);
            _ShowResult(Currency);
        }
        else {

            std::cout << "\nPlease Enter Currency Code: ";
            std::string Code = clsInputValidate<std::string>::ReadString();
            clsCurrency Currency = clsCurrency::FindByCode(Code);
            _ShowResult(Currency);
        }

    }
};