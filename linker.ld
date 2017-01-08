MEMORY
{
    ram (rwx)  : ORIGIN = 0x20000000, LENGTH = 8K
    stack(rwx) : ORIGIN = ORIGIN(ram) + LENGTH(ram), LENGTH = 0k 
    rom (rx)    : ORIGIN =  0x00010000, LENGTH = 128K
}


SECTIONS
{
    .nvic_vector : 
    {
        *(vectors)    /* Vector table */
    } >rom

    .text : 
    {
        *(.text)      /* Program code */
        *(.text.*)
        *(.rodata)    /* Read only data */
        *(.rodata.*)
        _datai_start = .;
    } >rom

    .data : 
    {
        _data_start = .;
        *(.data)      /* Data memory */
        _data_end = .;
    } >ram AT >rom 

    .data_init : 
    {
        _datai_end = .;
    } >rom

    .bss :
    {
        __bss_start__ = .;
        *(.bss)       
        *(COMMON)        
        __bss_end__ = .;
    } >ram 

    .init.array :
    {
        __init_array_start = .;
        *(.init_array)
        *(.init_array.*)
        __init_array_end = .;
    } > ram

    .ARM.exidx :
    {
        __exidx_start = . ;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } >ram

    .heap :
    {
        _HEAP = .;
    } >ram

    .stack :
    {
        _stack_top = .;
    } >stack

}  
