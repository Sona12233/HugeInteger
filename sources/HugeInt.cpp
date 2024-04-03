#include "../headers/HugeInt.hpp"

#include <cstring>

std::ostream&
operator<<(std::ostream& output, const HugeInt& rhv)
{
    int i;

    for (i = 0; (rhv.integer_[i] == 0) && (i < MAX_SIZE); i++);

    if (i == MAX_SIZE) {
        output << 0;
        return output;
    }
    if (rhv.sign_ == '-') {
        output << '-';
    }
    for (; i < MAX_SIZE; i++)
        output << rhv.integer_[i];

    return output;
}

HugeInt::HugeInt(long value)
{
    sign_ = '+';
    if (value < 0) {
        sign_ = '-';
        value = -value;
    }
    for (int i = 0; i < MAX_SIZE; ++i) {
        integer_[i] = 0;
    }
    for (int i = MAX_SIZE - 1; value != 0 && i > 0 ; --i) {
        integer_[i] = value % 10;
        value /= 10;
    }
}

HugeInt::HugeInt(const char* string)
{
    sign_ = '+';
    for (int i = 0; i < MAX_SIZE; ++i) {
        integer_[i] = 0;
    }
    int length = ::strlen(string);
    for (int i = MAX_SIZE - length, j = 0; i < MAX_SIZE; ++i, ++j) {
        if (string[j] == '-') {
            sign_ = '-';
            integer_[i] = 0;
        }
        if (::isdigit(string[j])) {
            integer_[i] = string[j] - '0';
        }
    }
}

int HugeInt::getSize() const
{
    for (int i = 0; i < MAX_SIZE; ++i) {
        if (integer_[i] != 0) {
            return MAX_SIZE - i;
        }
    }
    return 0;
}

const HugeInt
HugeInt::operator+(const HugeInt &rhv) const
{
    HugeInt result;
    if ('-' == sign_ && '-' == rhv.sign_) result.sign_ = '-';
    if ('+' == sign_ && '-' == rhv.sign_) return *this - (-rhv);
    if ('-' == sign_ && '+' == rhv.sign_) return rhv - (-(*this));

    int carry = 0;
    for (int i = MAX_SIZE - 1; i >= 0; --i) {
        result.integer_[i] = integer_[i] + rhv.integer_[i] + carry;
        if (result.integer_[i] > 9) {
            result.integer_[i] %= 10;
            carry = 1;
            continue;
        }
        carry = 0;
    }
    return result;
}

const HugeInt
HugeInt::operator+(const int rhv) const
{
    return this->operator+(HugeInt(rhv));
}

const HugeInt
HugeInt::operator+(const char* rhv) const
{
    return this->operator+(HugeInt(rhv));
}

const HugeInt
HugeInt::operator*(const HugeInt &rhv) const
{
    HugeInt result;
    int carry = 0;
    for (int i = MAX_SIZE - 1, k = 0; i >= 0 || k < rhv.getSize(); --i, ++k) {
        HugeInt temp;
        for (int j = MAX_SIZE - 1; j >= MAX_SIZE - rhv.getSize() || (carry != 0 && j - k >= 0); --j) {
            temp.integer_[j - k] = integer_[i] * rhv.integer_[j] + carry;
            if (temp.integer_[j - k] > 9) {
                carry = temp.integer_[j - k] / 10;
                temp.integer_[j - k] %= 10;
                continue;
            }
            carry = 0;
        }
        result = result + temp;
    }
    if (sign_ != rhv.sign_) result.sign_ = '-';
    return result;
}

const HugeInt
HugeInt::operator*(const int rhv) const
{
    return this->operator*(HugeInt(rhv));
}

const HugeInt
HugeInt::operator*(const char* rhv) const
{
    return this->operator*(HugeInt(rhv));
}

const HugeInt
HugeInt::operator-() const
{
    HugeInt result;
    for (int i = 0; i < MAX_SIZE; ++i) {
        result.integer_[i] = integer_[i];
    }
    result.sign_ = ('+' == sign_) ? '-' : '+';
    return result;
}

