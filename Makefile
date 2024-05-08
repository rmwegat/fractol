NAME = fractol

CC = cc

CFLAGS = -Wall -Wextra -Werror -Ofast -o3

SRCS = src/main.c src/calculations.c src/utils.c src/fractals.c src/inits.c

OBJS = $(SRCS:.c=.o)

MLXFLAGS = -framework Cocoa -framework OpenGL -framework IOKit -lglfw
MLXINCLUDE = include/MLX42/build/libmlx42.a -Iinclude -lglfw
MLX_REPO_URL = https://github.com/codam-coding-college/MLX42.git


all: MLX42 $(NAME)
$(NAME): $(OBJS) MLX42
	@$(CC) $(OBJS) $(MLXFLAGS) $(CFLAGS) $(MLXINCLUDE) -o $(NAME)
MLX42:
	@if [ ! -d "MLX42" ]; then \
		cd include && git clone $(MLX_REPO_URL) MLX42; \
		cd MLX42 && cmake -B build && cd build && make && cd ../..; \
	else \
		echo "MLX already installed"; \
	fi
MLXR:
	rm -rf include/MLX42
clean:
	rm -f $(OBJS)
fclean: clean
	rm -rf include/MLX42
	rm -f $(NAME)
re: fclean all
.PHONY: MLX42


#cc include/MLX42/build/libmlx42.a src/fractol.c src/calculations.c src/utils.c -Iinclude -lglfw