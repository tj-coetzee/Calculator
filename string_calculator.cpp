#include <iostream>
#include <string>
#include "./string_calculator.h"

using std::cout, std::endl;
using std::string;

unsigned int digit_to_decimal(char digit) {

    char digits[10] = {'0','1','2','3','4','5','6','7','8','9'};
    int index = -1;
    for (int i = 0; i < 10; ++i) {
        if (digit == digits[i]) {
            index = i;
            break;
        }
    }
    // if digit doesn't equal any digit 0-9, throw invalid_argument
    if (index == -1) {
        throw std::invalid_argument("Invalid digit");
    }
    return index;
}

char decimal_to_digit(unsigned int decimal) {

    char digits[10] = {'0','1','2','3','4','5','6','7','8','9'};
    // if decimal is greater than 10, throw invalid_argument
    // no need to check if less than 0 because of unsigned int
    if (decimal >= 10) {
        throw std::invalid_argument("Invalid decimal");
    } else {
        return digits[decimal];
    }
    
}

string trim_leading_zeros(string num) {

    string trim = "";
    unsigned int index = 0;

    while (index < num.size()) {
        // checks for first character thats nonzero and not '-'
        if (num.at(index) != '-' && num.at(index) != '0') { 
            trim = num.substr(index, num.size() - index);
            // if contains any nonzero digit, index is size + 1
            index = num.size() + 1; 
        }
        ++index;
    }
    // if index is NOT size + 1, no non zero digits and returns 0
    if (index == num.size()) {
        return "0";
    }
    // checks for negative sign
    if (num.at(0) == '-') {
        trim.insert(0,"-");
    }
    return trim;
}

string add(string lhs, string rhs) {
    string answer = "", temp = "";
    bool is_negative = false;
    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);
    // checks for negative sign
    if (lhs.at(0) == '-') {
        is_negative = true;
        lhs = lhs.substr(1, lhs.size() - 1);
        rhs = rhs.substr(1, rhs.size() - 1);
    }
    // if lhs size < rhs size, swap variable values
    if (lhs.size() < rhs.size()) {
        temp = rhs;
        rhs = lhs;
        lhs = temp;
    }

    int remainder = 0, lhs_digit = 0, rhs_digit = 0, ans = 0, j = lhs.size()-1, i = rhs.size()-1;
    while (i >= 0) {
        lhs_digit = digit_to_decimal(lhs.at(j));
        rhs_digit = digit_to_decimal(rhs.at(i));
        ans = lhs_digit + rhs_digit + remainder;
        remainder = ans / 10;
        answer = decimal_to_digit(ans % 10) + answer;
        --i;
        --j;
    }
    while (remainder != 0) {
        if (j < 0) {
            answer = decimal_to_digit(remainder) + answer;
            break;
        } else {
            answer = decimal_to_digit((digit_to_decimal(lhs.at(j)) + remainder) % 10) + answer;
            remainder = (digit_to_decimal(lhs.at(j)) + remainder) / 10;
        }
        --j;
    }
    while (j != -1) {
        answer = lhs.at(j) + answer;
        --j;
    }
    // adds back negative sign if true
    if (is_negative) {
        answer.insert(0, "-");
    }
    return answer;
}

string multiply(string lhs, string rhs) {
    string answer = "0", temp = "";
    bool is_negative = false;
    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);
    if ((lhs.at(0) == '-' && rhs.at(0) != '-') || (lhs.at(0) != '-' && rhs.at(0) == '-')) {
        is_negative = true;
    }

    if (lhs.at(0) == '-') {
        lhs = lhs.substr(1, lhs.size()-1);
    } 
    if (rhs.at(0) == '-') {
        rhs = rhs.substr(1, rhs.size()-1);
    }

    int remainder = 0, lhs_digit = 0, rhs_digit = 0, ans = 0;
    string a = "";
    for (int i = rhs.size()-1; i >= 0; --i) {
        for (int k = rhs.size()-1; k > i; --k) {
            a = "0" + a;
        }
        rhs_digit = digit_to_decimal(rhs.at(i));
        for (int j = lhs.size()-1; j >= 0; --j) {
            lhs_digit = digit_to_decimal(lhs.at(j));
            ans = (lhs_digit * rhs_digit) + remainder;
            remainder = ans / 10;
            a = decimal_to_digit(ans % 10) + a;
            if (j == 0 && remainder != 0) {
                a = decimal_to_digit(remainder) + a;
            }
        }
        answer = add(answer, a);
        a = "";
        remainder = 0;
    }

    if (is_negative) {
        answer = "-" + answer;
    }
    return answer;
}
