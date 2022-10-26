# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/08 10:12:01 by dlerma-c          #+#    #+#              #
#    Updated: 2022/03/21 13:23:04 by dlerma-c         ###   ########.fr        #
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
SRCS_DRAW_PATH = draw

SRCS_PARSE =	check_map.c \
				utils.c \
				init.c \
				save.c
SRCS_DRAW = 
SRCS = main.c
SRCS_NAME = $(addprefix $(SRCS_PARSE_PATH)/, $(SRCS_PARSE)) \
			$(addprefix $(SRCS_DRAW_PATH)/, $(SRCS_DRAW)) \
			$(SRCS)
OBJS_NAME_PATH = $(SRCS_PARSE_PATH) $(SRCS_DRAW_PATH)
OBJS_PATH = $(addprefix $(OBJ_PATH)/, $(OBJS_NAME_PATH))
OBJS_NAME = $(SRCS_NAME:%.c=%.o)
OBJS = $(addprefix $(OBJ_PATH)/, $(OBJS_NAME))

#··············································································#
#                                    FLAGS                                     #
#··············································································#

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3
#include <xx.h> // path of .h
CFLAGS += -I $(INC_PATH) -I $(LBFT_PATH)

#··············································································#
#                                    RULES                                     #
#··············································································#

.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LBFT_PATH)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS) $(LDLIBS)

debug: CFLAGS += -fsanitize=address -g3
debug: $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

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