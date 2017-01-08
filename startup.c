#include <stdint.h>

extern int main(void);

extern "C" {
    void __libc_init_array(void);
    void _init(void);
}

void low_level_init(void);
void nmi_handler(void);
void hardfault_handler(void);

extern unsigned int _stack_top;

// Define the vector table
unsigned int * the_nvic_vector[4] 
__attribute__ ((section(".nvic_vector")))= {
    (unsigned int *)	&_stack_top,        // stack pointer
    (unsigned int *) 	low_level_init,    // code entry point
    (unsigned int *)	nmi_handler,       // NMI handler (not really)
    (unsigned int *)	hardfault_handler  // hard fault handler (let's hope not)
};


extern uint32_t __bss_start__;
extern uint32_t __bss_end__;

extern uint32_t _data_start;
extern uint32_t _data_end;
extern uint32_t _datai_start;
extern uint32_t _datai_end;

void low_level_init(void)
{
    uint32_t* bss_start = (uint32_t*)&__bss_start__;
    uint32_t* bss_end = (uint32_t*)&__bss_end__;
    while(bss_start < bss_end)
    {
        *bss_start = 0;
        bss_start++;
    }

    uint32_t* data_start = (uint32_t*) &_data_start;
    uint32_t* data_end = (uint32_t*) &_data_end;
    uint32_t* datai_start = (uint32_t*) &_datai_start;
    uint32_t* datai_end = (uint32_t*) &_datai_end;

    uint32_t data_size  = data_end  - data_start;
    uint32_t datai_size = datai_end - datai_start;

    if(data_size != datai_size) {
        //Linker script is not correct.
        while(1);
    }

    while(data_start < data_end)
    {
        *data_start = *datai_start;
        data_start++;
        datai_start++;
    }

    __libc_init_array();

    main();
}
extern "C"{
void _init()
{};
}


void nmi_handler(void)
{
    return ;
}

void hardfault_handler(void)
{
    return ;
}

