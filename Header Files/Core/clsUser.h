#pragma once

#include <iostream>
#include <string>
#include "clsPerson.h"
#include "../Lib/clsString.h"
#include <vector>
#include <fstream>
#include "../Lib/clsUtil.h"
#include "../Lib/clsDate.h"

class clsUser : public clsPerson{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode  _Mode;
    std::string _Username;
    std::string _Password;
    int _Permissions;
    bool _MarkedForDelete = false;


    static clsUser _ConvertLineToUserObject(std::string Line, std::string Seperator){
        std::vector<std::string> vUser = clsString::Split(Line, Seperator);



        return clsUser(enMode::UpdateMode, vUser[0], vUser[1],
            vUser[2], vUser[3], vUser[4],
            clsUtil::DecryptText(vUser[5]), stoi(vUser[6]));
    }

    static std::string _ConvertUserObjetToLine(clsUser User, std::string Seperator){
        std::string Line;
        Line += User.getFirstName() + Seperator;
        Line += User.getLastName() + Seperator;
        Line += User.getEmail() + Seperator;
        Line += User.getPhone() + Seperator;
        Line += User.getUsername() + Seperator;
        Line += clsUtil::EncryptText(User.getPassword()) + Seperator;
        Line += std::to_string(User.getPermissions());
        return Line;
    }

    static std::vector<clsUser> _LoadUsersDataFromFile(){
        std::vector<clsUser> vUser;
        std::fstream File;

        File.open("Users.txt", std::ios::in); // read mode
        if (File.is_open()){
            std::string Line;
            while (getline(File, Line)){
                vUser.push_back(_ConvertLineToUserObject(Line, "#//#"));
            }
            File.close();
        }
        return vUser;
    }

    static void _SaveUsersDataToFile(std::vector<clsUser> vUsers){
        std::fstream File;

        File.open("Users.txt", std::ios::out); // Write mode
        if (File.is_open()){
            for (clsUser& U : vUsers){
                if (!U._MarkedForDelete){
                    File << _ConvertUserObjetToLine(U, "#//#") << std::endl;
                }
            }
            File.close();
        }
    }

    static clsUser _GetEmptyUserObject(){
        return clsUser(enMode::EmptyMode, "", "",
                             "", "", "", "", 0);
    }

    static void _AddDataLineToFile(std::string Line){
        std::fstream File;
        File.open("Users.txt", std::ios::out | std::ios::app); // Append mode

        if (File.is_open()){
            File << Line << std::endl;
            File.close();
        }
    }

    void _Update(){
        std::vector<clsUser> vUsers;
        vUsers = _LoadUsersDataFromFile();

        for (clsUser& U: vUsers) {
            if (U.getUsername() == getUsername()){
                U = *this;
                break;
            }
        }

        _SaveUsersDataToFile(vUsers);
    }

    void _AddNew(){
        _AddDataLineToFile(_ConvertUserObjetToLine(*this, "#//#"));
    }

    std::string _PrepareLoginRecord(std::string Seperator = "#//#"){
        std::string sWord;
        sWord += clsDate::GetSystemDateTimeString() + Seperator;
        sWord += _Username + Seperator;
        sWord += clsUtil::EncryptText(_Password) + Seperator;
        sWord += std::to_string(_Permissions);
        return sWord;
    }

public:

    enum enPermissions {
        eAll = -1, pListClients = 1, pAddNewClients = 2, pDeleteClients = 4,
        pUpdateClients = 8, pFindClients = 16, pTransactions = 32, pManageUsers = 64,
        pLoginRegister = 128
    };
     struct stLoginRegisterRecord {
        std::string Time;
        std::string Username;
        std::string Password;
        int Permissions;
    };


    clsUser(enMode Mode, std::string FirstName, std::string LastName,
            std::string Email, std::string Phone, std::string Username,
            std::string Password, int Permissions) :
            clsPerson(FirstName, LastName, Email, Phone)

    {

        _Mode = Mode;
        _Username = Username;
        _Password = Password;
        _Permissions = Permissions;


    }

    bool CheckAccessPermissions(enPermissions Permission){
        if (this->getPermissions() == enPermissions::eAll){
            return true;
        }

        if ((Permission & this->getPermissions()) == Permission){
            return true;
        } else {
            return false;
        }
    }

    // Property get
    enMode getMode() {
        return _Mode;
    }
    // Property set
    void setMode(enMode mode) {
        _Mode = mode;
    }

