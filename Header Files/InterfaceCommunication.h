#pragma once
#include <iostream>
#include <string>

class InterFaceCommunication {
    virtual void SendEmail(std::string Title, std::string Body) = 0;
    virtual void SendSMS(std::string Title, std::string Body) = 0;
    virtual void SendFax(std::string Title, std::string Body) = 0;

};