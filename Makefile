ARMGNU ?= arm-none-eabi

AOPS = --warn --fatal-warnings 
CFLAGS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding 


all : kernel7.img 

clean :
	rm -f *.o
	rm -f hal/*.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf
	rm -f *.list
	rm -f *.img
	rm -f *.bc

OBJS=main.o hal/rpi-gpio.o hal/rpi-armtimer.o hal/rpi-interrupts.o

vectors.o : vectors.s
	$(ARMGNU)-as vectors.s -o vectors.o

	
%.o: %.c
	$(ARMGNU)-gcc $(CFLAGS) -c $< -o $@
	
hal/%.o: hal/%.c
	$(ARMGNU)-gcc $(CFLAGS) -c $< -o $@

main.elf : memmap vectors.o  $(OBJS)
	$(ARMGNU)-ld vectors.o $(OBJS) -T memmap -o main.elf
	$(ARMGNU)-objdump -D main.elf > main.list

kernel7.img : main.elf
	$(ARMGNU)-objcopy main.elf -O binary kernel7.img

main.hex : main.elf
	$(ARMGNU)-objcopy main.elf -O ihex main.hex

