# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 09:53:10 by fsandel           #+#    #+#              #
#    Updated: 2023/04/06 11:38:24 by fsandel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	cub3D

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
LINKFLAGS		=
REDIRECT		=	#2> /dev/null 1> /dev/null
OS				=	$(shell uname)

################################################################################
################################################################################

SRC				=	$(addprefix $(SRC_DIR), $(SRC_FILES))
SRC_DIR			=	src/
SRC_FILES		=	main.c

PARSER			=	$(addprefix $(PARSER_DIR), $(PARSER_FILES))
PARSER_DIR		=	src/parser/
PARSER_FILES	=	

UTILS			=	$(addprefix $(UTILS_DIR), $(UTILS_FILES))
UTILS_DIR		=	src/utils/
UTILS_FILES		=	

HDR				=	$(addprefix $(HDR_DIR), $(HDR_DIR))
HDR_DIR			=	include/
HDR_FILES		=	
HDR_INCLUDE		=	-I $(HDR_DIR)

ALL_SRC			=	$(SRC) $(PARSER)

################################################################################
################################################################################

OBJ_DIR			=	obj/
ALL_OBJ			=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(ALL_SRC))
ALL_OBJ_DIR		=	$(sort $(dir $(ALL_OBJ)))

################################################################################
################################################################################

all: libft mlx $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(HDR_INCLUDE) $(MLX_INCLUDE) $(LIBFT_INCLUDE)
	@echo $(LGREEN)"compiled "$^$(DEFAULT)

$(NAME): $(ALL_OBJ_DIR) $(ALL_OBJ)
	@$(CC) $(ALL_OBJ) -o $(NAME) $(LINK_FLAGS) $(LIBFT) $(MLX) $(GLFW)
	@echo $(GREEN)" compiled "$@$(DEFAULT)

clean:
	@echo $(RED)"cleaning:"
	@rm -rfv $(patsubst %/,%,$(OBJ_DIR))
	@echo "cleaned"$(DEFAULT)

fclean:
	@echo $(RED)"fcleaning:"
	@rm -rfv $(patsubst %/,%,$(OBJ_DIR)) $(NAME)
	@echo "fcleaned"$(DEFAULT)

re:	fclean all

bonus:
	@echo "make sure to implement bonus"
test:
	gcc src/main.c $(MLX) -ldl -lglfw -pthread -lm -I ./include -I ./lib/MLX42/include/MLX42 -I ./lib/libft $(LIBFT) -L lib/MLX42/build -lXext -lX11
################################################################################
################################################################################

ffclean:
	@echo $(RED)"hard reset"
	@rm -rf obj
	@rm -rf lib
	@rm -f $(NAME)
	@echo $(DEFAULT)

t:
	make all
	./$(NAME)

$(ALL_OBJ_DIR):
	@mkdir -p $(ALL_OBJ_DIR)

################################################################################
################################################################################

help:
	@make check_brew

check_brew:
ifeq ($(shell which brew ), $(HOME)/.brew/bin/brew)
	@echo "brew is installed"
	@make check_glfw
else
	@echo "no brew found in standart path."
	@echo "use make brew to install"
endif

check_glfw:
ifeq ($(shell brew list | grep glfw), glfw)
	@echo "glfw is installed"
	@make check_cmake
else
	@echo "no glfw found"
	@echo "use make glfw to install"
endif

check_cmake:
		ifeq ($(shell which cmake), $(HOME)/.brew/bin/cmake)
			@echo "cmake is installed in the default directory"
		else
			@echo "no cmake found in the default directory"
			@echo "use make cmake to install"
		endif

################################################################################
################################################################################

brew:
	rm -rf $$HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $$HOME/.brew && echo 'export PATH=$$HOME/.brew/bin:$$PATH' >> $$HOME/.zshrc && source $$HOME/.zshrc && brew update

glfw:
	brew install glfw

cmake:
	brew install cmake

################################################################################
################################################################################

BREW			= $(HOME)/.brew


MLX				=	lib/MLX42/build/libmlx42.a
MLX_INCLUDE		=	-I ./lib/MLX42/include/MLX42
ifeq ($(OS), Darwin)
	GLFW			=	-lglfw -L"$(BREW)/opt/glfw/lib/"
endif
ifeq ($(OS), Linux)
	GLFW			=	-ldl -lglfw -pthread -lm
endif
mlx: $(MLX)

$(MLX):
	@git submodule init $(REDIRECT)
	@git submodule update $(REDIRECT)
	@cd lib/MLX42 && cmake -B build $(REDIRECT)
	@cd lib/MLX42/build && make $(REDIRECT)
	@echo $(GREEN)"created libmlx42.a"$(DEFAULT)

################################################################################
################################################################################

LIBFT			=	$(LIBFT_DIR)$(LIBFT_LIB)
LIBFT_LIB		=	libft.a
LIBFT_DIR		=	lib/libft/
LIBFT_INCLUDE	=	-I ./lib/libft

libft: $(LIBFT)

$(LIBFT):
	@git submodule init $(REDIRECT)
	@git submodule update $(REDIRECT)
	@make -C lib/libft

################################################################################
################################################################################

LSAN			=	LeakSanitizer
LSANLIB			=	/LeakSanitizer/liblsan.a

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
#	LINK_FLAGS += -ltinfo
	LSANLFLAGS := -rdynamic -LLeakSanitizer -llsan -ldl -lstdc++
endif
ifeq ($(UNAME_S),Darwin)
	LSANLFLAGS := -LLeakSanitizer -llsan -lc++
endif

lsan: CFLAGS += -ILeakSanitizer -Wno-gnu-include-next
lsan: LINK_FLAGS += $(LSANLFLAGS)
lsan: fclean $(LSANLIB)
lsan: all
$(LSAN):
	git clone https://github.com/mhahnFr/LeakSanitizer.git $(REDIRECT)
$(LSANLIB): $(LSAN)
	@$(MAKE) -C LeakSanitizer $(REDIRECT)

################################################################################
################################################################################

GREEN			= "\033[32m"
LGREEN			= "\033[92m"
DEFAULT			= "\033[39m"
RED				= "\033[31m"

################################################################################
################################################################################

.PHONY: all clean fclean ffclean re libft readline lsan tester env
