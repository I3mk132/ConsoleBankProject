#pragma once

#include <iostream>
#include <cstdlib>
#include "clsDate.h"



class clsUtil {

public:
    enum enCharType {
        SmallLetter = 1, CapitalLetter = 2,
        Digit = 3, MixChars = 4, SpecialCharacter = 5
    };
    static void Srand(){
        //Seeds the random number generator in C++, called only once
        srand((unsigned)time(NULL));
    }
    // =======================================================

    static int RandomNumber(int From, int To){
        return rand() % (To - From + 1) + From;
    }

    // =======================================================

    static char GetRandomCharacter(enCharType CharType){

        // Capital-Small-Digit
        if (CharType == enCharType::MixChars){
            CharType = (enCharType) RandomNumber(1, 3);
        }

        switch (CharType){
            case enCharType::CapitalLetter:{
                return char(RandomNumber(65, 90));
            }
            case enCharType::SmallLetter:{
                return char(RandomNumber(97, 122));
            }
            case enCharType::Digit:{
                return char(RandomNumber(48, 57));
            }
            case enCharType::SpecialCharacter:{
                return char(RandomNumber(33, 47));
            }
        }
        return 0;
    }

    // =========================================================

    static std::string GenerateWord(enCharType CharType, short Length){
        std::string sWord = "";
        for (short i = 0; i < Length; i++){
            sWord += GetRandomCharacter(CharType);
        }
        return sWord;
    }

    // =========================================================

    static std::string GenerateKey(enCharType CharType){
        std::string sKey;
        sKey = GenerateWord(CharType, 4) + "-";
        sKey += GenerateWord(CharType, 4) + "-";
        sKey += GenerateWord(CharType, 4) + "-";
        sKey += GenerateWord(CharType, 4);
        return sKey;
    }

    // ==========================================================

    static void GenerateKeys(short NumberOfKeys, enCharType CharType){
        for (short i = 1; i <= NumberOfKeys; i++){
            std::cout << "Key [" << i << "] : ";
            std::cout << GenerateKey(CharType) << std::endl;
        }
    }

    // ==========================================================

    static void FillArrayWithRandomNumbers(int arr[100], short arrLength, int From, int To){
        for (short i = 0; i < arrLength; i++){
            arr[i] = RandomNumber(From, To);
        }
    }

    // =========================================================

    static void FillArrayWithRandomWords(std::string arr[100], short arrLength, enCharType CharType, short WordLength){
        for (short i = 0; i < arrLength; i++){
            arr[i] = GenerateWord(CharType, WordLength);
        }
    }

    // =========================================================

    static void FillArrayWithRandomKeys(std::string arr[100], short arrLength, enCharType CharType){
        for (short i = 0; i < arrLength; i++){
            arr[i] = GenerateKey(CharType);
        }
    }

    // ========================================================

    static void Swap(int& A, int& B){
        int Temp;

        Temp = A;
        A = B;
        B = Temp;
    }
    static void Swap(double& A, double& B){
        double Temp;

        Temp = A;
        A = B;
        B = Temp;
    }
    static void Swap(bool& A, bool& B){
        bool Temp;

        Temp = A;
        A = B;
        B = Temp;
    }
    static void Swap(char& A, char& B){
        char Temp;

        Temp = A;
        A = B;
        B = Temp;
    }
    static void Swap(std::string& A, std::string& B){
        std::string Temp;

        Temp = A;
        A = B;
        B = Temp;
    }
    static void Swap(clsDate& A, clsDate& B){
        clsDate::SwapDates(A, B);
    }

    // =======================================================

    static void ShuffleArray(int arr[100], short arrLength){
        for (short i = 0; i < arrLength; i++){
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
        }
    }
    static void ShuffleArray(std::string arr[100], short arrLength){
        for (short i = 0; i < arrLength; i++){
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
        }
    }

    // ======================================================

    static std::string Tabs(short NumberOfTabs){
        std::string t;
        for (short i = 0; i < NumberOfTabs; i++){
            t += "\t";
        }
        return t;
    }

    // ======================================================

    static std::string EncryptText(std::string Text, short EncryptionKey=2){
        for (int i = 0; i <= Text.length(); i++){
            Text[i] = char((int)Text[i] + EncryptionKey);
        }
        return Text;
    }
    static std::string DecryptText(std::string Text, short EncryptionKey=2){
        for (int i = 0; i <= Text.length(); i++){
            Text[i] = char((int)Text[i] - EncryptionKey);
        }
        return Text;
    }

    // ======================================================

    static std::string NumberToText(long Number){
        std::string Sentence = "";

        std::string OneToNineteen[] = {
                "Zero", "One", "Two", "Three", "Four",
                "Five", "Six", "Seven", "Eight", "Nine",
                "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen",
                "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"
        };
        std::string Tens[] = {
                "", "", "Twenty", "Thirty", "Forty",
                "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"
        };

        if (Number == 0) {
            return Sentence;
        }

        if (Number >= 1 && Number <= 19) {
            return OneToNineteen[Number] + " ";
        }

        if (Number >= 20 && Number <= 99) {
            return Tens[Number / 10] + " " + NumberToText(Number % 10);
        }

        if (Number >= 100 && Number <= 199) {
            return "Hundred " + NumberToText(Number % 100);
        }

        if (Number >= 200 && Number <= 999) {
            return OneToNineteen[Number / 100] + " Hundred " + NumberToText(Number % 100);
        }

        if (Number >= 1000 && Number <= 1999) {
            return "Thousand " + NumberToText(Number % 1000);
        }

        if (Number >= 2000 && Number <= 999999) {
            return NumberToText(Number / 1000) + "Thousand " + NumberToText(Number % 1000);
        }

        if (Number >= 1000000 && Number <= 1999999) {
            return "Million " + NumberToText(Number % 1000000);
        }

        if (Number >= 2000000 && Number <= 999999999) {
            return NumberToText(Number / 1000000) + "Million " + NumberToText(Number % 1000000);
        }

        if (Number >= 1000000000 && Number <= 1999999999) {
            return "Billion " + NumberToText(Number % 1000000000);
        }
        else {
            return NumberToText(Number / 1000000000) + "Billion " + NumberToText(Number % 1000000000);
        }

    }

};