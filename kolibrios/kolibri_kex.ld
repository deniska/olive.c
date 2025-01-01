OUTPUT_FORMAT("binary")

SECTIONS {
    . = 0x0;
    .text : {
        *(_kolibri_header)
        *(.text)
    }
    .data : {
        *(.rodata)
        *(.data)
    }
    _kolibri_program_end = .;
    .bss : {
        *(.bss)
    }
    . += 10485760;
    . = ALIGN(32);
    _kolibri_stack_top = .;
}
