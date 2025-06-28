#pragma once

#include <iostream>
#include "../../Lib/clsInputValidate.h"
#include "../../Core/clsBankClient.h"
#include "../../clsScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferLogScreen.h"
#include "clsTransferScreen.h"

class clsTransactionsScreen : protected clsScreen {
private:
    enum enTransactionsMenuOptions {
        eDeposit = 1, eWithdraw = 2, eShowTotalBalance = 3,
        eTransfer = 4, eTransferLog = 5,  eShowMainMenu = 6
    };

    static short _ReadTransactionsMenuOption()
    {
        std::cout << std::setw(37) << std::left << "" << "Choose what do you want to do? [1 to 6]? ";
        return clsInputValidate<short>::ReadNumberBetween(1, 6);
    }

    static void _GoBackToTransactionsMenu()
    {
        std::cout << "\n\nPress any key to go back to Transactions Menu...";
        system("pause > 0");
        ShowTransactionsMenu();
    }

    static void _ShowDepositScreen(){
        clsDepositScreen::ShowDepositScreen();
        //std::cout << "\nDeposit screen will be here.\n";
    }

    static void _ShowWithdrawScreen(){
        clsWithdrawScreen::ShowWithdrawScreen();
        //std::cout << "\nWithdraw screen will be here.\n";
    }

    static void _ShowTotalBalanceScreen(){
        //std::cout << "\nTotal Balance Screen will be here.\n";
        clsTotalBalancesScreen::ShowTotalBalances();
    }

    static void _ShowTransferScreen() {
        clsTransferScreen::ShowTransferScreen();
    }

    static void _ShowTransferLogScreen() {
        clsTransferLogScreen::ShowTransferLog();
    }

    static void _PerformTransactionsMenuOption(enTransactionsMenuOptions Option)
    {
        switch (Option)
        {
            case enTransactionsMenuOptions::eDeposit:{
                system("cls");
                 _ShowDepositScreen();
                _GoBackToTransactionsMenu();
                break;
            }
            case enTransactionsMenuOptions::eWithdraw:{
                system("cls");
                 _ShowWithdrawScreen();
                _GoBackToTransactionsMenu();
                break;
            }
            case enTransactionsMenuOptions::eShowTotalBalance:{
                system("cls");
                _ShowTotalBalanceScreen();
                _GoBackToTransactionsMenu();
                break;
            }
            case enTransactionsMenuOptions::eTransfer: {
                system("cls");
                _ShowTransferScreen();
                _GoBackToTransactionsMenu();
                break;
            }
            case enTransactionsMenuOptions::eTransferLog: {
                system("cls");
                _ShowTransferLogScreen();
                _GoBackToTransactionsMenu();
                break;
            }
            case enTransactionsMenuOptions::eShowMainMenu:{
                // do nothing here main screen will handle it :-)
            }
        }    
    }

public:
    static void ShowTransactionsMenu(){

        if(!CheckAccessRights(clsUser::enPermissions::pTransactions)){
            return;
        }

        system("cls");
        _DrawScreenHeader("\t  Transactions Screen ");

        std::cout << std::setw(37) << std::left << "" << "===========================================\n";
        std::cout << std::setw(37) << std::left << "" << "\t\t  Transactions Menu\n";
        std::cout << std::setw(37) << std::left << "" << "===========================================\n";
        std::cout << std::setw(37) << std::left << "" << "\t[1] Deposit.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[2] Withdraw.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[3] Total Balances.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[4] Transfer. \n";
        std::cout << std::setw(37) << std::left << "" << "\t[5] Transfer Log. \n";
        std::cout << std::setw(37) << std::left << "" << "\t[6] Main Menu.\n";
        std::cout << std::setw(37) << std::left << "" << "===========================================\n";

        _PerformTransactionsMenuOption((enTransactionsMenuOptions)_ReadTransactionsMenuOption());
    }
};
