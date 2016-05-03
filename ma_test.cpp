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
#include "modulararith.h"
#include <crypto++/modarith.h>
using namespace std;
using namespace CryptoPP;

string charcode2string(char c)
{
    stringstream ss;
    ss << (int)c;
    return ss.str();
}

string string2code(string s)
{
    string o = "";
    for (unsigned int i = 0; i < s.size(); i++)
        o += charcode2string(s[i]);
    return o;
}

void printIntegerBits(Integer &v)
{
    unsigned short c = 0;
    for (unsigned int i = 0; i < v.BitCount(); i++)
    {
        c++;
        cout << v.GetBit(i);
        if (c % 4 == 0)
            cout << " ";
    }
    cout << endl;
}

unsigned short shtpower(unsigned short n, unsigned short p)
{
    unsigned short m = 1;
    for (unsigned short i = 1; i < p; i++)
        m *= n;
    return m;
}

string short2binstr(unsigned short n)
{
    string s = "";
    unsigned short r = 0;
    unsigned short c = 0;
    for (unsigned short i = sizeof(unsigned short) * 8; i > 0; i--)
    {

        if (!(c % 4))
        {
            s += ' ';
            c = 0;
        }
        c++;
        r = 0;
        if (n >= shtpower(2, i))
        {
            r = 1;
            n -= shtpower(2, i);
        }
        if (r)
            s += '1';
        else
            s += '0';
        //cout << shtpower(2, i) << "\t" << r << endl;
    }
    return s;
}

string integer2str(Integer &i)
{
    stringstream ss;
    ss << hex << i << dec;
    return ss.str();
}

bool equiv(BigInteger &a, Integer &b)
{
    return a.toHexString() == integer2str(b);
}

bool equiv(Integer &b, BigInteger &a)
{
    return a.toHexString() == integer2str(b);
}

unsigned int bits = 128;

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
        Integer sumcheck = a + b;
        if (!equiv(sum, sumcheck))
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

bool testModAdditions()
{
    AutoSeededRandomPool gen;
    static const int c = 1000;
    bool pass = true;
    cout << "Testing " << c << " modular additions." << endl;
    for (unsigned int i = 0; i < c; i++)
    {
        Integer a(gen, bits);
        Integer b(gen, bits);
        BigInteger aa(integer2str(a));
        BigInteger bb(integer2str(b));
        Integer m(gen, bits * 2);
        BigInteger mm(integer2str(m));
        ModularArithmetic ma(m);
        BigInteger sum = ModArith::Add(aa, bb, mm);
        Integer sumcheck = ma.Add(a, b);
        if (!equiv(sum, sumcheck))
        {
            //cout << hex << a << "\t+\n" << b << "\t\n" << a + b << dec << endl;
            //cout << endl;
            //cout << aa.toHexString() << "\t+\n" << bb.toHexString() << "\t\n" << sum.toHexString() << endl;
            cout << "Addition failed." << endl;
            pass = false;
        }

    }
    cout << "Done." << endl;
    return pass;
}

bool testModSubtractions()
{
    AutoSeededRandomPool gen;
    static const int c = 1000;
    bool pass = true;
    cout << "Testing " << c << " modular subtractions." << endl;
    for (unsigned int i = 0; i < c; i++)
    {
        Integer a(gen, bits);
        Integer b(gen, bits);
        BigInteger aa(integer2str(a));
        BigInteger bb(integer2str(b));
        Integer m(gen, bits * 2);
        BigInteger mm(integer2str(m));
        ModularArithmetic ma(m);
        BigInteger sum = ModArith::Subtract(aa, bb, mm);
        Integer sumcheck = ma.Subtract(a, b);
        if (!equiv(sum, sumcheck))
        {
            //cout << hex << a << "\t+\n" << b << "\t\n" << a + b << dec << endl;
            //cout << endl;
            //cout << aa.toHexString() << "\t+\n" << bb.toHexString() << "\t\n" << sum.toHexString() << endl;
            cout << "Subtraction failed." << endl;
            pass = false;
        }

    }
    cout << "Done." << endl;
    return pass;
}

