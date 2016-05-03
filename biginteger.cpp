#include "biginteger.h"

BigInteger::BigInteger()
{
    //basicInit();
    //init();
    initData();
}

BigInteger::BigInteger(const BigInteger &source)
{
    initData();
    clone(source);
}

BigInteger::BigInteger(const string number)
{
    //init();
    //setZero();
    initData();
    setNumber(number);
}

BigInteger::BigInteger(const unsigned int number)
{
    initData();
    setNumber(number);
}

BigInteger::BigInteger(const int number)
{
    initData();
    setNumber(number);
}

/*BigInteger::BigInteger(bool initialize)
{
    basicInit();
    if (initialize) init();
}*/

BigInteger::~BigInteger()
{
    if (/*data && canDeleteData()*/ true)
    {
        //cout << "Deleting int data at " << data << endl;
        delete[] data;
        //data = NULL;
    }
}

void BigInteger::copyData(SharedMemory2 *destination)
{
    ((BigInteger*)destination)->data = data;
}

void BigInteger::shareData(SharedMemory2 *destination)
{

}

void BigInteger::basicInit()
{
    data = NULL;
}

void BigInteger::init()
{
    initData();
    setZero();
}

void BigInteger::initData()
{
    data = new USHORT[MAX_LENGTH];
}

/*void BigInteger::failIfNotInitialized()
{
    //assert(data != 0);
    if (data == 0) initData();
}*/

void BigInteger::setZero()
{
    assert(memset(data, 0, MAX_LENGTH * USHORT_BYTES) != NULL);
}

string BigInteger::toBinString()
{
    string s = "";

    for (short i = MAX_LENGTH - 1; i >= 0; i--)
        s = s + short2binstr(data[i]) + ' ';

    return s.substr(0, s.size() - 1);
}

string BigInteger::toHexString()
{
    //if (data == 0) return "NOT INITIALIZED.";
    //failIfNotInitialized();

    string s = "";
    USHORT sh = 0;
    USHORT working = 0;
    USHORT r = 0;
    stack<char> st;
    string workingstr = "";
    unsigned int hexPerBlock = USHORT_BITS / 4;
    for (int i = actualBlockLength(); i >= 0; i--)
    {
        workingstr = "";
        //cout << data[i] << " ";
        working = data[i];
        //cout << working << endl;
        /*if (!working)
            for (int j = 0; j < 4; j++)
                st.push('0');*/
        if (!working)
            workingstr += "0000";
        while (working)
        {
            r = working % 16;
            working = working / 16;
            //cout << working << "\t" << r << endl;
            //st.push(r);
            //cout << r << endl;
            if (r >= 0 && r <= 9)
                st.push(r + 48);
                //s += r + 48;
            if (r >= 10 && r <= 15)
                st.push(r + 97 - 10);
                //s += r + 65 - 10;
        }
        while (!st.empty())
        {
            //s += st.top();
            workingstr += st.top();
            st.pop();
        }
        if (workingstr.size() % 4)
            for (unsigned int i = 0; i < workingstr.size() % 4; i++)
                workingstr = '0' + workingstr;
        s += workingstr;
    }
    while (!st.empty())
    {
        //s += ushort2hexchar(st.top());
        //s += st.top();
        st.pop();
    }
    return stripLeadingZeros(s) + 'h';
    //return s + 'h';
}

string BigInteger::stripLeadingZeros(string str)
{
    bool isZero = true;
    string s = "";
    for (unsigned int i = 0; i < str.size(); i++)
    {
        if (isZero && str[i] != '0')
            isZero = false;
        if (!isZero)
        {
            s += str[i];
        }
    }
    if (s.size() == 0)
        s += '0';
    return s;
}

unsigned int BigInteger::actualBlockLength()
{
    if (data == 0) return 0;
    for (int i = MAX_LENGTH - 1; i >= 0; i--)
        if (data[i] != 0)
            return (i + 1);
    return 0;
}

void BigInteger::setNumber(string number)
{
    if (data == 0) initData();
    //writeData();
    if (number[number.size() - 1] == 'b')
        setBinString(number);
    if (number[number.size() - 1] == 'h')
        setHexString(number);
}

