/*
Задача 2. Большие числа
Описание
Вам нужно реализовать класс для работы с большими числами, которые не помещаются в стандартные типы данных.

Для этого класса нужно определить методы:

конструктор перемещения;
перемещающий оператор присваивания;
оператор сложения двух больших чисел;
оператор умножения на число.
Для реализации этого класса можно воспользоваться std::string или std::vector.

Пример правильной работы программы
auto number1 = big_integer("114575");
auto number2 = big_integer("78524");
auto result = number1 + number2;
std::cout << result; // 193099
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class big_integer {
public:
    big_integer() = default;

    explicit big_integer(const std::string& str) {
        for (size_t i = str.size(); i > 0; --i) {
            digits.push_back(str[i - 1] - '0');
        }
        remove_leading_zeros();
    }

    big_integer(big_integer&& other) noexcept : digits(std::move(other.digits)) {}

    big_integer& operator=(big_integer&& other) noexcept {
        if (this != &other) {
            digits = std::move(other.digits);
        }
        return *this;
    }

    ~big_integer() = default;

    big_integer operator+(const big_integer& other) const {
        big_integer result("");
        int carry = 0;
        size_t max_size = std::max(digits.size(), other.digits.size());
        
        for (size_t i = 0; i < max_size || carry; ++i) {
            int sum = carry;
            if (i < digits.size()) sum += digits[i];
            if (i < other.digits.size()) sum += other.digits[i];
            
            result.digits.push_back(sum % 10);
            carry = sum / 10;
        }
        return result;
    }

    big_integer operator*(int n) const {
        big_integer result("");
        int carry = 0;
        
        for (size_t i = 0; i < digits.size() || carry; ++i) {
            int prod = carry;
            if (i < digits.size()) prod += digits[i] * n;
            
            result.digits.push_back(prod % 10);
            carry = prod / 10;
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const big_integer& num) {
        if (num.digits.empty()) {
            os << 0;
        } else {
            for (size_t i = num.digits.size(); i > 0; --i) {
                os << num.digits[i - 1];
            }
        }
        return os;
    }

private:
    std::vector<int> digits;

    void remove_leading_zeros() {
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
    }
};

int main() {
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    std::cout << result << std::endl;
    return 0;
}