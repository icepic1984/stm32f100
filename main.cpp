#include <stdint.h>
#include "stm32xx.hpp"

int main(void)
{

    constexpr stm32xx::address stack = stm32xx::address(0x2000);

    int i = 0;

    {
        test t;
        t.t = 10;
    }

    while (1) {
        glob.t++;
        i++;
        my_global_variable_zero++;
        my_global_variable_one++;
        my_global_variable_two++;
        my_global_variable_one = stack.value();

    }
}

