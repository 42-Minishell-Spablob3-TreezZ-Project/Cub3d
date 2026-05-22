GREEN  = $(shell printf '\033[0;32m')
YELLOW = $(shell printf '\033[0;33m')
BLUE   = $(shell printf '\033[0;34m')
RED    = $(shell printf '\033[0;31m')
RESET  = $(shell printf '\033[0m')

NAME = cub3D

SRC = $(shell find src -name "*.c")
OBJS := $(SRC:%.c=%.o)

CC = cc
RM = rm -f

MLX_LIB = minilibx-linux/libmlx_Linux.a
LIBFT = libft/libft.a

CFLAGS = -Wall -Wextra -Werror -Iincludes -Iminilibx-linux -g

MLX_FLAGS = -Lminilibx-linux -lmlx_Linux -L/usr/lib/X11 -lXext -lX11 -lm

all: $(MLX_LIB) $(LIBFT) $(NAME)

$(LIBFT):
	@echo "$(YELLOW)[LIBFT] Compiling...$(RESET)"
	@git submodule update --init --recursive
	@make -C libft --silent

$(MLX_LIB):
	@echo "$(YELLOW)[MINILIBX] Compiling...$(RESET)"
	@git submodule update --init --recursive
	@make -C minilibx-linux --silent

$(NAME): $(OBJS)
	@echo "$(BLUE)[LINKING]$(RESET) cub3D..."
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	@echo "$(YELLOW)[COMPILING]$(RESET) $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)[CLEAN] objects...$(RESET)"
	@make -C minilibx-linux/ clean --silent
	@make -C libft/ clean --silent
	@$(RM) $(OBJS)

fclean: clean

	@echo "$(RED)[FCLEAN] executable...$(RESET)"
	@$(RM) $(NAME)
	@make -C libft/ fclean --silent

re: fclean all

.PHONY: all clean fclean re