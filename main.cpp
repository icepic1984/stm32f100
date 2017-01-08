#include <stdint.h>

unsigned int my_global_variable_zero = 0;
unsigned int my_global_variable_one  = 1;
unsigned int my_global_variable_two  = 2;

struct test
{
    test() : t(0) {
    }
    test(int a) : t(a) {
    }

    int t;
};

test glob(100);

int main(void)
{
    int i=0;

    {
        test t;
        t.t = 10;
    }
        
    

    while(1)
    {
        glob.t++;
        i++;
        my_global_variable_zero++;
        my_global_variable_one++;
        my_global_variable_two++;
    }
}

