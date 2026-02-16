# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saalarco <saalarco@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/16 08:12:02 by saalarco          #+#    #+#              #
#    Updated: 2026/02/16 08:19:54 by saalarco         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# Var

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm
RMFLAGS = -rf
MKDIR = mkdir -p
INCLUDE = -I${INCLUDE_DIR}

# Dir

SRC_DIR = src/
OBJ_DIR = bin/obj/
BIN_DIR = bin/
INCLUDE_DIR = include/

# Data races
LINKER = -lpthread

#Files

FILES = \
main


# Files add

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))

OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

# 1st rule
all: $(NAME)

# Debug rule
debug: CFLAGS += -g3 -O0 -DDEBUG
debug: fclean $(NAME)

# Fsanitize rule
fsanitize: CFLAGS += -fsanitize=address
fsanitize: $(NAME)

# Exec with valgrind
valgrind: valgrind --tool=helgrind ./$(NAME)
valgrind: fclean $(NAME)


# Comp bin
$(NAME): $(OBJ) $(LIBFT_NAME)
	$(MKDIR) $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJ) -o $@

# Comp .O
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(LINKER) $(INCLUDE) -c $< -o $@


# clean OBJ
clean:
	$(RM) $(RMFLAGS) $(OBJ_DIR)
	$(MAKE) clean

# clean binary OBJ
fclean: clean
	$(RM) $(RMFLAGS) $(BIN_DIR) $(NAME)
	$(MAKE) fclean

# Recompilar todo
re: fclean all

.PHONY: all clean fclean re