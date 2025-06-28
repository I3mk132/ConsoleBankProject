#pragma once
#include <iostream>
#include <string>
#include "../Lib/clsString.h"
#include "clsPerson.h"
#include <vector>
#include <fstream>
#include "../Lib/clsDate.h"

class clsBankClient : public clsPerson {
private:
    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2};
    enMode _Mode;

    std::string _AccountNumber;
    std::string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;

    static clsBankClient _ConvertLineToClientObject(std::string Line, std::string Seperator = "#//#")
    {
        std::vector<std::string> vClientDate = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientDate[0], vClientDate[1],
            vClientDate[2],vClientDate[3], vClientDate[4], vClientDate[5],
            stof(vClientDate[6]));
    }

    static std::string _ConvertClientObjectToLine(clsBankClient Client, std::string Seperator = "#//#")
    {
        std::string S;
        S = Client.getFirstName() + Seperator;
        S += Client.getLastName() + Seperator;
        S += Client.getEmail() + Seperator;
        S += Client.getPhone() + Seperator;
        S += Client.AccountNumber() + Seperator;
        S += Client.getPinCode() + Seperator;
        S += std::to_string(Client.getAccountBalance());
        return S;
    }

    static clsBankClient _GetEmptyClientObject(){
        return clsBankClient(enMode::EmptyMode, "", "",
            "", "", "", "", 0);
    }

    static std::vector<clsBankClient> _LoadClientDataFromFile() {
        std::fstream File;
        std::vector<clsBankClient> vClients;

        File.open("Database/Clients.txt", std::ios::in); // Read Mode
        if (File.is_open()) {
            std::string Line;
            while (getline(File, Line)) {
                vClients.push_back(_ConvertLineToClientObject(Line));
            }
            File.close();
        }

        return vClients;
    }

    static void _SaveClientsDataToFile(std::vector<clsBankClient> vClients) {

        std::fstream File;

        File.open("Database/Clients.txt", std::ios::out); // Write mode
        if (File.is_open()) {
            std::string Line;
            for (clsBankClient& C : vClients) {
                if (!C._MarkedForDelete){
                    File << _ConvertClientObjectToLine(C) << std::endl;
                }
            }

            File.close();
        }
    }

    static void _AddDataLineToFile(std::string stDataLine){
        std::fstream File;

        File.open("Database/Clients.txt", std::ios::out | std::ios::app);

        if (File.is_open()){

            File << stDataLine << std::endl;
            File.close();

        }
    }

    void _Update()
    {
        std::vector<clsBankClient> _vClients;
        _vClients = _LoadClientDataFromFile();

        for (clsBankClient& C : _vClients) {
            if (C.AccountNumber() == AccountNumber()) {
                C = *this;
                break;
            }
        }

        _SaveClientsDataToFile(_vClients);
    }

    void _AddNew(){
        _AddDataLineToFile(_ConvertClientObjectToLine(*this));
    }

    std::string _PrepareTransferLogRecord(clsBankClient Destination, float Amount, std::string& Username, std::string Seperator = "#//#") {
        std::string sWord;
        sWord += clsDate::GetSystemDateTimeString() + Seperator;
        sWord += _AccountNumber + Seperator;
        sWord += Destination.AccountNumber() + Seperator;
        sWord += std::to_string(Amount) + Seperator;
        sWord += std::to_string(_AccountBalance) + Seperator;
        sWord += std::to_string(Destination.getAccountBalance()) + Seperator;
        sWord += Username;
        return sWord;
    }

    void _RegisterTransfer(clsBankClient& Destination, float Amount, std::string& Username)
    {
        std::string DataLine = _PrepareTransferLogRecord(Destination, Amount, Username);

        std::fstream File;
        File.open("Database/TransferLog.txt", std::ios::out | std::ios::app);
        if (File.is_open()) {
            File << DataLine << std::endl;
            File.close();
        }
    }

