#pragma once

#include "../../clsScreen.h"
#include <iostream>
#include "../../Core/clsCurrency.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

class clsCurrencyExchangeScreen : protected clsScreen {
private:
    enum enCurrencyExchangeOption {
        eList = 1, eFind = 2, eUpdate = 3, eCalculator = 4, eMainMenu = 5
    };

    static short _ReadCurrencyExchangeOption(){
        std::cout << std::setw(37) << std::left << "" << "Choose what do you want to do? [1 to 5]? ";
        return clsInputValidate<short>::ReadNumberBetween(1, 5, "Enter Number Between 1 to 5? ");
    }

    static void _GoBackToCurrencyExchangeOptions(){
        std::cout << std::setw(37) << std::left << "" << "\n\tPress any key to go back to Currency Exchange Menu...\n";

        system("pause > 0");
        ShowCurrencyExchangeScreen();
    }

    static void ShowCurrenciesListScreen(){
        clsCurrenciesListScreen::ShowCurrenciesListScreen();
    }
    static void ShowFindCurrencyScreen(){
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
        //std::cout << "\nHere will be Find Currency Screen";
    }
    static void ShowUpdateRateScreen(){
        //std::cout << "\nHere will be Update Rate Screen";
        clsUpdateRateScreen::ShowUpdateRateScreen();
    }
    static void ShowCurrencyCalculatorScreen(){
        //std::cout << "\nHere will be Currency Calculator Screen";
        clsCurrencyCalculatorScreen::ShowCurrencyExchangeScreen();
    }

    static void _PerformCurrencyExchangeOption(enCurrencyExchangeOption Option){
        switch (Option) {
            case enCurrencyExchangeOption::eList:{
                system("cls");
                ShowCurrenciesListScreen();
                _GoBackToCurrencyExchangeOptions();
                break;
            }
            case enCurrencyExchangeOption::eFind:{
                system("cls");
                ShowFindCurrencyScreen();
                _GoBackToCurrencyExchangeOptions();
                break;
            }
            case enCurrencyExchangeOption::eUpdate:{
                system("cls");
                ShowUpdateRateScreen();
                _GoBackToCurrencyExchangeOptions();
                break;
            }
            case enCurrencyExchangeOption::eCalculator:{
                system("cls");
                ShowCurrencyCalculatorScreen();
                _GoBackToCurrencyExchangeOptions();
                break;
            }
            case enCurrencyExchangeOption::eMainMenu:{
                // Empty
            }
        }
    }

public:
    static void ShowCurrencyExchangeScreen(){
        system("cls");
        _DrawScreenHeader("\t  Currency Exchange Main Screen");

        std::cout << std::setw(37) << "" << "=================================================\n";
        std::cout << std::setw(37) << "" << "\t\t  Currency Exchange Menu\n";
        std::cout << std::setw(37) << "" << "=================================================\n";
        std::cout << std::setw(37) << "" << "\t[1] List Currencies.\n";
        std::cout << std::setw(37) << "" << "\t[2] Find Currency. \n";
        std::cout << std::setw(37) << "" << "\t[3] Update Rate. \n";
        std::cout << std::setw(37) << "" << "\t[4] Currency Calculator. \n";
        std::cout << std::setw(37) << "" << "\t[5] Main Menu.\n";
        std::cout << std::setw(37) << "" << "=================================================\n";

        _PerformCurrencyExchangeOption((enCurrencyExchangeOption)_ReadCurrencyExchangeOption());
    }
};