# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ikole    <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/12/03 09:14:14 by ikole          #+#    #+#                 #
#    Updated: 2020/03/07 14:29:48 by ikole         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC_ = windowmaker.c get_next_line.c parser.c \
		map_validator.c create_bmp.c helpers.c calc_texture.c \
		floor_ceiling.c sprite_helpers.c extra.c movement.c \
		rotate.c events.c init.c bmp_helpers.c parser_helpers.c \
		parse_img.c set_spawn.c parse_map.c res_color.c add_shadow.c ft_itoa.c \
		draw_hud.c

SRC = $(addprefix srcs/, $(SRC_))

OBJ = $(SRC:.c=.o)

BONUS_SRC_ = windowmaker.c get_next_line.c parser_bonus.c \
		map_validator_bonus.c create_bmp.c helpers.c calc_texture.c \
		floor_ceiling.c sprite_helpers.c extra.c movement.c \
		rotate.c events.c init.c bmp_helpers.c parser_helpers.c \
		parse_img.c set_spawn.c parse_map_bonus.c res_color.c add_shadow.c \
		ft_itoa.c parse_animation_bonus.c draw_hud.c

BONUS_SRC = $(addprefix srcs/, $(BONUS_SRC_))

ifdef WITH_BONUS
	OBJ_FILES = $(BONUS_OBJ)
else
	OBJ_FILES = $(OBJ)
endif

BONUS_OBJ = $(BONUS_SRC:.c=.o)

MLX = mlx

FLAGS = -Wall -Wextra -Werror -Ofast

BMP = A_REALLY_FLUFFY_BMP_IMAGE_OF_MY_CUB3D_WHICH_IS_ALSO_FLUFFY.bmp

.PHONY: clean fclean

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@make -C $(MLX)
	@mv mlx/libmlx.dylib .
	@$(CC) -L. -lmlx -framework OpenGL -framework AppKit $(OBJ_FILES) -o $(NAME)

bonus: $(OBJ_FILES)
	@make WITH_BONUS=1 all

%.o: %.c
	@printf "\e[0;34mCompiling $<\n\e[0;35m"
	@gcc $(FLAGS) -Imlx -Iinc -c $< -o $@

re: fclean all

clean:
	@rm -f $(OBJ) $(BONUS_OBJ) $(BMP)
	@cd mlx && make clean

fclean: clean
	@rm -f libmlx.dylib
	@rm -f $(NAME)
