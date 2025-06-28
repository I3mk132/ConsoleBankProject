#pragma once

#include <iostream>
#include "../../Lib/clsInputValidate.h"
#include "../../clsScreen.h"
#include "../../Core/clsCurrency.h"

class clsCurrencyCalculatorScreen : protected clsScreen {
private:
    static void _PrintCurrency(clsCurrency Currency, std::string Message){
        std::cout << "\t\t" << Message << "\n";
        std::cout << "\t\t_________________________________\n";
        std::cout << "\n\t\tCountry      : " << Currency.Country();
        std::cout << "\n\t\tCode         : " << Currency.CurrencyCode();
        std::cout << "\n\t\tName         : " << Currency.CurrencyName();
        std::cout << "\n\t\tRate(1$)=    : " << Currency.Rate();
        std::cout << "\n\t\t_________________________________\n";

    }

    static clsCurrency _GetCurrency(std::string Message)
    {

        std::string CurrencyCode;
        std::cout << Message << std::endl;

        CurrencyCode = clsInputValidate<std::string>::ReadString();

        while (!clsCurrency::isCurrencyExists(CurrencyCode))
        {
            std::cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate<std::string>::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        return Currency;

    }

    static float _ReadAmount(){
        std::cout << "\nEnter Amount to Exchange: ";
        return  clsInputValidate<float>::ReadNumber();
    }

    static void _PrintCalculationResult(float Amount, clsCurrency Currency1, clsCurrency Currency2){
        _PrintCurrency(Currency1, "Convert From:");

        float AmountUSD = Currency1.ConvertToUSD(Amount);

        std::cout << Amount << " " << Currency1.CurrencyCode() << " = " << AmountUSD << " USD\n";

        if (Currency2.CurrencyCode() == "USD"){
            return;
        }

        std::cout << "\nConverting From USD to: \n";
        _PrintCurrency(Currency2, "To:");

        float AmountInCurrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2);

        std::cout << Amount << " " << Currency1.CurrencyCode() << " = " << AmountInCurrency2 << " ";
        std::cout << Currency2.CurrencyCode();
    }

public:
    static void ShowCurrencyExchangeScreen(){
        char Continue = 'y';
        while (tolower(Continue) == 'y'){
            system("cls");
            _DrawScreenHeader("\t  Update Currency Screen");

            clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code: ");
            clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code: ");
            float Amount = _ReadAmount();

            _PrintCalculationResult(Amount, CurrencyFrom, CurrencyTo);

            std::cout << "\n\nDo you want to perform another calculation? y/n? ";
            std::cin >> Continue;
        }

    }
};

typedef std::vector<std::vector<clsCurrency[]>> VectorForVectorOfArrays;
