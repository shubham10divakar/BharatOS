[org 0x7c00]
start:
    mov ah, 0x0e
    mov al, 'H'
    int 0x10
    mov al, 'i'
    int 0x10
    cli
    hlt
times 510 - ($-$$) db 0
dw 0xaa55