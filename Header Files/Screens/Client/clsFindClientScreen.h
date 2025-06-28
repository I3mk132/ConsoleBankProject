#pragma once

#include <iostream>
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsInputValidate.h"
#include "../../clsScreen.h"

class clsShowFindClientScreen : protected clsScreen {
private:
    static void _PrintClient(clsBankClient& Client) {
        std::cout << "\nClient Card: ";
        std::cout << "\n_________________________";
        std::cout << "\nFirstName   : " << Client.getFirstName();
        std::cout << "\nLastName    : " << Client.getLastName();
        std::cout << "\nFullName    : " << Client.FullName();
        std::cout << "\nEmail       : " << Client.getEmail();
        std::cout << "\nPhone       : " << Client.getPhone();
        std::cout << "\nAcc. Number : " << Client.AccountNumber();
        std::cout << "\nPinCode     : " << Client.getPinCode();
        std::cout << "\nBalance     : " << Client.getAccountBalance();
        std::cout << "\n_________________________\n";
    }

public:
    static void ShowFindClientScreen(){

        if (!CheckAccessRights(clsUser::enPermissions::pFindClients)){
            return;
        }

        _DrawScreenHeader("\tFind Client Screen");

        std::string AccountNumber = "";
        std::cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate<std::string>::ReadString();

        while (!clsBankClient::isClientExist(AccountNumber)){
            std::cout << "\nAccount Number is not found, choose another one: ";
            AccountNumber = clsInputValidate<std::string>::ReadString();
        }
        clsBankClient Client = clsBankClient::Find(AccountNumber);

        if (!Client.isEmpty()){
            std::cout << "\nClient Found :-)\n";
        }
        else {
            std::cout << "\nClient Was not Found :-(\n";
        }

        _PrintClient(Client);

    }
};