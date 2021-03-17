/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_helpers.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 15:15:50 by ikole          #+#    #+#                */
/*   Updated: 2020/03/07 09:42:55 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	sort_sprites(t_vars *vars)
{
	register int	i;
	register int	j;
	register double	*tmp;

	i = 0;
	while (i < vars->sprite_count)
	{
		j = i + 1;
		while (j < vars->sprite_count)
		{
			if (vars->sprite_pos[i][2] < vars->sprite_pos[j][2])
			{
				tmp = vars->sprite_pos[i];
				vars->sprite_pos[i] = vars->sprite_pos[j];
				vars->sprite_pos[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	sprite_dist(t_vars *vars)
{
	register int x;

	x = 0;
	while (x < vars->sprite_count)
	{
		if (vars->sprite_pos[x][2] == -1)
		{
			x++;
			continue ;
		}
		if (vars->img_status == 0)
		{
			if (vars->sprite_pos[x][3] == 1)
				vars->sprite_pos[x][3] = 2;
			else if (vars->sprite_pos[x][3] == 2)
				vars->sprite_pos[x][3] = 3;
			else if (vars->sprite_pos[x][3] == 3)
				vars->sprite_pos[x][3] = 1;
		}
		vars->sprite_pos[x][2] = ((vars->pos->pos_x - vars->sprite_pos[x][0]) *
		(vars->pos->pos_x - vars->sprite_pos[x][0]) + (vars->pos->pos_y -
		vars->sprite_pos[x][1]) * (vars->pos->pos_y - vars->sprite_pos[x][1]));
		x++;
	}
	sort_sprites(vars);
}

void	sprite_init(t_vars *vars, int x)
{
	vars->sprite_vars->sprite_x = vars->sprite_pos[x][0] - vars->pos->pos_x;
	vars->sprite_vars->sprite_y = vars->sprite_pos[x][1] - vars->pos->pos_y;
	vars->sprite_vars->inv_det = 1.0 / (vars->pos->plane_x * vars->pos->dir_y -
	vars->pos->dir_x * vars->pos->plane_y);
	vars->sprite_vars->transform_x = vars->sprite_vars->inv_det *
	(vars->pos->dir_y * vars->sprite_vars->sprite_x
	- vars->pos->dir_x * vars->sprite_vars->sprite_y);
	vars->sprite_vars->transform_y = vars->sprite_vars->inv_det *
	(-vars->pos->plane_y * vars->sprite_vars->sprite_x +
	vars->pos->plane_x * vars->sprite_vars->sprite_y);
	vars->sprite_vars->sprite_screen_x = (int)((vars->screen_width / 2) *
	(1 + vars->sprite_vars->transform_x / vars->sprite_vars->transform_y));
	vars->sprite_vars->sprite_height = abs((int)(vars->screen_height /
	vars->sprite_vars->transform_y));
	vars->sprite_vars->draw_start_y = -vars->sprite_vars->sprite_height /
	2 + vars->screen_height / 2;
}

void	sprite_draw_start(t_vars *vars)
{
	if (vars->sprite_vars->draw_start_y < 0)
		vars->sprite_vars->draw_start_y = 0;
	vars->sprite_vars->draw_end_y = vars->sprite_vars->sprite_height / 2 +
	vars->screen_height / 2;
	if (vars->sprite_vars->draw_end_y > vars->screen_height)
		vars->sprite_vars->draw_end_y = vars->screen_height - 1;
	vars->sprite_vars->sprite_width = abs((int)(vars->screen_height /
	vars->sprite_vars->transform_y));
	vars->sprite_vars->draw_start_x = -vars->sprite_vars->sprite_width / 2
	+ vars->sprite_vars->sprite_screen_x;
	if (vars->sprite_vars->draw_start_x < 0)
		vars->sprite_vars->draw_start_x = 0;
	vars->sprite_vars->draw_end_x = vars->sprite_vars->sprite_width / 2
	+ vars->sprite_vars->sprite_screen_x;
	if (vars->sprite_vars->draw_end_x >= vars->screen_width)
		vars->sprite_vars->draw_end_x = vars->screen_width - 1;
}

void	put_sprite(t_vars *vars, int x, int stripe)
{
	register unsigned int	color;
	register int			y;

	y = vars->sprite_vars->draw_start_y + 1;
	while (y < vars->sprite_vars->draw_end_y)
	{
		vars->sprite_vars->d = y * 256 - vars->screen_height * 128
		+ vars->sprite_vars->sprite_height * 128;
		vars->sprite_vars->tex_y = ((vars->sprite_vars->d *
		vars->sprite[(int)vars->sprite_pos[x][3]]->height) /
		vars->sprite_vars->sprite_height) / 256;
		color = *(unsigned int*)
		(vars->sprite[(int)vars->sprite_pos[x][3]]->addr +
		(vars->sprite_vars->tex_y *
		vars->sprite[(int)vars->sprite_pos[x][3]]->line_length +
		vars->sprite_vars->tex_x *
		(vars->sprite[(int)vars->sprite_pos[x][3]]->bits_per_pixel / 8)));
		if (color < 0xFF000000)
			put_pixel(vars, stripe, y,
			add_shadow_sprite(color, vars->sprite_pos[x][2]));
		y++;
	}
}
