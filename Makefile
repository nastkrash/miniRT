NAME	= minirt
FLAGS	= -Wall -Wextra -Werror -Ofast
SRCS	= ft_atof.c init_mlx.c main.c render_frame.c get_next_line.c check_cylinder_intersections.c parse_scene.c vector_math.c calculate_lighting.c check_sphere_intersections.c check_plane_intersections.c vector_math2.c process_line.c parse_ambient.c \
			parse_camera.c parse_light.c parse_sphere.c parse_plane.c parse_cylinder.c parse_utils.c
RM		= rm -rf
LIBFT_A = libft/libft.a
MLX42_A = MLX42/build/libmlx42.a
LIBS = -lglfw -lm -lXext -lX11
CC = cc

OBJDIR	= obj
OBJS	= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

all: $(NAME)

# -IMLX42/include/MLX42 : Tells the compiler where to look for additional header files.
# -LMLX42/build : Tells the linker where to search for library files.
# -lmlx42       : Links with the 'mlx42' library.
# -lXext      : Links with the Xext (extension library for X11) library.
# -lX11       : Links with the X11 library.
# -lm         : Links with the math library.

$(NAME): $(LIBFT_A) $(MLX42_A) $(OBJS)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) -Llibft -lft -LMLX42/build -lmlx42 $(LIBS)
$(LIBFT_A):
	@make bonus -C libft --no-print-directory

$(MLX42_A):
	@cmake -B MLX42/build MLX42
	@cmake --build MLX42/build -j4

$(OBJS): $(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(FLAGS) -Ilibft -IMLX42/include/MLX42 -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@$(RM) $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libft --no-print-directory
#	$(RM) MLX42/build

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=mlx.supp ./$(NAME) scenes/scene1.rt

re: fclean all

.PHONY: clean fclean valgrind re
