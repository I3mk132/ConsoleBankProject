#pragma once

#include <iostream>
#include "Global.h"
#include "Lib/clsDate.h"

class clsScreen {
protected:
    static void _DrawScreenHeader(std::string Title, std::string SubTitle = ""){
        std::cout << "\t\t\t\t\t____________________________________________";
        std::cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != ""){
            std::cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        std::cout << "\n\t\t\t\t\t____________________________________________\n";

        std::cout << "\t\t\t\t\t\t\t\tDate : " << clsDate::DateToString(clsDate());
        std::cout << "\n\t\t\t\t\t\t\t\tUser : " << CurrentUser.getUsername() << "\n\n";
    }

    static bool CheckAccessRights(clsUser::enPermissions Permissions)
    {
        if (!CurrentUser.CheckAccessPermissions(Permissions)){
            std::cout << "\t\t\t\t\t______________________________________";
            std::cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            std::cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else {
            return true;
        }
    }


};