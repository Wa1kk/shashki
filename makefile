OBJS=main.o console.o x86.o libc.o proc.o idt.o isr.o syscall.o irq.o timer.o keyboard.o
CFLAGS=-m32 -nostdlib -nodefaultlibs -Wno-builtin-declaration-mismatch

kernel: $(OBJS)
	ld -m elf_i386 -T link.ld -o kernel $(OBJS)

x86.o: x86.asm
	nasm -f elf32 x86.asm -o x86.o
run:
	qemu-system-i386 -kernel kernel
run_nokey:
	qemu-system-i386 -kernel kernel -bt device:keyboard
debug:
	qemu-system-i386 -kernel kernel -s -S