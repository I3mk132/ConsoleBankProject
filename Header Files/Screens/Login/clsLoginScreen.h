#pragma once

#include "../../Core/clsUser.h"
#include "../../Lib/clsInputValidate.h"
#include "../../Global.h"
#include "../../clsScreen.h"
#include "../../clsMainScreen.h"



class clsLoginScreen : protected clsScreen {
private:
    static bool _Login(){
        short Trials = 3;
        bool LoginFailed = false;
        std::string Username, Password;

        do {

            if (LoginFailed){
                std::cout << "\nInvalid Username/Password!";
                Trials--;
                if (Trials == 0){
                    std::cout << "\nYour are Locked after 3 filed Trials. ";
                    return false;
                }
                    std::cout << "\nYou have " << Trials <<  " Trials to login.\n\n";
            }

            std::cout << "\nEnter Username? ";
            Username = clsInputValidate<std::string>::ReadString();

            std::cout << "\nEnter Password? ";
            Password = clsInputValidate<std::string>::ReadString();

            CurrentUser = clsUser::Find(Username, Password);

            LoginFailed = CurrentUser.isEmpty();

        } while (LoginFailed);

        CurrentUser.RegisterLogin();
        clsMainScreen::ShowMainMenu();
        return true;
    }

public:
    static bool ShowLoginScreen(){
        system("cls");
        _DrawScreenHeader("\t  Login Screen ");
        return _Login();
    }
};