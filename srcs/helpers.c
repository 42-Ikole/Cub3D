/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helpers.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 13:22:56 by ikole          #+#    #+#                */
/*   Updated: 2020/03/02 13:23:11 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	put_pixel(t_vars *vars, int x, int y, int color)
{
	register char	*dst;

	dst = vars->img[vars->img_status]->addr + (y *
		vars->img[vars->img_status]->line_length + x *
		(vars->img[vars->img_status]->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		ft_close_window(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		return (1);
	}
	return (0);
}

void	cam_init(t_vars *vars, int x)
{
	vars->cam->cam_x = 2 * x / (double)vars->screen_width - 1;
	vars->cam->raydir_x = vars->pos->dir_x + vars->pos->plane_x *
			vars->cam->cam_x;
	vars->cam->raydir_y = vars->pos->dir_y + vars->pos->plane_y *
			vars->cam->cam_x;
	vars->pos->map_x = (int)vars->pos->pos_x;
	vars->pos->map_y = (int)vars->pos->pos_y;
	vars->pos->delta_dist_x = fabs(1 / vars->cam->raydir_x);
	vars->pos->delta_dist_y = fabs(1 / vars->cam->raydir_y);
	vars->pos->hit = 0;
}

void	set_raydir(t_vars *vars)
{
	if (vars->cam->raydir_x < 0)
	{
		vars->pos->step_x = -1;
		vars->pos->side_dist_x = (vars->pos->pos_x - vars->pos->map_x) *
		vars->pos->delta_dist_x;
	}
	else
	{
		vars->pos->step_x = 1;
		vars->pos->side_dist_x = (vars->pos->map_x + 1.0 - vars->pos->pos_x) *
		vars->pos->delta_dist_x;
	}
	if (vars->cam->raydir_y < 0)
	{
		vars->pos->step_y = -1;
		vars->pos->side_dist_y = (vars->pos->pos_y - vars->pos->map_y) *
		vars->pos->delta_dist_y;
	}
	else
	{
		vars->pos->step_y = 1;
		vars->pos->side_dist_y = (vars->pos->map_y + 1.0 - vars->pos->pos_y) *
		vars->pos->delta_dist_y;
	}
}

void	check_hit(t_vars *vars)
{
	while (vars->pos->hit == 0)
	{
		if (vars->pos->side_dist_x < vars->pos->side_dist_y)
		{
			vars->pos->side_dist_x += vars->pos->delta_dist_x;
			vars->pos->map_x += vars->pos->step_x;
			if (vars->pos->step_x < 0)
				vars->pos->side = 3;
			else
				vars->pos->side = 1;
		}
		else
		{
			vars->pos->side_dist_y += vars->pos->delta_dist_y;
			vars->pos->map_y += vars->pos->step_y;
			if (vars->pos->step_y < 0)
				vars->pos->side = 2;
			else
				vars->pos->side = 0;
		}
		if (vars->map->map[vars->pos->map_y][vars->pos->map_x] == '1')
			vars->pos->hit = 1;
	}
}
