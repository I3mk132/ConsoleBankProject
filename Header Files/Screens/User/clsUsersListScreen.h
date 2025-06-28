#pragma once

#include <iostream>
#include "../../Core/clsPerson.h"
#include "../../clsScreen.h"
#include "../../Core/clsUser.h"
#include <iomanip>

class clsUsersListScreen : protected clsScreen {
private:
    static void _PrintUserRecordLine(clsUser User)
    {

        std::cout << std::setw(8) << std::left << "" << "| " << std::setw(12) << std::left << User.getUsername();
        std::cout << "| " << std::setw(25) << std::left << User.FullName();
        std::cout << "| " << std::setw(12) << std::left << User.getPhone();
        std::cout << "| " << std::setw(20) << std::left << User.getEmail();
        std::cout << "| " << std::setw(10) << std::left << User.getPassword();
        std::cout << "| " << std::setw(12) << std::left << User.getPermissions();

    }

public:
    static void ShowUsersList(){
        std::vector <clsUser> vUsers = clsUser::GetUsersList();

        std::string Title = "\t  User List Screen";
        std::string SubTitle = "\t    (" + std::to_string(vUsers.size()) + ") User(s).";

        _DrawScreenHeader(Title, SubTitle);

        std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
        std::cout << "______________________________________________\n" << std::endl;

        std::cout << std::setw(8) << std::left << "" << "| " << std::left << std::setw(12) << "Username";
        std::cout << "| " << std::left << std::setw(25) << "Full Name";
        std::cout << "| " << std::left << std::setw(12) << "Phone";
        std::cout << "| " << std::left << std::setw(20) << "Email";
        std::cout << "| " << std::left << std::setw(10) << "Password";
        std::cout << "| " << std::left << std::setw(12) << "Permissions";
        std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
        std::cout << "______________________________________________\n" << std::endl;

        if (vUsers.size() == 0)
            std::cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (clsUser& User : vUsers)
            {

                _PrintUserRecordLine(User);
                std::cout << std::endl;
            }

        std::cout << std::setw(8) << std::left << "" << "\n\t_______________________________________________________";
        std::cout << "______________________________________________\n" << std::endl;
    }
};