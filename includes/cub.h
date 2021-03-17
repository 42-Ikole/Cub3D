/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/29 09:16:05 by ikole          #+#    #+#                */
/*   Updated: 2020/03/11 09:58:23 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef	struct	s_key
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
	int			mouse_x;
	int			tab;
}				t_key;

typedef struct	s_cam
{
	int			x;
	double		cam_x;
	double		raydir_x;
	double		raydir_y;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_cam;

typedef struct	s_pos
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		perp_wall_distance;
}				t_pos;

typedef struct	s_texture
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
	int			x;
	int			y;
}				t_texture;

typedef struct	s_sprite
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_sprite;

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct	s_map
{
	char		**map;
	int			ceiling;
	int			floor;
	int			m_width;
	int			m_height;
	int			status;
}				t_map;

typedef	struct	s_floor
{
	double		ray_dir_x0;
	double		ray_dir_x1;
	double		ray_dir_y0;
	double		ray_dir_y1;
	int			p;
	double		pos_z;
	double		row_distance;
	double		floor_step_x;
	double		floor_step_y;
	double		floor_x;
	double		floor_y;
	int			cell_x;
	int			cell_y;
}				t_floor;

typedef struct	s_sprite_vars
{
	double		sprite_x;
	double		sprite_y;
	double		inv_det;
	double		transform_x;
	double		transform_y;
	int			sprite_screen_x;
	int			sprite_height;
	int			draw_start_y;
	int			draw_end_y;
	int			sprite_width;
	int			draw_start_x;
	int			draw_end_x;
	int			tex_x;
	int			tex_y;
	int			d;
}				t_sprite_vars;

typedef struct	s_vars
{
	t_img			*img[3];
	t_pos			*pos;
	t_cam			*cam;
	t_key			*key;
	t_texture		*texture[6];
	t_map			*map;
	t_floor			*floor;
	t_sprite		*sprite[4];
	t_sprite_vars	*sprite_vars;
	void			*mlx;
	void			*win;
	int				screen_height;
	int				screen_width;
	int				tex_y;
	int				tex_x;
	double			wall_x;
	double			step;
	double			texpos;
	int				img_status;
	double			**sprite_pos;
	int				*sprite_order;
	int				*sprite_distance;
	double			*z_buffer;
	int				sprite_count;
	int				save;
	int				health;
	int				points;
}				t_vars;

int				ft_makescene(t_vars *vars);
int				get_next_line(int fd, char **line);
int				parser(char **args, t_vars *vars);
size_t			ft_strlen(const char *s);
void			map_filler(t_vars *vars);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			ft_save(t_vars *vars, char **str);
void			init_img(t_vars *vars);

void			put_pixel(t_vars *vars, int x, int y, int color);
void			cam_init(t_vars *vars, int x);
void			set_raydir(t_vars *vars);
void			check_hit(t_vars *vars);
void			check_wall(t_vars *vars);

void			calculate_texture(t_vars *vars);
void			draw_texture(t_vars *vars, int x, int y);
void			draw_screen(t_vars *vars, int x, int y);

void			floor_ceiling_init(t_vars *vars, int y);
void			draw_ceiling(t_vars *vars, int check, int x);
void			draw_floor(t_vars *vars, int x, int y);
void			draw_floor_ceiling(t_vars *vars, int x, int y);

void			sort_sprites(t_vars *vars);
void			sprite_dist(t_vars *vars);
void			sprite_init(t_vars *vars, int x);
void			sprite_draw_start(t_vars *vars);
void			put_sprite(t_vars *vars, int x, int stripe);

void			you_died(t_vars *vars);
void			draw_healthbar(t_vars *vars);
void			ft_switch_img(t_vars *vars);

void			move_forward(t_vars *vars, double movespeed);
void			move_left(t_vars *vars, double movespeed);
void			move_back(t_vars *vars, double movespeed);
void			move_right(t_vars *vars, double movespeed);

void			rotate_right(t_vars *vars, double rotatespeed);
void			rotate_left(t_vars *vars, double rotatespeed);
int				mouse_move(int x, int y, t_vars *vars);

int				close_window(t_vars *vars);
int				walk(t_vars *vars);
int				state_anti_walk(int key, t_vars *vars);
int				state_walk(int key, t_vars *vars);

void			init_struct(t_vars *vars);
void			init_values(t_vars *vars);
void			init_window(t_vars *vars);
void			init_img(t_vars *vars);

int				diff(int nb1, int nb2);
void			*ft_memset(void *ptr, int x, size_t n);

int				ft_error(t_vars *vars, char *str);
char			*ft_strdup(const char *str);
char			*ft_substr(char const *s, unsigned int start, size_t len);
size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

void			check_sprite(t_vars *vars, char *line, int count, int i);
void			check_img(t_vars *vars, char *line, int side, int i);

void			spawn_north(t_vars *vars, int m_index, int y);
void			spawn_east(t_vars *vars, int m_index, int y);
void			spawn_south(t_vars *vars, int m_index, int y);
void			spawn_west(t_vars *vars, int m_index, int y);

void			check_map(t_vars *vars, char *line);
void			init_sprite_pos(t_vars *vars, int m_index, int type);

void			validate_map(t_vars *vars);
void			map_validator_diagonal(t_vars *vars, int x, int y);
void			map_validator(t_vars *vars, int x, int y);

void			check_color(t_vars *vars, char *line, char c, int i);
void			check_res(t_vars *vars, char *line, int i);

int				ft_atoi(char *str);

unsigned int	add_shadow(t_vars *vars, unsigned int color);
unsigned int	add_shadow_sprite(unsigned int color, double distance);
unsigned int	add_shadow_fc_tex(t_vars *vars, unsigned int color);
unsigned int	shift_color(unsigned int color);

char			*ft_itoa(int n);
void			check_animation(t_vars *vars, char *line, int count, int i);
void			draw_hud(t_vars *vars);

#endif
