[extern kernel_main]
[bits 32]

start:
    cli
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp code_segment:start32

[section .text]
[bits 32]
start32:
    call kernel_main
    hlt
