#ifndef MODARITH_H
#define MODARITH_H
#include "biginteger.h"
#include <vector>

class ModArith
{
public:
    ModArith();
    static BigInteger Add(BigInteger &a, BigInteger &b, BigInteger &m);
    static BigInteger Subtract(BigInteger &a, BigInteger &b, BigInteger &m);
    static BigInteger Multiply(BigInteger &a, BigInteger &b, BigInteger &m);
    static BigInteger Square(BigInteger &a, BigInteger &m);
    static BigInteger Divide(BigInteger &a, BigInteger &b, BigInteger &m);
    static BigInteger GCD(BigInteger &a, BigInteger &b);
    static BigInteger Inverse(BigInteger &a, BigInteger &m);
};

#endif // MODARITH_H
