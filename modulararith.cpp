#include "modulararith.h"

ModArith::ModArith()
{
}

BigInteger ModArith::Add(BigInteger &a, BigInteger &b, BigInteger &m)
{
    BigInteger aa, bb;
    if (a > m)
        aa = a % m;
    else
        aa = a;
    if (b > m)
        bb = b % m;
    else
        bb = b;
    BigInteger sum = a + b;
    return sum % m;
}

BigInteger ModArith::Subtract(BigInteger &a, BigInteger &b, BigInteger &m)
{
    BigInteger aa = a % m;
    BigInteger bb = b % m;
    BigInteger r;
    if (aa > bb || aa == bb)
    {
        r = aa - bb;
    }
    else
    {
        bb = m - bb;
        r = aa + bb;
    }
    if (!r.isZero())
        r = r % m;
    return r;
}

BigInteger ModArith::Multiply(BigInteger &a, BigInteger &b, BigInteger &m)
{
    BigInteger p = a * b;
    if (!p.isZero())
        p = p % m;
    return p;
}

BigInteger ModArith::Square(BigInteger &a, BigInteger &m)
{
    BigInteger p = a.square();
    if (!p.isZero())
        p = p % m;
    return p;
}

BigInteger ModArith::Divide(BigInteger &a, BigInteger &b, BigInteger &m)
{
    //if (a.isZero && b.isZero)
    BigInteger d = a / b;
    if (!d.isZero())
        d = d % m;
    return d;
}

BigInteger ModArith::GCD(BigInteger &a, BigInteger &b)
{
    if (a.isZero()) return b;
    if (b.isZero()) return a;
    BigInteger q, r;
    a.divideInt(a, b, q, r);
    return GCD(b, r);
}

BigInteger ModArith::Inverse(BigInteger &a, BigInteger &m)
{
    /*BigInteger *p0 = new BigInteger("0h");
    BigInteger *p1 = new BigInteger("1h");

    BigInteger *q, *d, *r, *p;

    q = new BigInteger();
    d = new BigInteger();
    r = new BigInteger();
    p = new BigInteger();

    m.divideInt(m, a, *q, *r);

    cout << q->toHexString() << "\t" << r->toHexString() << endl;





    return *p0;*/
    BigInteger mc;
    mc.clone(m);
    BigInteger ac;
    ac.clone(a);
    BigInteger p0("0h");
    BigInteger p1("1h");
    BigInteger zero("0h");
    BigInteger one("1h");

    BigInteger q, d, r, p;
    BigInteger q0, q1;

    // step 0

    m.divideInt(mc, ac, q, r);
    q0.clone(q);


    //cout << q0.toHexString() << endl;
    //cout << mc.toHexString() << " = " << q.toHexString() << "(" << ac.toHexString() << ") + " << r.toHexString() << "\t\tp[0]=" << p0.toHexString() << endl;

    // step 1

    mc.clone(ac);
    ac.clone(r);

    m.divideInt(mc, ac, q, r);
    q1.clone(q);
    //cout << q1.toHexString() << endl;
    //cout << mc.toHexString() << " = " << q.toHexString() << "(" << ac.toHexString() << ") + " << r.toHexString() << "\t\tp[1]=" << p1.toHexString() << endl;

    int i = 1;
    BigInteger temp;

    while (!(r == zero))
    {
        i++;
        mc.clone(ac);
        ac.clone(r);

        temp = Multiply(p1, q0, m);
        //cout << "\t" << temp.toHexString() << endl << endl;
        temp = Subtract(p0, temp, m);
        //cout << "\t" << temp.toHexString() << endl << endl;
        //cout << "p[" << i << "] = " << p0.toHexString() << " - " << p1.toHexString() << "." << q0.toHexString() << " = " << temp.toHexString() << endl;
        p0.clone(p1);
        p1.clone(temp);

        m.divideInt(mc, ac, q, r);
        q0.clone(q1);
        q1.clone(q);
        //cout << mc.toHexString() << " = " << q.toHexString() << "(" << ac.toHexString() << ") + " << r.toHexString() << "\t\tp[i]=" << p1.toHexString() << endl;
    }

    if ((q0 == one))
    {
        temp = Multiply(p1, q0, m);
        //cout << "\t" << temp.toHexString() << endl << endl;
        temp = Subtract(p0, temp, m);
        //cout << "\t" << temp.toHexString() << endl << endl;
        //cout << "p[" << i << "] = " << p0.toHexString() << " - " << p1.toHexString() << "." << q0.toHexString() << " = " << temp.toHexString() << endl;
        p0.clone(p1);
        p1.clone(temp);
    }
    else
    {
        // no inverse.
        //return zero;
        p1.clone(zero);
    }


    return p1;












    /*vector<BigInteger> q, d, r, p;
    BigInteger qq, dd, rr, pp, l;
    unsigned int c = 0;
    dd.clone(a);
    l.clone(m);

    //BigInteger qqq, ddd, rrr, ppp;

    BigInteger bi0("0h");
    BigInteger bi1("1h");
    //bi0.setNumber(0);
    //bi1.setNumber(1);
    //p.push_back(bi0);
    //p.push_back(bi1);

    p.emplace_back(bi0.copy());
    p.emplace_back(bi1.copy());

    a.divideInt(m, a, qq, rr);
    q.push_back(qq);
    d.push_back(a);
    r.push_back(rr);

    BigInteger h("11110h");

    cout << m.toHexString() << " = " << qq.toHexString() << "." << a.toHexString() << " + " << rr.toHexString() << "\t";
    cout << "p0" << " = " << bi0.toHexString() << endl;

    a.divideInt(d[0], r[0], qq, rr);
    q.push_back(qq);
    d.push_back(r[0]);
    r.push_back(rr);
    c = 2;

    while (!rr.isZero())
    {
        pp = ModArith::Multiply(p[c - 1], q[c - 2], m);
        pp = ModArith::Subtract(p[c - 2], pp, m);
        p.push_back(pp);

        a.divideInt(d[c - 1], r[c - 1], qq, rr);
        q.push_back(qq);
        d.push_back(r[c - 1]);
        r.push_back(rr);

        c++;
    }

    pp = ModArith::Multiply(p[c - 1], q[c - 2], m);
    pp = ModArith::Subtract(p[c - 2], pp, m);

    return pp;
    */

}
