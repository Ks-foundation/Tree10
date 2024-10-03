; boot.asm
BITS 16
ORG 0x7C00

start:
    ; Load the kernel (starting from sector 2)
    mov ah, 0x02        ; BIOS function: read sectors
    mov al, 5           ; Number of sectors to read
    mov ch, 0           ; Cylinder
    mov dh, 0           ; Head
    mov cl, 2           ; Starting sector
    mov bx, 0x1000      ; Load address: 0x1000
    int 0x13            ; BIOS disk interrupt

    ; Jump to kernel entry point
    jmp 0x1000

times 510-($-$$) db 0
dw 0xAA55
