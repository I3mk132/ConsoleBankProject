#pragma once
#include <iostream>
#include "../../Core/clsBankClient.h"
#include "../../clsScreen.h"
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsUtil.h"

class clsTotalBalancesScreen : protected clsScreen {
private:
    static void _PrintClientRecordBalanceLine(clsBankClient Client){
        std::cout << std::setw(25) << std::left << "" << "| " << std::left << std::setw(15) << Client.AccountNumber();
        std::cout << "| " << std::left << std::setw(40) << Client.FullName();
        std::cout << "| " << std::left << std::setw(12) << Client.getAccountBalance();
    }

public:
    static void ShowTotalBalances()
    {
        std::vector<clsBankClient> vClients = clsBankClient::getClientsList();

        _DrawScreenHeader("Balances List Screen",
                          "Balances List (" + std::to_string(vClients.size()) + ") Client(s).");
        std::cout << "\n";
        std::cout << std::setw(25) << std::left << "" << "________________________________________________________"
                     "__________________________________________\n" << std::endl;
        std::cout << std::setw(25) << std::left << "" << "| " << std::left << std::setw(15) << "Account Number";
        std::cout << "| " << std::left << std::setw(40) << "Client Name";
        std::cout << "| " << std::left << std::setw(12) << "Balance";
        std::cout << "\n";
        std::cout << std::setw(25) << std::left << "" << "__________________________________________________________"
                     "________________________________________\n" << std::endl;

        double TotalBalances = clsBankClient::getTotalBalances();

        if (vClients.size() == 0){
            std::cout << "\t\t\t\tNo Clients Available In the System!";
        }
        else {
            for (clsBankClient& C : vClients)
            {
                _PrintClientRecordBalanceLine(C);
                std::cout << std::endl;
            }
        }
        std::cout << "\n";
        std::cout << std::setw(25) << std::left << "" << "_______________________________________________________________"
                     "___________________________________\n" << std::endl;
        std::cout << "\t\t\t\t\t TotalBalances = " << TotalBalances << std::endl;
        std::cout << "\t\t\t\t\t (" << clsUtil::NumberToText((long)TotalBalances) << ")" << std::endl;
    }

};