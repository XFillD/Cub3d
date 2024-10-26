#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/include/MLX42/MLX42.h"
# include "libft/get_next_line.h"
# include "libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>

# define COLOUR_RED "\033[0;31m"
# define COLOUR_GREEN "\033[0;32m"
# define COLOUR_RESET "\033[0m"
# define COLOUR_BLUE "\033[0;34m"

# define S_W 1900
# define S_H 1000
# define S_SQUARE 30
# define PLAYER_SPEED 4
# define ROTATION_SPEED 0.05
# define FOV 60
# define MINIMAP_SCALE 0.5
// # define S_SQUARE_M 15
# define S_SQUARE_M (S_SQUARE * MINIMAP_SCALE)
# define P_SIZE (S_SQUARE_M / 2)

# define M_PI 3.14159265358979323846
# define M_PI2 (M_PI / 2)
# define M_PI3 (3 * M_PI / 2)

# define P_BOX "imgs/box.xpm"
# define P_CAT "imgs/cat.xpm"
# define P_WALL "imgs/wall.xpm"
# define P_SPACE "imgs/space.xpm"
# define P_HEAD "imgs/head.xpm"
# define P_DOOR "imgs/door.xpm"

# define FAIL 1
# define SUCCESS 0

typedef struct s_player
{
	int			p_x;
	int			p_y;
	int			m_v;
	int			m_h;
	double		angle;
	int			p_dx;
	int			p_dy;
	int			rot;
	float		fov;
}				t_player;

typedef struct s_game
{
	// char **map_test;
	char		**map;
	char		**buffer;
	int			player_x;
	int			player_y;
	int			map_h;
	int			map_w;

	int			m_map_w;
	int			m_map_h;
	int			m_map_x;
	int			m_map_y;

}				t_game;

typedef struct s_ray
{
	double		r_angle;
	int			wall;
	double		distance;

	float		vx;
	float		vy;
	float		hx;
	float		hy;

	float		interv;
	float		interh;

}				t_ray;

typedef struct s_mlx
{
	t_game		*game;
	t_player	*player;
	void		*p_mlx;
	mlx_image_t	*img;
	t_ray		*ray;
}				t_mlx;

void			game_loop(void *p_mlx);

/*RAY CASTING*/
void			ray_caster(t_mlx *mlx);
float			horizontal(t_mlx *mlx, float angle);
float			vertical(t_mlx *mlx, float angle);
int				check_inter(float angle, float *inter, float *step, int hrzntl);
int				angle_check(float angle, char c);

/*MAP FUNCTION*/
int				map_read(t_game *game, char *file);
void			find_player(t_game *game);
void			map_size(t_game *game);

/*MINIMAP FUNCTIONS*/
void			render_mini_map2(t_mlx *mlx);
void			render_mini_map(t_mlx *mlx);
void			mini_map_size(t_game *game);
void			render_player(t_mlx *mlx, int colour);
void			render_square(t_mlx *mlx, int x, int y, int colour,
					int border_colour);
void			render_player_direction_mini(t_mlx *mlx);
void			draw_ray_mini(t_mlx *mlx, float start_x, float start_y,
					float end_x, float end_y, int color);

/*EXIT AND CLEAN*/
void			ft_exit(t_mlx *mlx);

/*PLAYER MOVEMENT*/
void			hook(t_mlx *mlx, double move_v, double move_h);
void			move_player(t_mlx *mlx, double move_v, double move_h);
void			rotate_player(t_mlx *mlx, int x);
void			mlx_key(mlx_key_data_t keydata, void *ml);
void			ft_release(mlx_key_data_t keydata, t_mlx *mlx);

/*3D RENDERING*/
void			render_wall(t_mlx *mlx, int ray);
void			draw_wall(t_mlx *mlx, int ray, int top_pix, int bottom_pix);
int				check_wall(float x, float y, t_mlx *mlx);
int				get_colour(t_mlx *mlx, int flag);
void			draw_floor_ceiling(t_mlx *mlx, int ray, int top_pix,
					int bottom_pix);

/*OTHER UTILS*/
void			ft_pixel_put(t_mlx *mlx, int x, int y, int color);
float			angle_nor(float angle);
void			error(char *error_text);

/*CHECKS*/
int				map_check(t_game *game);

void			check_argv(char *argv);
void			check_player(t_game *game);

#endif
