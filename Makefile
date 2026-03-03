# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saalarco <saalarco@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/16 08:12:02 by saalarco          #+#    #+#              #
#    Updated: 2026/03/03 18:03:29 by saalarco         ###   ########.fr        #
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

# Linker flags
LDFLAGS = -lpthread

#Files

FILES = \
main \
philo_utils \
alloc_utils \
mutex_utils \
args_utils \
init_philos \
create_threads_and_join \
time_utils \
routine \
routine_monitor \
do_sleep \
state_messages


# Files add

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))

OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

# 1st rule
all: $(NAME)

# Debug rule
debug: CFLAGS += -g3 -O0 -DDEBUG
debug: re

# Fsanitize rule (thread sanitizer, more useful for philosophers)
fsanitize: CFLAGS += -fsanitize=thread -g3 -O0
fsanitize: LDFLAGS += -fsanitize=thread
fsanitize: re

# Fsanitize address rule
fsanitize-addr: CFLAGS += -fsanitize=address -g3 -O0
fsanitize-addr: LDFLAGS += -fsanitize=address
fsanitize-addr: re


# Comp bin
$(NAME): $(OBJ) $(LIBFT_NAME)
	$(MKDIR) $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@

# Comp .O
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@


# clean OBJ
clean:
	$(RM) $(RMFLAGS) $(OBJ_DIR)

# clean binary OBJ
fclean: clean
	$(RM) $(RMFLAGS) $(BIN_DIR) $(NAME)

# Recompilar todo
re: fclean all

.PHONY: all clean fclean re