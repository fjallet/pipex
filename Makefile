NAME = pipex

NAME_BONUS = bonus

HEADERS = pipex.h

SRCS = pipex.c pipex_str.c pipex_parsing.c ft_split.c pipex_free.c pipex_exe.c gnl.c gnl_utils.c

BONUS_SRCS = pipex_bonus.c pipex_str.c pipex_parsing.c ft_split.c pipex_free.c pipex_exe.c gnl.c \
		gnl_utils.c

OBJETS = ${SRCS:%.c=./.build/%.o}

OBJS_BONUS = ${BONUS_SRCS:%.c=./.build/%.o}

FT_PRINTF = cd ft_printf && make re

CC = gcc

FLAGS = -Wall -Werror -Wextra

./.build/%.o : %.c
	${CC} -I. -o $@ -c $? ${FLAGS}

all: 
	mkdir -p .build
	make ${NAME}

b: 
	mkdir -p .build
	make ${NAME_BONUS}

${NAME}	 : ${OBJETS} ${HEADERS}
		${FT_PRINTF}
		${CC} -o ${NAME} ${OBJETS} ft_printf/libftprintf.a

${NAME_BONUS} : ${OBJS_BONUS} ${HEADERS}
		${FT_PRINTF}
		@${CC} -o ${NAME} ${OBJS_BONUS} ft_printf/libftprintf.a


clean :
	rm -rf .build

fclean : clean
	cd ft_printf && make fclean
	rm -rf ${NAME}

re :  fclean all

PHONY = all clean fclean re
