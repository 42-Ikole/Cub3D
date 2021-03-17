/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_hud.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 18:55:16 by ikole          #+#    #+#                */
/*   Updated: 2020/03/05 18:55:29 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	draw_hud_two(t_vars *vars, int y)
{
	register int	x;
	unsigned int	color;

	x = 0;
	while (x < vars->screen_width)
	{
		color = *(unsigned int*)(vars->img[vars->img_status]->addr + (y *
		vars->img[vars->img_status]->line_length + x *
		(vars->img[vars->img_status]->bits_per_pixel / 8)));
		if (y == vars->screen_height - 120 || x == 0 ||
		y == vars->screen_height - 1 || x == vars->screen_width - 1)
			put_pixel(vars, x, y, 0);
		else
			put_pixel(vars, x, y, shift_color(color));
		x++;
	}
}

void		draw_hud(t_vars *vars)
{
	register char	*points;
	register int	y;

	y = vars->screen_height - 120;
	while (y < vars->screen_height)
	{
		draw_hud_two(vars, y);
		y++;
	}
	points = ft_itoa(vars->points);
	mlx_string_put(vars->mlx, vars->win, vars->screen_width - 80,
		vars->screen_height - 60, 0x00F56F00, points);
	free(points);
}
