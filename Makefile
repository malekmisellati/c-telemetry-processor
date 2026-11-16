
CC = gcc

CFLAGS = -Wall -Wextra -std=c11

TARGET = telemetry.exe

SOURCE = src/main.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

clean:
	del $(TARGET)
