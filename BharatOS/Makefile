all: os-image.bin

os-image.bin: boot.bin kernel.bin
    cat boot.bin kernel.bin > os-image.bin

boot.bin: boot.asm
    nasm -f bin boot.asm -o boot.bin

kernel.bin: kernel.o kernel_asm.o
    ld -o kernel.bin -Ttext 0x1000 kernel_asm.o kernel.o --oformat binary

kernel.o: kernel.c
    gcc -ffreestanding -c kernel.c -o kernel.o

kernel_asm.o: kernel.asm
    nasm -f elf kernel.asm -o kernel_asm.o

clean:
    rm -f *.bin *.o
