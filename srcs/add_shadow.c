/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_shadow.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 09:36:10 by ikole          #+#    #+#                */
/*   Updated: 2020/03/05 18:53:15 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

unsigned int	add_shadow(t_vars *vars, unsigned int color)
{
	register int	r;
	register int	g;
	register int	b;
	register double	multi;

	r = (color & 0xFF0000) >> 16;
	g = (color & 0xFF00) >> 8;
	b = color & 0xFF;
	multi = 15 / vars->pos->perp_wall_distance / 3;
	if (multi > 1)
		multi = 1;
	if (multi <= 0.1)
		multi = 0.1;
	r *= multi;
	g *= multi;
	b *= multi;
	color = (r << 16) + (g << 8) + b;
	return (color);
}

unsigned int	add_shadow_sprite(unsigned int color, double distance)
{
	register int	r;
	register int	g;
	register int	b;
	register double	multi;

	r = (color & 0xFF0000) >> 16;
	g = (color & 0xFF00) >> 8;
	b = color & 0xFF;
	multi = 20 / distance;
	if (multi > 1)
		multi = 1;
	if (multi <= 0.1)
		multi = 0.1;
	r *= multi;
	g *= multi;
	b *= multi;
	color = (r << 16) + (g << 8) + b;
	return (color);
}

unsigned int	add_shadow_fc_tex(t_vars *vars, unsigned int color)
{
	register int	r;
	register int	g;
	register int	b;
	register double multi;

	r = (color & 0xFF0000) >> 16;
	g = (color & 0xFF00) >> 8;
	b = color & 0xFF;
	multi = 15 / vars->floor->row_distance / 3;
	if (multi > 1)
		multi = 1;
	if (multi <= 0.1)
		multi = 0.1;
	r *= multi;
	g *= multi;
	b *= multi;
	color = (r << 16) + (g << 8) + b;
	return (color);
}

unsigned int	shift_color(unsigned int color)
{
	register int	r;
	register int	g;
	register int	b;

	r = (color & 0xFF0000) >> 16;
	g = (color & 0xFF00) >> 8;
	b = color & 0xFF;
	r = r / 2 + 17;
	g = g / 2 + 25;
	b = b / 2 + 34;
	color = (r << 16) + (g << 8) + b;
	return (color);
}
