#include <iostream>
#include <string>
using namespace std;

class BigInt
{
    string number;    // Stores the number as a string
    bool isNegative;  // True if number is negative

    void removeLeadingZeros() {
        int i = 0;
        while (i < number.size() - 1 && number[i] == '0') {
            i++;
        }
        number = number.substr(i);

        if (number == "0") {
            isNegative = false;
        }
    }

    // Compare absolute values of two BigInts (ignore signs)
    // Returns: 1 if |this| > |other|, 0 if equal, -1 if |this| < |other|
   int compareMagnitude(const BigInt& other) const {
        // Compare lengths first
        if (number.size() > other.number.size()) return 1;
        if (number.size() < other.number.size()) return -1;

        // Same length → lexicographical comparison
        if (number > other.number) return 1;
        if (number < other.number) return -1;

        return 0; // Equal
    }

public:
    // Default constructor - initialize to zero
    BigInt()
    {
        number="0";
        isNegative=false;
    }

    // Constructor from 64-bit integer
    BigInt(int64_t value)
    {
        if(value<0)
        {
            int64_t v=-value;
            number=to_string(v);
            isNegative=true;
        }
        else
        {
            number=to_string(value);
            isNegative=false;
        }
    }

    // Constructor from string representation
    BigInt(const string& str)
    {
        if(str[0]=='-')
        {
            isNegative=true;
            number = str.substr(1);
        }
        else
        {
            isNegative=false;
            number=str;
        }
        removeLeadingZeros();
    }

    // Copy constructor
    BigInt(const BigInt& other)
    {
        this->number=other.number;
        this->isNegative=other.isNegative;
    }

    // Destructor
    ~BigInt()
    {
        // TODO: Implement if needed
    }

    // Assignment operator
    BigInt& operator=(const BigInt& other)
    {
        if(this==&other){

        return *this;

        }
        this->number=other.number;
        this->isNegative=other.isNegative;
        return *this;


    }

    // Unary negation operator (-x)
    BigInt operator-() const
    {
        BigInt result;
        return result;
    }

    // Unary plus operator (+x)
    BigInt operator+() const
    {
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

    // Division assignment operator (x /= y)
    BigInt& operator/=(const BigInt& other)
    {
        // TODO: Implement this operator
        if(other.number == "0")
        {
            throw runtime_error("Division by zero");
        }

        BigInt dividend = *this;
        BigInt divisor = other;
        bool resultNegative = (dividend.isNegative != divisor.isNegative);
        dividend.isNegative = false;
        divisor.isNegative = false;
        if(dividend.compareMagnitude(divisor) == -1)
        {
                number = "0";
                isNegative = false ;
                return *this;
        }
        BigInt low("0");
        BigInt high = dividend;
        BigInt best("0");
        while(low <= high)
        {

            BigInt mid = (low + high) / BigInt(2);
            BigInt product = mid * divisor;
            if(product <= dividend)
            {
                best = mid ;
                low = mid + BigInt(1);
            }
            else
            {
             high = mid - BigInt(1);
            }
        }
        *this = best;
        if(resultNegative && number != "0")
        {
            isNegative = true;

        }
        else
        {
        isNegative = false;
        }


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

    // Pre-decrement operator (--x)
    BigInt& operator--()
    {
        // TODO: Implement this operator
        return *this;
    }

    // Post-decrement operator (x--)
    BigInt operator--(int)
    {
        BigInt temp;
        return temp;
    }

    // Convert BigInt to string representation
    string toString() const
    {
        // TODO: Implement this function
        if (isNegative && number != "0") {
            return "-" + number;
        }
        return number;
    }

    // Output stream operator (for printing)
    friend ostream& operator<<(ostream& os, const BigInt& num)
    {
        // TODO: Implement this operator
        os << num.toString();
        return os;
    }

    // Input stream operator (for reading from input)
    friend istream& operator>>(istream& is, BigInt& num)
    {
        // TODO: Implement this operator
           string input;
        is >> input;

        // Reset values
        num.isNegative = false;
        num.number = "";

        // Check for sign
        if (input[0] == '-') {
            num.isNegative = true;
            num.number = input.substr(1);
        } else if (input[0] == '+') {
            num.number = input.substr(1);
        } else {
            num.number = input;
        }

        // Handle empty case (just in case)
        if (num.number.empty()) {
            num.number = "0";
            num.isNegative = false;
        }

        // Remove leading zeros and normalize
        num.removeLeadingZeros();

        return is;
    }


    // Friend declarations for comparison operators
    friend bool operator==(const BigInt& lhs, const BigInt& rhs);
    friend bool operator<(const BigInt& lhs, const BigInt& rhs);
};

// Binary addition operator (x + y)
BigInt operator+(BigInt lhs, const BigInt& rhs)
{
    BigInt result;
    return result;
}

// Binary subtraction operator (x - y)
BigInt operator-(BigInt lhs, const BigInt& rhs)
{
    BigInt result;
    return result;
}

BigInt operator*(BigInt lhs, const BigInt& rhs) {
    lhs *= rhs;
    return lhs;
}

BigInt operator/(BigInt lhs, const BigInt& rhs) {
   // BigInt result;
    // TODO: Implement this operator
    lhs /= rhs;

    return lhs;
}

// Binary modulus operator (x % y)
BigInt operator%(BigInt lhs, const BigInt& rhs)
{
    BigInt result;
    return result;
}

// Equality comparison operator (x == y)
bool operator==(const BigInt& lhs, const BigInt& rhs)
{
    // TODO: Implement this operator
    if(lhs.isNegative != rhs.isNegative)
    {
        return false;
    }

    return lhs.number == rhs.number ;
}

// Inequality comparison operator (x != y)
bool operator!=(const BigInt& lhs, const BigInt& rhs)
{
    // TODO: Implement this operator
    return !(lhs == rhs);
}

// Less-than comparison operator (x < y)
bool operator<(const BigInt& lhs, const BigInt& rhs)
{
    // TODO: Implement this operator
    if(lhs.isNegative && !rhs.isNegative)
        return true;
    if(!lhs.isNegative && rhs.isNegative)
        return false;
    int temp = lhs.compareMagnitude(rhs);
    if(!lhs.isNegative)
        return temp == -1;
    else
    return temp == 1;


}

// Less-than-or-equal comparison operator (x <= y)
bool operator<=(const BigInt& lhs, const BigInt& rhs)
{
    // TODO: Implement this operator
   return (lhs < rhs) || (lhs == rhs) ;
}

// Greater-than comparison operator (x > y)
bool operator>(const BigInt& lhs, const BigInt& rhs)
{
    // TODO: Implement this operator
   return !(lhs <= rhs);
}

// Greater-than-or-equal comparison operator (x >= y)
bool operator>=(const BigInt& lhs, const BigInt& rhs)
{
    // TODO: Implement this operator
    return !(lhs < rhs);
}

int main()
{
    cout << "=== BigInt Class Test Program ===" << endl << endl;
    cout << "NOTE: All functions are currently empty." << endl;
    cout << "Your task is to implement ALL the functions above." << endl;
    cout << "The tests below will work once you implement them correctly." << endl << endl;

    return 0;
}
