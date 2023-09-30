NAME = cub3D
BONUS_NAME = cub3D_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP
CFLAGS += $(INCFLAGS)


INCDIR	=	./includes ./libft
INC	=	$(addprefix -I,$(INCDIR)) 

B_INCDIR	=	./includes_bonus ./libft
B_INC	=	$(addprefix -I,$(B_INCDIR))

SRCSDIR = ./srcs
SRCS	=	$(SRCSDIR)/game/game.c \
			$(SRCSDIR)/main.c \
			$(SRCSDIR)/map/check_map.c \
			$(SRCSDIR)/map/flood_fill.c \
			$(SRCSDIR)/map/free_2d.c \
			$(SRCSDIR)/map/map.c \
			$(SRCSDIR)/map/read_file.c \
			$(SRCSDIR)/player/field_of_view.c \
			$(SRCSDIR)/player/player.c \
			$(SRCSDIR)/player/player_utils.c \
			$(SRCSDIR)/utils/my_mlx_pixel_put.c \
			$(SRCSDIR)/utils/trigonometric_function.c \
			$(SRCSDIR)/utils/vector_utils.c \
			$(SRCSDIR)/window/color.c \
			$(SRCSDIR)/window/draw_window.c \
			$(SRCSDIR)/window/texture.c

BONUSDIR = ./bonus
BONUS	=	$(BONUSDIR)/game/event_bonus.c \
			$(BONUSDIR)/game/game_bonus.c \
			$(BONUSDIR)/main_bonus.c \
			$(BONUSDIR)/map/check_map_bonus.c \
			$(BONUSDIR)/map/flood_fill_bonus.c \
			$(BONUSDIR)/map/free_2d.c \
			$(BONUSDIR)/map/map_bonus.c \
			$(BONUSDIR)/map/read_file_bonus.c \
			$(BONUSDIR)/player/field_of_view_bonus.c \
			$(BONUSDIR)/player/player_bonus.c \
			$(BONUSDIR)/player/player_utils_bonus.c \
			$(BONUSDIR)/utils/my_mlx_pixel_put_bonus.c \
			$(BONUSDIR)/utils/trigonometric_function_bonus.c \
			$(BONUSDIR)/utils/vector_utils_bonus.c \
			$(BONUSDIR)/window/color_bonus.c \
			$(BONUSDIR)/window/draw_window_bonus.c \
			$(BONUSDIR)/window/texture_bonus.c

OBJSDIR = ./objs
OBJS	=	$(patsubst $(SRCSDIR)/%.c,$(OBJSDIR)/%.o,$(SRCS))
DEPS	=	$(OBJS:.o=.d)

B_OBJDIR = ./objs_bonus
B_OBJS	=	$(patsubst $(BONUSDIR)/%.c,$(B_OBJDIR)/%.o,$(BONUS))
B_DEPS	=	$(B_OBJS:.o=.d)

LIBFTDIR = ./libft
LIBFT = $(LIBFTDIR)/libft.a

LDFLAGS = -lmlx -L/usr/X11R6/lib -lX11 -lXext -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(LIBFT):
		$(MAKE) -C $(LIBFTDIR)

-include $(DEPS)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(B_OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(B_OBJS) $(LIBFT) $(LDFLAGS) -o $(BONUS_NAME)

$(B_OBJDIR)/%.o: $(BONUSDIR)/%.c
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) $(B_INC) -c -o $@ $<

-include $(B_DEPS)

clean:
		$(MAKE) fclean -C $(LIBFTDIR)
		$(RM) $(OBJS) $(DEPS) $(B_OBJS) $(B_DEPS)
		@$(RM) -rf $(OBJSDIR) $(B_OBJDIR)

fclean: clean
		$(RM) $(NAME) $(BONUS_NAME)

re: fclean all


debug: CFLAGS += -g -fsanitize=address
debug: re

.PHONY: all clean fclean re bonus norm debug
