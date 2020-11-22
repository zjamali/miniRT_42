NAME  = miniRT

SRC_PATH= src
SRC_NAME=	main.c		vector.c	pixel_color.c	intersection.c \
		camera.c 	light.c		get_next_line.c get_next_line_utils.c \
		parsing.c	ft_split.c	ft_atoi.c	ft_atod.c \
		ft_strncmp.c	minirt.c	bmp.c	hooks.c \
		vector2.c	light2.c	check.c		transformation.c \
		transformation2.c	check2.c	list.c	list2.c		parsing2.c \
		parse_scene.c	parsing_objects.c	parsing_objects2.c \
		transformation3.c	intersection2.c	free.c	ft_memset.c	dark.c \

HDR_PATH= headers
HDR_NAME= get_next_line.h	minirt.h

OBJ_PATH= objs
OBJ_NAME= $(SRC_NAME:.c=.o)

OBJ= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
SRC= $(addprefix $(SRC_PATH)/,$(SRC_NAME))
HDR= $(addprefix $(HDR_PATH)/,$(HDR_NAME))


# *****     flags     ***** #

COM= gcc
CFLAGE= -Wall -Wextra -Werror
HDR_INC= -I ./headers/

MLX= -lmlx -framework OpenGL -framework AppKit #-lX11
## MLX_INC= /usr/local/include
MLX_LIB1= /usr/local/lib
MLX_LIB2= /usr/X11/lib


# *****     rules     ***** #

all: $(NAME)

$(NAME): $(OBJ)
		@$(COM) $(CFLAGE) -L$(MLX_LIB1) -L$(MLX_LIB2) $(OBJ) $(MLX) -o $@
		@echo "         Made by : \033[1;91mzjamali\033[m"
		@echo "          _       _______ _____    "
		@echo "         (_)     (_) ___ \_   _|   "
		@echo "  _ __ ___  _ _ __  _| |_/ / | |   "
		@echo " | '_ ' _ \| | '_ \| |    /  | |   "
		@echo " | | | | | | | | | | | |\ \  | |   "
		@echo " |_| |_| |_|_|_| |_|_\_| \_| \_/   "
		@echo "Compilation of miniRT:  \033[1;32mOK\033[m"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HDR)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(COM) $(CFLAGE) $(HDR_INC) -o $@ -c $<

clean:
	@rm -rf $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "miniRT : Removing Objs"
		
fclean: clean
	@rm -rf $(NAME)
	@echo "miniRT : Removing miniRT"
		
re: fclean all
