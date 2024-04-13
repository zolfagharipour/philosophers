
NAME = philo

SRCS =  ft_atoi.c \
		philo_action.c \
		philo.c \
		supervisor.c \
		threading.c \
		utils.c


OBJS = ${SRCS:.c=.o}


CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread #-fsanitize=thread
RM	=	rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} $^

clean: 
	${RM} ${OBJS} ${BONUS_OBJS}


fclean: clean
	${RM} ${NAME} ${CHECK}

re: fclean all

.PHONY: all bonus clean fclean re