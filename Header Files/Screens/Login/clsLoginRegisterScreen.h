#pragma once

#include <iostream>
#include "../../clsScreen.h"
#include "../../Core/clsUser.h"
#include <vector>

class clsLoginRegisterScreen : protected clsScreen {
private:

    static void _PrintClientRecordLine(clsUser::stLoginRegisterRecord Log){
        std::cout << std::setw(8) << std::left << "" << "| " << std::setw(35) << std::left  << Log.Time;
        std::cout << "| " << std::left << std::setw(20) << Log.Username;
        std::cout << "| " << std::left << std::setw(20) << Log.Password;
        std::cout << "| " << std::left << std::setw(10) << Log.Permissions;
    }
public:
    static void ShowLoginRegisterScreen(){

        if (!CheckAccessRights(clsUser::enPermissions::pLoginRegister)){
            return;
        }

        std::vector<clsUser::stLoginRegisterRecord> vLog = clsUser::LoadLoginRegisterRecordFromFile();
        _DrawScreenHeader("\t  Login Register List Screen", "\t\t(" + std::to_string(vLog.size()) + ") Record(s).");

        std::cout << std::setw(8) << std::left << "" << "_______________________________________________________";
        std::cout << "_____________________________________\n";
        std::cout << std::setw(8) << std::left << "" << "| " << std::setw(35) << std::left << "Date/Time";
        std::cout << "| " << std::setw(20) << std::left << "Username";
        std::cout << "| " << std::setw(20) << std::left << "Password";
        std::cout << "| " << std::setw(10) << std::left << "Permissions\n";
        std::cout << std::setw(8) << std::left << "" << "_______________________________________________________";
        std::cout << "_____________________________________\n";

        if (!vLog.size() == 0){
            for (clsUser::stLoginRegisterRecord& Log : vLog){
                _PrintClientRecordLine(Log);
                std::cout << std::endl;
            }
        }
        else {
            std::cout << std::setw(8) << std::left << "There is no Log Registers. \n";
        }

        std::cout << std::setw(8) << std::left << "" << "_______________________________________________________";
        std::cout << "_____________________________________\n";


    }
};