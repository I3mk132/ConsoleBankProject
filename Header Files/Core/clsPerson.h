#pragma once
#include <iostream>
#include "../InterfaceCommunication.h"


class clsPerson : public InterFaceCommunication
{
private:
    std::string _FirstName;
    std::string _LastName;
    std::string _Email;
    std::string _Phone;

public:
    // Constructor
    clsPerson(std::string FirstName, std::string LastName, std::string Email, std::string Phone)
    {
        _FirstName = FirstName;
        _LastName = LastName;
        _Email = Email;
        _Phone = Phone;
    }

    // Property Set
    void setFirstName(std::string FirstName){
        _FirstName = FirstName;
    }
    // Property Get
    std::string getFirstName(){
        return _FirstName;
    }

    // Property Set
    void setLastName(std::string LastName){
        _LastName = LastName;
    }
    // Property Get
    std::string getLastName(){
        return _LastName;
    }

    // Property Set
    void setEmail(std::string Email){
        _Email = Email;
    }
    // Property Get
    std::string getEmail(){
        return _Email;
    }

    // Property Set
    void setPhone(std::string Phone){
        _Phone = Phone;
    }
    // Property Get
    std::string getPhone() {
        return _Phone;
    }

    void Print()
    {
        std::cout << "\nInfo: ";
        std::cout << "\n______________________";
        std::cout << "\nFirstName : " << _FirstName;
        std::cout << "\nLastName  : " << _LastName;
        std::cout << "\nFullName  : " << FullName();
        std::cout << "\nEmail     : " << _Email;
        std::cout << "\nPhone     : " << _Phone;
        std::cout << "\n______________________\n";
    }

    std::string FullName(){
        return _FirstName + " " + _LastName;
    }

    void SendEmail(std::string Title, std::string Body) {
        std::cout << Title << Body << std::endl;
    }
    void SendSMS(std::string Title, std::string Body) {
        std::cout << Title << Body << std::endl;
    }
    void SendFax(std::string Title, std::string Body) {
        std::cout << Title << Body << std::endl;
    }

};