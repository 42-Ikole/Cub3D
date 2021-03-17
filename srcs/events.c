/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   events.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 15:39:47 by ikole          #+#    #+#                */
/*   Updated: 2020/03/07 11:12:03 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		close_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

int		walk(t_vars *vars)
{
	register double movespeed;
	register double rotatespeed;

	movespeed = 0.08;
	rotatespeed = 0.05;
	if (!vars->key->tab)
		mlx_mouse_hide();
	else
		mlx_mouse_show();
	if (vars->key->w)
		move_forward(vars, movespeed);
	if (vars->key->a)
		move_left(vars, movespeed);
	if (vars->key->s)
		move_back(vars, movespeed);
	if (vars->key->d)
		move_right(vars, movespeed);
	if (vars->key->right)
		rotate_right(vars, rotatespeed);
	if (vars->key->left)
		rotate_left(vars, rotatespeed);
	return (1);
}

int		state_anti_walk(int key, t_vars *vars)
{
	if (key == 13)
		vars->key->w = 0;
	if (key == 0)
		vars->key->a = 0;
	if (key == 1)
		vars->key->s = 0;
	if (key == 2)
		vars->key->d = 0;
	if (key == 123)
		vars->key->left = 0;
	if (key == 124)
		vars->key->right = 0;
	return (0);
}

int		state_walk(int key, t_vars *vars)
{
	if (key == 13)
		vars->key->w = 1;
	if (key == 0)
		vars->key->a = 1;
	if (key == 1)
		vars->key->s = 1;
	if (key == 2)
		vars->key->d = 1;
	if (key == 123)
		vars->key->left = 1;
	if (key == 124)
		vars->key->right = 1;
	if (key == 48)
	{
		if (vars->key->tab == 1)
			vars->key->tab = 0;
		else
			vars->key->tab = 1;
	}
	if (key == 53)
		close_window(vars);
	return (1);
}
