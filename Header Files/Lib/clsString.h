#pragma once
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>


class clsString {
private:
    // string
    std::string _Value;
    // character
    char _Character ;


public:
    clsString() {
        this->_Value = "";
    }
    clsString(std::string Value) {
        this->_Value = Value;
    }
    clsString(char Character) {
        this->_Character = Character;
    }
    clsString(std::string Value, char Character) {
        this->_Value = Value;
        this->_Character = Character;
    }



    void setCharacter(char Character) {
        this->_Character = Character;
    }
    char Character() {
        return this->_Character;
    }
    void setValue(std::string Value) {
        this->_Value = Value;
    }
    std::string Value() {
        return this->_Value;
    }

    // =======================================================================================================

    static std::vector<char> GetFirstLetterOfEveryWord(std::string Sentence) {
        std::vector<char> vChar;
         bool isFirstLetter = true;

         for (short i = 0; i < Sentence.length(); i++) {

             if (Sentence[i] != ' ' && isFirstLetter) {
                 vChar.push_back(Sentence[i]);
             }

             isFirstLetter = (Sentence[i] == ' ');
         }
        return vChar;
     }
    std::vector<char> GetFirstLetterOfEveryWord() {
        return GetFirstLetterOfEveryWord(_Value);
    }

    // =======================================================================================================

    static void UpperFirstLetterOfEachWord(std::string& Sentence) {
        bool isFirstLetter = true;

        for (short i = 0; i < Sentence.length(); i++) {
            if (Sentence[i] != ' ' && isFirstLetter) {
                Sentence[i] = toupper(Sentence[i]);
            }

            isFirstLetter = (Sentence[i] == ' ') ? true : false;
        }
    }
    void UpperFirstLetterOfEachWord() {
        UpperFirstLetterOfEachWord(_Value);
    }

    // ======================================================================================================

    static void LowerFirstLetterOfEachWord(std::string &Sentence) {
        bool isFirstLetter = true;

        for (short i = 0; i < Sentence.length(); i++) {
            if (Sentence[i] != ' ' && isFirstLetter) {
                Sentence[i] = tolower(Sentence[i]);
            }

            isFirstLetter = (Sentence[i] == ' ');
        }

    }
    void LowerFirstLetterOfEachWord() {
        LowerFirstLetterOfEachWord(_Value);
    }

    // =====================================================================================================

    static std::string UpperAllString(std::string Sentence) {
        for (short i = 0; i < Sentence.length(); i++) {
            Sentence[i] = toupper(Sentence[i]);
        }
        return Sentence;
    }
    void UpperAllString() {
        _Value = UpperAllString(_Value);
    }

    // =====================================================================================================

    static std::string LowerAllString(std::string Sentence) {
        for (short i = 0; i < Sentence.length(); i++) {
            Sentence[i] = tolower(Sentence[i]);
        }
        return Sentence;
    }
    void LowerAllString() {
        _Value = LowerAllString(_Value);
    }

    // =====================================================================================================

    static void InvertLetterCase(char& Letter) {
        Letter =  isupper(Letter) ? tolower(Letter) : toupper(Letter);
    }
    void InvertLetterCase() {
        InvertLetterCase(_Character);
    }

    // ======================================================================================================

    static std::string InvertAllLettersCase(std::string Sentence) {
        for (short i = 0; i < Sentence.length(); i++) {
            InvertLetterCase(Sentence[i]);
        }
        return Sentence;
    }
    void InvertAllLettersCase() {
        _Value = InvertAllLettersCase(_Value);
    }

    // ======================================================================================================

    enum enWhatToCount { CapitalLetter, SmallLetter, All };
    static short CountLetters(std::string Sentence, enWhatToCount WhatToCount = enWhatToCount::All) {
        short Counter = 0;
        for (short i = 0; i < Sentence.length(); i++) {

            if (WhatToCount == enWhatToCount::CapitalLetter && isupper(Sentence[i])) {
                Counter++;
            }

            if (WhatToCount == enWhatToCount::SmallLetter && islower(Sentence[i])) {
                Counter++;
            }

            if (WhatToCount == enWhatToCount::All) {
                Counter++;
            }

        }
        return Counter;
    }
    short CountLetters(enWhatToCount WhatToCount) {
        return CountLetters(_Value, WhatToCount);
    }

    // ===================================================================================================

    static short CountSpecificLetter(std::string Sentence, char Letter, bool MatchCase = true) {
        short Counter = 0;
        for (short i = 0; i < Sentence.length(); i++) {

            if (MatchCase) {

                if (Sentence[i] == Letter) {
                    Counter++;
                }

            }
            else {

                if (islower(Sentence[i]) == islower(Letter)) {
                    Counter++;
                }

            }

        }
        return Counter;
    }
    short CountSpecificLetter(char Letter, bool MatchCase = true) {
        return CountSpecificLetter(_Value, Letter, MatchCase);
    }

    // ==================================================================================================

    static bool isVowel(char Character) {
        char ch = tolower(Character);

        std::vector <char> vVowels = { 'a', 'e', 'i', 'o', 'u'};

        for (char& i : vVowels) {
            if (ch == i) {
                return true;
            }
        }
        return false;
    }
    bool isVowel() {
        return isVowel(_Character);
    }

