# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmesa-or <fmesa-or@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/11 15:59:19 by fmesa-or          #+#    #+#              #
#    Updated: 2024/09/23 18:48:11 by fmesa-or         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Name
NAME		:= philo

#Compile
CC			:= cc

#Flags
CFLAGS		:= -Wextra -Werror -Wall -g -pthread 
#-fsanitize=address

#Clean
CLEAN		:= rm -Rf

#Sources
SRCS_DIR	:= src
#SRCS		:= src/ src/ src/ src/
SRCS		:= $(shell find $(SRCS_DIR) -iname "*.c")

#Objects
OBJS_DIR	:= obj
OBJS		:= $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

#Headers
HEADERS		:= -I ./include

#Colors
COLOR_INFO = \033[1;36m
COLOR_SUCCESS = \033[1;32m
COLOR_RESET = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
		@$(CC) $(OBJS) $(HEADERS) -o $(NAME)

bonus:$(LIBFT) $(OBJS_B)
		@$(CC) $(OBJS_B) $(HEADERS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
		@mkdir -p $(OBJS_DIR)
		@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS) && printf "$(COLOR_INFO)Compiling: $(notdir $<)$(COLOR_RESET)\t\t"
		@sleep 0.25
		@printf "✅\n"

clean:
		@printf "$(COLOR_INFO)Cleaning as fast as I can$(COLOR_RESET)\t"
		@$(CLEAN) $(OBJS_DIR)
		@sleep 0.25
		@printf "✅\n"

fclean: clean
		@printf "$(COLOR_INFO)Deleting $(NAME)$(COLOR_RESET)\t\t\t"
		@$(CLEAN) $(NAME)
		@sleep 0.25
		@printf "✅\n"

re: fclean clean all

.PHONY: all, clean, fclean, re
