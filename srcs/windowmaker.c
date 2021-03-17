/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   windowmaker.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/29 10:09:58 by ikole          #+#    #+#                */
/*   Updated: 2020/03/07 14:28:23 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	draw_sprite(t_vars *vars, int x, int stripe)
{
	sprite_dist(vars);
	while (x < vars->sprite_count)
	{
		if (vars->sprite_pos[x][2] == -1)
			x++;
		if (x > 0 && vars->sprite_pos[x - 1][2] == -1)
			continue ;
		sprite_init(vars, x);
		sprite_draw_start(vars);
		stripe = vars->sprite_vars->draw_start_x;
		while (stripe < vars->sprite_vars->draw_end_x)
		{
			vars->sprite_vars->tex_x = (int)(256 * (stripe -
			(-vars->sprite_vars->sprite_width / 2 +
			vars->sprite_vars->sprite_screen_x))
			* vars->sprite[(int)vars->sprite_pos[x][3]]->width /
			vars->sprite_vars->sprite_width) / 256;
			if (vars->sprite_vars->transform_y > 0 && stripe > 0
			&& stripe < vars->screen_width &&
			vars->sprite_vars->transform_y < vars->z_buffer[stripe])
				put_sprite(vars, x, stripe);
			stripe++;
		}
		x++;
	}
}

int		ft_makescene(t_vars *vars)
{
	register int	x;

	walk(vars);
	if (vars->texture[5]->width)
		draw_floor_ceiling(vars, 0, 0);
	x = 0;
	while (x < vars->screen_width)
	{
		cam_init(vars, x);
		set_raydir(vars);
		check_hit(vars);
		check_wall(vars);
		calculate_texture(vars);
		draw_screen(vars, x, 0);
		vars->z_buffer[x] = vars->pos->perp_wall_distance;
		x++;
	}
	draw_sprite(vars, 0, 0);
	if (!vars->save)
		mlx_put_image_to_window(vars->mlx, vars->win,
		vars->img[vars->img_status]->img, 0, 0);
	ft_switch_img(vars);
	return (1);
}

void	second_main(char **str, t_vars *vars, int arg)
{
	t_sprite_vars	sprite_vars;
	t_floor			floor;

	vars->sprite_vars = &sprite_vars;
	vars->floor = &floor;
	if (arg == 3)
	{
		if (ft_strncmp(str[2], "--save", 6))
			ft_error(vars, "WHOA, thats not --save!\n");
		if (str[2][6] != '\0')
			ft_error(NULL, "invalid argument --save\n");
		ft_save(vars, str);
	}
	parser(str, vars);
	init_img(vars);
	init_window(vars);
	mlx_hook(vars->win, 2, 1L << 0, state_walk, vars);
	mlx_hook(vars->win, 3, 1L << 1, state_anti_walk, vars);
	mlx_hook(vars->win, 6, 1L << 6, mouse_move, vars);
	mlx_hook(vars->win, 17, 1L << 17, close_window, vars);
	mlx_do_key_autorepeatoff(vars->mlx);
	mlx_loop_hook(vars->mlx, ft_makescene, vars);
	mlx_loop(vars->mlx);
}

void	init_vars(int arg, char **str, t_vars *vars, int i)
{
	t_texture		texture[6];
	t_sprite		sprite[4];
	t_key			key;
	t_map			map;

	vars->sprite[0] = &sprite[0];
	vars->sprite[1] = &sprite[1];
	vars->sprite[2] = &sprite[2];
	vars->sprite[3] = &sprite[3];
	vars->points = 0;
	while (i < 6)
	{
		vars->texture[i] = &texture[i];
		i++;
	}
	vars->key = &key;
	vars->map = &map;
	vars->key->tab = 0;
	init_struct(vars);
	init_values(vars);
	second_main(str, vars, arg);
}

int		main(int arg, char **str)
{
	t_vars			vars;
	t_img			img[4];
	t_cam			cam;
	t_pos			pos;

	if (arg == 1 || arg > 3)
		ft_error(&vars, "You did not specify a .cub file or you\
		gave too many arguments!\n");
	vars.img[0] = &img[0];
	vars.img[1] = &img[1];
	vars.img[2] = &img[2];
	vars.cam = &cam;
	vars.pos = &pos;
	vars.mlx = mlx_init();
	if (!vars.mlx)
		ft_error(&vars, "Whoops, initializing mlx failed!\n");
	init_vars(arg, str, &vars, 0);
	return (0);
}
