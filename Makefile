NAME			=	cub3D

CC				=	cc
CFLAGS			=	-Wall -Wextra -g -Ofast -Werror
LINKFLAGS		=
REDIRECT		=	2> /dev/null 1> /dev/null
OS				=	$(shell uname -s)
BREW			=	$(HOME)/.brew

################################################################################
################################################################################

SRC				=	$(addprefix $(SRC_DIR), $(SRC_FILES))
SRC_DIR			=	src/
SRC_FILES		=	main.c utils.c keyboard_input.c doors.c movement.c start_end_screen.c endcondition.c setup.c setup_player.c sound.c

PARSER			=	$(addprefix $(PARSER_DIR), $(PARSER_FILES))
PARSER_DIR		=	src/parser/
PARSER_FILES	=	parser.c validate_args.c validate_map.c parse_options.c check_syntax.c validate_options.c handle_errors.c parser_init.c

HUD				=	$(addprefix $(HUD_DIR), $(HUD_FILES))
HUD_DIR			=	src/hud/
HUD_FILES		=	hud.c minimap.c minimap_fov_border.c minimap_enemies.c

UTILS			=	$(addprefix $(UTILS_DIR), $(UTILS_FILES))
UTILS_DIR		=	src/utils/
UTILS_FILES		=	vector.c utils.c colors.c map.c

MATH			=	$(addprefix $(MATH_DIR), $(MATH_FILES))
MATH_DIR		=	src/math/
MATH_FILES		=	distance.c rotate.c misc.c

WALLS			=	$(addprefix $(WALLS_DIR), $(WALLS_FILES))
WALLS_DIR		=	src/walls/
WALLS_FILES		=	raycasting.c textures.c fog.c

ENEMIES			=	$(addprefix $(ENEMIES_DIR), $(ENEMIES_FILES))
ENEMIES_DIR		=	src/enemies/
ENEMIES_FILES	=	enemies.c enemy_draw.c enemy_movement.c enemy_state.c enemy_utils.c enemy_setup.c enemy_attack.c enemy_load_png.c standard_values.c

WEAPON			=	$(addprefix $(WEAPON_DIR), $(WEAPON_FILES))
WEAPON_DIR		=	src/weapon/
WEAPON_FILES	=	weapon_clear.c weapon_draw.c player_attack.c weapon_utils.c weapon_details.c

FREE			=	$(addprefix $(FREE_DIR), $(FREE_FILES))
FREE_DIR		=	src/free/
FREE_FILES		=	free_utils.c free_utils2.c free_enemy_textures.c

HDR				=	$(addprefix $(HDR_DIR), $(HDR_FILES))
HDR_DIR			=	include/
HDR_FILES		=	cub3D.h design.h
HDR_INCLUDE		=	-I $(HDR_DIR)

ALL_SRC			=	$(SRC) $(PARSER) $(UTILS) $(MATH) $(WALLS) $(HUD) $(ENEMIES) $(WEAPON) $(FREE)

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

################################################################################
################################################################################

test: $(ALL_OBJ_DIR) $(ALL_OBJ)
	@ar -rcs libcub3dtest.a $(ALL_OBJ) lib/libft/obj/*.o
	@cd tests && $(MAKE) run

testclean:
	rm libcub3dtest.a
	rm tests/*.out

$(ALL_OBJ_DIR):
	@mkdir -p $(ALL_OBJ_DIR)

norm:
	@norminette $(ALL_SRC) $(HDR) | grep -v "Missing or invalid 42 header"

r: all
	./$(NAME) maps/enemy.cub

################################################################################
################################################################################

#help:
#	@make check_brew

#check_brew:
#ifeq ($(shell which brew ),$(BREW)/bin/brew)
#	@echo "brew is installed"
#	@make check_glfw
#else
#	@echo "no brew found in standard path."
#	@echo "use make brew to install"
#endif

#check_glfw:
#ifeq ($(shell brew list | grep glfw), glfw)
#	@echo "glfw is installed"
#	@make check_cmake
#else
#	@echo "no glfw found"
#	@echo "use make glfw to install"
#endif

#check_cmake:
#ifeq ($(shell which cmake), $(BREW)/bin/cmake)
#	@echo "cmake is installed in the default directory"
#else
#	@echo "no cmake found in the default directory"
#	@echo "use make cmake to install"
#endif

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

MLX				=	$(MLX_DIR)/build/$(MLX_LIB)
MLX_LIB			=	libmlx42.a
MLX_DIR			=	lib/MLX42
MLX_INCLUDE		=	-I ./$(MLX_DIR)/include/MLX42

ifeq ($(OS), Darwin)
	GLFW			=	-lglfw -L"$(BREW)/opt/glfw/lib/"
endif
ifeq ($(OS), Linux)
	GLFW			=	-ldl -lglfw -pthread -lm
endif

mlx: $(MLX)

$(MLX):
	@git submodule init $(MLX_DIR) $(REDIRECT)
	@git submodule update $(MLX_DIR) $(REDIRECT)
	@cd $(MLX_DIR) && cmake -B build $(REDIRECT)
	@cd $(MLX_DIR)/build && make $(REDIRECT)
	@echo $(GREEN)"created $(MLX_LIB)"$(DEFAULT)

################################################################################
################################################################################

LIBFT			=	$(LIBFT_DIR)$(LIBFT_LIB)
LIBFT_LIB		=	libft.a
LIBFT_DIR		=	lib/libft/
LIBFT_INCLUDE	=	-I ./$(LIBFT_DIR)

libft: $(LIBFT)

$(LIBFT):
	@git submodule init $(LIBFT_DIR) $(REDIRECT)
	@git submodule update $(LIBFT_DIR) $(REDIRECT)
	@make -C lib/libft

################################################################################
################################################################################

LSAN			=	lib/LeakSanitizer
LSANLIB			=	$(LSAN)/liblsan.a

ifeq ($(OS),Linux)
	LSANLFLAGS := -rdynamic -Llib/LeakSanitizer -llsan -ldl -lstdc++
endif
ifeq ($(OS),Darwin)
	LSANLFLAGS := -Llib/LeakSanitizer -llsan -lc++
endif

lsan: CFLAGS += -I $(LSAN) -Wno-gnu-include-next
lsan: LINK_FLAGS += $(LSANLFLAGS)
lsan: fclean $(LSANLIB)
lsan: all

$(LSAN):
	@git submodule init $(LSAN) $(REDIRECT)
	@git submodule update $(LSAN) $(REDIRECT)

$(LSANLIB): $(LSAN)
	@$(MAKE) -C $(LSAN) $(REDIRECT)
	@echo $(GREEN)"created liblsan.a"$(DEFAULT)


################################################################################
################################################################################

GREEN			= "\033[32m"
LGREEN			= "\033[92m"
DEFAULT			= "\033[39m"
RED				= "\033[31m"

################################################################################
################################################################################

.PHONY: all clean fclean ffclean re libft readline lsan tester env
