SRC			= ft_memset ft_striteri ft_strmapi ft_putendl_fd ft_putnbr_fd ft_putstr_fd ft_itoa ft_putchar_fd ft_split ft_strtrim ft_strcat ft_strjoin ft_strcpy ft_substr ft_strdup ft_strnstr ft_calloc ft_strlcpy ft_strlcat ft_bzero ft_memchr ft_strchr ft_memcmp ft_memcpy ft_memmove ft_strlen ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint ft_toupper ft_tolower ft_strrchr ft_strncmp ft_atoi 

BSRC		= ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back ft_lstdelone ft_lstclear ft_lstiter ft_lstmap

SRCS		= $(addsuffix .c, ${SRC})

BSRCS		= $(addsuffix .c, ${BSRC})

OBJS		= ${SRCS:.c=.o}

BOBJS		= ${BSRCS:.c=.o}

NAME		= libft.a

CC			= cc
RM			= rm -f
AR			= ar rc
RN			= ranlib

CFLAGS		= -Wall -Wextra -Werror

all:		$(NAME)

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			${AR} ${NAME} ${OBJS}
			${RN} ${NAME}
			

clean:
			${RM} ${OBJS} ${BOBJS}

fclean:		clean
			${RM} $(NAME)

re:			fclean all

bonus:		${BOBJS}
			${AR} ${NAME} ${BOBJS}
			${RN} ${NAME}

.PHONY:		all bonus clean fclean re
