/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   floor_ceiling.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 13:28:10 by ikole          #+#    #+#                */
/*   Updated: 2020/03/05 09:18:51 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	draw_ceiling(t_vars *vars, int check, int x)
{
	register int			tx;
	register int			ty;
	register unsigned int	color;

	if (check >= 0 && check < vars->screen_height)
	{
		tx = (int)(vars->texture[4]->width * (vars->floor->floor_x -
			vars->floor->cell_x)) & (vars->texture[4]->width - 1);
		ty = (int)(vars->texture[4]->height * (vars->floor->floor_y -
			vars->floor->cell_y)) & (vars->texture[4]->height - 1);
		color = *(unsigned int*)(vars->texture[4]->addr + (tx *
		vars->texture[4]->line_length + ty *
		(vars->texture[4]->bits_per_pixel / 8)));
		if (color == 0xFF000000)
			ft_error(vars, "Whoops, you seem to have a seetrough ceiling \
			texture!\n");
		put_pixel(vars, x, check, add_shadow_fc_tex(vars, color));
	}
}

void	draw_floor(t_vars *vars, int x, int y)
{
	register int			tx;
	register int			ty;
	register unsigned int	color;

	if (y >= 0 && y < vars->screen_height)
	{
		tx = (int)(vars->texture[5]->width * (vars->floor->floor_x -
			vars->floor->cell_x)) & (vars->texture[5]->width - 1);
		ty = (int)(vars->texture[5]->height * (vars->floor->floor_y -
			vars->floor->cell_y)) & (vars->texture[5]->height - 1);
		color = *(unsigned int*)(vars->texture[5]->addr + (tx *
		vars->texture[5]->line_length + ty *
		(vars->texture[5]->bits_per_pixel / 8)));
		if (color == 0xFF000000)
			ft_error(vars, "Whoops, you seem to have a seetrough floor \
			texture!\n");
		put_pixel(vars, x, y, add_shadow_fc_tex(vars, color));
	}
}

void	draw_floor_ceiling(t_vars *vars, int x, int y)
{
	register int check;

	vars->floor->ray_dir_x0 = vars->pos->dir_x - vars->pos->plane_x;
	vars->floor->ray_dir_y0 = vars->pos->dir_y - vars->pos->plane_y;
	vars->floor->ray_dir_x1 = vars->pos->dir_x + vars->pos->plane_x;
	vars->floor->ray_dir_y1 = vars->pos->dir_y + vars->pos->plane_y;
	while (y < vars->screen_height)
	{
		floor_ceiling_init(vars, y);
		x = 0;
		check = vars->screen_height - y - 1;
		while (x < vars->screen_width)
		{
			vars->floor->cell_x = (int)(vars->floor->floor_x);
			vars->floor->cell_y = (int)(vars->floor->floor_y);
			vars->floor->floor_x += vars->floor->floor_step_x;
			vars->floor->floor_y += vars->floor->floor_step_y;
			draw_ceiling(vars, check, x);
			draw_floor(vars, x, y);
			x++;
		}
		y++;
	}
}
