CC = cc
BREW = $(HOME)/.brew
LDFLAGS = -lcriterion -L.. -lcub3dtest
SRC = arg_tests.c map_tests.c
EXECS = $(SRC:%.c=%.out)
%.out: %.c
	@$(CC) $< -o $@ $(LDFLAGS) ../lib/MLX42/build/libmlx42.a -lglfw -L"$(BREW)/opt/glfw/lib/"
all: $(EXECS)
run: all
	@for exec in $(EXECS); do ./$$exec; done
clean:
	rm *.out
re:
	clean run
