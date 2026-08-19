CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -g
TARGET = mini-rpg
SOURCE = src/main.c

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)