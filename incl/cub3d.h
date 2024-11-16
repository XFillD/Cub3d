/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:32:52 by yalechin          #+#    #+#             */
/*   Updated: 2024/11/16 17:05:41 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/get_next_line.h"
# include "../libft/libft.h"
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

# define M_PI 3.14159265358979323846

# define FLOOR_M_COLOUR 0x000000
# define FLOOR_M_B_COLOUR 0x000000
# define WALL_M_COLOUR 0xFFD8BFD8
# define WALL_M_B_COLOUR 0xFFD8BFD8

# define FAIL 1
# define SUCCESS 0

# define T_NORTH "cat_textures/NORTH.png"
# define T_SOUTH "cat_textures/SOUTH.png"
# define T_WEST "cat_textures/WEST.png"
# define T_EAST "cat_textures/EAST.png"

typedef struct s_player
{
	int				p_x;
	int				p_y;
	int				m_v;
	int				m_h;
	double			angle;
	int				p_dx;
	int				p_dy;
	int				rot;
	float			fov;
}					t_player;

typedef struct s_design_config
{
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	int				floor_color[3];
	int				ceiling_color[3];
}					t_design_config;

typedef struct s_game
{
	// char **map_test;
	char			**map;
	char			**buffer;
	int				player_x;
	int				player_y;
	int				map_h;
	int				map_w;

	int				m_map_w;
	int				m_map_h;
	int				m_map_x;
	int				m_map_y;

	t_design_config	*design_config;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*east_texture;
	mlx_texture_t	*image;

	float			x_textures;
	float			y_textures;
	int				was_hit_vertical;
	int				map_flag;
	int				line_flag;
}					t_game;

typedef struct s_ray
{
	double			r_angle;
	int				wall;
	double			distance;

	float			vx;
	float			vy;
	float			hx;
	float			hy;

	float			wall_hit_x;
	float			wall_hit_y;

	int				index;
	double			wall_h;
}					t_ray;

typedef struct s_mlx
{
	t_game			*game;
	t_player		*player;
	void			*p_mlx;
	int				counter;
	mlx_image_t		*img;
	t_ray			*ray;
}					t_mlx;

void				game_loop(void *p_mlx);

/*RAY CASTING*/
void				ray_caster(t_mlx *mlx, double inter_h, double inter_v,
						int ray);
float				horizontal(t_mlx *mlx, float angle);
float				vertical(t_mlx *mlx, float angle);
int					check_inter(float angle, float *inter, float *step,
						int hrzntl);
int					angle_check(float angle, char c);

/*MAP FUNCTION*/
int					map_read(t_game *game, char *file, int x, int i);
void				find_player(t_game *game);
void				map_size(t_game *game);

/*MINIMAP FUNCTIONS*/
void				render_mini_map2(t_mlx *mlx);
void				render_mini_map(t_mlx *mlx);
void				mini_map_size(t_game *game);
void				render_player(t_mlx *mlx, int colour, int start_x,
						int start_y);
void				render_square(t_mlx *mlx, int x, int y);
void				render_square_floor(t_mlx *mlx, int x, int y);
void				render_player_direction_mini(t_mlx *mlx);
void				draw_ray_mini(t_mlx *mlx, float end_x, float end_y,
						int color);

/*EXIT AND CLEAN*/
void				ft_exit(t_mlx *mlx);
void				check_and_exit(int condition, t_game *game,
						const char *message);
void				ft_exit_simple(t_game *game);
void				close_game_callback(void *param);
void				free_textures(t_game *game);
void				free_floor_ceiling(t_design_config *config);
void				free_design_config(t_design_config *config);

/*PLAYER MOVEMENT*/
void				hook(t_mlx *mlx, double move_v, double move_h);
void				move_player(t_mlx *mlx, double move_v, double move_h);
void				rotate_player(t_mlx *mlx, int x);
void				mlx_key(mlx_key_data_t keydata, void *ml);
void				ft_release(mlx_key_data_t keydata, t_mlx *mlx);

/*3D RENDERING*/
void				render_wall(t_mlx *mlx, int ray);
void				detect_texture(t_mlx *mlx);
void				draw_floor_ceiling(t_mlx *mlx, int ray, int top_pix,
						int bottom_pix);
void				get_texture_x(t_mlx *mlx, mlx_texture_t *image);
int					check_wall(float x, float y, t_mlx *mlx);

/*OTHER UTILS*/
void				ft_pixel_put(t_mlx *mlx, int x, int y, int color);
float				angle_nor(float angle);
void				error(char *error_text);
int					bytes_reverse(int c);
int					get_rgba(int r, int g, int b, int a);
int					get_color_of_texture(int x, int y, mlx_texture_t *image);
void				check_empty_line(const char *line, t_game *game);
int					is_map_line(t_game *game, const char *line, size_t x,
						size_t count);
void				remove_newline_all(t_game *game);
int					ft_strncmp2(char *s1, char *s2, size_t n);
void				get_colours(char *buffer, int *r, int *g, int *b);
int					buffer_check(char **buffer, int rows);
void				init_arrays(t_game *game, int rows);
void				file_check(void);

/*CHECKS*/
int					map_check(t_game *game);
void				check_argv(char *argv);
void				check_player(t_game *game);

#endif
