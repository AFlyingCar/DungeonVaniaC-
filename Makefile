CC = g++

CFLAGS = -g -Wfatal-errors -std=c++11

TARGET = DungeonVania

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) *.cpp #$(TARGET).cpp

clean:
	$(RM) $(TARGET)
