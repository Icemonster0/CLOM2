# CLOM2
A single-header Command Line Option Manager library for C++ using macros. For an unnecessarily overcomplicated alternative see [CLOM](https://github.com/Icemonster0/CLOM).

---

## Features
- Parse the values given in the command line to various types and detect the presence of flags
- Declare a variable and initialize it with the value assigned to it in the command line at the same time using a single macro
- Store lists of parameters in an `std::vector` of the corresponding type
- Generate a help message listing the options' names, types, default values and descriptions

## Demo
This is an example for how you could use this library.

``` C++
#include "../clom2.hpp"
#include <iostream>

struct Settings {
    /* Parse and store the option values in variables */
    CLOM2_SETTING_STRING(name, --name, -n, Mr X, The name of our subject);
    CLOM2_SETTING_FLOAT(height, --height, -h, 6.0f, The height of our subject in feet);
    CLOM2_SETTING_STRING_VEC(favorite_fruits, --favorite-fruits, -ff,
                             apple banana cherry,
                             The fruits our subject prefers to consume);
    CLOM2_FLAG(is_smart, --smart, -s, Specify whether our subject is smart);
};

int main(int argc, char const *argv[]) {
    /* Pass the command line arguments to CLOM2 */
    CLOM2_SET_ARGS(argc, argv);

    /* Create the setting wrapper object and check if the user requested
     * a help message */
    CLOM2_CHECK_FOR_HELP_BEGIN(help, h);
    Settings S;
    CLOM2_CHECK_FOR_HELP_END();

    /* Access the options as member variables of the settings object */
    std::cout << S.name << " is " << S.height << " foot tall ";
    std::cout << "and is " << (S.is_smart ? "smart." : "not smart.") << '\n';
    std::cout << "Their favorite fruits are:" << '\n';
    for (auto fruit : S.favorite_fruits) std::cout << "- " << fruit << '\n';

    return 0;
}
```
Here are possible results:
```
$ my-app
Mr X is 6 foot tall and is not smart.
Their favorite fruits are:
- apple
- banana
- cherry
```
```
$ my-app --name Mark --is_smart --height 5.2 --favorite_fruits 'mango orange'
Mark is 5.2 foot tall and is smart.
Their favorite fruits are:
- mango
- orange
```
```
$ my-app help
Available options:
primary-name, alternate-name (type) ['default-value']: description

--name, -n (std::string) ['Mr X']: The name of our subject
--height, -h (float) ['6.0f']: The height of our subject in feet
--favorite-fruits, -ff (std::vector<std::string>) ['apple banana cherry']: The fruits our subject prefers to consume
--smart, -s (flag): Specify whether our subject is smart
help, h (flag): Display this help and exit
```

## Macros
Here is a list of all macros and what they do.

###### Setup
``` C++
CLOM2_SET_ARGS(argc, argv);

```
Pass the argument list to clom2 and store it internally. Must happen before parsing options.

###### Settings
``` C++
CLOM2_SETTING_STRING(var_name, prim_name, alt_name, default_value, hint);
CLOM2_SETTING_STRING_VEC(var_name, prim_name, alt_name, default_value, hint);
CLOM2_SETTING_INT(var_name, prim_name, alt_name, default_value, hint);
CLOM2_SETTING_INT_VEC(var_name, prim_name, alt_name, default_value, hint);
CLOM2_SETTING_FLOAT(var_name, prim_name, alt_name, default_value, hint);
CLOM2_SETTING_FLOAT_VEC(var_name, prim_name, alt_name, default_value, hint);
CLOM2_SETTING_DOUBLE(var_name, prim_name, alt_name, default_value, hint);
CLOM2_SETTING_DOUBLE_VEC(var_name, prim_name, alt_name, default_value, hint);
```
Declare a variable named `var_name` of the corresponding type and initialize it with the command line parameter following either of `prim_name` or `alt_name` if specified, otherwise with `default_value`. Also declare and initialize an `std::string` named `var_name_hint` (where `var_name` is replaced with the variable name) with `hint`.  
The `VEC` variants create an `std::vector` of the corresponding type so that each element in the vector is one word (delimited by spaces) of the given input (in the command line, the list of elements needs to be enclosed in quotation marks, i.e " " or ' ', or each element except the last one has to be followed by a backslash \\ ).
``` C++
CLOM2_GENERAL_SETTING(var_name, prim_name, alt_name, type, default_value, hint, converter);
```
Declare a variable of the type `type` and use the `converter` function (which must return `type` and take an `std::string` as parameter) to parse a string to the right type. See the example in [test/test_all.cpp](test/test_all.cpp).

###### Flags
``` C++
CLOM2_FLAG(var_name, prim_name, alt_name, hint);
```
Similar to `CLOM2_SETTING_<TYPE>` with the difference that a flag always has the type `bool`. If its name is listed in the command line parameters, it is initialized with `true`, otherwise with `false`.

###### Help Message
```C++
CLOM2_CHECK_FOR_HELP_BEGIN(help_flag, alt_help_flag);
CLOM2_CHECK_FOR_HELP_END();
```
Optionally place all settings and flags between `BEGIN` and `END` to generate a help message if the user requests one. If the flag `help_flag` or `alt_help_flag` is found in the command line, the help message is printed and the process exits.
