#pragma once
#include <iostream>
#include "../../Lib/clsInputValidate.h"
#include "../../clsScreen.h"
#include "../../Core/clsBankClient.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsManageUsersScreen : protected clsScreen {
private:
    enum enManageUsersMenuOptions {
        eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
        eUpdateUser = 4, eFindUser = 5, eMainMenu = 6
    };

    static short ReadManageUsersMenuOption(){
        std::cout << std::setw(37) << std::left << "" << "Choose what do you want to do? [1 to 6]? ";
        return clsInputValidate<short>::ReadNumberBetween(1, 6);
    }

    static void _GoBackToManageUsersMenu(){
        std::cout << "\n\nPress any key to go back to Manage Users Menu...";
        system("pause > 0");
        ShowManageUsersMenu();
    }

    static void _ShowListUsersScreen(){
        clsUsersListScreen::ShowUsersList();
        //std::cout << "\nShow list users screen will be here .\n";
    }

    static void _ShowAddNewUserScreen(){
        clsAddNewUserScreen::ShowAddNewUserScreen();
        //std::cout << "\nShow Add new user screen will be here \n";
    }

    static void _ShowDeleteUserScreen(){
        clsDeleteUserScreen::ShowDeleteUserScreen();
        //std::cout << "\nShow Delete User screen will be here \n";
    }

    static void _ShowUpdateUserScreen(){
        clsUpdateUserScreen::ShowUpdateUserScreen();
        //std::cout << "\nShow Update User Screen will be here \n";
    }

    static void _ShowFindUserScreen(){
        clsFindUserScreen::ShowFindUserScreen();
        //std::cout << "\nShow Find User Screen will be here \n";
    }

    static void _PerformManageUsersMenuOption(enManageUsersMenuOptions Option){
        switch (Option) {
            case enManageUsersMenuOptions::eListUsers:{
                system("cls");
                _ShowListUsersScreen();
                _GoBackToManageUsersMenu();
                break;
            }
            case enManageUsersMenuOptions::eAddNewUser:{
                system("cls");
                _ShowAddNewUserScreen();
                _GoBackToManageUsersMenu();
                break;
            }
            case enManageUsersMenuOptions::eDeleteUser:{
                system("cls");
                _ShowDeleteUserScreen();
                _GoBackToManageUsersMenu();
                break;
            }
            case enManageUsersMenuOptions::eUpdateUser:{
                system("cls");
                _ShowUpdateUserScreen();
                _GoBackToManageUsersMenu();
                break;
            }
            case enManageUsersMenuOptions::eFindUser:{
                system("cls");
                _ShowFindUserScreen();
                _GoBackToManageUsersMenu();
                break;
            }
            case enManageUsersMenuOptions::eMainMenu:{
                // empty
            }
        }
    }

public:
    static void ShowManageUsersMenu(){

        if (!CheckAccessRights(clsUser::enPermissions::pManageUsers)){
            return;
        }
        system("cls");
        _DrawScreenHeader("\t  Manage Users Screen");

        std::cout << std::setw(37) << std::left << "" << "===========================================\n";
        std::cout << std::setw(37) << std::left << "" << "\t\t  Manage Users Menu \n";
        std::cout << std::setw(37) << std::left << "" << "===========================================\n";
        std::cout << std::setw(37) << std::left << "" << "\t[1] List Users.\n";
        std::cout << std::setw(37) << std::left << "" << "\t[2] Add New User. \n";
        std::cout << std::setw(37) << std::left << "" << "\t[3] Delete User. \n";
        std::cout << std::setw(37) << std::left << "" << "\t[4] Update User. \n";
        std::cout << std::setw(37) << std::left << "" << "\t[5] Find User. \n";
        std::cout << std::setw(37) << std::left << "" << "\t[6] Main Menu. \n";
        std::cout << std::setw(37) << std::left << "" << "===========================================\n";

        _PerformManageUsersMenuOption((enManageUsersMenuOptions) ReadManageUsersMenuOption());
    }
};