    // property get
    std::string getUsername() {
        return _Username;
    }
    // property set
    void setUsername(std::string username) {
        _Username = username;
    }

    // property get
    std::string getPassword() {
        return _Password;
    }
    // property set
    void setPassword(std::string password) {
        _Password = password;
    }

    // property get
    int getPermissions () {
        return _Permissions;
    }
    // property set
    void setPermissions(int permissions) {
        _Permissions = permissions;
    }

    // property get
    bool isMarkedForDelete() {
        return _MarkedForDelete;
    }
    // property set
    void setMarkedForDelete(bool markedForDelete) {
        _MarkedForDelete = markedForDelete;
    }


    bool isEmpty(){
        return (_Mode == enMode::EmptyMode);
    }

    static clsUser Find(std::string Username) {
        std::fstream MyFile;
        MyFile.open("Users.txt", std::ios::in);//read Mode

        if (MyFile.is_open()) {
            std::string Line;
            while (getline(MyFile, Line)) {
                clsUser User = _ConvertLineToUserObject(Line, "#//#");
                if (User.getUsername() == Username) {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();

        }

        return _GetEmptyUserObject();
    }

    static clsUser Find(std::string Username, std::string Password) {
        std::fstream MyFile;
        MyFile.open("Users.txt", std::ios::in);//read Mode

        if (MyFile.is_open()) {
            std::string Line;
            while (getline(MyFile, Line)) {
                clsUser User = _ConvertLineToUserObject(Line, "#//#");
                if (User.getUsername() == Username && User.getPassword() == Password) {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();

        }

        return _GetEmptyUserObject();
    }

    enum enSaveResults { svFailedEmptyObject = 0, svSucceeded = 1, svFailedUsernameExists = 2};
    enSaveResults Save(){
        switch (_Mode) {
            case enMode::EmptyMode:{
                return enSaveResults::svFailedEmptyObject;
            }
            case enMode::UpdateMode:{
                _Update();
                return enSaveResults::svSucceeded;
            }
            case enMode::AddNewMode:{
                if (clsUser::isUserExists(_Username)){
                    return enSaveResults::svFailedUsernameExists;
                }
                else {
                    _AddNew();

                    // We need to set the mode to update after add new
                    _Mode = enMode::UpdateMode;
                    return enSaveResults::svSucceeded;
                }
            }

        }
    }

    static bool isUserExists(std::string Username){
        return !clsUser::Find(Username).isEmpty();
    }

    static clsUser getAddNewUserObject(std::string Username){
        return clsUser(enMode::AddNewMode, "", "", "", "",
                       Username, "", 0);
    }

    bool Delete(){
        std::vector<clsUser> _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers){
            if (U.getUsername() == _Username){
                U._MarkedForDelete = true;
                break;
            }
        }
        _SaveUsersDataToFile(_vUsers);

        *this = _GetEmptyUserObject();
        return true;
    }

    static std::vector <clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    void RegisterLogin()
    {
        std::string stDataLine = _PrepareLoginRecord();

        std::fstream File;
        File.open("Log.txt", std::ios::out | std::ios::app);
        if (File.is_open()){
            File << stDataLine << std::endl;
            File.close();
        }
    }

    static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(std::string Line, std::string Seperator = "#//#"){
        stLoginRegisterRecord LoginRegisterRecord;

        std::vector<std::string> vLoginRegisterDate = clsString::Split(Line, "#//#");
        LoginRegisterRecord.Time = vLoginRegisterDate[0];
        LoginRegisterRecord.Username = vLoginRegisterDate[1];
        LoginRegisterRecord.Password = clsUtil::DecryptText(vLoginRegisterDate[2]);
        LoginRegisterRecord.Permissions = stoi(vLoginRegisterDate[3]);
        return LoginRegisterRecord;
    }


    static std::vector<stLoginRegisterRecord> LoadLoginRegisterRecordFromFile(){
        std::vector<stLoginRegisterRecord> vLoginRegisterRecord;

        std::fstream File;
        File.open("Log.txt", std::ios::in); // read mode

        if (File.is_open()){
            std::string Line;
            while (getline(File, Line)){
                vLoginRegisterRecord.push_back(_ConvertLoginRegisterLineToRecord(Line));
            }

            File.close();
        }
        return vLoginRegisterRecord;
    }
};