public:

    struct stTransferLog {
        std::string Date;
        std::string SourceAccountNumber;
        std::string DestinationAccountNumber;
        float TransferAmount;
        float SourceAccountBalance;
        float DestinationAccountBalance;
        std::string User;
    };


    clsBankClient(enMode Mode, std::string FirstName, std::string LastName,
        std::string Email, std::string Phone, std::string AccountNumber, std::string PinCode,
        float AccountBalance) : clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;
    }

    bool isEmpty(){
        return (_Mode == enMode::EmptyMode);
    }

    // Property ReadOnly
    std::string AccountNumber(){
        return _AccountNumber;
    }

    // Property Set
    void setPinCode (std::string PinCode){
        _PinCode = PinCode;
    }
    // Property Get
    std::string getPinCode(){
        return _PinCode;
    }

    // Property Set
    void setAccountBalance(float AccountBalance){
        _AccountBalance = AccountBalance;
    }
    // Property Get
    float getAccountBalance() {
        return _AccountBalance;
    }

    // Property Set
    void setMarkedForDelete(bool MarkedForDelete){
        _MarkedForDelete = MarkedForDelete;
    }
    // Property get
    bool getMarkedForDelete(){
        return _MarkedForDelete;
    }

    /*
      No UI Related code inside object.
    void Print()
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << FirstName;
        cout << "\nLastName    : " << LastName;
        cout << "\nFull Name   : " << FullName();
        cout << "\nEmail       : " << Email;
        cout << "\nPhone       : " << Phone;
        cout << "\nAcc. Number : " << _AccountNumber;
        cout << "\nPassword    : " << _PinCode;
        cout << "\nBalance     : " << _AccountBalance;
        cout << "\n___________________\n";

    }*/

    static clsBankClient Find(std::string AccountNumber) {
        std::fstream File;
        std::vector <clsBankClient> vClients;

        File.open("Database/Clients.txt", std::ios::in );
        if (File.is_open()) {
            std::string Line;
            while (getline(File, Line)) {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                if (Client.AccountNumber() == AccountNumber) {
                    File.close();
                    return Client;
                }
                vClients.push_back(Client);
            }

            File.close();

        }
        return _GetEmptyClientObject();
    }

    static clsBankClient Find(std::string AccountNumber, std::string PinCode) {
        std::fstream File;
        std::vector <clsBankClient> vClients;

        File.open("Database/Clients.txt", std::ios::in);
        if (File.is_open()) {
            std::string Line;
            while (getline(File, Line)) {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                if (Client.AccountNumber() == AccountNumber) {
                    File.close();
                    return Client;
                }
                vClients.push_back(Client);
            }

            File.close();
        }
        return _GetEmptyClientObject();
    }

    enum enSaveResults { svFailedEmptyObject = 0, svSucceeded = 1, svFailedAccountNumberExists = 2};
    enSaveResults Save() {
        switch (_Mode) {
            case enMode::EmptyMode: {
                return enSaveResults::svFailedEmptyObject;
            }
            case enMode::UpdateMode: {
                _Update();
                return enSaveResults::svSucceeded;
            }
            case enMode::AddNewMode:{
                // This will add new record to file or database
                if (clsBankClient::isClientExist(_AccountNumber)){
                    return svFailedAccountNumberExists;
                }
                else {
                    _AddNew();

                    // We need to set the mode to update after add new
                    _Mode = enMode::UpdateMode;
                    return enSaveResults::svSucceeded;
                };
            }
            default: {
                return enSaveResults::svFailedEmptyObject;
            }
        }
    }

    static bool isClientExist(std::string AccountNumber) {
        return !clsBankClient::Find(AccountNumber).isEmpty();
    }

    static clsBankClient getAddNewClientObject(std::string AccountNumber){
        return clsBankClient(enMode::AddNewMode, "", "", "",
                             "", AccountNumber, "", 0);
    }

    bool Delete(){
        std::vector<clsBankClient> vClients = _LoadClientDataFromFile();

        for (clsBankClient& C : vClients){
            if (C.AccountNumber() == _AccountNumber){
                C._MarkedForDelete = true;
                break;
            }
        }

        _SaveClientsDataToFile(vClients);
        *this = _GetEmptyClientObject();
        return true;
    }

    static std::vector<clsBankClient> getClientsList(){
        return _LoadClientDataFromFile();
    }

    static double getTotalBalances(){
        std::vector<clsBankClient> vClients = _LoadClientDataFromFile();
        double TotalBalances = 0;
        for (clsBankClient& C : vClients){
            TotalBalances += C.getAccountBalance();
        }
        return TotalBalances;
    }

    void Deposit(float Amount){
        _AccountBalance += Amount;
        Save();
    }

    bool Withdraw(float Amount){

        if (Amount > _AccountBalance) {
            return false;
        } else {
            _AccountBalance -= Amount;
            Save();
            return true;
        }
    }

    bool Transfer(clsBankClient &Destination, float Amount, std::string Username) {
        if (Amount > _AccountBalance) {
            return false;
        }

        Withdraw(Amount);
        Destination.Deposit(Amount);
        _RegisterTransfer(Destination, Amount, Username);
        return true;
    }

    static stTransferLog _ConvertTransferLogLineToRecord(std::string Line, std::string Seperator = "#//#"){
        stTransferLog TransferLogRecord;

        std::vector<std::string> vTransferLogDate = clsString::Split(Line, "#//#");
        TransferLogRecord.Date = vTransferLogDate[0];
        TransferLogRecord.SourceAccountNumber = vTransferLogDate[1];
        TransferLogRecord.DestinationAccountNumber = vTransferLogDate[2];
        TransferLogRecord.TransferAmount = stof(vTransferLogDate[3]);
        TransferLogRecord.SourceAccountBalance = stof(vTransferLogDate[4]);
        TransferLogRecord.DestinationAccountBalance = stof(vTransferLogDate[5]);
        TransferLogRecord.User = vTransferLogDate[6];

        return TransferLogRecord;
    }


    static std::vector<stTransferLog> LoadTransferLogRecordFromFile(){
        std::vector<stTransferLog> vTransferRecord;

        std::fstream File;
        File.open("Database/TransferLog.txt", std::ios::in); // read mode

        if (File.is_open()){
            std::string Line;
            while (getline(File, Line)){
                vTransferRecord.push_back(_ConvertTransferLogLineToRecord(Line));
            }

            File.close();
        }
        return vTransferRecord;
    }

};