void BigInteger::setBinString(string number)
{
    //for (unsigned short i = 0; i < 8; i++)
    //    cout << i << "\t" << shtpower(2, i) << endl;
    //cout << number << endl;
    string working = number.substr(0, number.size() - 1);
    int c = 0;
    USHORT nibble = 0;
    int block = 0;
    double dblocks = (double) number.size() / (sizeof(USHORT) * 8);
    unsigned int blocks = dblocks;
    if (dblocks > blocks)
        blocks++;
    //cout << blocks << " blocks." << endl;
    setZero();
    //cout << blocks * sizeof(USHORT) * 8 << "\t" << working.size() << endl;
    int pad = (blocks * sizeof(USHORT) * 8) - working.size();
    //cout << pad << endl;
    string padding = "";
    for (unsigned int i = 0; i < pad; i++)
        padding += '0';
    working = padding + working;

    dblocks = (double) working.size() / (sizeof(USHORT) * 8);
    blocks = dblocks;
    //cout << dblocks << endl;
    USHORT cblock = 0;
    stack<char> rstack;
    for (unsigned int i = 0; i < working.size(); i++)
        rstack.push(working[i]);
    //cout << working << endl;
    working = "";
    while (!rstack.empty())
    {
        working += rstack.top();
        rstack.pop();
    }
    //cout << working << endl;
    for (int i = 0; i < blocks; i++)
    {
        for (int j = 0; j < sizeof(USHORT) * 8; j++)
        {
            cblock = 0;

            if (working[i * sizeof(USHORT) * 8 + j] == '1')
            {
                //data[i] += shtpower(2, j);
                data[i] += (USHORT)1 << j;
            }
            /*cout << cblock;
            cblock = cblock << j;
            cout << "\t" << cblock << endl;
            data[i] += cblock;*/
        }
    }
    //cout << endl;
}

void BigInteger::setHexString(string number)
{
    string working = number.substr(0, number.size() - 1);
    //cout << working << endl;
    stack<char> st;
    for (unsigned int i = 0; i < working.size(); i++)
        st.push(working[i]);
    working = "";
    while (!st.empty())
    {
        working += st.top();
        st.pop();
    }
    setZero();
    double dblocks = (double) working.size() * 4 / USHORT_BITS;
    //cout << working << endl;
    //cout << dblocks << " blocks." << endl;

    unsigned short blocks = dblocks;
    if (working.size() * 4 % USHORT_BITS != 0)
        blocks++;
    //cout << blocks << " blocks." << endl;
    for (USHORT i = 0; i < blocks; i++)
    {
        string bl = working.substr(i * USHORT_BITS / 4, USHORT_BITS / 4);
        //cout << bl << endl;
        data[i] = hexStr2ushort(bl);
    }
}

void BigInteger::setNumber(unsigned int number)
{
    //if (data == 0) initData();
    //writeData();
    setZero();
    int ratio = sizeof(unsigned int) / sizeof(USHORT);
    USHORT n;
    for (unsigned int i = 0; i < ratio; i++)
    {
        n = number >> (sizeof(USHORT) * i * 8);
        data[i] = n;
    }
}

void BigInteger::setNumber(int number)
{
    setNumber((unsigned int) number);
}

USHORT BigInteger::hexStr2ushort(string number)
{
    USHORT s = 0;
    USHORT n = 0;
    for (unsigned int i = 0; i < number.size(); i++)
    {
        n = 0;
        if (number[i] >= '0' && number[i] <= '9')
            n = number[i] - '0';
        if (number[i] >= 'A' && number[i] <= 'F')
            n = number[i] - 'A' + 10;
        if (number[i] >= 'a' && number[i] <= 'f')
            n = number[i] - 'a' + 10;
        //cout << n << endl;
        n = n << (i * 4);
        s += n;
    }
    //cout << number << "\t" << s << endl;
    return s;
}

/**
 * @brief BigInteger::isZero
 * @return
 * true if numerically 0.
 * false if not.
 */
bool BigInteger::isZero()
{
    for (unsigned int i = 0; i < MAX_LENGTH; i++)
        if (data[i] != 0)
            return false;
    return true;
}

/**
 * @brief BigInteger::equal
 * Checks whether this BigInteger is numerically equal to another.
 * @param other
 * @return
 * true is equal.
 * false is not equal.
 */
