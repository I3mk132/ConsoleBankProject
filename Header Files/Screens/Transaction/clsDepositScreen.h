#pragma once

#include <iostream>
#include "../../clsScreen.h"
#include "../../Lib/clsInputValidate.h"
#include "../../Core/clsBankClient.h"

class clsDepositScreen : protected clsScreen {
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
    static void ShowDepositScreen(){
        _DrawScreenHeader("\t  Deposit Screen ");

        std::cout << "Please Enter AccountNumber? : ";
        std::string AccountNumber = clsInputValidate<std::string>::ReadString();

        while (!clsBankClient::isClientExist(AccountNumber)){
            std::cout << "\nClient with [" << AccountNumber << "] does not exists. Enter another one: ";
            AccountNumber = clsInputValidate<std::string>::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        float Amount = 0;
        std::cout << "\nPlease enter deposit amount? ";
        Amount = clsInputValidate<float>::ReadNumber();

        std::cout << "\nAre you sure you want to perform this transaction? ";
        char Answer = 'n';
        std::cin >> Answer;

        if (tolower(Answer) == 'y'){
            Client.Deposit(Amount);
            std::cout << "\nAmount Deposited Successfully. \n";
            std::cout << "\nNew Balance is: " << Client.getAccountBalance();
        } else {
            std::cout << "\nOperation was canceled.\n";
        }
    }
};