#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <crypto++/integer.h>
#include <crypto++/osrng.h>
#include <crypto++/hex.h>
#include "biginteger.h"
#include <QTime>
#include <QElapsedTimer>
#include <QList>
#include <QMap>
#include <vector>
#include <queue>
using namespace std;
using namespace CryptoPP;

unsigned int bits = 256;

void startTime(QElapsedTimer &time)
{
    time.start();
}

int getElapsedSeconds(QElapsedTimer &time)
{
   return time.elapsed() / 10;
}

int getElapsedMilliSeconds(QElapsedTimer &time)
{
   return time.elapsed();
}


string integer2str(Integer &i)
{
    stringstream ss;
    ss << hex << i << dec;
    return ss.str();
}

bool testSetting()
{
    AutoSeededRandomPool gen;
    static const int c = 1000;
    bool pass = true;
    cout << "Testing " << c << " assignments." << endl;
    for (unsigned int i = 0; i < 1000; i++)
    {
        Integer source(gen, bits);
        BigInteger target(integer2str(source));
        //cout << integer2str(source) << endl << target.toHexString() << endl << endl;
        if (integer2str(source) != target.toHexString())
        {
            cout << target.toBinString() << endl;
            cout << "Setting failed." << endl;
            pass = false;
        }
    }
    cout << "Done." << endl;
    return pass;
}

int testSettingTiming(int bits)
{
    AutoSeededRandomPool gen;
    static const int c = 1000;

    queue<string> ints;
    queue<BigInteger> bints;
    for (unsigned int i = 0; i < c; i++)
    {
        Integer source(gen, bits);
        ints.push(integer2str(source));
        bints.push(BigInteger(integer2str(source)));
    }
    QElapsedTimer timer;
    string cint = "";
    BigInteger bi, bi1;
    timer.start();
    while (!bints.empty())
    {
        //cint = ints.front();
        //ints.pop();
        //bi.setNumber(cint);
        bi1 = bints.front();
        bints.pop();
        //bi = bi1;
    }

    return getElapsedMilliSeconds(timer);
}

int testAdditionTiming(int bits)
{
    AutoSeededRandomPool gen;
    static const int c = 1000;

    queue<string> ints;
    queue<BigInteger> bints;
    for (unsigned int i = 0; i < c * 2; i++)
    {
        Integer source(gen, bits);
        ints.push(integer2str(source));
        bints.push(BigInteger(integer2str(source)));
    }
    QElapsedTimer timer;
    string cint1 = "";
    string cint2 = "";
    BigInteger sum, bi1, bi2;
    timer.start();
    while (!bints.empty())
    {
        //cint = ints.front();
        //ints.pop();
        bi1 = bints.front();
        bints.pop();
        bi2 = bints.front();
        bints.pop();
        sum = bi1 + bi2;

    }

    return getElapsedMilliSeconds(timer);
}

bool testComparing()
{
    AutoSeededRandomPool gen;
    static const int c = 1000;
    bool pass = true;
    cout << "Testing " << c << " comparisions." << endl;
    for (unsigned int i = 0; i < c; i++)
    {
        Integer a(gen, bits);
        Integer b(gen, bits);
        BigInteger aa(integer2str(a));
        BigInteger bb(integer2str(b));
        //BigInteger sum = aa.multiply(bb);
        //Integer sumcheck = a * b;
        int compareA = a.Compare(b);
        int compareB = aa.compare(bb);
        if (compareA != compareB)
        {
            //cout << hex << a << "\t | \n" << b << "\t\n" << "" << dec << endl;
            //cout << endl;
            //cout << aa.toHexString() << "\t|\n" << bb.toHexString() << "\t\n" << "" << endl;
            cout << "Compare failed." << endl;
            cout << i << "\t" << compareA << "\t" << compareB << endl;
            pass = false;
        }
        /*if ((a < b) && !(aa.LessThan(bb)))
        {
            cout << "Less than failed." << endl;
            pass = false;
        }
        if ((a == b) && (aa.equal(bb)))
        {
            cout << "Equals failed." << endl;
            pass = false;
        }*/

    }
    cout << "Done." << endl;
    return pass;
}

bool testAdditions()
{
    AutoSeededRandomPool gen;
    static const int c = 1000;
    bool pass = true;
    cout << "Testing " << c << " additions." << endl;
    for (unsigned int i = 0; i < c; i++)
    {
        Integer a(gen, bits);
        Integer b(gen, bits);
        BigInteger aa(integer2str(a));
        BigInteger bb(integer2str(b));
        BigInteger sum = aa + bb;
        //sum = aa.add(bb);
        Integer sumcheck = a + b;
        if (sum.toHexString() != integer2str(sumcheck))
        {
            cout << hex << a << "\t+\n" << b << "\t\n" << a + b << dec << endl;
            cout << endl;
            cout << aa.toHexString() << "\t+\n" << bb.toHexString() << "\t\n" << sum.toHexString() << endl;
            cout << "Addition failed." << endl;
            pass = false;
        }

    }
    cout << "Done." << endl;
    return pass;
}