bool BigInteger::equal(BigInteger &other)
{
    //failIfNotInitialized();
    //other.failIfNotInitialized();

    if (isZero() && other.isZero())
        return true;
    for (unsigned int i = 0; i < MAX_LENGTH; i++)
        if (data[i] != other.dataPtr()[i])
            return false;
    return true;
    //return equal(*(&other));
}

int BigInteger::compare(BigInteger &other)
{
    //failIfNotInitialized();
    //other.failIfNotInitialized();
    if (equal(other))
    {
        return 0;
    }
    unsigned int tt = maxBlockLength(*this, other);
    for (int i = tt; i >= 0; i--)
    {
        if (data[i] > other.dataPtr()[i])
            return 1;
        if (data[i] < other.dataPtr()[i])
            return -1;
    }
    return 0;
}

bool BigInteger::greaterThan(BigInteger &other)
{
    return (compare(other) > 0);
}

bool BigInteger::LessThan(BigInteger &other)
{
    return (compare(other) < 0);
}

bool BigInteger::isNegative()
{
    return false;
}

bool BigInteger::isPositive()
{
    return true;
}

bool BigInteger::operator>(BigInteger &other)
{
    return greaterThan(other);
}

bool BigInteger::operator<(BigInteger &other)
{
    return LessThan(other);
}

bool BigInteger::operator==(BigInteger &other)
{
    return equal(other);
}

unsigned int BigInteger::min(unsigned int a, unsigned int b)
{
    if (a < b)
        return a;
    return b;
}

unsigned int BigInteger::max(unsigned int a, unsigned int b)
{
    if (a > b)
        return a;
    return b;
}

unsigned int BigInteger::minBlockLength(BigInteger &a, BigInteger &b)
{
    unsigned int la = a.actualBlockLength();
    unsigned int lb = b.actualBlockLength();
    return min(la, lb);
}

unsigned int BigInteger::maxBlockLength(BigInteger &a, BigInteger &b)
{
    unsigned int la = a.actualBlockLength();
    unsigned int lb = b.actualBlockLength();
    return max(la, lb);
}

BigInteger &BigInteger::clone(BigInteger &source)
{
    memcpy(data, source.dataPtr(), MAX_LENGTH * USHORT_BYTES);
    return *this;
}

BigInteger &BigInteger::clone(const BigInteger &source)
{
    memcpy(data, source.dataPtr(), MAX_LENGTH * USHORT_BYTES);
    return *this;
}

string BigInteger::short2binstr(unsigned short n)
{
    string s = "";
    unsigned short r = 0;
    int c = 0;
    for (unsigned short i = sizeof(unsigned short) * 8; i > 0; i--)
    {
        //c++;
        //cout << c << endl;
        if (!(c % 4) && (c > 0))
        {
            s += ' ';
            //c = 0;

        }
        c++;
        r = 0;
        if (n >= shtpower(2, i-1))
        {
            r = 1;
            n -= shtpower(2, i-1);
        }
        if (r)
            s += '1';
        else
            s += '0';
        //cout << shtpower(2, i) << "\t" << r << endl;
    }
    return s;
}

unsigned short BigInteger::shtpower(unsigned short n, unsigned short p)
{
    if (!p)
        return 1;
    if (n == 2)
        return (1 << p);
    unsigned short m = n;
    for (unsigned short i = 1; i < p; i++)
        m *= n;
    return m;
}

BigInteger BigInteger::add(BigInteger &other)
{
    unsigned int ll = maxBlockLength(*this, other);
    BigInteger n;
    n.setZero();
    USHORT *a = data;
    USHORT *b = other.dataPtr();
    USHORT *c = n.dataPtr();

    USHORT carry, aa, bb;
    carry = aa = bb = 0;
    unsigned int working = 0;

    for (unsigned int i = 0; i < ll + 1; i++)
    {
        aa = a[i];
        bb = b[i];
        working = aa + bb + carry;
        if (working > USHORT_MAX)
        {
            c[i] = (USHORT)working;
            carry = working - c[i] - USHORT_MAX;
        }
        else
        {
            c[i] = aa + bb + carry;
            carry = 0;
        }
        //overflow = (i == MAX_LENGTH - 1 && carry);
    }

    return n;
}

