/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:00:26 by minabe            #+#    #+#             */
/*   Updated: 2023/09/30 14:16:41 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdlib.h>
# include <limits.h>
# include <float.h>
# include <stdarg.h>
# include <unistd.h>
# include <errno.h>
# include <math.h>
# include <mlx.h>
# include "trigonometric.h"
# include "../libft/include/libft.h"

# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define WALL_HEIGHT 50

# define SIZE 64
# define WIN_WIDTH 1280
# define WIN_HEIGHT 960

# define ROT_INTERVAL 60
# define MOVE_SPEED 0.15

# define DEBUG 1
# define HEADER_LEN 6

# define DEFAULT 0

# define TEX_WIDTH 64
# define TEX_HEIGHT 64

# define X_AXIS 0
# define Y_AXIS 1

# define MAP_HEIGHT_MAX 100
# define MAP_WIDTH_MAX 100

enum e_direction
{
	FRONT,
	BACK,
	LEFT,
	RIGHT,
};

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
	int		items;
}	t_map;

typedef struct s_header
{
	char	*east_tex_path;
	char	*west_tex_path;
	char	*north_tex_path;
	char	*south_tex_path;
	char	*ceiling_color;
	char	*floor_color;
}	t_header;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}	t_image;

typedef struct s_wall
{
	t_image	*east;
	t_image	*west;
	t_image	*north;
	t_image	*south;
}	t_wall;

// 視野角90で固定
typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
}	t_player;

typedef struct s_ray
{
	int			x;
	double		wall_x;
	t_vector	pos;
	t_vector	dir;
	t_vector	side_distance;
	t_vector	delta_distance;
	t_vector	step;
	t_vector	map;
	int			side;
	bool		hit;
	double		perpendicular_wall_distance;
	void		*tex;
}	t_ray;

typedef struct s_game
{
	void		*ptr;
	void		*win_ptr;
	t_wall		wall;
	int			ceiling_color;
	int			floor_color;
	t_player	player;
	t_map		*map;
	t_image		*img;
	int			wall_height;
	t_ray		ray;
}	t_game;

bool		is_cub_file(char *filename);
int			count_map_height(char **file);
bool		check_wall(t_map *map);
bool		check_map(t_map *map);
void		get_file(char *file, t_map *map, t_header *header);
void		free_2d(char **strs);

void		start_game(t_map *map, t_header *header);
int			end_game(t_game *game);

void		init_player(t_game *game);

void		set_position(t_game *game, int direction);
void		set_field_of_view(t_player *player, double fov);

void		set_vector(t_vector *vector, double x, double y);

void		calculate_ray(t_game *game, t_ray *ray);

int			draw_window(t_game *game);

double		vectorlen(t_vector vector);

void		add_textures(t_game *game, t_header *header);
void		remove_textures(t_game *game);

int			create_rgb(char *rgb);
u_int32_t	get_color_from_img(t_image *img, int x, int y);

void		my_mlx_pixel_put(t_image *img, int x, int y, int color);

#endif
