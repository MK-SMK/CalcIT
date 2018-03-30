#
# Makefile zum Erzeugen von calcit
#
SRCDIR = src
SRCS = $(wildcard $(SRCDIR)/*.c)

all: calcit

calcit: $(SRCS)
	gcc -Wall -g -o calcit $(SRCS) -lreadline -lm

clean:
	rm -f *~ calcit