void BigInteger::addAccumulator(BigInteger &other)
{
    unsigned int ll = maxBlockLength(*this, other);
    //BigInteger n;
    //n.setZero();
    USHORT *a = data;
    USHORT *b = other.dataPtr();
    //USHORT *c = data;

    USHORT carry, aa, bb;
    carry = aa = bb = 0;
    unsigned int working = 0;

    for (unsigned int i = 0; i < ll + 1; i++)
    {
        aa = a[i];
        bb = b[i];
        working = aa + bb + carry;
        if (working > USHORT_MAX)
        {
            a[i] = (USHORT)working;
            carry = working - a[i] - USHORT_MAX;
        }
        else
        {
            a[i] = aa + bb + carry;
            carry = 0;
        }
        //overflow = (i == MAX_LENGTH - 1 && carry);
    }

    //return n;
}

BigInteger BigInteger::subtract(BigInteger &other)
{
    BigInteger b = other.TwoCompliment();
    return this->add(b);
}

void BigInteger::subtractAccumulator(BigInteger &other)
{
    BigInteger b = other.TwoCompliment();
    addAccumulator(b);
}

BigInteger BigInteger::TwoCompliment()
{
    BigInteger one = 1;
    BigInteger ans = bwNot();
    //ans = this->bwNot();
    ans = ans.add(one);
    return ans;
}

BigInteger BigInteger::bwNot()
{
    BigInteger bi;
    for (unsigned int i = 0; i < MAX_LENGTH; i++)
        bi.dataPtr()[i] = ~data[i];
    //cout << toHexString() << endl;
    //cout << bi.toHexString() << endl;
    return bi;
}

BigInteger BigInteger::shiftLeft(unsigned int n)
{
    BigInteger o;
    o.clone(*this);
    for (unsigned int i = 0; i < n; i++)
        o.shiftThisLeft();
    return o;
}

BigInteger BigInteger::shiftRight(unsigned int n)
{
    BigInteger o;
    o.clone(*this);
    for (unsigned int i = 0; i < n; i++)
        o.shiftThisRight();
    return o;
}

void BigInteger::shiftThisLeft()
{
    unsigned int tt = actualBlockLength();
    for (int i = tt; i > 0; i--)
    {
        data[i] = data[i] << 1;
        data[i] += lastBit(data[i - 1]);
    }
    data[0] = data[0] << 1;
}

void BigInteger::shiftThisRight()
{
    bool carry = firstBit(data[MAX_LENGTH - 1]);
    bool carry2 = 0;
    data[MAX_LENGTH - 1] = data[MAX_LENGTH - 1] >> 1;
    for (int i = MAX_LENGTH - 2; i >= 0; i--)
    {
        carry2 = carry;
        carry = firstBit(data[i]);
        data[i] = data[i] >> 1;
        data[i] += (32768 * carry2);
    }
}

bool BigInteger::firstBit(USHORT num)
{
    return (num & 1);
}

bool BigInteger::lastBit(USHORT num)
{
    return (num & (1 << 15));
}

BigInteger BigInteger::multiply(BigInteger &other)
{
    unsigned int ll = maxBlockLength(*this, other);

    BigInteger n = 0;   // if one number is signed, make the result signed.
    //unsigned int steps = other.maxLength();
    unsigned int steps = other.actualBlockLength();
    //BigInteger levels[steps];
    unsigned int working = 0;
    BigInteger biWorking;
    for (unsigned int i = 0; i < steps; i++)
    {
        for (unsigned j = 0; j < ll * 2; j++)
        {
            working = data[j] * other.dataPtr()[i];
            if (working != 0)
            {
                //if (updateExternalClock)    updateExternalClock(0);
                biWorking.setNumber(working);
                //if (updateExternalClock)    updateExternalClock(1);
                biWorking.shiftBlockLeft(i + j);
                //if (updateExternalClock)    updateExternalClock(2);
                //n = n + (biWorking);
                n.addAccumulator(biWorking);
                //if (updateExternalClock)    updateExternalClock(3);
            }
        }
    }
    return n;
}

