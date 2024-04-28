CC = clang
CFLAGS = -Wall -I/opt/homebrew/Cellar/raylib/5.0/include
LDFLAGS = -L/opt/homebrew/Cellar/raylib/5.0/lib -lraylib -framework IOKit -framework Cocoa -framework OpenGL

TARGET = game
SOURCES = main.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET)

# Define a rule for rebuilding when a header file is changed
%.h: ;
