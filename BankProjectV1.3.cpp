#include <iostream>
#include "Header Files/Screens/Login/clsLoginScreen.h"
#include "Header Files/Global.h"
#include "Header Files/Lib/clsUtil.h"

using namespace std;


int main() {
    
    clsUtil::Srand();

    
    clsLoginScreen::ShowLoginScreen();

    return 0;
}