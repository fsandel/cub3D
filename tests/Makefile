CC = cc
LDFLAGS = -lcriterion -L.. -lcub3dtest
SRC = arg_checks.c
EXECS = $(SRC:%.c=%.out)
%.out: %.c
	@$(CC) $< -o $@ $(LDFLAGS)
all: $(EXECS)
run: all
	@for exec in $(EXECS); do ./$$exec; done
clean:
	rm *.out
re:
	clean run
