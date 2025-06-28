#pragma once

#include <iostream>
#include "../../Core/clsUser.h"
#include "../../Lib/clsInputValidate.h"
#include "../../clsScreen.h"

class clsFindUserScreen : protected clsScreen {
private:
    static void _PrintUser(clsUser& User) {
        std::cout << "\nUser Card: ";
        std::cout << "\n_________________________";
        std::cout << "\nFirstName   : " << User.getFirstName();
        std::cout << "\nLastName    : " << User.getLastName();
        std::cout << "\nFullName    : " << User.FullName();
        std::cout << "\nEmail       : " << User.getEmail();
        std::cout << "\nPhone       : " << User.getPhone();
        std::cout << "\nUsername    : " << User.getUsername();
        std::cout << "\nPassword    : " << User.getPassword();
        std::cout << "\nPermissions : " << User.getPermissions();
        std::cout << "\n_________________________\n";
    }

public:
    static void ShowFindUserScreen(){
        _DrawScreenHeader("\t  Find User Screen ");

        std::string Username;
        std::cout << "\nPlease enter Username: ";
        Username = clsInputValidate<std::string>::ReadString();

        while (!clsUser::isUserExists(Username)){
            std::cout << "\nUsername is not found, Please enter another one: ";
            Username = clsInputValidate<std::string>::ReadString();
        }

        clsUser User = clsUser::Find(Username);

        if (!User.isEmpty()){
            std::cout << "\nUser Found :-) \n";
            _PrintUser(User);
        }
        else {
            std::cout << "\nUser Was not Found :-( \n";
        }
    }
};