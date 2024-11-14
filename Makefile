NAME = cub3D

LIBFT = ./includes/libft
LFLAGS = -L $(LIBFT) -lft -lm

MLX = ./includes/MLX42
MFLAGS = $(MLX)/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm

SRC = src/main.c src/init.c src/draw/text.c src/draw/draw_shapes.c src/draw/color.c src/draw/draw_raycast.c src/hooks.c src/map.c src/utils.c src/move.c src/struct_utils.c src/draw/texture.c src/dda.c src/dda_floor.c src/move_more.c src/parsing/ft_parsing.c src/parsing/ft_parsing_color.c src/parsing/ft_parsing_color_error.c src/parsing/ft_parsing_texture.c src/parsing/ft_parsing_texture_error.c src/parsing/ft_init_struct.c src/parsing/ft_parsing_map.c src/parsing/ft_parsing_map_utils.c src/parsing/ft_parsing_map_error.c src/parsing/ft_parse_line_break.c
SRC_DIR = ./src/

INC_DIR = ./includes/

OBJ	= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJ_DIR = obj

FLAGS =  -Wall -Werror -Wextra -g -Ofast

CC = clang
all : $(NAME)

$(NAME) : $(OBJ_DIR) $(OBJ)
	@echo "Building MLX..."
	@cmake $(MLX) -B $(MLX)/build && make -C $(MLX)/build -j4
	@echo "MLX built."
	@echo "Building Libft..."
	@make -C $(LIBFT)
	@echo "Libft built."
	@echo "Building Cub3D..."
	@$(CC) $(FLAGS) -I $(INC_DIR) $(OBJ) $(MFLAGS) $(LFLAGS) -o $(NAME)
	@echo "Done."

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) -o $@ -c $< $(FLAGS) -I $(INC_DIR)

%.o : %.c
	$(CC) $(FLAGS) -I/src/ -c $< -o $@

clean :
	rm -rf ./$(MLX)/build
	make -C $(LIBFT) clean
	rm -rf $(OBJ_DIR)

fclean : clean
	make -C $(LIBFT) fclean
	rm -rf $(NAME) cub3D_bonus

re : fclean all