const HugeInt
HugeInt::operator-(const HugeInt& rhv) const
{
    HugeInt result;
    if (*this < rhv && '+' == sign_ && '+' == rhv.sign_) return -(rhv - *this);
    if ('-' == sign_ && '-' == rhv.sign_) return *this + (-rhv);
    if ('-' == sign_ && '+' == rhv.sign_) return -rhv + (*this);
    if ('+' == sign_ && '-' == rhv.sign_) return *this + (-rhv);

    int carry = 0;
    for (int i = MAX_SIZE - 1; i >= 0 ; --i) {
        result.integer_[i] = integer_[i] - rhv.integer_[i] - carry;
        if(result.integer_[i] < 0) {
            result.integer_[i] = integer_[i] - carry + 10 - rhv.integer_[i];
            carry = 1;
            continue;
        }
        carry = 0;
    }
    return result;
}


const HugeInt
HugeInt::operator-(const int rhv) const
{
    return this->operator-(HugeInt(rhv));
}

const HugeInt
HugeInt::operator-(const char* rhv) const
{
    return this->operator-(HugeInt(rhv));
}

const HugeInt
HugeInt::operator/(const HugeInt &rhv) const
{
    HugeInt result;
    if (sign_ != rhv.sign_) {
        HugeInt temp1 = *this;
        if ('-' == sign_) {
            temp1 = -(*this);
        }
        HugeInt temp2 = rhv;
        if ('-' == rhv.sign_) {
            temp2 = -rhv;
        }
        return - (temp1 / temp2);
    }
    HugeInt remainder(this->integer_[MAX_SIZE - getSize()]);
    for (int i = MAX_SIZE - getSize(); i < MAX_SIZE - 1 || remainder >= rhv; ++i) {
        int count = 0;
        while (remainder >= rhv) {
            remainder = remainder - rhv;
            ++count;
        }

        result = result * 10 + count;
        if (i < 0 || i >= MAX_SIZE - 1) break;
        remainder = remainder * 10 + integer_[i + 1];
    }

    return result;
}

const HugeInt
HugeInt::operator/(int rhv) const
{
    return this->operator/(HugeInt(rhv));
}

const HugeInt
HugeInt::operator/(const char *rhv) const
{
    return this->operator/(HugeInt(rhv));
}


bool
HugeInt::operator>(const HugeInt& rhv) const
{
    if (*this == rhv) return false;
    if ('-' == sign_ && '+' == rhv.sign_) return false;
    if ('+' == sign_ && '-' == rhv.sign_) return true;

    if (getSize() < rhv.getSize()) return !('+' == sign_ && '+' == rhv.sign_);
    if (getSize() > rhv.getSize()) return ('+' == sign_ && '+' == rhv.sign_);

    if ('-' == sign_ && '-' == rhv.sign_) return !(-*this > -rhv);

    for (int i = MAX_SIZE - getSize(); i < MAX_SIZE; ++i) {
        if ( integer_[i] == rhv.integer_[i]) continue;
        if (integer_[i] > rhv.integer_[i]) return true;
        if (integer_[i] < rhv.integer_[i]) return false;
    }
    return false;
}

bool
HugeInt::operator>=(const HugeInt& rhv) const
{
    return !(rhv > *this);
}

bool
HugeInt::operator<(const HugeInt &rhv) const
{
    return rhv > *this;
}

bool
HugeInt::operator<=(const HugeInt &rhv) const
{
    return !(*this > rhv);
}

bool
HugeInt::operator==(const HugeInt& rhv) const
{
    if ((sign_ != rhv.sign_) || (getSize() != rhv.getSize())) {
        return false;
    }
    for (int i = MAX_SIZE - 1; i >= MAX_SIZE - getSize(); --i) {
        if (integer_[i] != rhv.integer_[i]) {
            return false;
        }
    }
    return true;
}

const HugeInt&
HugeInt::operator=(const HugeInt &rhv)
{
    if (*this == rhv) {
        return *this;
    }
    sign_ = rhv.sign_;
    for (int i = 0; i < MAX_SIZE; ++i) {
        integer_[i] = rhv.integer_[i];
    }
    return *this;
}
