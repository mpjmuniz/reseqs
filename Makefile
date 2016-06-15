CC=gcc
#CFLAGS=-g -Wall -Wextra -Isrc -rdynamic -DNDEBUG -Iinclude $(OPTFLAGS)
CFLAGS=-O2 -Isrc -rdynamic -DNDEBUG -Iinclude $(OPTFLAGS)

LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

#TEST_SRC=$(wildcard tests/*_tests.c)
#TESTS=$(patsubst %.c,%,$(TEST_SRC))

INTERFACE_SRC=$(wildcard interface/*.c)
INTERFACE=$(patsubst %.c,%,$(INTERFACE_SRC))

TARGET=build/reseqs.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# The Target Build
all: $(TARGET) $(SO_TARGET) interface tests

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -fPIC -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

# The Unit Tests
#.PHONY: tests
#tests: CFLAGS += $(TARGET) -ldl
#tests: LDLIBS += $(TARGET)
#tests: LDLIBS += -lm
#tests: $(TESTS)
#	sh ./tests/runtests.sh

interface: LDLIBS += $(TARGET)
interface: LDLIBS += -lm
interface: $(INTERFACE)

# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
#	rm -f tests/tests.log 
	rm -f interface/interface.o
	rm -f interface/interface
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

# The Install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
check:
	@echo Files with potentially dangerous functions.
	@egrep '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)\
		|stpn?cpy|a?sn?printf|byte_)' $(SOURCES) || true

