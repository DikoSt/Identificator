#include "Identificator.h"

Identificator::Identificator():Identificator("A1"){}

Identificator::Identificator(std::string initStr){
        mLockString = new std::mutex;
        if (checkInputStr(initStr)){
            mIdentificator = initStr;
        } else {
            std::cout << "Incorrect identificator";
        }
}

Identificator::~Identificator(){
    if (mLockString != nullptr){
        delete mLockString;
    }
}

/* Метод инкрементации младшего разряда октета (цифра)
 * если переполнение позвращает true, в противном случае false
 */
bool Identificator::incDigit(char &digit){
    if ( digit =='9' ){
        digit = '1';
        return true;
    }else {
        digit += 1;
        return false; 
    }
}

/* Метод инкрементации старшего разряда октета (буква)
 * если переполнение позвращает true, в противном случае false
 */
bool Identificator::incAlpha(char &alpha){
   if ( alpha =='Z' ){
        alpha = 'A';
        return true;
    }else {
        while (notPresent.find(alpha += 1) != std::string::npos){
        }
        return false; 
    }
}

void Identificator::incIdentificator(int shift) {
  if (mIdentificator.empty()) return;

  if (shift == amountOctets * 3 + 1) { // если 10 октетов и переполнение, значи начинаем всё с начала - с А1
    mIdentificator = "A1";
    return;
  }

  int currentIndex = mIdentificator.size() - shift;
  if (currentIndex < 0 ){
    mIdentificator = "A1-" + mIdentificator;
    return;
  }
  if (incDigit(mIdentificator[currentIndex])){
    if(incAlpha(mIdentificator[currentIndex-1])){
        incIdentificator(shift + 3);
        return;
    }
  }
}

Identificator& Identificator::operator ++(){
    mLockString->lock();
    incIdentificator();
    mLockString->unlock();
    return *this;
}

Identificator Identificator::operator ++ (int){
        mLockString->lock();
        Identificator prev = *this;
        incIdentificator();
        mLockString->unlock();
        return prev;
    }

Identificator& Identificator::operator = (const std::string &id){
        if (checkInputStr(id)){
            mIdentificator = id;
        }
        return *this;
    }

std::ostream& operator<<(std::ostream &out, const Identificator &idf){
        out << idf.mIdentificator;
        return out;
    }


bool Identificator::checkInputStr(const std::string &inputStr){
        if (inputStr.size() > 29){
            return false;
        }

        for (int i=2; i < inputStr.size(); i+=3){
            if (inputStr[i] != '-') {
                return false ;
            }
        }

    for (const auto &ch : inputStr){
        if (notPresent.find(ch)!= std::string::npos){
            return false;
        }
    }
    return true;
}

