# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/04 23:05:13 by aiblanco          #+#    #+#              #
#    Updated: 2025/11/25 20:27:06 by almorene         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME      := minishell
READLINE_INC := /opt/homebrew/opt/readline/include
READLINE_LIB := /opt/homebrew/opt/readline/lib
CC        := gcc
CFLAGS    := -Wall -Wextra -Werror -Iincludes -Ilibft -I$(READLINE_INC) 

LIBFT_DIR := libft
LIBFT_A   := $(LIBFT_DIR)/libft.a

LIBS      := -L$(READLINE_LIB)  -lreadline

SRC_DIR   := src
OBJ_DIR   := obj

SRC_FILES := main.c main_utils.c dup_env.c line_comander.c\
print_cmds.c print_token.c frees.c free_main_mem.c\
signals.c signals_heredoc.c signals_heredoc2.c \
tokenize.c tokenize2.c manage_tokens.c token_utils.c \
expans_token.c expans_token2.c\
parse_args.c parse_tokens.c parse_tokens2.c parse_new.c \
free_error.c \
expanse_utils1.c expanse_utils2.c \
expanse_utils3.c \
execute.c execute_utils1.c execute_utils2.c execute_utils3.c \
execute_utils4.c execute_utils5.c \
pipex_redir.c pipex_utils1.c pipex_utils2.c pipex_utils3.c \
pipex_utils4.c pipex_utils5.c pipex_utils6.c\
pipex_utils3_2.c \
set_get.c \
tokenize_utils.c tokenize_utils2.c \
malloc_error.c \
built_cd.c built_cd1.c built_cd2.c \
built_echo.c \
built_pwd.c \
parse_token_type.c \
parse_token_type2.c \
built_env.c \
built_export.c built_export_utils.c built_export_utils_2.c \
built_export_utils_3.c \
built_exit.c built_unset.c


SRC       := $(foreach file, $(SRC_FILES), $(shell find $(SRC_DIR) -name $(file)))
OBJ       := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

$(NAME): $(LIBFT_A) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) -lm -o $(NAME) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

bonus:

re: fclean all

all: $(NAME)

.PHONY: all clean fclean re