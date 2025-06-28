#pragma once

#include <iostream>
#include "../../clsScreen.h"
#include "../../Core/clsCurrency.h"
#include "../../Lib/clsInputValidate.h"

class clsUpdateRateScreen : protected clsScreen {
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

    static float _ReadRate(){
        std::cout << "\n\nEnter New Rate: ";
        float NewRate = clsInputValidate<float>::ReadNumber();
        return NewRate;
    }

public:
    static void ShowUpdateRateScreen(){
        _DrawScreenHeader("\t  Update Currency Screen");

        std::cout << "\n\nPlease Enter Currency Code: ";
        std::string Code = clsInputValidate<std::string>::ReadString();
        while (!clsCurrency::isCurrencyExists(Code)){
            std::cout << "\nCurrency Code is not Exists, Please Enter another one: ";
            Code = clsInputValidate<std::string>::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCode(Code);
        _PrintCurrency(Currency);

        std::cout << "\nAre you sure you want to update the rate of this currency? y/n? ";
        char Answer = 'n';
        std::cin >> Answer;
        if (tolower(Answer) == 'y'){

            std::cout << "\n\n\nUpdate Currency Rate:";
            std::cout << "\n____________________";
            Currency.UpdateRate(_ReadRate());


            std::cout << "\nCurrency Rate Updated Successfully :-)\n";
            _PrintCurrency(Currency);
        }
    }
};