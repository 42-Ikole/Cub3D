/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extra.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 15:19:20 by ikole          #+#    #+#                */
/*   Updated: 2020/03/05 18:55:57 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void		you_died(t_vars *vars)
{
	int x;
	int y;

	if (vars->health < 0)
		vars->health = 0;
	y = 0;
	while (y < vars->screen_height)
	{
		x = 0;
		while (x < vars->screen_width)
		{
			put_pixel(vars, x, y, 0x00FF0000);
			x++;
		}
		y++;
	}
}

static void	draw_life(t_vars *vars, int x, int y)
{
	register int width;
	register int start;

	width = vars->screen_width / 10;
	start = (0.5 * vars->screen_width) - 100;
	y = vars->screen_height - 70;
	while (y < vars->screen_height - 50)
	{
		x = start;
		while (x < start + 2 * vars->health)
		{
			if (x > 0 && x < vars->screen_width && y > 0 &&
			y < vars->screen_height)
				put_pixel(vars, x, y, 0x0000FF00);
			x++;
		}
		while (x < start + 200)
		{
			if (x > 0 && x < vars->screen_width && y > 0 &&
			y < vars->screen_height)
				put_pixel(vars, x, y, 0x00FF0000);
			x++;
		}
		y++;
	}
}

void		draw_healthbar(t_vars *vars)
{
	register int	x;
	register int	y;

	x = 0;
	y = 0;
	if (vars->health <= 0)
	{
		you_died(vars);
		return ;
	}
	draw_life(vars, x, y);
}

void		ft_switch_img(t_vars *vars)
{
	if (vars->points < 0)
		vars->health = 0;
	if (vars->health <= 0)
		mlx_string_put(vars->mlx, vars->win, 0.42 * vars->screen_width,
		0.5 * vars->screen_height, 0, "You were not fluffy enough!");
	if (vars->key->tab && vars->screen_height >= 960)
	{
		draw_hud(vars);
		draw_healthbar(vars);
	}
	if (vars->img_status == 0)
		vars->img_status = 1;
	else if (vars->img_status == 1)
		vars->img_status = 2;
	else
		vars->img_status = 0;
}
