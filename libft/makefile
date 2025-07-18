# 컴파일러 설정
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# 만들 라이브러리 이름
NAME = libft.a

# 모든 .c 파일 리스트
SRCS = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	   ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
	   ft_memmove.c ft_memset.c ft_strdup.c ft_strchr.c ft_strlcat.c \
	   ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
	   ft_tolower.c ft_toupper.c ft_calloc.c ft_substr.c ft_strjoin.c \
	   ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c \
	   ft_striteri.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
# .o 파일 리스트로 바꾸기
OBJS = $(SRCS:.c=.o)

# 기본 타겟: libft.a 만들기
all: $(NAME)

# libft.a 만드는 방법
$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

# .o 파일 만드는 규칙 (필수: -fPIC)
%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

# 중간 파일 삭제
clean:
	rm -f $(OBJS)

# 라이브러리까지 삭제
fclean: clean
	rm -f $(NAME)

# 다시 빌드
re: fclean all

# test 타겟
test: main.c $(NAME)
	$(CC) -o $@ $(CFLAGS) $^ -lbsd
	./$@

# 공유 라이브러리(libft.so) 만들기
so: $(OBJS)
	$(CC) -nostartfiles -fPIC -shared -o libft.so $(OBJS)

# object 파일들 정의 (정확하게 지정된 SRCS 사용)
OBJS = $(SRCS:.c=.o)

