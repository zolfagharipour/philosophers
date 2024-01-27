
NAME = philo

SRCS =  $(wildcard *.c)

BONUS = 

OBJS = ${SRCS:.c=.o}
BONUS_OBJS = ${BONUS:.c=.o}


CC = cc
CFLAGS = -g
RM	=	rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} $^

bonus: ${BONUS_OBJS}
	${CC} ${CFLAGS} -o ${NAME} $^

clean: 
	${RM} ${OBJS} ${BONUS_OBJS}


fclean: clean
	${RM} ${NAME} ${CHECK}

re: fclean all

.PHONY: all bonus clean fclean re