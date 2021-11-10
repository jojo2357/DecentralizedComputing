// MIT License

// Copyright (c) 2020 William Chanrico

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

/*
* Title: BigInt
* Description: Big Integer class (coded with competitive programming problems in mind)
* Date: 09-October-2017
* Author: William Chanrico
*/

#ifndef DECENTRALIZEDCOMPUTING_BIGINT_H
#define DECENTRALIZEDCOMPUTING_BIGINT_H

#include "stdafx.h"

class BigInt {
public:
    static BigInt ZERO;
    static BigInt ONE;
    static BigInt TWO;
    static BigInt THREE;
    static BigInt SIX;
#ifdef DEBUG_PRINTS
    std::string debug_toString;
#endif
    int sign;
    std::string s;

    BigInt();
    BigInt(std::string x);
    BigInt(int x);

    BigInt negative();
    BigInt normalize(int newSign);

    void operator=(std::string x);
    bool operator==(const BigInt &x) const;
    bool operator<(const BigInt &x) const;
    bool operator<=(const BigInt &x) const;
    bool operator>(const BigInt &x) const;
    bool operator>=(const BigInt &x) const;
    BigInt operator+(BigInt x);
    BigInt operator-(BigInt x);
    BigInt operator*(BigInt x);
    BigInt operator/(BigInt x);
    BigInt operator%(BigInt x);
    BigInt operator++();
    BigInt operator+=(BigInt x);

    BigInt sqrt();

    std::string toString() const;
    BigInt toBase10(int base);
    BigInt toBase10(int base, BigInt mod);
    std::string convertToBase(int base);
    BigInt toBase(int base);
    friend std::ostream &operator<<(std::ostream &os, const BigInt &x);
};

#endif //DECENTRALIZEDCOMPUTING_BIGINT_H
