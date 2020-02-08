
BIN=./gbdk-n/bin
OBJ=./obj

build: lib
	mkdir -p $(OBJ)
	$(BIN)/gbdk-n-compile.sh main.c -o $(OBJ)/main.rel
	$(BIN)/gbdk-n-compile.sh tiles.c -o $(OBJ)/tiles.rel
	$(BIN)/gbdk-n-link.sh $(OBJ)/main.rel $(OBJ)/tiles.rel -o $(OBJ)/main.ihx
	$(BIN)/gbdk-n-make-rom.sh $(OBJ)/main.ihx main.gb

build-dir:
	mkdir -p $(OBJ)

clean:
	$(MAKE) -C gbdk-n clean
	rm -rf $(OBJ)
	rm -f main.gb

.PHONY: lib
lib:
	$(MAKE) -C gbdk-n lib
