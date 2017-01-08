#include <stdint.h>

unsigned int my_global_variable_zero = 0;
unsigned int my_global_variable_one  = 1;
unsigned int my_global_variable_two  = 2;

int main(void)
{
    int i=0;

    while(1)
    {
        i++;
        my_global_variable_zero++;
        my_global_variable_one++;
        my_global_variable_two++;
    }
}

