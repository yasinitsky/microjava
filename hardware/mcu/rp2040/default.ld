MEMORY {
    ROM(R) : ORIGIN = 0x00000000, LENGTH = 16K
    FLASH(RX) : ORIGIN = 0x10000000, LENGTH = 2M
    RAM(RWX) : ORIGIN = 0x20000000, LENGTH = 264K
}

SECTIONS {
    __flash_start = ORIGIN(FLASH);

    .flash.boot2 : {
        __boot2_start = .;
        *(.boot2)
        __boot2_end = .;
    } > FLASH

    ASSERT(__boot2_end - __boot2_start == 256, "2nd stage bootloader must be 256 bytes in size.")

    .flash.vectors : {
        *(.vectors)
    } > FLASH

    .flash.text : {
        *(.text)
        . = ALIGN(4);
    } > FLASH

    .flash.rodata : {
        *(.rodata)
        . = ALIGN(4);
    } > FLASH

    .memory_info : {
        *(.memory_info)
        . = ALIGN(4);
    } > FLASH
    
    __flash_end = .;

    __ram_text_begin = ORIGIN(RAM);
    .ram.text : {
        *(.ram.text)
        . = ALIGN(4);
    } > RAM
    __ram_text_end = .;

    __ram_data_begin = .;
    .ram.data : {
        *(.data)
        . = ALIGN(4);
    } > RAM
    __ram_data_end = .;

    __ram_bss_begin = .;
    .ram.bss : {
        *(.bss)
        . = ALIGN(4);
    } > RAM
    __ram_bss_end = .;

    __ram_text_size = __ram_text_end - __ram_text_begin;
    __ram_data_size = __ram_data_end - __ram_data_begin;
    __ram_bss_size = __ram_bss_end - __ram_bss_begin;
    __stack_top = ORIGIN(RAM) + LENGTH(RAM);
}