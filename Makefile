LIBFTPATH	= ./libft
LIBFT		= $(LIBFTPATH)/libft.a

SRCFILES	= minishell.c \
			  ms_init_list.c \
			  ms_builtins.c \
			  ms_builtins2.c \
			  ms_parser.c \
			  ms_init.c \
			  ms_prompt.c \
			  ms_utils.c \
			  ms_init_data.c \
			  ms_init_patterns.c \
			  ms_parser_patterns.c \
			  ms_translate.c \
			  ms_translate_trim.c \

BONUSFILES	= bonus.c \


CC			= clang
RM			= rm -f
CFLAGS		=
SRCDIR		= src
BONUSDIR	= srcbonus
OBJDIR		= obj
HEADER		= minishell.h
#BONUSHEADER= checker.h
NAME		= minishell
#BONUSNAME	= checker
INCLUDES	= -I./libft -I./
LINKS		= -I$(LIBFTPATH) -L$(LIBFTPATH) -lft -lreadline

SRC			= $(addprefix $(SRCDIR)/, $(SRCFILES))
#BONUSSRC	= $(addprefix $(BONUSDIR)/, $(BONUSFILES))
OBJ			= $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
#BONUSOBJ	= $(BONUSSRC:$(BONUSDIR)/%.c=$(OBJDIR)/%.o)

all:		mkdir $(NAME)

$(NAME):	$(OBJ) $(HEADER)
			make -C $(LIBFTPATH) all
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LINKS)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c $(HEADER)
			$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
			$(RM) $(OBJ)
			rm -rf obj
			make -C $(LIBFTPATH) clean

fclean:		clean
			make -C $(LIBFTPATH) fclean
			$(RM) $(NAME)

mkdir:
			mkdir -p obj

re:			fclean all

run:		mkdir $(OBJ) $(HEADER)
			make -C libft
			$(CC) main.c $(OBJ) -o $(NAME) $(INCLUDES) $(LINKS)
			./$(NAME)

runv:		mkdir $(OBJ) $(HEADER)
			make -C libft
			$(CC) main.c $(OBJ) -o $(NAME) $(INCLUDES) $(LINKS)
			valgrind ./$(NAME)

.PHONY:		all clean fclean re
