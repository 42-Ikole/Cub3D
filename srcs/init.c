/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 15:42:13 by ikole          #+#    #+#                */
/*   Updated: 2020/03/03 09:08:50 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_struct(t_vars *vars)
{
	vars->texture[0]->width = 0;
	vars->texture[1]->width = 0;
	vars->texture[2]->width = 0;
	vars->texture[3]->width = 0;
	vars->texture[4]->width = 0;
	vars->texture[5]->width = 0;
	vars->sprite[0]->width = 0;
	vars->sprite[1]->width = 0;
}

void	init_values(t_vars *vars)
{
	vars->win = NULL;
	vars->key->w = 0;
	vars->key->a = 0;
	vars->key->s = 0;
	vars->key->d = 0;
	vars->key->left = 0;
	vars->key->right = 0;
	vars->screen_width = -1;
	vars->screen_height = -1;
	vars->img_status = 0;
	vars->save = 0;
	vars->map->floor = -1;
	vars->map->ceiling = -1;
	vars->map->m_width = -1;
	vars->key->mouse_x = 0;
	vars->map->status = 0;
	vars->sprite[0]->width = 0;
	vars->sprite[1]->width = 0;
	vars->sprite_count = 0;
	vars->health = 100;
	vars->pos->pos_x = 0;
	vars->save = 0;
	vars->map->map = malloc(sizeof(int *));
	if (!vars->map->map)
		ft_error(vars, "Whoops, malloc for innitial map failed!\n");
}

void	init_window(t_vars *vars)
{
	vars->win = mlx_new_window(vars->mlx, vars->screen_width,
		vars->screen_height, "FLUFFY CUB3D!");
	if (!vars->win)
		ft_error(vars, "Whoops, crating a new window failed!\n");
}

void	init_img(t_vars *vars)
{
	vars->img[0]->img = mlx_new_image(vars->mlx, vars->screen_width,
	vars->screen_height);
	if (!vars->img[0]->img)
		ft_error(vars, "Whoops, creating the first image failed!\n");
	vars->img[0]->addr = mlx_get_data_addr(vars->img[0]->img,
		&vars->img[0]->bits_per_pixel, &vars->img[0]->line_length,
		&vars->img[0]->endian);
	if (vars->save)
		return ;
	vars->img[1]->img = mlx_new_image(vars->mlx, vars->screen_width,
		vars->screen_height);
	if (!vars->img[1]->img)
		ft_error(vars, "Whoops, creating the second image failed!\n");
	vars->img[1]->addr = mlx_get_data_addr(vars->img[1]->img,
		&vars->img[1]->bits_per_pixel, &vars->img[1]->line_length,
		&vars->img[1]->endian);
	vars->img[2]->img = mlx_new_image(vars->mlx, vars->screen_width,
		vars->screen_height);
	if (!vars->img[2]->img)
		ft_error(vars, "Whoops, creating the third image failed!\n");
	vars->img[2]->addr = mlx_get_data_addr(vars->img[2]->img,
		&vars->img[2]->bits_per_pixel, &vars->img[2]->line_length,
		&vars->img[2]->endian);
}
