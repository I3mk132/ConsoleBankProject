#pragma once

#include <iostream>
#include "../../clsScreen.h"
#include "../../Core/clsCurrency.h"
#include <vector>

class clsCurrenciesListScreen : protected clsScreen {
private:
    static void _PrintCurrencyDataLine(clsCurrency Currency){
        std::cout << std::setw(8) << "";
        std::cout << "| " << std::setw(30) << std::left << Currency.Country();
        std::cout << "| " << std::setw(10) << std::left << Currency.CurrencyCode();
        std::cout << "| " << std::setw(40) << std::left << Currency.CurrencyName();
        std::cout << "| " << std::setw(15) << std::left << Currency.Rate();
    }

public:
    static void ShowCurrenciesListScreen(){
        std::vector<clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();

        std::string Title = "\t  Currencies List Screen";
        std::string SubTitle = "\t\t(" + std::to_string(vCurrencies.size()) + ") Currency.";
        _DrawScreenHeader(Title, SubTitle);

        std::cout << std::setw(8) << "";
        std::cout << "_____________________________________________________________________________________________\n\n";
        std::cout << std::setw(8) << "";
        std::cout << "| " << std::setw(30) << std::left << "Country ";
        std::cout << "| " << std::setw(10) << std::left << "Code ";
        std::cout << "| " << std::setw(40) << std::left << "Name ";
        std::cout << "| " << std::setw(15) << std::left << "Rate/(1$) \n";
        std::cout << std::setw(8) << "";
        std::cout << "_____________________________________________________________________________________________\n";
        std::cout << std::endl;

        for (clsCurrency& C : vCurrencies){
            _PrintCurrencyDataLine(C);
            std::cout << std::endl;
        }

        std::cout << std::setw(8) << "";
        std::cout << "_____________________________________________________________________________________________\n";

    }
};