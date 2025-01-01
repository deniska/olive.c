OUTPUT_FORMAT("binary")

SECTIONS {
    . = 0x0;
    .text : {
        LONG(0x554e454D); /* MENU */
        LONG(0x31305445); /* ET01 */
        LONG(1); /* version */
        LONG(_kolibri_start);
        LONG(_kolibri_program_end); /* program file size */
        LONG(_kolibri_stack_top); /* initially allocated memory */
        LONG(_kolibri_stack_top); /* top of the stack */
        LONG(_kolibri_params);
        LONG(_kolibri_exe_path);
        *(.text)
    }
    . = ALIGN(16);
    .data : {
        *(.rodata)
        *(.rodata.*)
        *(.data)
    }
    _kolibri_program_end = .;
    .bss : {
        *(.bss)
    }
    . += 1024;
    _kolibri_exe_path = .;
    . += 256;
    _kolibri_params = .;
    . += 10485760;
    . = ALIGN(16);
    _kolibri_stack_top = .;
}
