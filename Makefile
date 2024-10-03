all: os-image

boot.bin: boot.asm
    nasm -f bin boot.asm -o boot.bin

kernel.bin: kernel.c memory.c string.c stdio.c io.c fs.c
    gcc -m32 -ffreestanding -c kernel.c -o kernel.o
    gcc -m32 -ffreestanding -c memory.c -o memory.o
    gcc -m32 -ffreestanding -c string.c -o string.o
    gcc -m32 -ffreestanding -c stdio.c -o stdio.o
    gcc -m32 -ffreestanding -c io.c -o io.o
    gcc -m32 -ffreestanding -c fs.c -o fs.o
    ld -m elf_i386 -Ttext 0x1000 --oformat binary kernel.o memory.o string.o stdio.o io.o fs.o -o kernel.bin

dmd.air: dmd.c string.c stdio.c keyboard.c io.c
    gcc -m32 -ffreestanding -c dmd.c -o dmd.o
    gcc -m32 -ffreestanding -c string.c -o string.o
    gcc -m32 -ffreestanding -c stdio.c -o stdio.o
    gcc -m32 -ffreestanding -c keyboard.c -o keyboard.o
    gcc -m32 -ffreestanding -c io.c -o io.o
    ld -m elf_i386 -Ttext 0x8000 --oformat binary dmd.o string.o stdio.o keyboard.o io.o -o dmd.air

os-image: boot.bin kernel.bin dmd.air
    cat boot.bin kernel.bin dmd.air > os-image

clean:
    rm -f *.bin *.o os-image
