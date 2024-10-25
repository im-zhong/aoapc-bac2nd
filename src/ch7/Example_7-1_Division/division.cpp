// 2024/10/25
// zhangzhong

#include <ios>
#include <iostream>
#include <vector>

struct Fractional {
    int numerator;
    int denominator;
};

bool HasFiveDifferentDigit(const int number) {
    // three digit number is impossible to have five different digit
    if (number < 1000) {
        return false;
    }

    // 大于五位数的数字也不可能拥有五个不同的digit
    if (number > 99999) {
        return false;
    }

    int num = number;
    int digits[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int digit = 0;
    while (num > 0) {
        digit = num % 10;
        digits[digit] += 1;
        num = num / 10;
    }

    // 如果是四位数
    if (number >= 1000 && number <= 9999) {
        // 我们要给digits补一个零
        digits[0] += 1;
    }

    // 然后检查digits
    // 当且仅当 所有数字都是1 or 0 且刚好有五个1时 符合条件
    int digit_count = 0;
    for (int i = 0; i < 10; i++) {
        if (digits[i] != 0 && digits[i] != 1) {
            return false;
        }
        if (digits[i] == 1) {
            digit_count++;
        }
    }

    return digit_count == 5;
}

bool UseTenDigits(const int num1, const int num2) {

    int num = num1;
    int digits[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int digit = 0;
    while (num > 0) {
        digit = num % 10;
        digits[digit] += 1;
        num = num / 10;
    }

    num = num2;
    while (num > 0) {
        digit = num % 10;
        digits[digit] += 1;
        num = num / 10;
    }

    // 如果是四位数
    // 那么补零
    if (num1 >= 1000 && num1 <= 9999) {
        // 我们要给digits补一个零
        digits[0] += 1;
    }
    if (num2 >= 1000 && num2 <= 9999) {
        // 我们要给digits补一个零
        digits[0] += 1;
    }

    for (int i = 0; i < 10; i++) {
        if (digits[i] != 1) {
            return false;
        }
    }
    return true;
}

std::vector<Fractional> EnumerateFractional(int number) {

    auto fracs = std::vector<Fractional>{};

    for (int denominator = 0; denominator < 99999; denominator++) {
        // first check the number is composed by five different digits
        if (!HasFiveDifferentDigit(denominator)) {
            continue;
        }

        // then calculate the numerator
        int numerator = number * denominator;
        if (number > 99999) {
            // early stop
            break;
        }

        if (HasFiveDifferentDigit(numerator)) {
            // 就算是这样，也不能掉以轻心啊
            // 我们要保证numerator和的nominator使用的digits不一样才行
            if (UseTenDigits(numerator, denominator)) {
                fracs.push_back(Fractional{numerator, denominator});
            }
        }
    }

    return fracs;
}

int main() {
    int number = 0;
    int test_case_id = 0;
    while (std::cin >> number) {
        if (number == 0) {
            break;
        }

        if (test_case_id != 0) {
            std::cout << std::endl;
        }
        test_case_id++;

        std::vector<Fractional> fractionals = EnumerateFractional(number);
        if (fractionals.empty()) {
            std::cout << "There are no solutions for " << number << ".\n";
        } else {
            for (const auto& fractional : fractionals) {
                std::printf("%05d / %05d = %d\n", fractional.numerator,
                            fractional.denominator, number);
                // std::cout < < fractional.numerator
                //                   << " / " << fractional.denominator << " = "
                //                   << number << "\n";
            }
        }
    }
}