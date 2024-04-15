
NAME = philo_bonus

SRCS =  ft_atoi.c \
		philo_action_bonus.c \
		forking_bonus.c \
		philo_bonus.c \
		monitor_bonus.c \
		utils_bonus.c


OBJS = ${SRCS:.c=.o}


CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread #-fsanitize=thread
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