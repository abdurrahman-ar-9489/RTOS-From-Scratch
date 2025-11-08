CC = arm-none-eabi-gcc
INCLUDES = 	-I. \
			-I../../Include/CMSIS/Include \
			-I../../Include/ek-tm4c123gxl
MACH = cortex-m4
CFLAGS = -mcpu=$(MACH) -mthumb -O0 -std=gnu11 $(INCLUDES)
LDFLAGS = -nostdlib -T linker_script.ld -Wl,-Map=linker_map.map


all: main.o delay.o startup_tm4c.o bsp.o system_TM4C123GH6PM.o final.elf

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $^

delay.o: delay.c
	$(CC) $(CFLAGS) -c -o $@ $^

bsp.o: bsp.c
	$(CC) $(CFLAGS) -c -o $@ $^

startup_tm4c.o: startup_tm4c.c
	$(CC) $(CFLAGS) -c -o $@ $^

system_TM4C123GH6PM.o: system_TM4C123GH6PM.c
	$(CC) $(CFLAGS) -c -o $@ $^

final.elf: main.o delay.o startup_tm4c.o bsp.o system_TM4C123GH6PM.o
	$(CC) $(LDFLAGS) -o $@ $^


clean:
	rm -rf *.o *.elf