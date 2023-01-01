NAME	= ft_containers

SRCS_MAP	= tests/test_map.cpp
SRCS_VEC	= tests/test_vector.cpp
SRCS_STACK	= tests/test_stack.cpp
SRCS_MAIN	= main.cpp

SRCS_ALL	= $(SRCS_VEC) $(SRCS_MAP) $(SRCS_STACK)

CC		= c++
FLAGS	= -Wall -Wextra -Werror -std=c++98 -pedantic

all:		${NAME}

${NAME}:
			${CC} ${SRCS_ALL} ${FLAGS} -o ${NAME}

vector:
	${CC} ${SRCS_VEC} ${FLAGS} -o ${NAME}

map:
	${CC} ${SRCS_MAP} ${FLAGS} -o ${NAME}

stack:
	${CC} ${SRCS_STACK} ${FLAGS} -o ${NAME}

main:
	${CC} ${SRCS_MAIN} ${FLAGS} -o ${NAME}

debug: all
			${CC} ${SRCS_ALL} ${FLAGS} -D M_DEBUG=1 -o ${NAME}

debug_vector:
			${CC} ${SRCS_VEC} ${FLAGS} -D M_DEBUG=1 -o ${NAME}

debug_map:
			${CC} ${SRCS_MAP} ${FLAGS} -D M_DEBUG=1 -o ${NAME}

debug_stack:
			${CC} ${SRCS_STACK} ${FLAGS} -D M_DEBUG=1 -o ${NAME}

docker:
	docker run -ti -v $(PWD):/test memory-test:0.1 bash -c "cd /test/; make re && valgrind --leak-check=full ./${NAME} 12"

exe:
	docker run -ti -v $(PWD):/test memory-test:0.1 bash -c "cd /test/; ./${NAME} 12"

leaks:
	make re
	leaks --fullStacks --atExit -- ./${NAME}

fclean:	
			rm -f ${NAME}

re:			fclean all

.PHONY:		re fclean all