NAME = pipex

HEADERS = pipex.h

SRCS = pipex.c pipex_str.c pipex_parsing.c ft_split.c pipex_free.c pipex_exe.c

OBJETS = ${SRCS:%.c=./.build/%.o}

FT_PRINTF = cd ft_printf && make re

CC = gcc

FLAGS = -Wall -Werror -Wextra

./.build/%.o : %.c
	${CC} -I. -o $@ -c $? ${FLAGS}

all: 
	mkdir -p .build
	make ${NAME}

${NAME}	 : ${OBJETS} ${HEADERS}
		${FT_PRINTF}
		${CC} -o ${NAME} ${OBJETS} ft_printf/libftprintf.a

clean :
	rm -rf .build

fclean : clean
	cd ft_printf && make fclean
	rm -rf ${NAME}

re :  fclean all

PHONY = all clean fclean re
