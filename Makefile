LIBFT_PATH		=	libft
LIBFT			=	$(LIBFT_PATH)/libft.a

SOURCES			=	minishell.c \
					main.c \
					ms_builtin_echo.c \
					ms_builtin_pwd.c \
					ms_builtin_export.c \
					ms_builtin_unset.c \
					ms_builtin_env.c \
					ms_builtin_cd.c \
					ms_builtin_exit.c \
					ms_execute.c \
					ms_execute_system.c \
					ms_execute_builtin.c \
					ms_execute_dup_utils.c \
					ms_execute_dup.c \
					ms_init_list.c \
					ms_init_data.c \
					ms_init_patterns.c \
					ms_init_flags.c \
					ms_reinit.c \
					ms_parse.c \
					ms_parse_patterns.c \
					ms_parse_presplit.c \
					ms_parse_flags.c \
					ms_prompt.c \
					ms_prompt_validate.c \
					ms_prompt_validate_files.c \
					ms_prompt_buf.c \
					ms_prompt_colors.c \
					ms_prompt_utils.c \
					ms_prompt_token.c \
					ms_signals.c \
					ms_translate.c \
					ms_translate_trim.c \
					ms_translate_star.c \
					ms_translate_home.c \
					ms_utils.c \
					ms_utils_env.c \
					ms_utils_print.c \
					ms_error.c \

SOURCES_DIR		=	src
OBJ_DIR			=	obj
HEADER			=	minishell.h
OBJECTS			=	$(SOURCES:%.c=$(OBJ_DIR)/%.o)
NAME			=	minishell
CC				=	gcc
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror -g3

INCLUDES		=	-I./libft -I./
LDFLAGS			=	-lreadline

VPATH			=	src src/builtins src/execute src/init src/parse \
					src/prompt src/signals src/translate src/utils \

$(OBJ_DIR)/%.o:		%.c $(HEADER)
					$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

all:				$(NAME)

$(NAME):			$(LIBFT) $(OBJ_DIR) $(OBJECTS) $(HEADER)
					$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
					$(MAKE) -C $(LIBFT_PATH)

$(OBJ_DIR):
					mkdir -p obj

test:
					echo $(VPATH)

run:				all
					./$(NAME)

runv:				all
					valgrind --leak-check=full -s --trace-children=yes --error-exitcode=1 --track-origins=yes ./$(NAME)

clean:
					$(MAKE) -C $(LIBFT_PATH) clean
					$(RM) $(OBJ_DIR)

fclean:				clean
					$(MAKE) -C $(LIBFT_PATH) fclean
					$(RM) $(NAME) $(NAME_BONUS)

re:					fclean all

.PHONY:				all clean fclean re libft bonus
