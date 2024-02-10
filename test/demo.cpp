/*
 * This demonstration shows how one could use the CLOM2 library.
 * In this case, we can set the name, height, smartness, and
 * taste in fruits of our subject using command line options.
 * Example:
 * $ MyApp --name Mark --height 5.2 --smart --favorite-fruits 'mango orange'
 * Result:
 * Mark is 5.2 foot tall and is smart.
 * Their favorite fruits are:
 * - mango
 * - orange
*/

#define CLOM2_IMPLEMENTATION
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
