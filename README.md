# CLOM2

A single-header Command Line Option Manager library for C++ using macros. For a run-time alternative see [CLOM](https://github.com/Icemonster0/CLOM).

---

## Demo
This is an example for how you could use this library.

``` C++
#include "clom2.hpp"
#include <iostream>

struct Settings {
    /* Parse and store the option values in variables */
    CLOM2_SETTING_STRING(name, Mr X, The name of our subject)
    CLOM2_SETTING_FLOAT(height, 6.0f, The height of our subject in feet)
    CLOM2_FLAG(is_smart, Specify whether our subject is smart)
};

int main(int argc, char const *argv[]) {
    /* Pass the command line arguments to CLOM2 */
    CLOM2_SET_ARGS(argc, argv)

    Settings S;

    /* Access the options as member variables of Settings */
    std::cout << S.name << " is " << S.height << " foot tall ";
    std::cout << "and is " << (S.is_smart ? "smart." : "not smart.") << '\n';

    return 0;
}
```
Here are possible results:
```
$ my-app
Mr X is 6 foot tall and is not smart.
```
```
$ my-app name Mark is_smart height 5.2
Mark is 5.2 foot tall and is smart.
```

## Macros

Here is a list of all macros and what they do.

###### Setup
``` C++
CLOM2_SET_ARGS(argc, argv)

```
Pass the argument list to clom2 and store it internally. Must happen before parsing options.

###### Settings
``` C++
CLOM2_SETTING_STRING(name, default_value, hint)
CLOM2_SETTING_INT(name, default_value, hint)
CLOM2_SETTING_FLOAT(name, default_value, hint)
CLOM2_SETTING_DOUBLE(name, default_value, hint)
```
Declare a variable named `name` of the corresponding type and initialize it with the command line parameter if specified, otherwise with `default_value`. Also declare and initialize an `std::string` named `name_hint` (where `name` is replaced with the setting name) with `hint`.
``` C++
CLOM2_GENERAL_SETTING(name, type, default_value, hint, converter)
```
Declare a variable of the type `type` and use the `converter` function (which must return `type` and take an `std::string` as parameter) to parse a string to the right type.

###### Flags
``` C++
CLOM2_FLAG(name, hint)
```
Similar to `CLOM2_SETTING_<TYPE>` with the difference that a flag always has the type `bool`. If its name is listed in the command line parameters, it is initialized with `true`, otherwise with `false`.
