#pragma once

#include <iostream>
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsInputValidate.h"
#include "../../clsScreen.h"
#include "../../Global.h"

class clsTransferScreen : protected clsScreen {
private:
    static void _PrintClient(clsBankClient Client) {
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

    static std::string _ReadAccountNumber(std::string Message) {
        std::string AccountNumber;
        std::cout << Message;
        AccountNumber = clsInputValidate<std::string>::ReadString();
        while (!clsBankClient::isClientExist(AccountNumber)) {
            std::cout << "\nAccount Number is Not exists, Please enter another one: ";
            AccountNumber = clsInputValidate<std::string>::ReadString();
        }
        return AccountNumber;
    }

    static float ReadAmount(clsBankClient SourceClient) {
        std::cout << "\n\n\nEnter Transfer Amount? ";
        float Amount = clsInputValidate<float>::ReadNumber();
        while (Amount > SourceClient.getAccountBalance()) {
            std::cout << "\nAmount Exceeds the available Balance, Enter another Amount? ";
            Amount = clsInputValidate<float>::ReadNumber();
        }
        return Amount;
    }

public:
    static void ShowTransferScreen() {
        _DrawScreenHeader("\t  Transfer Screen");

        clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Account Number to Transfer From: "));
        _PrintClient(SourceClient);

        clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("\n\nPlease Enter Account Number to Transfer To: "));
        _PrintClient(DestinationClient);

        float Amount = ReadAmount(SourceClient);

        std::cout << "\n\nAre you sure you want to perform this transaction? ";
        char Answer = 'n';
        std::cin >> Answer;
        if (tolower(Answer) == 'y') {
            if (SourceClient.Transfer(DestinationClient, Amount, CurrentUser.getUsername())) {
                std::cout << "\nTransfer done Successfully\n";
            }
            else {
                std::cout << "\nTransfer Faild.\n";
            }
        }

        _PrintClient(SourceClient);
        _PrintClient(DestinationClient);
    }
};