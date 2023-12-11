/*
 * This is test supposed to check if every macro is working correctly.
 * It also demonstrates a way one can use the library without a wrapper
 * struct (although not recommended).
 * Run this or a similar comand to test:
 * ./a.out word hi words 'what_up wie_gehts' number 5 numbers '3 2 1 3' floaty 0.1234 floaties '0.3 2.0 1.5 3.2' constant 1.0 constants 0.0 letter B banner
*/

#include "../clom2.hpp"
#include <iostream>

char str_to_char(std::string str) {
    return str.at(0);
}

template <typename T>
void print_vec(std::vector<T> vec) {
    for (T element : vec) std::cout << element << ' ';
}

int main(int argc, char const *argv[]) {
    CLOM2_SET_ARGS(argc, argv);

    CLOM2_CHECK_FOR_HELP_BEGIN(help);

    CLOM2_SETTING_STRING(word, hello, a greeting);
    CLOM2_SETTING_STRING_VEC(words, hello hallo hola hej, a list of greetings in different languages);
    CLOM2_SETTING_INT(number, 3, an integer);
    CLOM2_SETTING_INT_VEC(numbers, 42 36 1, a list of integers);
    CLOM2_SETTING_FLOAT(floaty, 1.0f, a number);
    CLOM2_SETTING_FLOAT_VEC(floaties, 0.5f 2.33f, a list of numbers);
    CLOM2_SETTING_DOUBLE(constant, 0.0000000000000000001602, a mathematical or physical constant);
    CLOM2_SETTING_DOUBLE_VEC(constants, 3.1415 2.7182 9.81, a list of mathematical or physical constants);

    /* you need your own str_to_char converter function since chars aren't supported by default */
    CLOM2_GENERAL_SETTING(letter, char, A, any letter or other character, str_to_char);

    CLOM2_FLAG(banner, whether the national flag of C++ exists);

    CLOM2_CHECK_FOR_HELP_END();

    std::cout << "word: " << word_hint << ": "; std::cout << word << '\n';
    std::cout << "words: " << words_hint << ": "; print_vec(words); std::cout << '\n';
    std::cout << "number: " << number_hint << ": "; std::cout << number << '\n';
    std::cout << "numbers: " << numbers_hint << ": "; print_vec(numbers); std::cout << '\n';
    std::cout << "floaty: " << floaty_hint << ": "; std::cout << floaty << '\n';
    std::cout << "floaties: " << floaties_hint << ": "; print_vec(floaties); std::cout << '\n';
    std::cout << "constant: " << constant_hint << ": "; std::cout << constant << '\n';
    std::cout << "constants: " << constants_hint << ": "; print_vec(constants); std::cout << '\n';
    std::cout << "letter: " << letter_hint << ": "; std::cout << letter << '\n';
    std::cout << "banner: " << banner_hint << ": "; std::cout << banner << '\n';

    return 0;
}
