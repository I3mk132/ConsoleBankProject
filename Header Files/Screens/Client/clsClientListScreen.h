#pragma once

#include <iostream>
#include "../../clsScreen.h"
#include "../../Core/clsBankClient.h"

class clsClientListScreen : protected clsScreen {
private:
    static void _PrintClientRecordLine(clsBankClient Client){
        std::cout << std::setw(8) << std::left << "" << "| " << std::left << std::setw(15) << Client.AccountNumber();
        std::cout << "| " << std::left << std::setw(20) << Client.FullName();
        std::cout << "| " << std::left << std::setw(12) << Client.getPhone();
        std::cout << "| " << std::left << std::setw(20) << Client.getEmail();
        std::cout << "| " << std::left << std::setw(10) << Client.getPinCode();
        std::cout << "| " << std::left << std::setw(12) << Client.getAccountBalance();
    }

public:
    static void ShowClientsList(){

        if (!CheckAccessRights(clsUser::enPermissions::pListClients)){
            return;
        }

        std::vector<clsBankClient> vClients = clsBankClient::getClientsList();

        std::string Title = "\t  Client List Screen";
        std::string SubTitle = "\t\t(" + std::to_string(vClients.size()) + ") Client(s).";

        _DrawScreenHeader(Title, SubTitle);
        std::cout << std::setw(8) << "\n\t_______________________________________________"
                     "___________________________________________________\n" << std::endl;
        std::cout << std::setw(8) << std::left << "" << "| " << std::left << std::setw(15) << "Account Number";
        std::cout << "| " << std::left << std::setw(20) << "Client Name";
        std::cout << "| " << std::left << std::setw(12) << "Phone";
        std::cout << "| " << std::left << std::setw(20) << "Email";
        std::cout << "| " << std::left << std::setw(10) << "Pin Code";
        std::cout << "| " << std::left << std::setw(12) << "Balance";
        std::cout << std::setw(8) << std::left << "" << "\n\t_________________________________________________"
                     "_________________________________________________\n" << std::endl;

        if (vClients.size() == 0){
            std::cout << "\t\t\t\tNo Client Available In the system! ";
        } else {

            for (clsBankClient& Client : vClients)
            {
                _PrintClientRecordLine(Client);
                std::cout << std::endl;

            }

        }
        std::cout << std::setw(8) << std::left << "" << "\n\t_________________________________________________"
                                                        "_________________________________________________\n" << std::endl;
    }
};
