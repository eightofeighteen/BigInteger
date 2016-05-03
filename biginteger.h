#ifndef BIGINTEGER_H
#define BIGINTEGER_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>
#include <cstring>
#include <new>
#include <cassert>
#include "sharedmemory2.h"
using namespace std;

typedef unsigned short USHORT;

class IntWrapper
{
public:
    inline IntWrapper(unsigned int n)
    {
        i = n;
    }

    unsigned int i;
};

class BigInteger;

class BigInteger //: public SharedMemory2
{
public:
    BigInteger();
    //BigInteger(bool initialize);
    BigInteger(const BigInteger &source);
    BigInteger(const string number);
    BigInteger(const unsigned int number);
    BigInteger(const int number);
    virtual ~BigInteger();

    void initData();

    virtual void copyData(SharedMemory2 *destination);  /** Copies shared data to destination - implementation is specific to child object. **/
    virtual void shareData(SharedMemory2 *destination); /** Shares shared data with destination - implementation is specific to child object. **/

    string toBinString();
    string toHexString();
    unsigned int actualBlockLength();

    void setNumber(string number);
    void setNumber(unsigned int number);
    void setNumber(int number);

    // Read-only comparing functions.
    int compare(BigInteger &other);
    bool equal(BigInteger &other);
    bool greaterThan(BigInteger &other);
    bool LessThan(BigInteger &other);
    bool isZero();
    bool isNegative();
    bool isPositive();

    bool operator>(BigInteger &other);
    bool operator<(BigInteger &other);
    bool operator==(BigInteger &other);
    inline bool operator>=(BigInteger &other) { return (compare(other) >= 0); }
    inline bool operator<=(BigInteger &other) { return (compare(other) <= 0); }
    inline bool operator!=(BigInteger &other) { return (compare(other) != 0); }

    // Assignment functions.
    BigInteger &clone(BigInteger &source);
    BigInteger &clone(const BigInteger &source);
    //inline BigInteger &clone(const BigInteger &source) { return clone(const_cast<BigInteger>(source)); }
    //void clone(const BigInteger &source);
    inline BigInteger &operator=(BigInteger &other) { return clone(other); }
    inline BigInteger &operator=(const BigInteger &other) { return clone(other); }
    inline BigInteger &operator=(int other) { setNumber(other); return *this; }
    inline BigInteger &operator=(unsigned int other) { setNumber(other); return *this; }

    //inline void operator=(const BigInteger &other) { clone(other); }
    //inline BigInteger &operator=(BigInteger &other) { cout << "=====" << endl; }

    // Arithmatic operations.
    BigInteger add(BigInteger &other);
    void addAccumulator(BigInteger &other);
    BigInteger subtract(BigInteger &other);
    void subtractAccumulator(BigInteger &other);
    BigInteger multiply(BigInteger &other);
    BigInteger square();
    BigInteger divide(BigInteger &other);
    BigInteger modulo(BigInteger &other);
    static void divideInt(BigInteger &a, BigInteger &b, BigInteger &q, BigInteger &r);
    BigInteger TwoCompliment();
    BigInteger bwNot();

    BigInteger shiftLeft();
    void shiftThisLeft();
    BigInteger shiftLeft(unsigned int n);
    BigInteger shiftRight();
    void shiftThisRight();
    BigInteger shiftRight(unsigned int n);
    void shiftBlockLeft();
    void shiftBlockRight();
    void shiftBlockLeft(unsigned int n);
    void shiftBlockRight(unsigned int n);
    bool lastBit(USHORT num);
    bool firstBit(USHORT num);

    inline BigInteger operator+(BigInteger &other) { return add(other); }
    inline BigInteger operator-(BigInteger &other) { return subtract(other); }
    inline BigInteger operator<<(unsigned int n) { return shiftLeft(n); }
    inline BigInteger operator>>(unsigned int n) { return shiftRight(n); }
    inline BigInteger operator*(BigInteger &other) { return multiply(other); }
    inline BigInteger operator/(BigInteger &other) { return divide(other); }
    inline BigInteger operator%(BigInteger &other) { return modulo(other); }
    //inline BigInteger &operator++() { return *this; }

    USHORT *dataPtr() const { return data; }
    //void failIfNotInitialized();
    void setZero();


private:
    static const unsigned int MAX_LENGTH = 256; /** Maximum length of the integer in sizeof(unsigned short). **/
    static const unsigned int USHORT_BITS = sizeof(USHORT) * 8;
    static const unsigned int USHORT_BYTES = sizeof(USHORT);
    static const USHORT USHORT_MAX = ~0;

    USHORT *data; /** Actual integer. **/

    void basicInit();
    void init();



    string stripLeadingZeros(string str);
    void setBinString(string number);
    void setHexString(string number);
    USHORT hexStr2ushort(string number);
    unsigned int min(unsigned int a, unsigned int b);
    unsigned int max(unsigned int a, unsigned int b);
    unsigned int minBlockLength(BigInteger &a, BigInteger &b);
    unsigned int maxBlockLength(BigInteger &a, BigInteger &b);
    string short2binstr(unsigned short n);
    unsigned short shtpower(unsigned short n, unsigned short p);
};

#endif // BIGINTEGER_H
