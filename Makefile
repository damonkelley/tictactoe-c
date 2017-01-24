SOURCES = $(wildcard src/*.c)
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

TEST_SOURCES = $(wildcard test/*.c)
TEST_OBJECTS = $(patsubst %.c,%.o,$(TEST_SOURCES))

TICTACTOE_TARGET = build/libtictactoe.so

CFLAGS = -g -Wall -Wextra -fPIC

.PHONY: deps
deps:
	$(MAKE) -C $@

.PHONY: clean-all
clean-all:
	git clean -ffxd --exclude=.exrc

.PHONY: clean
clean:
	rm -f */*.o
	rm -f main runtests
	rm -rf build

.PHONY: build-image
build-image:
	docker build . -t damonkelley/tttc

.PHONY: docker-%
docker-%:
	docker run -it --rm -v $(CURDIR):/build damonkelley/tttc make $*

build:
	mkdir $@

$(TICTACTOE_TARGET): build $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

.PHONY: tictactoe
tictactoe: $(TICTACTOE_TARGET)

runtests: CFLAGS += -Isrc -Ldeps/usr/local/lib -Ideps/usr/local/include
runtests: $(TEST_OBJECTS) tictactoe
	$(CC) $(CFLAGS) -Lbuild $(TEST_OBJECTS) -o $@ -ltictactoe -lcriterion

.PHONY: test
test: runtests
	LD_LIBRARY_PATH=build:deps/usr/local/lib ./runtests --verbose

.PHONY: valgrind
valgrind: runtests
	LD_LIBRARY_PATH=build:deps/usr/local/lib valgrind ./runtests --verbose
