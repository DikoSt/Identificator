#pragma once
#include <iostream>
#include <mutex>

class Identificator{
private:
    const int amountOctets = 10;
    const std::string notPresent = "DFGJMQV0";
    std::string mIdentificator = "";
    std::mutex *mLockString = nullptr;
    
    bool checkInputStr(const std::string &inputStr);
    bool incDigit(char &digit);
    bool incAlpha(char &alpha);
    void incIdentificator(int shift = 1);
public:
    Identificator();
    Identificator(std::string initStr);
    ~Identificator();
    Identificator& operator ++ ();
    Identificator operator ++ (int);
    Identificator& operator = (const std::string &id);
    friend std::ostream& operator<<(std::ostream &out, const Identificator &idf);
};
