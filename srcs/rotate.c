/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 15:38:09 by ikole          #+#    #+#                */
/*   Updated: 2020/03/05 19:01:45 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	rotate_right(t_vars *vars, double rotatespeed)
{
	register double	olddir_x;
	register double	oldplane_x;

	olddir_x = vars->pos->dir_x;
	vars->pos->dir_x = vars->pos->dir_x * cos(rotatespeed) -
		vars->pos->dir_y * sin(rotatespeed);
	vars->pos->dir_y = olddir_x * sin(rotatespeed) +
		vars->pos->dir_y * cos(rotatespeed);
	oldplane_x = vars->pos->plane_x;
	vars->pos->plane_x = vars->pos->plane_x * cos(rotatespeed) -
		vars->pos->plane_y * sin(rotatespeed);
	vars->pos->plane_y = oldplane_x * sin(rotatespeed) +
		vars->pos->plane_y * cos(rotatespeed);
}

void	rotate_left(t_vars *vars, double rotatespeed)
{
	register double	olddir_x;
	register double	oldplane_x;

	olddir_x = vars->pos->dir_x;
	vars->pos->dir_x = vars->pos->dir_x * cos(-rotatespeed) -
	vars->pos->dir_y * sin(-rotatespeed);
	vars->pos->dir_y = olddir_x * sin(-rotatespeed) +
	vars->pos->dir_y * cos(-rotatespeed);
	oldplane_x = vars->pos->plane_x;
	vars->pos->plane_x = vars->pos->plane_x * cos(-rotatespeed) -
	vars->pos->plane_y * sin(-rotatespeed);
	vars->pos->plane_y = oldplane_x * sin(-rotatespeed) +
	vars->pos->plane_y * cos(-rotatespeed);
}

int		mouse_move(int x, int y, t_vars *vars)
{
	if (vars->key->tab)
		return (0);
	if (x >= 0 && x < vars->screen_width && y >= 0 && y < vars->screen_height)
	{
		mlx_mouse_move(vars->win, vars->screen_width / 2, vars->screen_height
		/ 2);
		if (x < vars->screen_width / 2)
			rotate_left(vars, 0.001 * (double)((vars->screen_width / 2) - x));
		else
			rotate_right(vars, 0.001 * (double)(x - (vars->screen_width / 2)));
	}
	return (1);
}
