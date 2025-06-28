#pragma once

#include <iostream>
#include "../../clsScreen.h"
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsInputValidate.h"

class clsDeleteClientScreen : protected clsScreen {
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
    static void ShowDeleteClientScreen(){

        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClients)){
            return;
        }
        std::string AccountNumber = "";

        _DrawScreenHeader("\tDelete Client Screen");

        std::cout << "\nPlease Enter AccountNumber: ";
        AccountNumber = clsInputValidate<std::string>::ReadString();
        while (!clsBankClient::isClientExist(AccountNumber)){
            std::cout << "\nAccount Number is not found. choose another one: ";
            AccountNumber = clsInputValidate<std::string>::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        std::cout << "\nAre you Sure you want to delete this user? ";
        char Sure = 'n';
        std::cin >> Sure;

        if (tolower(Sure) == 'y'){
            if (Client.Delete()){
                std::cout << "\nClient Deleted Successfully. :-)" << std::endl;
                _PrintClient(Client);
            }
            else {
                std::cout << "\nError Client Was not Deleted" << std::endl;
            }
        }
    }

};