bool testModMultiplication()
{
    AutoSeededRandomPool gen;
    static const int c = 1000;
    bool pass = true;
    cout << "Testing " << c << " modular multiplications." << endl;
    for (unsigned int i = 0; i < c; i++)
    {
        Integer a(gen, bits);
        Integer b(gen, bits);
        BigInteger aa(integer2str(a));
        BigInteger bb(integer2str(b));
        Integer m(gen, bits * 2);
        BigInteger mm(integer2str(m));
        ModularArithmetic ma(m);
        BigInteger sum = ModArith::Multiply(aa, bb, mm);
        Integer sumcheck = ma.Multiply(a, b);
        if (!equiv(sum, sumcheck))
        {
            //cout << hex << a << "\t+\n" << b << "\t\n" << a + b << dec << endl;
            //cout << endl;
            //cout << aa.toHexString() << "\t+\n" << bb.toHexString() << "\t\n" << sum.toHexString() << endl;
            cout << "Multiplication failed." << endl;
            pass = false;
        }

    }
    cout << "Done." << endl;
    return pass;
}

bool testModSquaring()
{
    AutoSeededRandomPool gen;
    static const int c = 1000;
    bool pass = true;
    cout << "Testing " << c << " modular squaring." << endl;
    for (unsigned int i = 0; i < c; i++)
    {
        Integer a(gen, bits);
        //Integer b(gen, bits);
        BigInteger aa(integer2str(a));
        //BigInteger bb(integer2str(b));
        Integer m(gen, bits * 2);
        BigInteger mm(integer2str(m));
        ModularArithmetic ma(m);
        //BigInteger sum = ModArith::Multiply(aa, bb, mm);
        BigInteger sum = ModArith::Square(aa, mm);
        //Integer sumcheck = ma.Multiply(a, b);
        Integer sumcheck = ma.Square(a);
        if (!equiv(sum, sumcheck))
        {
            //cout << hex << a << "\t+\n" << b << "\t\n" << a + b << dec << endl;
            //cout << endl;
            //cout << aa.toHexString() << "\t+\n" << bb.toHexString() << "\t\n" << sum.toHexString() << endl;
            cout << "Squaring failed." << endl;
            pass = false;
        }

    }
    cout << "Done." << endl;
    return pass;
}

bool testModInverse()
{
    AutoSeededRandomPool gen;
    static const int c = 1000;
    bool pass = true;
    cout << "Testing " << c << " modular inversions." << endl;
    for (unsigned int i = 0; i < c; i++)
    {
        Integer a(gen, bits);
        //Integer b(gen, bits);
        BigInteger aa(integer2str(a));
        //BigInteger bb(integer2str(b));
        Integer m(gen, bits * 2);
        BigInteger mm(integer2str(m));
        ModularArithmetic ma(m);
        //BigInteger sum = ModArith::Multiply(aa, bb, mm);
        BigInteger sum = ModArith::Inverse(aa, mm);
        //Integer sumcheck = ma.Multiply(a, b);
        Integer sumcheck = ma.MultiplicativeInverse(a);
        if (!equiv(sum, sumcheck))
        {
            //cout << hex << a << "\t+\n" << b << "\t\n" << a + b << dec << endl;
            //cout << endl;
            //cout << aa.toHexString() << "\t+\n" << bb.toHexString() << "\t\n" << sum.toHexString() << endl;
            cout << "Inversion failed." << endl;
            cout << aa.toHexString() << endl << mm.toHexString() << endl << endl;
            cout << sum.toHexString() << endl << integer2str(sumcheck) << endl << endl;
            //cout << "!";
            pass = false;
        }
        else
        {
            //cout << ".";
            cout << "Inversion passed." << endl;
            cout << aa.toHexString() << endl << mm.toHexString() << endl << endl;
            cout << sum.toHexString() << endl << integer2str(sumcheck) << endl << endl;
        }
        cout.flush();

    }
    cout << endl;
    cout << "Done." << endl;
    return pass;
}

