
BUILD_DIR = build/
BIN_DIR = bin/
LIB_DIR = lib/

OBJECTS = $(shell find src -iname *.c | sed -E 's/^(.*)\.c$$/\1.o/g')
BUILT_OBJECTS = $(shell echo "$(OBJECTS)" | sed -E 's~(src[^ ]+)~$(BUILD_DIR)\1~g')

CFLAGS=-fPIC -g

.PHONY: all lib clean examples

all: clean lib examples

%.o: %.c
	mkdir -p $$(dirname $(BUILD_DIR)$@)
	$(CC) -c -o $(BUILD_DIR)$@ $< $(CFLAGS)

examples: lib examples/cli.o
	mkdir -p $(BIN_DIR)
	$(CC) -L$(LIB_DIR) -lopone -o $(BIN_DIR)cli $(BUILD_DIR)examples/cli.o

lib: $(OBJECTS)
	mkdir -p $(LIB_DIR)
	ar rcs $(LIB_DIR)libopone.a $(BUILT_OBJECTS)
	$(CC) -shared -W1,-soname,libopone.so.1 -o $(LIB_DIR)libopone.so.1 $(BUILT_OBJECTS)

clean:
	rm -rf $(BUILD_DIR) $(LIB) $(BIN)
