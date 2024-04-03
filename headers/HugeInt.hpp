#ifndef __HUGE_INT_HPP__
#define __HUGE_INT_HPP__

#include <iostream>

const int MAX_SIZE = 30;

class HugeInt
{
    friend std::ostream& operator<<(std::ostream& output, const HugeInt& rhv);
public:
    HugeInt(long value = 0);
    HugeInt(const char* string);
    int getSize() const;
    const HugeInt operator+(const HugeInt& rhv) const;
    const HugeInt operator+(const int rhv) const;
    const HugeInt operator+(const char* rhv) const;
    const HugeInt operator*(const HugeInt& rhv) const;
    const HugeInt operator*(const int rhv) const;
    const HugeInt operator*(const char* rhv) const;
    const HugeInt operator-() const;
    const HugeInt operator-(const HugeInt& rhv) const;
    const HugeInt operator-(const int rhv) const;
    const HugeInt operator-(const char* rhv) const;
    const HugeInt operator/(const HugeInt& rhv) const;
    const HugeInt operator/(int rhv) const;
    const HugeInt operator/(const char* rhv) const;
    bool operator>(const HugeInt& rhv) const;
    bool operator>=(const HugeInt& rhv) const;
    bool operator<(const HugeInt& rhv) const;
    bool operator<=(const HugeInt& rhv) const;
    bool operator==(const HugeInt& rhv) const;
    const HugeInt& operator=(const HugeInt& rhv);

private:
    short integer_[MAX_SIZE];
    char sign_;
};

#endif
