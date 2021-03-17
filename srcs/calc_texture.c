/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc_texture.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 13:25:43 by ikole          #+#    #+#                */
/*   Updated: 2020/03/06 11:53:45 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	check_wall(t_vars *vars)
{
	if (vars->pos->side == 3 || vars->pos->side == 1)
		vars->pos->perp_wall_distance = (vars->pos->map_x - vars->pos->pos_x +
			(1 - vars->pos->step_x) / 2) / vars->cam->raydir_x;
	else
		vars->pos->perp_wall_distance = (vars->pos->map_y - vars->pos->pos_y +
			(1 - vars->pos->step_y) / 2) / vars->cam->raydir_y;
	vars->cam->line_height = (int)(vars->screen_height /
		vars->pos->perp_wall_distance);
	vars->cam->draw_start = -vars->cam->line_height / 2 +
		vars->screen_height / 2;
	if (vars->cam->draw_start < 0)
		vars->cam->draw_start = 0;
	vars->cam->draw_end = vars->cam->line_height / 2 +
		vars->screen_height / 2;
	if (vars->cam->draw_end >= vars->screen_height)
		vars->cam->draw_end = vars->screen_height - 1;
	if (vars->pos->side == 3 || vars->pos->side == 1)
		vars->wall_x = vars->pos->pos_y + vars->pos->perp_wall_distance *
			vars->cam->raydir_y;
	else
		vars->wall_x = vars->pos->pos_x + vars->pos->perp_wall_distance *
			vars->cam->raydir_x;
	vars->wall_x -= floor(vars->wall_x);
}

void	calculate_texture(t_vars *vars)
{
	vars->tex_x = (int)(vars->wall_x *
		(double)vars->texture[vars->pos->side]->width);
	if ((vars->pos->side == 3 || vars->pos->side == 1) &&
		vars->cam->raydir_x > 0)
		vars->tex_x = vars->texture[vars->pos->side]->width -
			vars->tex_x - 1;
	if ((vars->pos->side == 2 || vars->pos->side == 0) &&
		vars->cam->raydir_y < 0)
		vars->tex_x = vars->texture[vars->pos->side]->width -
			vars->tex_x - 1;
	vars->step = 1.0 * vars->texture[vars->pos->side]->height /
		vars->cam->line_height;
	vars->texpos = (vars->cam->draw_start - vars->screen_height / 2 +
		vars->cam->line_height / 2) * vars->step;
}

void	draw_texture(t_vars *vars, int x, int y)
{
	register unsigned int color;

	color = 0x00FF;
	vars->tex_y = (int)vars->texpos &
		(vars->texture[vars->pos->side]->height - 1);
	vars->texpos += vars->step;
	if (vars->pos->side == 0)
		color = *(unsigned int*)(vars->texture[0]->addr +
			(vars->tex_y * vars->texture[0]->line_length +
			vars->tex_x * (vars->texture[0]->bits_per_pixel / 8)));
	else if (vars->pos->side == 1)
		color = *(unsigned int*)(vars->texture[1]->addr +
		(vars->tex_y * vars->texture[1]->line_length +
		vars->tex_x * (vars->texture[1]->bits_per_pixel / 8)));
	else if (vars->pos->side == 2)
		color = *(unsigned int*)(vars->texture[2]->addr +
		(vars->tex_y * vars->texture[2]->line_length +
		vars->tex_x * (vars->texture[2]->bits_per_pixel / 8)));
	else if (vars->pos->side == 3)
		color = *(unsigned int*)(vars->texture[3]->addr +
		(vars->tex_y * vars->texture[3]->line_length +
		vars->tex_x * (vars->texture[3]->bits_per_pixel / 8)));
	if (color == 0xFF000000)
		ft_error(vars, "Whoops, you seem to have a seetrough wall texture!\n");
	put_pixel(vars, x, y, add_shadow(vars, color));
}

void	draw_screen(t_vars *vars, int x, int y)
{
	while (y < vars->cam->draw_start && !vars->texture[5]->width)
	{
		put_pixel(vars, x, y, vars->map->ceiling);
		y++;
	}
	y = vars->cam->draw_start;
	while (y <= vars->cam->draw_end)
	{
		draw_texture(vars, x, y);
		y++;
	}
	while (y < vars->screen_height && !vars->texture[5]->width)
	{
		put_pixel(vars, x, y, vars->map->floor);
		y++;
	}
}

void	floor_ceiling_init(t_vars *vars, int y)
{
	vars->floor->p = y - vars->screen_height / 2;
	vars->floor->pos_z = 0.5 * vars->screen_height;
	vars->floor->row_distance = vars->floor->pos_z / vars->floor->p;
	vars->floor->floor_step_x = vars->floor->row_distance *
	(vars->floor->ray_dir_x1 - vars->floor->ray_dir_x0) / vars->screen_width;
	vars->floor->floor_step_y = vars->floor->row_distance *
	(vars->floor->ray_dir_y1 - vars->floor->ray_dir_y0) / vars->screen_width;
	vars->floor->floor_x = vars->pos->pos_x + vars->floor->row_distance *
		vars->floor->ray_dir_x0;
	vars->floor->floor_y = vars->pos->pos_y + vars->floor->row_distance *
		vars->floor->ray_dir_y0;
}
