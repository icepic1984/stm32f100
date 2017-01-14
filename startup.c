#include <stdint.h>
#include <sys/stat.h>


// Definition of main function
extern int main(void);

extern "C" {

void __libc_init_array(void);

void _init(void);

}

// Definition of initialization function
void low_level_init(void);

// Defintion of nmi handler
void nmi_handler(void);

// Definition of hard default handler
void hardfault_handler(void);

// Start address of stack (defined by linker)
extern unsigned int _stack_top;

// Define the vector table
unsigned int* the_nvic_vector[4]
    __attribute__((section(".nvic_vector"))) = {
        (unsigned int*)&_stack_top,      // stack pointer
        (unsigned int*)low_level_init,   // code entry point
        (unsigned int*)nmi_handler,      // NMI handler (not really)
        (unsigned int*)hardfault_handler // hard fault handler (let's hope not)
};

// Start of .bss section (defined by linker)
extern uint32_t __bss_start__;

// End of .bss section (defined by linker)
extern uint32_t __bss_end__;

// Start of relocation address of .data section (defined by linker)
extern uint32_t _data_start;

// End of relocation address of .data section (defined by linker)
extern uint32_t _data_end;

// Start load address of data section (defined by linker)
extern uint32_t _datai_start;

// End load address of data section (defined by linker)
extern uint32_t _datai_end;

// Initialization of .bss section,  data section and call of global static
// constructors
void low_level_init(void)
{
    uint32_t* bss_start = (uint32_t*)&__bss_start__;
    uint32_t* bss_end = (uint32_t*)&__bss_end__;
    while (bss_start < bss_end) {
        *bss_start = 0;
        bss_start++;
    }

    uint32_t* data_start = (uint32_t*)&_data_start;
    uint32_t* data_end = (uint32_t*)&_data_end;
    uint32_t* datai_start = (uint32_t*)&_datai_start;
    uint32_t* datai_end = (uint32_t*)&_datai_end;

    uint32_t data_size = data_end - data_start;
    uint32_t datai_size = datai_end - datai_start;

    if (data_size != datai_size) {
        // Linker script is not correct.
        while (1)
            ;
    }

    while (data_start < data_end) {
        *data_start = *datai_start;
        data_start++;
        datai_start++;
    }

    __libc_init_array();

    main();
}


extern "C" {

// Start of heap space (defined by linker)
extern char _heap_start; 

// End of heap space (defined by linker)
extern char _heap_end; 


char *cur_heap = 0;
caddr_t _sbrk(int incr)
{

    char* prev_heap_end;

    if (cur_heap == 0) {
        cur_heap = &_heap_start;
    }
    prev_heap_end = cur_heap;

    if (cur_heap + incr > &_heap_end) {
        /* Heap and stack collision */
        return (caddr_t)0;
    }

    cur_heap += incr;
    return (caddr_t)prev_heap_end;
 }

 
void _exit()
{
    // Empty
}

void _kill()
{
    // Empty
}

void _init()
{
    // Empty
}

int _close(int file)
{
    // Empty
    return -1;
}

int _fstat(int file, struct stat* st)
{
    // Emtpy
    return 0;
}

int _isatty(int file)
{
    // Empty
    return 1;
}

int _lseek(int file, int ptr, int dir)
{
    // Empty
    return 0;
}

int _open(const char* name, int flags, int mode)
{
    // Empty
    return -1;
}

int _read(int file, char* ptr, int len)
{
    // Empty
    return -1;
}

int _write(int file, char* ptr, int len)
{
    return -1;
}

int _getpid()
{
    return -1;
}


}

void nmi_handler(void)
{
    return;
}

void hardfault_handler(void)
{
    return;
}
