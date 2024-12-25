.section _kolibri_header
    .ascii "MENUET01"
    .int 1 # version
    .int _kolibri_start
    .int _kolibri_program_end
    .int _kolibri_stack_top # initially allocated memory
    .int _kolibri_stack_top # top of the stack
    .int 0 # args
    .int 0 # exe_path
