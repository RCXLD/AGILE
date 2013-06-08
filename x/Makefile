CC = gcc
CCFLAGS = -Wall -g
LDFLAGS = -lm

TARGET = geo-project
SOURCES = $(wildcard ./source/*.c)
INCLUDES = ./include
OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

%.o: %.c
	$(CC) $(CCFLAGS) -I$(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJECTS)

cleaner: clean
	$(RM) $(TARGET)

.PHONY: clean cleaner