bool testModDivision()
{
    AutoSeededRandomPool gen;
    static const int c = 1000;
    bool pass = true;
    cout << "Testing " << c << " modular division." << endl;
    for (unsigned int i = 0; i < c; i++)
    {
        Integer a(gen, bits);
        Integer b(gen, bits);
        BigInteger aa(integer2str(a));
        BigInteger bb(integer2str(b));
        Integer m(gen, bits * 2);
        BigInteger mm(integer2str(m));
        ModularArithmetic ma(m);
        BigInteger sum = ModArith::Divide(aa, bb, mm);
        Integer sumcheck = ma.Divide(a, b);
        if (!equiv(sum, sumcheck))
        {
            //cout << hex << a << "\t+\n" << b << "\t\n" << a + b << dec << endl;
            //cout << endl;
            //cout << aa.toHexString() << "\t+\n" << bb.toHexString() << "\t\n" << sum.toHexString() << endl;
            cout << "Division failed." << endl;
            pass = false;
        }

    }
    cout << "Done." << endl;
    return pass;
}

void startTime(QElapsedTimer &time)
{
    time.start();
}

int getElapsedSeconds(QElapsedTimer &time)
{
   return time.elapsed() / 10;
}

qint64 totalList(QList<qint64> &list)
{
    qint64 total = 0;
    //cout << "Size is " << list.size() << endl;
    for (unsigned int i = 0; i < list.size(); i++)
    {
        total += list[i];
        //cout << list[i];
    }
    return total;
}

void nothing(int id)
{

}

bool doTest(bool (*test)())
{
    QElapsedTimer time;
    startTime(time);
    bool result = test();
    assert(result);
    cout << "Complete in " << getElapsedSeconds(time) << " centiseconds." << endl;
    return result;
}

