# See https://www.gnu.org/software/make/manual/html_node/ for more information

TARGET   = server

CC    = gcc
CFLAGS    = -std=c99 -D_POSIX_C_SOURCE=200112L -g -Wall -Wextra -Wpedantic -Wbad-function-cast \
          -Wconversion -Wwrite-strings -Wstrict-prototypes
		  
LINKER   = gcc
# linking flags here
LFLAGS   = -Wall -I. -lm		  
		
CFILES  = $(wildcard *.c)
EXE    = $(patsubst %.c, %  , ${CFILES})
TESTCASES=$(patsubst %, tests/%, ${EXE})
INCLUDES := $(wildcard *.h)
SOURCES  := $(wildcard *.c)
OBJECTS  := $(SOURCES:%.c=%.o)

$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): %.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: all clean realclean tests test-commex beautify ${TESTCASES}

all: ${TARGET} ${OBJECTS}

clean:
	${RM} ${OBJECTS}

realclean: clean
	${RM} ${TARGET}

test:    all
	./test01.sh localhost:8080

beautify:
	uncrustify -c ../uncrustify.cfg --replace ${CFILES}