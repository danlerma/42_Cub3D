# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/08 10:12:01 by dlerma-c          #+#    #+#              #
#    Updated: 2023/04/10 11:51:32 by pdel-pin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#··············································································#
#                                   NAMES                                      #
#··············································································#

NAME = cub3D

#··············································································#
#                                    PATH                                      #
#··············································································#

OBJ_PATH = obj
SRC_PATH = src
INC_PATH = inc
LBFT_PATH = lbft
MLX_PATH = mlx

#··············································································#
#                                    LIBS                                      #
#··············································································#

# flags librerias
# ruta .a
LDFLAGS = -L $(LBFT_PATH)
# nombre lib
LDLIBS = -lft

#··············································································#
#                                    SRCS                                      #
#··············································································#

SRCS_PARSE_PATH = parse
SRCS_PARSE =	check_map.c \
				check_file.c \
				check_img.c \
				to_hex.c \
				to_int.c \
				utils.c \
				init.c \
				save.c

SRCS_GAME_PATH = game
SRCS_GAME = game.c \
			init_game.c \
			tdmap.c \
			draw.c \
			sprites_draw.c \
			hooks.c \
			utils.c \

SRCS = main.c
SRCS_NAME = $(addprefix $(SRCS_PARSE_PATH)/, $(SRCS_PARSE)) \
			$(addprefix $(SRCS_GAME_PATH)/, $(SRCS_GAME)) \
			$(SRCS)

OBJS_NAME_PATH = $(SRCS_PARSE_PATH) $(SRCS_GAME_PATH)
OBJS_PATH = $(addprefix $(OBJ_PATH)/, $(OBJS_NAME_PATH))
OBJS_NAME = $(SRCS_NAME:%.c=%.o)
OBJS = $(addprefix $(OBJ_PATH)/, $(OBJS_NAME))

#··············································································#
#                                    FLAGS                                     #
#··············································································#

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3
#include <xx.h> // path of .h
INC = -I $(INC_PATH) -I $(LBFT_PATH)

#··············································································#
#                                     MLX                                      #
#··············································································#

ifeq ($(shell uname -s), Darwin)
	LDFLAGS += -L $(MLX_PATH)/mlx_mac
	LDLIBS += -lmlx
	INC += -I $(MLX_PATH)/mlx_mac
# CFLAGS += -framework OpenGL -framework AppKitk
endif

#··············································································#
#                                    RULES                                     #
#··············································································#

.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LBFT_PATH)
	make -C $(MLX_PATH)/mlx_mac
	$(CC) $^ -o $@ $(CFLAGS) $(INC) $(LDFLAGS) $(LDLIBS) -framework OpenGL -framework AppKit

debug: CFLAGS += -fsanitize=address -g3
debug: $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJS): | $(OBJ_PATH) $(OBJS_PATH)

$(OBJ_PATH): 
	mkdir -p $(OBJ_PATH) 2> /dev/null

$(OBJS_PATH): 
	mkdir -p $(OBJS_PATH)

clean:
	make fclean -C $(LBFT_PATH)
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all