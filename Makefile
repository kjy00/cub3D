NAME = cub3D
BONUS = cub3D_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
MLXFLAG = -L./libs/mlx -lmlx -framework OpenGL -framework AppKit

AR = ar rcs
RM = rm -rf

MLX_DIR = ./libs/mlx
MLXLIB = $(MLX_DIR)/libmlx.a

LIBFT_DIR = ./libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = main.c init.c free.c operate.c draw.c draw_util.c raycasting.c\
		parse.c parse_cub.c parse_map.c parse_color.c parse_utils.c
SRCS := $(addprefix srcs/, $(SRCS))

SRCS_BONUS = main_bonus.c init_bonus.c free_bonus.c operate_bonus.c\
			draw_bonus.c draw_minimap_bonus.c draw_util_bonus.c raycasting_bonus.c\
			parse_bonus.c parse_cub_bonus.c parse_map_bonus.c\
			parse_color_bonus.c parse_utils_bonus.c
SRCS_BONUS := $(addprefix bonus/, $(SRCS_BONUS))

GNL_SRCS	= gnl/get_next_line.c gnl/get_next_line_utils.c

OBJS = $(SRCS:.c=.o) $(GNL_SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o) $(GNL_SRCS:.c=.o)

all : $(NAME)

bonus : $(BONUS)

$(NAME) : $(OBJS)
	@make -C $(MLX_DIR)
	@make -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) -I ./ $(OBJS) $(LIBFT) $(MLXFLAG) -o $@
	@echo "☺️  make cub3d"

$(BONUS) : $(OBJS_BONUS)
	@make -C $(MLX_DIR)
	@make -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) -I ./ $(OBJS_BONUS) $(LIBFT) $(MLXFLAG) -o $@
	@echo "☺️  make cub3d"

clean :
	@make -C $(MLX_DIR) clean
	@make -C $(LIBFT_DIR) clean
	@$(RM) $(OBJS) $(OBJS_BONUS)
	@echo "🧹 clean~~"

fclean : clean
	@make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME) $(BONUS)
	@echo "🔥 fclean~~~"

re : 
	@make fclean
	@make all

.PHONY : all clean fclean re
