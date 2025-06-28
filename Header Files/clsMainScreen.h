#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "Lib/clsInputValidate.h"
#include "Screens/Client/clsClientListScreen.h"
#include "Screens/Client/clsAddNewClientScreen.h"
#include "Screens/Client/clsDeleteClientScreen.h"
#include "Screens/Client/clsUpdateClientScreen.h"
#include "Screens/Client/clsFindClientScreen.h"
#include "Screens/Transaction/clsTransactionsScreen.h"
#include "Screens/User/clsManageUsersScreen.h"
#include "Screens/Login/clsLoginRegisterScreen.h"
#include "Global.h"
#include "Screens/CurrencyExchange/clsCurrencyExchangeScreen.h"

class clsMainScreen : protected clsScreen {
private:
    enum enMainMenuOption {
        eListClients = 1, eAddNewClients = 2, eDeleteClients = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionMenu = 6,
        eManageUsers = 7, eLoginRegister = 8, eCurrencyExchange = 9,
        eExit = 10
    };

    static short _ReadMainMenuOption()
    {
        std::cout << std::setw(37) << std::left << "" << "Choose what do you want to do? [1 to 10]? ";
        return clsInputValidate<short>::ReadNumberBetween(1, 10, "Enter Number Between 1 to 10? ");
    }

    static void _GoBackToMainMenu(){
        std::cout << std::setw(37) << std::left << "" << "\n\tPress any key to go back to Main Menu...\n";

        system("pause > 0");
        ShowMainMenu();
    }

    static void _ShowAllClientsScreen(){
        //std::cout << "\nClient List Screen Will Be Here...\n";
        clsClientListScreen::ShowClientsList();
    }

    static void _ShowAddNewClientsScreen(){
        //std::cout << "\nAdd New Client Screen will be here...\n";
        clsAddNewClientScreen::ShowAddNewClientScreen();

    }

    static void _ShowDeleteClientScreen(){
        //std::cout << "\nDelete Client Screen will be here...\n";
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen(){
        //std::cout << "\nUpdate Client Screen will be here...\n";
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }

    static void _ShowFindClientScreen(){
        //std::cout << "\nFind Client Screen will be here...\n";
        clsShowFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionScreen(){
        //std::cout << "\nTransaction Menu will be here...\n";
        clsTransactionsScreen::ShowTransactionsMenu();
    }

    static void _ShowManageUsersMenu(){
        clsManageUsersScreen::ShowManageUsersMenu();
        // std::cout << "\nManage Users Menu will be here...\n";
    }

    static void _ShowLoginRegisterScreen(){
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }

    static void _ShowCurrencyExchangeMenu(){
        clsCurrencyExchangeScreen::ShowCurrencyExchangeScreen();
    }

    static void _Logout(){
        CurrentUser = clsUser::Find("", "");
        // then will go back to main menu

        //std::cout << "\nEndScreen Menu will be here... \n";
    }

    static void _PerformMainMenuOption(enMainMenuOption MainMenuOptions)
    {
        switch (MainMenuOptions) {
            case enMainMenuOption::eListClients:{
                system("cls");
                _ShowAllClientsScreen();
                _GoBackToMainMenu();
                break;
            }
            case enMainMenuOption::eAddNewClients:{
                system("cls");
                _ShowAddNewClientsScreen();
                _GoBackToMainMenu();
                break;
            }
            case enMainMenuOption::eDeleteClients:{
                system("cls");
                _ShowDeleteClientScreen();
                _GoBackToMainMenu();
                break;
            }
            case enMainMenuOption::eUpdateClient:{
                system("cls");
                _ShowUpdateClientScreen();
                _GoBackToMainMenu();
                break;
            }
            case enMainMenuOption::eFindClient:{
                system("cls");
                _ShowFindClientScreen();
                _GoBackToMainMenu();
                break;
            }
            case enMainMenuOption::eShowTransactionMenu:{
                system("cls");
                _ShowTransactionScreen();
                _GoBackToMainMenu();
                break;
            }
            case enMainMenuOption::eManageUsers:{
                system("cls");
                _ShowManageUsersMenu();
                _GoBackToMainMenu();
                break;
            }
            case enMainMenuOption::eLoginRegister:{
                system("cls");
                _ShowLoginRegisterScreen();
                _GoBackToMainMenu();
                break;
            }
            case enMainMenuOption::eCurrencyExchange:{
                system("cls");
                _ShowCurrencyExchangeMenu();
                _GoBackToMainMenu();
                break;
            }
            case enMainMenuOption::eExit:{
                system("cls");
                _Logout();
                //Login();
                break;
            }
        }
    }

public:
    static void ShowMainMenu(){
        system("cls");
        _DrawScreenHeader("\t\tMain Screen");

        std::cout << std::setw(37) << std::left << "" << "====================================================\n";
        std::cout << std::setw(37) << std::left << "" << "\t\t\tMain Menu\n";
        std::cout << std::setw(37) << std::left << "" << "====================================================\n";
        std::cout << std::setw(37) << std::left << "" << "\t[1] Show Client List. \n";
        std::cout << std::setw(37) << std::left << "" << "\t[2] Add New Client. \n";
        std::cout << std::setw(37) << std::left << "" << "\t[3] Delete Client. \n";
        std::cout << std::setw(37) << std::left << "" << "\t[4] Update Client. \n";
        std::cout << std::setw(37) << std::left << "" << "\t[5] Find Client. \n";
        std::cout << std::setw(37) << std::left << "" << "\t[6] Transaction. \n";
        std::cout << std::setw(37) << std::left << "" << "\t[7] Manage Users. \n";
        std::cout << std::setw(37) << std::left << "" << "\t[8] Login Register. \n";
        std::cout << std::setw(37) << std::left << "" << "\t[9] Currency Exchange. \n";
        std::cout << std::setw(37) << std::left << "" << "\t[10] Logout. \n";
        std::cout << std::setw(37) << std::left << "" << "====================================================\n";

        _PerformMainMenuOption((enMainMenuOption) _ReadMainMenuOption());
    }
};