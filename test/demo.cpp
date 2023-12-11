/*
 * This demonstration shows how one could use the CLOM2 library.
 * In this case, we can set the name, height and smartness
 * of our subject using command line options.
 * Example:
 * $ MyApp name Mark height 5.2 is_smart favorite_fruits 'mango orange'
 * Result:
 * Mark is 5.2 foot tall and is smart.
 * Their favorite fruits are:
 * - mango
 * - orange
*/

#include "../clom2.hpp"
#include <iostream>

struct Settings {
    /* Parse and store the option values in variables */
    CLOM2_SETTING_STRING(name, Mr X, The name of our subject);
    CLOM2_SETTING_FLOAT(height, 6.0f, The height of our subject in feet);
    CLOM2_SETTING_STRING_VEC(favorite_fruits, apple banana cherry, The fruits our subject prefers to consume);
    CLOM2_FLAG(is_smart, Specify whether our subject is smart);
};

int main(int argc, char const *argv[]) {
    /* Pass the command line arguments to CLOM2 */
    CLOM2_SET_ARGS(argc, argv);

    Settings S;

    /* Access the options as member variables of Settings */
    std::cout << S.name << " is " << S.height << " foot tall ";
    std::cout << "and is " << (S.is_smart ? "smart." : "not smart.") << '\n';
    std::cout << "Their favorite fruits are:" << '\n';
    for (auto fruit : S.favorite_fruits) std::cout << "- " << fruit << '\n';

    return 0;
}