void BigInteger::shiftBlockLeft(unsigned int n)
{
    //for (unsigned int i = 0; i < n; i++)
    //    shiftBlockLeft();
    unsigned int tt = actualBlockLength();
    /*for (int i = tt; i > n; i--)
    {
        data[i] = data[i - n];
    }
    //data[0] = 0;
    for (int i = 0; i < n; i++)
        data[i] = 0;*/
    USHORT *temp = new USHORT[tt];
    memcpy(temp, data, sizeof(USHORT) * tt);
    setZero();
    memcpy(data + n, temp, sizeof(USHORT) * tt);
    delete temp;
}

void BigInteger::shiftBlockLeft()
{
    //for (int i = 0; i < USHORT_BITS; i++)
    //    shiftThisLeft();
    unsigned int tt = actualBlockLength();
    for (int i = tt; i > 0; i--)
    {
        data[i] = data[i - 1];
    }
    data[0] = 0;
}

void BigInteger::shiftBlockRight()
{
    for (int i = 0; i < USHORT_BITS; i++)
        shiftThisRight();
}

/**
 * @brief BigInteger::square
 * Returns the square of the integer.
 * Takes advantage of the symetry of squares to calculate faster than normal multiplication.
 * @return
 * Square of the integer.
 */
BigInteger BigInteger::square()
{
    unsigned int ll = actualBlockLength();
    BigInteger ans = 0;
    BigInteger working;
    for (unsigned int i = 0; i < ll; i++)
    {
        working.setNumber(data[i] * data[i]);
        working.shiftBlockLeft(2 * i);
        ans = ans.add(working);
    }

    for (unsigned int i = 1; i < ll; i++)
    {
        for (unsigned int j = 0; j < i; j++)
        {
            working.setNumber(data[i] * data[j]);
            working = working.add(working);
            working.shiftBlockLeft(i + j);
            ans = ans.add(working);
        }
    }
    return ans;
}

BigInteger BigInteger::divide(BigInteger &other)
{
    BigInteger q, r;
    //q.clone(*this);
    divideInt(*this, other, q, r);
    return q;
}

BigInteger BigInteger::modulo(BigInteger &other)
{
    BigInteger q, r;
    //a.clone(*this);
    divideInt(*this, other, q, r);
    return r;
}

void BigInteger::divideInt(BigInteger &a, BigInteger &b, BigInteger &q, BigInteger &r)
{
    //  If b > a, then a = 0 * b + a.
    if (b.greaterThan(a))
    {
        q.setZero();
        r.clone(a);
        return;
    }
    r.setZero();
    q.setZero();
    unsigned int shift = 0;
    BigInteger qcount = 0;
    BigInteger bscaled = 0;
    BigInteger aa = 0;
    BigInteger precount = 0;
    aa.clone(a);
    r.clone(a);
    //unsigned int la = a.actualBlockLength();
    unsigned int lb = b.actualBlockLength();
    //unsigned int lr = r.actualBlockLength();

    /*cout << endl << endl << endl;
    cout << "b: " << b.toHexString() << endl;
    cout << "r: " << r.toHexString() << endl;
    cout << la << "\t" << lb << "\t" << lr << endl;*/
    while (r.greaterThan(b) || r.equal(b))
    {
        shift = r.actualBlockLength() - lb;
        bscaled.clone(b);
        bscaled.shiftBlockLeft(shift);

        while (bscaled.greaterThan(r))
        {
            shift--;
            bscaled.shiftBlockRight();
            //cout << "First inner loop" << endl;
            //cout.flush();
        }
        //cout << "bscaled: " << bscaled.toHexString() << endl;
        //cout << "r      : " << r.toHexString() << endl;
        while (bscaled.LessThan(r) || bscaled.equal(r))
        {
            precount.setNumber(1);
            precount.shiftBlockLeft(shift);
            //qcount = qcount.add(precount);
            qcount.addAccumulator(precount);
            //r = r.subtract(bscaled);
            r.subtractAccumulator(bscaled);
            /*cout << "Second inner loop" << endl;
            cout << "bscaled: " << bscaled.toHexString() << endl;
            cout << "r      : " << r.toHexString() << endl;
            cout << "qcount : " << qcount.toHexString() << endl;
            cout.flush();*/
        }
    }
    //q.clone(qcount);
    q = qcount;
    //cout << "END!!!!!!!!!!!!!!" << endl;
    //cout.flush();
}
