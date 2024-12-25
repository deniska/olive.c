ENTRY(_kolibri_start)

SECTIONS {
    . = 0x0;
    kolibri_header : { *(kolibri_header) }
    .text : { *(.text) }
    .data : { *(.data) }
    .bss : { *(.bss) }
}
