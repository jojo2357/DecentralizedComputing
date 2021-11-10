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

#ifndef BIG_INTEGER
#define BIG_INTEGER
#include "stdafx.h"


BigInt BigInt::ZERO = BigInt("0");
BigInt BigInt::ONE = BigInt("1");
BigInt BigInt::TWO = BigInt("2");
BigInt BigInt::THREE = BigInt("3");
BigInt BigInt::SIX = BigInt("6");

BigInt::BigInt(std::string x) {
    *this = x;
#ifdef DEBUG_PRINTS
    debug_toString = toString();
#endif
}

BigInt::BigInt(int x) {
    *this = std::to_string(x);
#ifdef DEBUG_PRINTS
    debug_toString = toString();
#endif
}

BigInt::BigInt()
        : s("") {
}

BigInt BigInt::negative() {
    BigInt x = *this;
    x.sign *= -1;
    return x;
}

BigInt BigInt::normalize(int newSign) {
    for (int a = s.size() - 1; a > 0 && s[a] == '0'; a--)
        s.erase(s.begin() + a);
    sign = (s.size() == 1 && s[0] == '0' ? 1 : newSign);
#ifdef DEBUG_PRINTS
    debug_toString = toString();
#endif
    return *this;
}

void BigInt::operator=(std::string x) {
    int newSign = (x[0] == '-' ? -1 : 1);
    s = (newSign == -1 ? x.substr(1) : x);
    reverse(s.begin(), s.end());
    this->normalize(newSign);
#ifdef DEBUG_PRINTS
    debug_toString = toString();
#endif
}

bool BigInt::operator==(const BigInt &x) const {
    return (s == x.s && sign == x.sign);
}

bool BigInt::operator<(const BigInt &x) const {
    if (sign != x.sign)
        return sign < x.sign;
    if (s.size() != x.s.size())
        return (sign == 1 ? s.size() < x.s.size() : s.size() > x.s.size());
    for (int a = s.size() - 1; a >= 0; a--)
        if (s[a] != x.s[a])
            return (sign == 1 ? s[a] < x.s[a] : s[a] > x.s[a]);
    return false;
}

bool BigInt::operator<=(const BigInt &x) const {
    return (*this < x || *this == x);
}

bool BigInt::operator>(const BigInt &x) const {
    return (!(*this < x) && !(*this == x));
}

bool BigInt::operator>=(const BigInt &x) const {
    return (*this > x || *this == x);
}

BigInt BigInt::operator+(BigInt x) {
    BigInt curr = *this;
    if (curr.sign != x.sign)
        return curr - x.negative();
    BigInt res;
    for (int a = 0, carry = 0; a < s.size() || a < x.s.size() || carry; a++) {
        carry += (a < curr.s.size() ? curr.s[a] - '0' : 0) + (a < x.s.size() ? x.s[a] - '0' : 0);
        res.s += (carry % 10 + '0');
        carry /= 10;
    }
    return res.normalize(sign);
}

BigInt BigInt::operator-(BigInt x) {
    BigInt curr = *this;

    if (curr.sign != x.sign)
        return curr + x.negative();

    int realSign = curr.sign;

    curr.sign = x.sign = 1;

    if (curr < x)
        return ((x - curr).negative()).normalize(-realSign);

    BigInt res;

    for (int a = 0, borrow = 0; a < s.size(); a++) {
        borrow = (curr.s[a] - borrow - (a < x.s.size() ? x.s[a] : '0'));

        res.s += (borrow >= 0 ? borrow + '0' : borrow + '0' + 10);

        borrow = (borrow >= 0 ? 0 : 1);
    }

    return res.normalize(realSign);
}

BigInt BigInt::operator*(BigInt x) {
    BigInt res("0");

    for (int a = 0, b = s[a] - '0'; a < s.size(); a++, b = s[a] - '0') {
        while (b--)
            res = (res + x);

        x.s.insert(x.s.begin(), '0');
    }

    return res.normalize(sign * x.sign);
}

BigInt BigInt::sqrt() {
    if (*this == ZERO) return ZERO;
    BigInt left = ONE;
    BigInt right = *this / TWO + ONE;
    BigInt res;

    while (left <= right) {
        BigInt mid = left + ((right - left) / TWO);
        if (mid <= *this / mid) {
            left = mid + ONE;
            res = mid;
        } else {
            right = mid - ONE;
        }
    }
    return res;
}

BigInt BigInt::operator/(BigInt x) {
    if (x.s.size() == 1 && x.s[0] == '0')
        x.s[0] /= (x.s[0] - '0');
    BigInt temp("0"), res;
    for (int a = 0; a < s.size(); a++)
        res.s += "0";
    int newSign = sign * x.sign;
    x.sign = 1;
    for (int a = s.size() - 1; a >= 0; a--) {
        temp.s.insert(temp.s.begin(), '0');
        temp = temp + s.substr(a, 1);

        while (!(temp < x)) {
            temp = temp - x;
            res.s[a]++;
        }
    }
    return res.normalize(newSign);
}

BigInt BigInt::operator%(BigInt x) {
    if (x.s.size() == 1 && x.s[0] == '0')
        x.s[0] /= (x.s[0] - '0');
    BigInt res("0");
    x.sign = 1;
    for (int a = s.size() - 1; a >= 0; a--) {
        res.s.insert(res.s.begin(), '0');
        res = res + s.substr(a, 1);
        while (!(res < x))
            res = res - x;
    }
    return res.normalize(sign);
}

std::string BigInt::toString() const {
    std::string ret = s;
    reverse(ret.begin(), ret.end());
    return (sign == -1 ? "-" : "") + ret;
}

BigInt BigInt::toBase10(int base) {
    BigInt exp(1), res("0"), BASE(base);
    for (int a = 0; a < s.size(); a++) {
        int curr = (s[a] < '0' || s[a] > '9' ? (toupper(s[a]) - 'A' + 10) : (s[a] - '0'));
        res = res + (exp * BigInt(curr));
        exp = exp * BASE;
    }
    return res.normalize(sign);
}

BigInt BigInt::toBase10(int base, BigInt mod) {
    BigInt exp(1), res("0"), BASE(base);
    for (int a = 0; a < s.size(); a++) {
        int curr = (s[a] < '0' || s[a] > '9' ? (toupper(s[a]) - 'A' + 10) : (s[a] - '0'));
        res = (res + ((exp * BigInt(curr) % mod)) % mod);
        exp = ((exp * BASE) % mod);
    }
    return res.normalize(sign);
}

std::string BigInt::convertToBase(int base) {
    BigInt ZERO(0), BASE(base), x = *this;
    std::string modes = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (x == ZERO)
        return "0";
    std::string res = "";
    while (x > ZERO) {
        BigInt mod = x % BASE;
        x = x - mod;
        if (x > ZERO)
            x = x / BASE;
        res = modes[stoi(mod.toString())] + res;
    }
    return res;
}

BigInt BigInt::toBase(int base) {
    return BigInt(this->convertToBase(base));
}

std::ostream &operator<<(std::ostream &os, const BigInt &x) {
    os << x.toString();
    return os;
}

BigInt BigInt::operator++() {
    return *this = *this + BigInt::ONE;
}

BigInt BigInt::operator+=(BigInt x) {
    return *this = *this + x;
}

#endif