bool testSubtraction()
{
    AutoSeededRandomPool gen;
    static const int c = 1000;
    bool pass = true;
    cout << "Testing " << c << " subtractions." << endl;
    for (unsigned int i = 0; i < c; i++)
    {
        Integer a(gen, bits);
        Integer b(gen, bits);
        Integer m;
        if (a >= b)
            m = a;
        else
            m = b;

        BigInteger aa(integer2str(m));
        BigInteger bb(integer2str(b));
        BigInteger sum = aa - bb;
        Integer sumcheck = m - b;
        if (sum.toHexString() != integer2str(sumcheck))
        {
            cout << hex << a << "\t-\n" << b << "\t\n" << a - b << dec << endl;
            cout << endl;
            cout << aa.toHexString() << "\t-\n" << bb.toHexString() << "\t\n" << sum.toHexString() << endl;
            cout << "Subtraction failed." << endl;
            pass = false;
        }

    }
    cout << "Done." << endl;
    return pass;
}

bool testShifts()
{
    AutoSeededRandomPool gen;
    static const int c = 1000;
    bool pass = true;
    cout << "Testing " << c * 2 << " shifts." << endl;
    int shift = 1;
    // shift left
    for (unsigned int i = 0; i < c; i++)
    {
        Integer a(gen, bits);
        BigInteger aa(integer2str(a));
        shift++;
        if (shift % 1024)
            shift = 1;
        Integer sa = a << shift;
        BigInteger saa = aa << shift;
        if (integer2str(sa) != saa.toHexString())
        {
            cout << "Left shift failed." << endl;
            pass = false;
        }
    }
    // shift right
    for (unsigned int i = 0; i < c; i++)
    {
        Integer a(gen, bits);
        BigInteger aa(integer2str(a));
        shift++;
        if (shift % 1024)
            shift = 1;
        Integer sa = a >> shift;
        BigInteger saa = aa >> shift;
        if (integer2str(sa) != saa.toHexString())
        {
            cout << integer2str(sa) << endl << saa.toHexString() << endl;
            cout << "Right shift failed." << endl;
            pass = false;
        }
    }
    cout << "Done." << endl;
    return pass;
}

bool testMultiplication()
{
    AutoSeededRandomPool gen;
    static const int c = 1000;
    bool pass = true;
    cout << "Testing " << c << " multiplications." << endl;
    for (unsigned int i = 0; i < c; i++)
    {
        Integer a(gen, bits);
        Integer b(gen, bits);
        BigInteger aa(integer2str(a));
        BigInteger bb(integer2str(b));
        //aa.updateExternalClock = triggerClock;
        //bb.updateExternalClock = triggerClock;
        BigInteger sum = aa * bb;
        Integer sumcheck = a * b;
        if (sum.toHexString() != integer2str(sumcheck))
        {
            cout << hex << a << "\t*\n" << b << "\t\n" << a * b << dec << endl;
            cout << endl;
            cout << aa.toHexString() << "\t*\n" << bb.toHexString() << "\t\n" << sum.toHexString() << endl;
            cout << "Multiplication failed." << endl;
            pass = false;
        }

    }
    cout << "Done." << endl;
    return pass;
}

bool testSquaring()
{
    AutoSeededRandomPool gen;
    static const int c = 1000;
    bool pass = true;
    cout << "Testing " << c << " squares." << endl;
    for (unsigned int i = 0; i < c; i++)
    {
        Integer a(gen, bits);
        Integer b(gen, bits);
        BigInteger aa(integer2str(a));
        BigInteger bb(integer2str(b));
        BigInteger sum = aa.square();
        Integer sumcheck = a.Squared();
        if (sum.toHexString() != integer2str(sumcheck))
        {
            cout << hex << a << "\t*\n" << a << "\t\n" << a * a << dec << endl;
            cout << endl;
            cout << aa.toHexString() << "\t*\n" << aa.toHexString() << "\t\n" << sum.toHexString() << endl;
            cout << "Squaring failed." << endl;
            pass = false;
        }

    }
    cout << "Done." << endl;
    return pass;
}

bool testDivision()
{
    AutoSeededRandomPool gen;
    static const int c = 1000;
    bool pass = true;
    cout << "Testing " << c << " divisions." << endl;
    for (unsigned int i = 0; i < c; i++)
    {
        Integer a(gen, bits);
        Integer b(gen, bits);
        BigInteger aa(integer2str(a));
        BigInteger bb(integer2str(b));
        BigInteger div, mod;
        //BigInteger::divideInt(aa, bb, div, mod);
        div = aa / bb;
        mod = aa % bb;
        Integer divcheck = a / b;
        Integer modcheck = a % b;
        if (div.toHexString() != integer2str(divcheck))
        {
            cout << hex << a << "\t/\n" << b << "\t\n" << a / b << dec << endl;
            cout << endl;
            cout << aa.toHexString() << "\t/\n" << bb.toHexString() << "\t\n" << div.toHexString() << endl;
            cout << "Division failed." << endl;
            pass = false;
        }
        if (mod.toHexString() != integer2str(modcheck))
        {
            cout << hex << a << "\t%\n" << b << "\t\n" << a % b << dec << endl;
            cout << endl;
            cout << aa.toHexString() << "\t%\n" << bb.toHexString() << "\t\n" << mod.toHexString() << endl;
            cout << "Modulo failed." << endl;
            pass = false;
        }

    }
    cout << "Done." << endl;
    return pass;
}


