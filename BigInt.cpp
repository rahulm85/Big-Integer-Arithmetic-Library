#include <algorithm>
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class BigInt {
private:
    bool negative_;
    std::string digits_;

    static std::string normalize(const std::string& value) {
        const std::size_t first = value.find_first_not_of('0');
        return first == std::string::npos ? "0" : value.substr(first);
    }

    static int compareAbs(const std::string& a, const std::string& b) {
        if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
        if (a == b) return 0;
        return a < b ? -1 : 1;
    }

    static std::string addAbs(const std::string& a, const std::string& b) {
        std::string result;
        int i = static_cast<int>(a.size()) - 1;
        int j = static_cast<int>(b.size()) - 1;
        int carry = 0;
        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) sum += a[i--] - '0';
            if (j >= 0) sum += b[j--] - '0';
            result.push_back(static_cast<char>('0' + sum % 10));
            carry = sum / 10;
        }
        std::reverse(result.begin(), result.end());
        return normalize(result);
    }

    // Requires a >= b, with both operands non-negative digit strings.
    static std::string subtractAbs(const std::string& a, const std::string& b) {
        std::string result;
        int i = static_cast<int>(a.size()) - 1;
        int j = static_cast<int>(b.size()) - 1;
        int borrow = 0;
        while (i >= 0) {
            int digit = (a[i--] - '0') - borrow;
            if (j >= 0) digit -= b[j--] - '0';
            borrow = 0;
            if (digit < 0) {
                digit += 10;
                borrow = 1;
            }
            result.push_back(static_cast<char>('0' + digit));
        }
        std::reverse(result.begin(), result.end());
        return normalize(result);
    }

    void removeNegativeZero() {
        digits_ = normalize(digits_);
        if (digits_ == "0") negative_ = false;
    }

public:
    BigInt() : negative_(false), digits_("0") {}

    explicit BigInt(const std::string& value) : negative_(false), digits_("0") {
        if (value.empty()) throw std::invalid_argument("Empty integer input");

        std::size_t start = 0;
        if (value[0] == '-' || value[0] == '+') {
            negative_ = value[0] == '-';
            start = 1;
        }
        if (start == value.size()) throw std::invalid_argument("Sign without digits");

        for (std::size_t i = start; i < value.size(); ++i) {
            if (!std::isdigit(static_cast<unsigned char>(value[i]))) {
                throw std::invalid_argument("Invalid integer: only decimal digits are accepted");
            }
        }

        digits_ = normalize(value.substr(start));
        removeNegativeZero();
    }

    std::string toString() const {
        return (negative_ ? "-" : "") + digits_;
    }

    BigInt operator-() const {
        BigInt result(*this);
        if (result.digits_ != "0") result.negative_ = !result.negative_;
        return result;
    }

    friend BigInt operator+(const BigInt& a, const BigInt& b) {
        BigInt result;
        if (a.negative_ == b.negative_) {
            result.digits_ = addAbs(a.digits_, b.digits_);
            result.negative_ = a.negative_;
        } else {
            const int cmp = compareAbs(a.digits_, b.digits_);
            if (cmp == 0) return BigInt("0");
            if (cmp > 0) {
                result.digits_ = subtractAbs(a.digits_, b.digits_);
                result.negative_ = a.negative_;
            } else {
                result.digits_ = subtractAbs(b.digits_, a.digits_);
                result.negative_ = b.negative_;
            }
        }
        result.removeNegativeZero();
        return result;
    }

    friend BigInt operator-(const BigInt& a, const BigInt& b) {
        return a + (-b);
    }

    friend BigInt operator*(const BigInt& a, const BigInt& b) {
        if (a.digits_ == "0" || b.digits_ == "0") return BigInt("0");

        std::vector<int> product(a.digits_.size() + b.digits_.size(), 0);
        for (int i = static_cast<int>(a.digits_.size()) - 1; i >= 0; --i) {
            for (int j = static_cast<int>(b.digits_.size()) - 1; j >= 0; --j) {
                const int position = i + j + 1;
                const int value = (a.digits_[i] - '0') * (b.digits_[j] - '0')
                                  + product[position];
                product[position] = value % 10;
                product[position - 1] += value / 10;
            }
        }

        std::string digits;
        std::size_t first = 0;
        while (first < product.size() && product[first] == 0) ++first;
        for (; first < product.size(); ++first) {
            digits.push_back(static_cast<char>('0' + product[first]));
        }

        BigInt result;
        result.digits_ = digits.empty() ? "0" : digits;
        result.negative_ = a.negative_ != b.negative_;
        result.removeNegativeZero();
        return result;
    }

    friend std::ostream& operator<<(std::ostream& out, const BigInt& value) {
        return out << value.toString();
    }
};

int main() {
    std::cout << "Big Integer Arithmetic Library (C++)\n";
    std::cout << "Supported operations: +, -, *\n";
    std::cout << "Enter: <number> <operator> <number> (or q to quit)\n";

    std::string left;
    while (std::cout << "> " && std::cin >> left) {
        if (left == "q" || left == "Q") break;

        char operation;
        std::string right;
        if (!(std::cin >> operation >> right)) {
            std::cerr << "Expected: <number> <operator> <number>\n";
            return 1;
        }

        try {
            const BigInt a(left);
            const BigInt b(right);
            BigInt result;

            switch (operation) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                default:
                    std::cerr << "Unsupported operator. Use +, -, or *.\n";
                    continue;
            }
            std::cout << "= " << result << '\n';
        } catch (const std::exception& error) {
            std::cerr << "Input error: " << error.what() << '\n';
        }
    }
    return 0;
}
