ARCHS_C := codigo_1.c codigo_2.c

OUTPUTS := $(ARCHS_C:.c=.out)

HEADERS := 
HEADERS_DIR := .
IMPLS_HEADERS := $(HEADERS:.h=.c)
OBJS_HEADERS := $(HEADERS:.h=.o)

OBJS := $(ARCHS_C:.c=.o) $(OBJS_HEADERS)


ARGS := -Wall -Wextra -pedantic -O0 -msse3

all: $(OUTPUTS)

$(OUTPUTS): $(OBJS)
	gcc -g $(@:.out=.o) $(OBJS_HEADERS) -o $@ -L $(HEADERS_DIR) $(ARGS)

%.o: %.c
	gcc -g -o $@ -c $< $(ARGS)

clean:
	-find . -type f -name '*.o' -delete
	-find . -type f -name '*.out' -delete
	-rm $(OUTPUTS:.out=)