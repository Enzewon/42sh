#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skavunen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/14 13:21:34 by skavunen          #+#    #+#              #
#    Updated: 2018/01/11 16:29:53 by skavunen         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = 42sh

N_INC = ft_shell.h

N_SRCS +=	main.c \
		ft_21.c \
		init.c \
		tools.c \
		args.c \
		args_2.c \
		ft_cmd.c \
		find.c \
		redirect.c \
		leaks.c \
		check.c \
		command.c \
		execute.c \
		pipes.c \
		exepipes.c \
		cd.c \
		env.c \
		heredoc.c \
		input_pro.c \
		input_action_keys.c \
		input_ctrl_and_history.c \
		input_ctrl_r.c \
		input_cut_and_words.c \
		input_lr_delete.c \
		input_making_read.c \
		input_quotes.c \
		input_tab.c \
		input_show_tab.c \
		input_termcap.c \
		input_termcap_2.c \
		input_termcap_3.c \
		input_termios.c \
		input_tools.c \
		input_tools_tab.c \
		input_up_down.c  \
		input_up_arrow.c \
		hash.c \
		hash_2.c \
		tools_2.c \
		glob.c	\
		logical.c \
		unsetenv.c \
		glob2.c \
		globtools.c \
		args_3.c \
		heredoc_2.c \
		execute_2.c

CC = gcc
CC_FLAGS = -Wall -Werror -Wextra -g

P_SRCS = ./srcs/
P_OBJ = ./obj/
P_LFT = libft/

I_INC = ./includes
I_LFT = ./libft/includes
I_ADD = -ltermcap
L_LFT = -L./libft/ -lft

NOC=\033[0m
OKC=\033[32;05m
ERC=\033[31m
WAC=\033[33m

SRC = $(addprefix $(P_SRCS),$(N_SRCS))
OBJ = $(addprefix $(P_OBJ),$(OBJ_NAME))
INC = $(addprefix -I,$(I_INC) $(I_LFT))

OBJ_NAME = $(N_SRCS:.c=.o)

all: $(NAME)

project: clean proj

proj: $(OBJ)
	@echo "$(OKC)$(NAME): Compiling objectives $(NAME)$(NOC)"
	@$(CC) $(CC_FLAGS) $(I_ADD) -o $(NAME) $(OBJ) $(INC) $(L_LFT)
	@echo "$(OKC)$(NAME): Compilation success!$(NOC)"

$(NAME): $(OBJ)
	@echo "$(OKC)$(NAME): Compiling libft.a$(NOC)"
	@make -C $(P_LFT)
	@echo "$(OKC)$(NAME): Compiling objectives $(NAME)$(NOC)"
	@$(CC) $(CC_FLAGS) $(I_ADD) -o $(NAME) $(OBJ) $(INC) $(L_LFT)
	@echo "$(OKC)$(NAME): Compilation success!$(NOC)"

$(P_OBJ)%.o: $(P_SRCS)%.c	
	@mkdir -p $(P_OBJ) $(ADD)
	@$(CC) $(CC_FLAGS) -o $@ -c $^ $(INC)

clean:
	@make -C $(P_LFT) clean
	@rm -rf $(P_OBJ)
	@echo "$(WAC)$(NAME): Removing $(NAME) ./obj/$(NOC)"

fclean: clean
	@make -C $(P_LFT) fclean
	@rm -f $(NAME)
	@echo "$(WAC)$(NAME): Removing executable$(NOC)"

re: fclean all
