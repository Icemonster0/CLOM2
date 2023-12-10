/**
 * MIT License
 *
 * Copyright (c) 2023 András Borsányi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CLOM2_H
#define CLOM2_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

#define CLOM2_SET_ARGS(c, v) clom2::args.reserve(c); for (int i = 0; i < c; ++i) clom2::args.emplace_back(v[i]);

#define CLOM2_GENERAL_SETTING(name, T, value, hint, converter) T name = converter(clom2::find_setting_value(#name, #value)); std::string name##_hint = #hint;

#define CLOM2_SETTING_STRING(name, value, hint) CLOM2_GENERAL_SETTING(name, std::string, value, hint, std::string)
#define CLOM2_SETTING_INT(name, value, hint) CLOM2_GENERAL_SETTING(name, int, value, hint, clom2::str_to_int)
#define CLOM2_SETTING_FLOAT(name, value, hint) CLOM2_GENERAL_SETTING(name, float, value, hint, clom2::str_to_float)
#define CLOM2_SETTING_DOUBLE(name, value, hint) CLOM2_GENERAL_SETTING(name, double, value, hint, clom2::str_to_double)

#define CLOM2_FLAG(name, hint) bool name = clom2::find_flag_value(#name); std::string name##_hint = #hint;

namespace clom2 {
    std::vector<std::string> args;

    std::string find_setting_value(std::string name, std::string default_value) {
        auto i = std::find(args.begin(), args.end(), name);

        if (args.end() == i) {
            return default_value;
        }

        if (--args.end() == i) {
            std::cout << "error: Missing value for setting '" << name << "'\n";
            exit(-1);
        }

        return (*++i);
    }

    bool find_flag_value(std::string name) {
        auto i = std::find(args.begin(), args.end(), name);

        if (args.end() == i) return false;
        else return true;
    }

    int str_to_int(std::string str) {
        int v;
        try {
            v = std::stoi(str);
        } catch (...) {
            std::cout << "error: Failed to parse the value '" << str << "' (Should be an integer)\n";
            exit(-1);
        }
        return v;
    }

    float str_to_float(std::string str) {
        float v;
        try {
            v = std::stof(str);
        } catch (...) {
            std::cout << "error: Failed to parse the value '" << str << "' (Should be a float)\n";
            exit(-1);
        }
        return v;
    }

    double str_to_double(std::string str) {
        double v;
        try {
            v = std::stod(str);
        } catch (...) {
            std::cout << "error: Failed to parse the value '" << str << "' (Should be a double)\n";
            exit(-1);
        }
        return v;
    }
} /* end of namespace clom2 */

#endif /* end of include guard: CLOM2_H */