void test()
{
    QElapsedTimer time;
    cout << "Testing with " << bits << " bit numbers." << endl;
    /*startTime(time);
    bool additionResult = testAdditions();
    assert(additionResult);
    cout << "Complete in " << getElapsedSeconds(time) << " centiseconds." << endl;

    startTime(time);
    bool modAddResults = testModAdditions();
    assert(modAddResults);
    cout << "Complete in " << getElapsedSeconds(time) << " centiseconds." << endl;

    startTime(time);
    bool modSubtractions = testModSubtractions();
    assert(modSubtractions);
    cout << "Complete in " << getElapsedSeconds(time) << " centiseconds." << endl;*/

    doTest(testModAdditions);
    doTest(testModSubtractions);
    doTest(testModMultiplication);
    doTest(testModSquaring);









    //doTest(testModDivision);

    /*AutoSeededRandomPool gen;
    Integer m("5");
    int mi = 5;
    ModularArithmetic ma(m);
    Integer a("1");
    Integer b("1");*/

    /*
     * FFFFFFFFFFFFFFFFFFFFFFFFF
     * BigInteger a, m, i;
    a.setNumber("Fh");
    m.setNumber("1Ah");
    i = ModArith::Inverse(a, m);

    cout << i.toHexString() << endl;

    Integer aa("Fh");
    Integer mm("1Ah");
    ModularArithmetic ma(mm);
    Integer ii = ma.MultiplicativeInverse(aa);

    cout << integer2str(ii) << endl;*/


    /*cout << "\t";
    for (int i = 0; i < mi; i++)
        cout << i << "\t";
    cout << endl;
    for (int i = 0; i < mi; i++)
    {
        cout << i << "\t";
        for (int j = 0; j < mi; j++)
        {
            Integer a(i);
            Integer b(j);
            Integer c = ma.Add(a, b);
            cout << c << "\t";
        }
        cout << endl;
    }

    cout << endl << endl;

    cout << "\t";
    for (int i = 0; i < mi; i++)
        cout << i << "\t";
    cout << endl;
    for (int i = 0; i < mi; i++)
    {
        cout << i << "\t";
        for (int j = 0; j < mi; j++)
        {
            IntWrapper ii(i);
            IntWrapper jj(j);
            IntWrapper mm(5);
            BigInteger a(ii);
            BigInteger b(jj);
            BigInteger mmm(mm);
            BigInteger c = ModArith::Add(a, b, mmm);
            cout << c.toHexString() << "\t";
        }
        cout << endl;
    }

    cout << endl << endl;

    cout << "\t";
    for (int i = 0; i < mi; i++)
        cout << i << "\t";
    cout << endl;
    for (int i = 0; i < mi; i++)
    {
        cout << i << "\t";
        for (int j = 0; j < mi; j++)
        {
            Integer a(i);
            Integer b(j);
            Integer c = ma.Subtract(a, b);
            cout << c << "\t";
        }
        cout << endl;
    }

    cout << endl << endl;

    cout << "\t";
    for (int i = 0; i < mi; i++)
        cout << i << "\t";
    cout << endl;
    for (int i = 0; i < mi; i++)
    {
        cout << i << "\t";
        for (int j = 0; j < mi; j++)
        {
            IntWrapper ii(i);
            IntWrapper jj(j);
            IntWrapper mm(5);
            BigInteger a(ii);
            BigInteger b(jj);
            BigInteger mmm(mm);
            BigInteger c = ModArith::Subtract(a, b, mmm);
            cout << c.toHexString() << "\t";
        }
        cout << endl;
    }

    cout << endl << endl;

    cout << "\t";
    for (int i = 0; i < mi; i++)
        cout << i << "\t";
    cout << endl;
    for (int i = 0; i < mi; i++)
    {
        cout << i << "\t";
        for (int j = 0; j < mi; j++)
        {
            Integer a(i);
            Integer b(j);
            Integer c = ma.Multiply(a, b);
            cout << c << "\t";
        }
        cout << endl;
    }

    cout << endl << endl;

    cout << "\t";
    for (int i = 0; i < mi; i++)
        cout << i << "\t";
    cout << endl;
    for (int i = 0; i < mi; i++)
    {
        cout << i << "\t";
        for (int j = 0; j < mi; j++)
        {
            BigInteger a(new IntWrapper(i));
            BigInteger b(new IntWrapper(j));
            BigInteger mmm(new IntWrapper(5));
            BigInteger c = ModArith::Multiply(a, b, mmm);
            cout << c.toHexString() << "\t";
        }
        cout << endl;
    }*/

    /*BigInteger ag("10eh");
    BigInteger bg("c0h");
    BigInteger gcd = ModArith::GCD(ag, bg);
    cout << gcd.toHexString() << endl;
    cout.flush();

    cout << endl << endl;

    cout << "\t";
    for (int i = 0; i < mi; i++)
        cout << i << "\t";
    cout << endl;
    for (int i = 0; i < mi; i++)
    {
        cout << i << "\t";
        for (int j = 0; j < mi; j++)
        {
            Integer a(i);
            Integer b(j);
            Integer c = ma.Divide(a, b);
            cout << c << "\t";
        }
        cout << endl;
    }

    cout << endl << endl;

    cout << "\t";
    for (int i = 0; i < mi; i++)
        cout << i << "\t";
    cout << endl;
    for (int i = 0; i < mi; i++)
    {
        cout << i << "\t";
        for (int j = 0; j < mi; j++)
        {
            BigInteger a(new IntWrapper(i));
            BigInteger b(new IntWrapper(j));
            BigInteger mmm(new IntWrapper(5));
            BigInteger c = ModArith::Divide(a, b, mmm);
            cout << c.toHexString() << "\t";
        }
        cout << endl;
    }*/
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}
