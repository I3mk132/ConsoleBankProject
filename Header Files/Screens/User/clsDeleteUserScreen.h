#pragma once

#include <iostream>
#include "../../clsScreen.h"
#include "../../Core/clsUser.h"
#include "../../Lib/clsInputValidate.h"

class clsDeleteUserScreen : protected clsScreen {
private:
    static void _PrintUser(clsUser User){
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
    static void ShowDeleteUserScreen(){
        _DrawScreenHeader("\tDelete User Screen ");

        std::string Username;

        std::cout << "\nPlease Enter Username: ";
        Username = clsInputValidate<std::string>::ReadString();

        while (!clsUser::isUserExists(Username)){
            std::cout << "\nUser is not found, choose another one: ";
            Username = clsInputValidate<std::string>::ReadString();
        }

        clsUser User = clsUser::Find(Username);
        _PrintUser(User);

        std::cout << "\nAre you sure you want to delete this User? y/n? ";

        char Answer = 'n';
        std::cin >> Answer;

        if (tolower(Answer) == 'y'){
            if (User.Delete()){
                std::cout << "\nUser Deleted Successfully :-)\n";
                _PrintUser(User);
            }
            else {
                std::cout << "\nError User Was not Deleted\n";
            }
        }
    }
};