void test()
{
    QElapsedTimer time;
    cout << "Testing with " << bits << " bit numbers." << endl;
    startTime(time);
    bool settingResult = testSetting();
    assert(settingResult);
    cout << "Complete in " << getElapsedSeconds(time) << " centiseconds." << endl;

    startTime(time);
    bool compareResult = testComparing();
    assert(compareResult);
    cout << "Complete in " << getElapsedSeconds(time) << " centiseconds." << endl;

    startTime(time);
    bool additionResult = testAdditions();
    assert(additionResult);
    cout << "Complete in " << getElapsedSeconds(time) << " centiseconds." << endl;

    startTime(time);
    bool subtractionResult = testSubtraction();
    assert(subtractionResult);
    cout << "Complete in " << getElapsedSeconds(time) << " centiseconds." << endl;

    startTime(time);
    bool shiftResult = testShifts();
    assert(shiftResult);
    cout << "Complete in " << getElapsedSeconds(time) << " centiseconds." << endl;

    startTime(time);
    bool multiplicationResult = testMultiplication();
    assert(multiplicationResult);
    cout << "Complete in " << getElapsedSeconds(time) << " centiseconds." << endl;

    startTime(time);
    bool squaringResult = testSquaring();
    assert(squaringResult);
    cout << "Complete in " << getElapsedSeconds(time) << " centiseconds." << endl;

    startTime(time);
    bool divisionResult = testDivision();
    assert(divisionResult);
    cout << "Complete in " << getElapsedSeconds(time) << " centiseconds." << endl;

    /*timers_add.clear();
    timers_set.clear();
    timers_shift.clear();
    cout << "Starting..." << endl;
    cout.flush();
    for (unsigned int i = 0; i < 1000; i++)
    {
        AutoSeededRandomPool gen;
        Integer a(gen, 256);
        Integer b(gen, 256);
        BigInteger aa(integer2str(a));
        BigInteger bb(integer2str(b));
        aa.updateExternalClock = triggerClock;
        bb.updateExternalClock = triggerClock;
        aa.multiply(bb);
    }

    outputTimers();*/
    cout << endl << endl << "Timers" << endl << endl;
    cout << "Assignment\t" << testSettingTiming(bits * 4) << endl;
    cout << "Addition\t" << testAdditionTiming(bits * 4) << endl;
}

int main(int argc, char *argv[])
{
    cout << "Begin." << endl;

    BigInteger b;
    BigInteger c;
    BigInteger d;

    //c.setNumber(1);

    cout << b.toHexString() << endl << c.toHexString() << endl << d.toHexString() << endl << endl;

    b.setNumber(578263672);
    c.setNumber("fffff6723642384h");
    d.setNumber("10101010101111010111b");

    cout << b.toHexString() << endl << c.toHexString() << endl << d.toHexString() << endl << endl;

    BigInteger s1, s2, small, big;
    small.setNumber(500);
    big.setNumber(1000);

    cout << (s1 == s2) << endl;
    cout << (small < big) << endl;
    cout << (small > big) << endl;
    cout << endl;

    BigInteger e = c;
    //BigInteger e;
    //e.clone(c);

    cout << e.toHexString() << endl << c.toHexString() << endl << d.toHexString() << endl;
    printf("%p\t%p\t%p\n\n", e.dataPtr(), c.dataPtr(), d.dataPtr());

    e = c;
    cout << e.toHexString() << endl << c.toHexString() << endl << d.toHexString() << endl;
    printf("%p\t%p\t%p\n\n", e.dataPtr(), c.dataPtr(), d.dataPtr());

    BigInteger aa = 5;
    BigInteger bb = 3;
    BigInteger dd = aa * bb;
    cout << dd.toHexString() << endl;

    cout << "*****" << endl;
    BigInteger f = 2;
    BigInteger g = 2;
    for (unsigned int i = 0; i < 5; i++)
    {

        cout << f.toHexString() << "\t" << g.toHexString() << endl;
        f.shiftBlockLeft();
        g.shiftBlockLeft(1);
    }

    BigInteger h = 7;
    BigInteger i = 2;
    BigInteger r;
    BigInteger q;
    h.divideInt(h, i, q, r);
    cout << endl;
    cout << q.toHexString() << "\t" << r.toHexString() << endl;

    test();

    cout << endl << sizeof(unsigned short) << endl;
    //int ll = 27;
    //ll+= 3;
    //cout << ll << endl;

    cout << "Complete." << endl;
    return 0;
}
