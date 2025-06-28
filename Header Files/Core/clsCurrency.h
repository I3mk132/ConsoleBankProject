#pragma once
#include <iostream>
#include <vector>
#include "../Lib/clsInputValidate.h"
#include "../Lib/clsString.h"


class clsCurrency {
private:
    enum enMode { EmptyMode = 1, UpdateMode = 2 };
    enMode _Mode;
    std::string _Country;
    std::string _CurrencyCode;
    std::string _CurrencyName;
    float _Rate;

    static clsCurrency _ConvertLineToCurrencyObject(std::string& Line, std::string Seperator = "#//#"){
        std::vector<std::string> vString = clsString::Split(Line, Seperator);

        return clsCurrency(enMode::UpdateMode, vString[0], vString[1],
                           vString[2], stof(vString[3]));
    }
    static std::string _ConvertCurrencyObjectToLine(clsCurrency Currency, std::string Seperator = "#//#"){
        std::string sWord;
        sWord += Currency.Country() + Seperator;
        sWord += Currency.CurrencyCode() + Seperator;
        sWord += Currency.CurrencyName() + Seperator;
        sWord += std::to_string(Currency.Rate());
        return sWord;
    }

    static std::vector<clsCurrency> _LoadCurrencyDataFromFile(){
        std::fstream File;
        std::vector <clsCurrency> vCurrencies;

        File.open("Currencies.txt", std::ios::in);
        if (File.is_open()){
            std::string Line;
            while (getline(File, Line)){
                vCurrencies.push_back(_ConvertLineToCurrencyObject(Line));
            }
            File.close();
        }
        return vCurrencies;
    }
    static void _SaveCurrencyDataToFile(std::vector<clsCurrency> vCurrencies){
        std::fstream File;

        File.open("Currencies.txt", std::ios::out);
        if (File.is_open()){
            for (clsCurrency& Currency : vCurrencies){
                File << _ConvertCurrencyObjectToLine(Currency) << std::endl;
            }
            File.close();
        }
    }

     void _Update(){
        std::vector<clsCurrency> _vCurrencies = _LoadCurrencyDataFromFile();

        for (clsCurrency& Currency : _vCurrencies){
            if (Currency.CurrencyCode() == CurrencyCode()){
                Currency = *this;
                break;
            }
        }

         _SaveCurrencyDataToFile(_vCurrencies);
    }

    static clsCurrency _GetEmptyCurrencyObject(){
        return clsCurrency(enMode::EmptyMode, "", "", "", 0);
    }


public:
    clsCurrency(enMode Mode, std::string Country, std::string CurrencyCode, std::string CurrencyName, float Rate){
        _Mode = Mode;
        _Country = Country;
        _CurrencyCode = CurrencyCode;
        _CurrencyName = CurrencyName;
        _Rate = Rate;
    }


    static std::vector<clsCurrency> GetAllUSDRates(){
        return _LoadCurrencyDataFromFile();
    }

    // Property Get
    std::string Country(){
        return _Country;
    }
    std::string CurrencyCode(){
        return _CurrencyCode;
    }
    std::string CurrencyName(){
        return _CurrencyName;
    }
    float Rate(){
        return _Rate;
    }

    void UpdateRate(float NewRate){
        _Rate = NewRate;
        _Update();
    }

    bool isEmpty(){
        return (_Mode == enMode::EmptyMode);
    }

    static clsCurrency FindByCode(std::string CurrencyCode){
        CurrencyCode = clsString::UpperAllString(CurrencyCode);
        std::fstream File;

        File.open("Currencies.txt", std::ios::in);

        if (File.is_open()){
            std::string Line;
            while (getline(File, Line)){
                clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
                if (Currency.CurrencyCode() == CurrencyCode){
                    File.close();
                    return Currency;
                }
            }
            File.close();
        }

        return _GetEmptyCurrencyObject();
    }
    static clsCurrency FindByCountry(std::string Country){

        Country = clsString::UpperAllString(Country);
        std::fstream File;

        File.open("Currencies.txt", std::ios::in);

        if (File.is_open()){
            std::string Line;
            while (getline(File, Line)){
                clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
                if (clsString::UpperAllString(Currency.Country()) == Country){
                    File.close();
                    return Currency;
                }
            }
            File.close();
        }

        return _GetEmptyCurrencyObject();
    }

    static bool isCurrencyExists(std::string CurrencyCode){
        clsCurrency C = clsCurrency::FindByCode(CurrencyCode);
        return !C.isEmpty();
    }

    static bool isCurrencyExistsByCountry(std::string Country){
        clsCurrency C = clsCurrency::FindByCountry(Country);
        return !C.isEmpty();
    }

    static std::vector<clsCurrency> GetCurrenciesList(){
        return _LoadCurrencyDataFromFile();
    }

    float ConvertToUSD(float Amount){
        return (Amount / Rate());
    }

    float ConvertToOtherCurrency(float Amount, clsCurrency Currency2){
        float AmountUSD = ConvertToUSD(Amount);

        if (Currency2.CurrencyCode() == "USD"){
            return AmountUSD;
        }

        return AmountUSD * Currency2.Rate();
    }

};