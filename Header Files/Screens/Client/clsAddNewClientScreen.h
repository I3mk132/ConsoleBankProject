#pragma once

#include <iostream>
#include "../../clsScreen.h"
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsInputValidate.h"

class clsAddNewClientScreen : protected clsScreen {
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
    static void ShowAddNewClientScreen(){

        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClients)){
            return;
        }

        _DrawScreenHeader("\t  Add New Client Screen");

        std::string AccountNumber = "";

        std::cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate<std::string>::ReadString();

        while (clsBankClient::isClientExist(AccountNumber)){
            std::cout << "\nAccount Number is Already Used, Choose enter another one: ";
            AccountNumber = clsInputValidate<std::string>::ReadString();
        }

        clsBankClient NewClient = clsBankClient::getAddNewClientObject(AccountNumber);

        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult = NewClient.Save();
        switch (SaveResult)
        {
            case clsBankClient::enSaveResults::svSucceeded:{
                std::cout << "\nAccount Created Successfully. " << std::endl;
                _PrintClient(NewClient);
                break;
            }
            case clsBankClient::enSaveResults::svFailedEmptyObject:{
                std::cout << "\nError. Account Was not saved because it is Empty. " << std::endl;
                break;
            }
            case clsBankClient::enSaveResults::svFailedAccountNumberExists:{
                std::cout << "\nError Account was not saved because account number is used! " << std::endl;
                break;
            }
        }
    }
};