#pragma once

#include <iostream>
#include "../../clsScreen.h"
#include "../../Core/clsUser.h"
#include "../../Lib/clsInputValidate.h"

class clsAddNewUserScreen : protected clsScreen {
private:

    static int _ReadPermissionsToSet()
    {

        int Permissions = 0;
        char Answer = 'n';


        std::cout << "\nDo you want to give full access? y/n? ";
        std::cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        std::cout << "\nDo you want to give access to : \n ";

        std::cout << "\nShow Client List? y/n? ";
        std::cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pListClients;
        }

        std::cout << "\nAdd New Client? y/n? ";
        std::cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pAddNewClients;
        }

        std::cout << "\nDelete Client? y/n? ";
        std::cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pDeleteClients;
        }

        std::cout << "\nUpdate Client? y/n? ";
        std::cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }

        std::cout << "\nFind Client? y/n? ";
        std::cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pFindClients;
        }

        std::cout << "\nTransactions? y/n? ";
        std::cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pTransactions;
        }

        std::cout << "\nManage Users? y/n? ";
        std::cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }

        std::cout << "\nShow Login Register? y/n? ";
        std::cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pLoginRegister;
        }

        return Permissions;

    }

    static void _ReadUsersInfo(clsUser& User)
    {
        std::cout << "\nPlease enter FirstName : ";
        User.setFirstName(clsInputValidate<std::string>::ReadString());

        std::cout << "\nPlease enter LastName : ";
        User.setLastName(clsInputValidate<std::string>::ReadString());

        std::cout << "\nPlease enter Email : ";
        User.setEmail(clsInputValidate<std::string>::ReadString());

        std::cout << "\nPlease enter Phone : ";
        User.setPhone(clsInputValidate<std::string>::ReadString());

        std::cout << "\nPlease enter Password : ";
        User.setPassword(clsInputValidate<std::string>::ReadString());

        User.setPermissions(_ReadPermissionsToSet());
    }

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
    static void ShowAddNewUserScreen(){
        _DrawScreenHeader("\t  Add New User Screen");

        std::string Username;

        std::cout << "Please Enter Username: ";
        Username = clsInputValidate<std::string>::ReadString();
        while (clsUser::isUserExists(Username)){
            std::cout << "\nUsername Is already Used, Choose another one: ";
            Username = clsInputValidate<std::string>::ReadString();
        }

        clsUser NewUser = clsUser::getAddNewUserObject(Username);
        _ReadUsersInfo(NewUser);

        clsUser::enSaveResults SaveResult;

        SaveResult = NewUser.Save();

        switch (SaveResult) {
            case clsUser::enSaveResults::svSucceeded:{
                std::cout << "\nUser Added Successfully :-)\n";
                _PrintUser(NewUser);
                break;
            }
            case clsUser::enSaveResults::svFailedEmptyObject:{
                std::cout << "\nError User was not saved because it's Empty. ";
                break;
            }
            case clsUser::enSaveResults::svFailedUsernameExists:{
                std::cout << "\nError User was not saved because Username is Used!\n";
                break;
            }
        }
    }
};