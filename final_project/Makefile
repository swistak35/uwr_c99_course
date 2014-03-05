TARGET = carrot
OBJS = main.o subjects.o activities.o interaction.o support.o statistics.o timer.o

OPTIMIZE = O2
CC = gcc
LD = gcc

CFLAGS  = -$(OPTIMIZE)
#CFLAGS += -Wall
CFLAGS += -std=c99

ESC = \033[
DEBUG = $(ESC)34;40;1m
PROGRAM = $(ESC)33;40;1m
STOP = $(ESC)0m

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS)

clean:
	@echo "$(DEBUG)> Removing the rubbish…$(STOP)"
	rm -rf *.o
	rm -f $(TARGET)

%.o: %.c
	@echo "$(DEBUG)>> Compiling $<…$(STOP)"
	$(CC) $(CFLAGS) -c -o $@ $<
