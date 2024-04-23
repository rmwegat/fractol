
NAME	:= fractol
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	:= ./include/MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include

LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCS	:=	./src/fractol.c \
			./src/calculations.c \
			./src/getandset.c

OBJS	:= ${SRCS:.c=.o}

#all: libmlx $(NAME)
all: 
	cc include/MLX42/build/libmlx42.a src/fractol.c src/calculations.c -Iinclude -lglfw
	
libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx


#cc include/MLX42/build/libmlx42.a src/fractol.c src/calculations.c -Iinclude -lglfw