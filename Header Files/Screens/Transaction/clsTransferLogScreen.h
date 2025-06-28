#pragma once

#include <iostream>
#include "../../Core/clsBankClient.h"
#include <vector>
#include "../../clsScreen.h"

class clsTransferLogScreen : protected clsScreen {
private:
    static void _PrintTransferLogLine(clsBankClient::stTransferLog& Info){
        std::cout << std::setw(8) << std::left << "" << "| " << std::left << std::setw(30) << Info.Date;
        std::cout << "| " << std::left << std::setw(10) << Info.SourceAccountNumber;
        std::cout << "| " << std::left << std::setw(10) << Info.DestinationAccountNumber;
        std::cout << "| " << std::left << std::setw(10) << Info.TransferAmount;
        std::cout << "| " << std::left << std::setw(10) << Info.SourceAccountBalance;
        std::cout << "| " << std::left << std::setw(10) << Info.DestinationAccountBalance;
        std::cout << "| " << std::left << std::setw(15) << Info.User;
    }

public:
    static void ShowTransferLog(){

        std::vector<clsBankClient::stTransferLog> vTransferLogRecords = clsBankClient::LoadTransferLogRecordFromFile();

        std::string Title = "\t  Transfer Log List Screen";
        std::string SubTitle = "\t\t(" + std::to_string(vTransferLogRecords.size()) + ") Records(s).";

        _DrawScreenHeader(Title, SubTitle);
        std::cout << std::setw(8) << "" << "_______________________________________________"
                     "___________________________________________________\n" << std::endl;
        std::cout << std::setw(8) << "" << "| " << std::left << std::setw(30) << "Date/Time";
        std::cout << "| " << std::left << std::setw(10) << "s.Acct";
        std::cout << "| " << std::left << std::setw(10) << "d.Acct";
        std::cout << "| " << std::left << std::setw(10) << "Amount";
        std::cout << "| " << std::left << std::setw(10) << "s.Balance";
        std::cout << "| " << std::left << std::setw(10) << "d.Balance";
        std::cout << "| " << std::left << std::setw(15) << "User\n";
        std::cout << std::setw(8) << "" << "_______________________________________________"
                     "___________________________________________________\n" << std::endl;

        if (vTransferLogRecords.size() == 0){
            std::cout << "\t\t\t\tThere are no Transfer Logs in the system! ";
        } else {

            for (clsBankClient::stTransferLog& Log : vTransferLogRecords)
            {
                _PrintTransferLogLine(Log);
                std::cout << std::endl;

            }

        }
        std::cout << std::setw(8) << "" << "_________________________________________________"
                                                        "_________________________________________________\n" << std::endl;
    }
};