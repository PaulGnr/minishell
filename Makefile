CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -g

RM			= rm -rf

#------------------------------COLOR------------------------------

nc=\033[0m# Text Reset

# Regular Colors
Green=\033[0;32m# Green

# Bold
BRed=\033[1;31m# Red
BYellow=\033[1;33m# Yellow

# Underline
UGreen=\033[4;32m# Green

# Background
On_Green=\033[42m# Green

NAME		= minishell

SRC_DIR		= src

SRCS		= $(patsubst %, $(SRC_DIR)/%, main.c exec_cmd.c fonction.c \
				error.c select_fd.c pipe_and_fd.c checker.c parser.c \
				parser_utils.c split_chevron.c split_quote.c strjoin.c \
			   	manage_env.c ft_export.c expansion.c expansion_utils.c \
				expansion_var.c expansion_split.c expansion_split_utils.c \
				expansion_remove.c expansion_heredoc.c heredoc_utils.c \
				exec_builtin.c expansion_heredoc_utils.c expansion_redir.c \
				ft_cd.c ft_cd_utils.c ft_cd_path.c ft_cd_pwd.c ft_echo.c \
				ft_pwd.c ft_exit.c ft_unset.c ft_export_without_arg.c utils.c \
				signal.c ft_env.c find_cmd.c heredoc.c)

OBJ_DIR		= obj

OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

INC			= inc

LIB			= $(SRC_DIR)/libft/libft.a -lreadline

DEF			= -D $(uname)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
			@mkdir -p $(OBJ_DIR)
			@$(CC) $(CFLAGS) -I $(INC) -c $< -o $@
			@printf "$(On_Green) $(nc)"

$(NAME):	$(OBJS) $(INC)/minishell.h
			@make -C $(SRC_DIR)/libft
			@$(CC) $(CFLAGS) $(OBJS) -I $(INC) $(DEF) -L $(LIB) -o $@
			@echo "\n$(Green)*** $(UGreen)Successfully compiling $(NAME)$(Green) ***$(nc)"

all:		$(NAME)

clean:
			@make clean -C $(SRC_DIR)/libft
			@$(RM) $(OBJ_DIR)
			@echo "$(BRed)/!\\ $(BYellow)Remove $(NAME) obj$(BRed) /!\\ $(nc)"

fclean:		clean
			@make fclean -C $(SRC_DIR)/libft
			@$(RM) $(NAME)
			@echo "$(BRed)/!\\ $(BYellow)Remove $(NAME)$(BRed) /!\\ $(nc)"

re:			fclean all

.PHONY:		all clean fclean re bonus clean_bonus fclean_bonus re_bonus
