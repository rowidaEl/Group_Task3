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
    BigInt operator-() const {
        BigInt result = *this;
        if (result.number != "0")
            result.isNegative = !result.isNegative;
        return result;
    }

    // Unary plus operator (+x)
    BigInt operator+() const {
        return *this;
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
        *this += BigInt(1);
        return *this;
    }

    BigInt operator++(int) {
        BigInt temp = *this;
        *this += BigInt(1);
        return temp;
    }

    // Pre-decrement operator (--x)
    BigInt& operator--() {
        *this -= BigInt(1);
        return *this;
    }

    // Post-decrement operator (x--)
    BigInt operator--(int) {
        BigInt temp = *this;
        *this -= BigInt(1);
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

    /*
    // Test 1: Constructors and basic output
    cout << "1. Constructors and output:" << endl;
    BigInt a(12345);
    BigInt b("-67890");
    BigInt c("0");
    BigInt d = a;
    cout << "a (from int): " << a << endl;
    cout << "b (from string): " << b << endl;
    cout << "c (zero): " << c << endl;
    cout << "d (copy of a): " << d << endl << endl;

    // Test 2: Arithmetic operations
    cout << "2. Arithmetic operations:" << endl;
    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "a * b = " << a * b << endl;
    cout << "b / a = " << b / a << endl;
    cout << "a % 100 = " << a % BigInt(100) << endl << endl;

    // Test 3: Relational operators
    cout << "3. Relational operators:" << endl;
    cout << "a == d: " << (a == d) << endl;
    cout << "a != b: " << (a != b) << endl;
    cout << "a < b: " << (a < b) << endl;
    cout << "a > b: " << (a > b) << endl;
    cout << "c == 0: " << (c == BigInt(0)) << endl << endl;

    // Test 4: Unary operators and increments
    cout << "4. Unary operators and increments:" << endl;
    cout << "-a: " << -a << endl;
    cout << "++a: " << ++a << endl;
    cout << "a--: " << a-- << endl;
    cout << "a after decrement: " << a << endl << endl;

    // Test 5: Large number operations
    cout << "5. Large number operations:" << endl;
    BigInt num1("12345678901234567890");
    BigInt num2("98765432109876543210");
    cout << "Very large addition: " << num1 + num2 << endl;
    cout << "Very large multiplication: " << num1 * num2 << endl << endl;

    // Test 6: Edge cases and error handling
    cout << "6. Edge cases:" << endl;
    BigInt zero(0);
    BigInt one(1);
    try {
        BigInt result = one / zero;
        cout << "Division by zero succeeded (unexpected)" << endl;
    } catch (const runtime_error& e) {
        cout << "Division by zero correctly threw error: " << e.what() << endl;
    }
    cout << "Multiplication by zero: " << one * zero << endl;
    cout << "Negative multiplication: " << BigInt(-5) * BigInt(3) << endl;
    cout << "Negative division: " << BigInt(-10) / BigInt(3) << endl;
    cout << "Negative modulus: " << BigInt(-10) % BigInt(3) << endl;
    */

    return 0;
}