    // ==================================================================================================

    static short CountVowels(std::string Sentence){
        short Counter = 0;
        for (short i = 0; i < Sentence.length(); i++) {
            if (isVowel(Sentence[i])) {
                Counter++;
            }
        }
        return Counter;
    }
    short CountVowels() {
        return CountVowels(_Value);
    }

    // ==================================================================================================

    static std::vector<char> GetVowels(std::string Sentence){
        std::vector<char> vChar;
        for (short i = 0; i < Sentence.length(); i++){

            if (isVowel(Sentence[i])){
                vChar.push_back(Sentence[i]);
            }
        }
        return vChar;
    }
    std::vector<char> GetVowels() {
        return GetVowels(_Value);
    }

    // ==================================================================================================

    static short CountWords(std::string Sentence){
        std::string delim = " ";
        short pos = 0;
        std::string sword = "";
        short Counter = 0;
        while ((pos = Sentence.find(delim)) != std::string::npos){
            sword = Sentence.substr(0, pos);
            if (sword != ""){
                Counter++;
            }
            Sentence.erase(0, pos + delim.length());
        }
        if (Sentence != ""){
            Counter++;
        }
        return Counter;
    }
    short CountWords() {
        return CountWords(_Value);
    }

    // ==================================================================================================

    static std::vector<std::string> Split(std::string S1, std::string Delim){

        std::vector<std::string> vString;

        short pos = 0;
        std::string sWord; // define a string variable

        // use find() function to get the position of the delimiters
        while ((pos = S1.find(Delim)) != std::string::npos)
        {
            sWord = S1.substr(0, pos); // store the word
            if (sWord != "")
            {
                vString.push_back(sWord);
            }

            S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
        }

        if (S1 != "")
        {
            vString.push_back(S1); // it adds last word of the string.
        }

        return vString;

    }
    std::vector<std::string> Split(std::string Delim) {
        return Split(_Value, Delim);
    }

    // ====================================================================================================

    static std::string TrimLeft(std::string S1){


        for (short i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ')
            {
                return S1.substr(i, S1.length() - i);
            }
        }
        return "";
    }
    void TrimLeft() {
        _Value = TrimLeft(_Value);
    }

    // ===================================================================================================

    static std::string TrimRight(std::string S1){


        for (short i = S1.length() - 1; i >= 0; i--)
        {
            if (S1[i] != ' ')
            {
                return S1.substr(0, i + 1);
            }
        }
        return "";
    }
    void TrimRight() {
        _Value = TrimRight(_Value);
    }

    // ===================================================================================================

    static std::string Trim(std::string S1){
        return (TrimLeft(TrimRight(S1)));

    }
    void Trim(){
        _Value = Trim(_Value);
    }

    // ====================================================================================================

    static std::string JoinString(std::vector<std::string> vString, std::string Delim){

        std::string S1 = "";

        for (std::string& s : vString)
        {
            S1 = S1 + s + Delim;
        }

        return S1.substr(0, S1.length() - Delim.length());

    }
    static std::string JoinString(std::string arrString[], short Length, std::string Delim){

        std::string S1 = "";

        for (short i = 0; i < Length; i++)
        {
            S1 = S1 + arrString[i] + Delim;
        }

        return S1.substr(0, S1.length() - Delim.length());
    }

    // ====================================================================================================

    static std::string ReverseWordsInString(std::string S1){

        std::vector<std::string> vString;
        std::string S2 = "";

        vString = Split(S1, " ");

        // declare iterator
        std::vector<std::string>::iterator iter = vString.end();

        while (iter != vString.begin())
        {

            --iter;

            S2 += *iter + " ";

        }

        S2 = S2.substr(0, S2.length() - 1); //remove last space.

        return S2;
    }
    void ReverseWordsInString() {
        _Value = ReverseWordsInString(_Value);
    }

    // ==================================================================================================

    static std::string ReplaceWord(std::string S1, std::string sToReplace, std::string sRepalceTo, bool MatchCase = true){

        std::vector<std::string> vString = Split(S1, " ");

        for (std::string& s : vString)
        {

            if (MatchCase)
            {
                if (s == sToReplace)
                {
                    s = sRepalceTo;
                }

            }
            else
            {
                if (LowerAllString(s) == LowerAllString(sToReplace))
                {
                    s = sRepalceTo;
                }

            }

        }

        return JoinString(vString, " ");
    }
    void ReplaceWord(std::string sToReplace, std::string sReplaceTo, bool MatchCase = true) {
        _Value =  ReplaceWord(_Value, sToReplace, sReplaceTo, MatchCase);
    }

    // =====================================================================================================

    static std::string RemovePunctuations(std::string S1){

        std::string S2 = "";

        for (short i = 0; i < S1.length(); i++)
        {
            if (!ispunct(S1[i]))
            {
                S2 += S1[i];
            }
        }

        return S2;

    }
    void RemovePunctuations(){
        _Value = RemovePunctuations(_Value);
    }

    // =====================================================================================================

    static short Length(std::string Sentence) {
        return Sentence.length();
    }
    short Length() {
        return Length(_Value);
    }

    // =====================================================================================================

};