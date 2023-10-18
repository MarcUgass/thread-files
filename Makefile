###############################################################################
# Makefile
###############################################################################
CC=gcc
FLAGS=-Wall -g

THEADS_EXAMPLES+=texample1 texample2 texample3 texample4

SRCS=$(addsuffix .c, $(THEADS_EXAMPLES))

all: $(THEADS_EXAMPLES)

# General building rule
$(THEADS_EXAMPLES): $(SRCS)
	gcc $(FLAGS) $@.c -o $@ -lpthread

clean:
	@rm -rf $(THEADS_EXAMPLES)

