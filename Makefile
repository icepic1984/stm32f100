CC = arm-none-eabi-g++
LD = arm-none-eabi-g++ 
CP = arm-none-eabi-objcopy
OD = arm-none-eabi-objdump

CFLAGS = -c -g -mcpu=cortex-m3 -mthumb -fno-unwind-tables -fno-exceptions
LDFLAGS = -Tlinker.ld -nostartfiles  -L/usr/arm-none-eabi/lib/thumb
CPFLAGS = -Obinary
ODFLAGS = -S

all: image.bin

clean:
	-rm image.bin main.o startup.o

image.bin: main.o startup.o
	$(LD) $(LDFLAGS) -o image.bin startup.o main.o -lm

main.o : 
	$(CC) $(CFLAGS) main.cpp

startup.o:
	$(CC) $(CFLAGS) startup.c

