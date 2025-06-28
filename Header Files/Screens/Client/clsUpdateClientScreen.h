#pragma once

#include <iostream>
#include "../../clsScreen.h"
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsInputValidate.h"

class clsUpdateClientScreen : protected clsScreen {
private:
    static void _ReadClientInfo(clsBankClient& Client)
    {
        std::cout << "\nPlease enter FirstName : ";
        Client.setFirstName(clsInputValidate<std::string>::ReadString());

        std::cout << "\nPlease enter LastName : ";
        Client.setLastName(clsInputValidate<std::string>::ReadString());

        std::cout << "\nPlease enter Email : ";
        Client.setEmail(clsInputValidate<std::string>::ReadString());

        std::cout << "\nPlease enter Phone : ";
        Client.setPhone(clsInputValidate<std::string>::ReadString());

        std::cout << "\nPlease enter PinCode : ";
        Client.setPinCode(clsInputValidate<std::string>::ReadString());

        std::cout << "\nPlease enter Acc. Balance : ";
        Client.setAccountBalance(clsInputValidate<float>::ReadNumber());
    }

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
    static void ShowUpdateClientScreen(){

        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients)){
            return;
        }
        std::string AccountNumber = "";

        _DrawScreenHeader("\tUpdate Client Screen");

        std::cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate<std::string>::ReadString();
        while (!clsBankClient::isClientExist(AccountNumber)) {
            std::cout << "\nAccount Number is not found. choose another one: ";
            AccountNumber = clsInputValidate<std::string>::ReadString();
        }
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        std::cout << "\n\nUpdate Client Info: ";
        std::cout << "\n_______________________\n";

        _ReadClientInfo(Client1);
        clsBankClient::enSaveResults SaveResult;

        SaveResult = Client1.Save();
        switch (SaveResult) {
            case clsBankClient::enSaveResults::svSucceeded: {
                std::cout << "\nAccount Updated Successfully. " << std::endl;
                _PrintClient(Client1);
                break;
            }
            case clsBankClient::enSaveResults::svFailedEmptyObject: {
                std::cout << "\nERROR. Account was not saved because it is empty. " << std::endl;
                break;
            }
        }
    }
};