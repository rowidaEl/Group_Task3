#include <iostream>
#include <string>
using namespace std;

class BigInt {
    string number;
    bool isNegative;

    void removeLeadingZeros() {
    }

    int compareMagnitude(const BigInt& other) const {
        return 0;
    }

public:
    BigInt() {
    }

    BigInt(int64_t value) {
    }

    BigInt(const string& str) {
    }

    BigInt(const BigInt& other) {
    }

    ~BigInt() {
    }

    BigInt& operator=(const BigInt& other) {
        return *this;
    }

    BigInt operator-() const {
        BigInt result;
        return result;
    }

    BigInt operator+() const {
        BigInt result;
        return result;
    }

    BigInt& operator+=(const BigInt& other) {
        return *this;
    }

    BigInt& operator-=(const BigInt& other) {
        return *this;
    }

    BigInt& operator*=(const BigInt& other) {
        if (number == "0" || other.number == "0") {
            number = "0";
            isNegative = false;
            return *this;
        }

        string num1 = number;
        string num2 = other.number;
        int n = num1.size(), m = num2.size();
        string result(n + m, '0');

        for (int i = n - 1; i >= 0; i--) {
            int carry = 0;
            for (int j = m - 1; j >= 0; j--) {
                int mul = (num1[i] - '0') * (num2[j] - '0') + (result[i + j + 1] - '0') + carry;
                result[i + j + 1] = (mul % 10) + '0';
                carry = mul / 10;
            }
            result[i] += carry;
        }

        number = result;
        removeLeadingZeros();
        isNegative = (isNegative != other.isNegative);

        return *this;
    }

    BigInt& operator/=(const BigInt& other) {
        return *this;
    }

    BigInt& operator%=(const BigInt& other) {
        if (other.number == "0") {
            throw runtime_error("Division by zero");
        }

        BigInt temp = *this;
        BigInt divisor = other;

        while (temp.compareMagnitude(divisor) >= 0) {
            temp -= divisor;
        }

        *this = temp;
        return *this;
    }

    BigInt& operator++() {
        return *this;
    }

    BigInt operator++(int) {
        BigInt temp;
        return temp;
    }

    BigInt& operator--() {
        return *this;
    }

    BigInt operator--(int) {
        BigInt temp;
        return temp;
    }

    string toString() const {
        return "";
    }

    friend ostream& operator<<(ostream& os, const BigInt& num) {
        return os;
    }

    friend istream& operator>>(istream& is, BigInt& num) {
        return is;
    }

    friend bool operator==(const BigInt& lhs, const BigInt& rhs);
    friend bool operator<(const BigInt& lhs, const BigInt& rhs);
};

BigInt operator+(BigInt lhs, const BigInt& rhs) {
    BigInt result;
    return result;
}

BigInt operator-(BigInt lhs, const BigInt& rhs) {
    BigInt result;
    return result;
}

BigInt operator*(BigInt lhs, const BigInt& rhs) {
    lhs *= rhs;
    return lhs;
}

BigInt operator/(BigInt lhs, const BigInt& rhs) {
    BigInt result;
    return result;
}

BigInt operator%(BigInt lhs, const BigInt& rhs) {
    BigInt result;
    return result;
}

bool operator==(const BigInt& lhs, const BigInt& rhs) {
    return false;
}

bool operator!=(const BigInt& lhs, const BigInt& rhs) {
    return false;
}

bool operator<(const BigInt& lhs, const BigInt& rhs) {
    return false;
}

bool operator<=(const BigInt& lhs, const BigInt& rhs) {
    return false;
}

bool operator>(const BigInt& lhs, const BigInt& rhs) {
    return false;
}

bool operator>=(const BigInt& lhs, const BigInt& rhs) {
    return false;
}

int main() {
    cout << "=== BigInt Class Test Program ===" << endl << endl;
    cout << "NOTE: All functions are currently empty." << endl;
    cout << "Your task is to implement ALL the functions above." << endl;
    cout << "The tests below will work once you implement them correctly." << endl << endl;

    return 0;
}
