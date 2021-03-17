/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 15:29:19 by ikole          #+#    #+#                */
/*   Updated: 2020/03/06 13:53:40 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	damage(t_vars *vars, int x, int y)
{
	int i;

	vars->health -= 5;
	vars->map->map[y][x] = '0';
	i = 0;
	while (i < vars->sprite_count)
	{
		if ((int)vars->sprite_pos[i][0] == x &&
		(int)vars->sprite_pos[i][1] == y)
			vars->sprite_pos[i][2] = -1;
		i++;
	}
	if (system("say -r 400 woof &") == -1)
		ft_error(vars, "WHOA, say failed!\n");
}

void	move_forward(t_vars *vars, double movespeed)
{
	if (vars->map->map[(int)vars->pos->pos_y]
		[(int)(vars->pos->pos_x + vars->pos->dir_x * movespeed)] == '0')
		vars->pos->pos_x += vars->pos->dir_x * movespeed;
	else if (vars->map->map[(int)vars->pos->pos_y]
	[(int)(vars->pos->pos_x + vars->pos->dir_x * movespeed)] == '3')
		damage(vars, (int)(vars->pos->pos_x + vars->pos->dir_x * movespeed),
		(int)vars->pos->pos_y);
	else if (vars->map->map[(int)vars->pos->pos_y]
	[(int)(vars->pos->pos_x + vars->pos->dir_x * movespeed)] == '2')
		vars->points += 5;
	if (vars->map->map[(int)(vars->pos->pos_y + vars->pos->dir_y * movespeed)]
		[(int)vars->pos->pos_x] == '0')
		vars->pos->pos_y += vars->pos->dir_y * movespeed;
	else if (vars->map->map[(int)(vars->pos->pos_y + vars->pos->dir_y *
		movespeed)][(int)vars->pos->pos_x] == '3')
		damage(vars, (int)vars->pos->pos_x,
		(int)(vars->pos->pos_y + vars->pos->dir_y * movespeed));
	else if (vars->map->map[(int)(vars->pos->pos_y + vars->pos->dir_y *
		movespeed)][(int)vars->pos->pos_x] == '2')
		vars->points += 5;
}

void	move_left(t_vars *vars, double movespeed)
{
	if (vars->map->map[(int)vars->pos->pos_y]
		[(int)(vars->pos->pos_x - vars->pos->dir_y * -movespeed)] == '0')
		vars->pos->pos_x -= vars->pos->dir_y * -movespeed;
	else if (vars->map->map[(int)vars->pos->pos_y]
		[(int)(vars->pos->pos_x - vars->pos->dir_y * -movespeed)] == '3')
		damage(vars, (int)(vars->pos->pos_x - vars->pos->dir_y * -movespeed),
		(int)vars->pos->pos_y);
	else if (vars->map->map[(int)vars->pos->pos_y]
		[(int)(vars->pos->pos_x - vars->pos->dir_y * -movespeed)] == '2')
		vars->points += 5;
	if (vars->map->map[(int)(vars->pos->pos_y - vars->pos->dir_x * movespeed)]
		[(int)vars->pos->pos_x] == '0')
		vars->pos->pos_y -= vars->pos->dir_x * movespeed;
	else if (vars->map->map[(int)(vars->pos->pos_y - vars->pos->dir_x *
		movespeed)][(int)vars->pos->pos_x] == '3')
		damage(vars, (int)vars->pos->pos_x,
		(int)(vars->pos->pos_y - vars->pos->dir_x * movespeed));
	else if (vars->map->map[(int)(vars->pos->pos_y - vars->pos->dir_x *
		movespeed)][(int)vars->pos->pos_x] == '2')
		vars->points += 5;
}

void	move_back(t_vars *vars, double movespeed)
{
	if (vars->map->map[(int)vars->pos->pos_y]
		[(int)(vars->pos->pos_x - vars->pos->dir_x * movespeed)] == '0')
		vars->pos->pos_x -= vars->pos->dir_x * movespeed;
	else if (vars->map->map[(int)vars->pos->pos_y]
		[(int)(vars->pos->pos_x - vars->pos->dir_x * movespeed)] == '3')
		damage(vars, (int)(vars->pos->pos_x - vars->pos->dir_x * movespeed),
		(int)vars->pos->pos_y);
	else if (vars->map->map[(int)vars->pos->pos_y]
		[(int)(vars->pos->pos_x - vars->pos->dir_x * movespeed)] == '2')
		vars->points += 5;
	if (vars->map->map[(int)(vars->pos->pos_y - vars->pos->dir_y * movespeed)]
		[(int)vars->pos->pos_x] == '0')
		vars->pos->pos_y -= vars->pos->dir_y * movespeed;
	else if (vars->map->map[(int)(vars->pos->pos_y - vars->pos->dir_y *
		movespeed)][(int)vars->pos->pos_x] == '3')
		damage(vars, (int)vars->pos->pos_x,
		(int)(vars->pos->pos_y - vars->pos->dir_y * movespeed));
	else if (vars->map->map[(int)(vars->pos->pos_y - vars->pos->dir_y *
		movespeed)][(int)vars->pos->pos_x] == '2')
		vars->points += 5;
}

void	move_right(t_vars *vars, double movespeed)
{
	if (vars->map->map[(int)vars->pos->pos_y]
		[(int)(vars->pos->pos_x + vars->pos->dir_y * -movespeed)] == '0')
		vars->pos->pos_x += vars->pos->dir_y * -movespeed;
	else if (vars->map->map[(int)vars->pos->pos_y]
		[(int)(vars->pos->pos_x + vars->pos->dir_y * -movespeed)] == '3')
		damage(vars, (int)(vars->pos->pos_x + vars->pos->dir_y * -movespeed),
		(int)vars->pos->pos_y);
	else if (vars->map->map[(int)vars->pos->pos_y]
		[(int)(vars->pos->pos_x + vars->pos->dir_y * -movespeed)] == '2')
		vars->points += 5;
	if (vars->map->map[(int)(vars->pos->pos_y + vars->pos->dir_x * movespeed)]
		[(int)vars->pos->pos_x] == '0')
		vars->pos->pos_y += vars->pos->dir_x * movespeed;
	else if (vars->map->map[(int)(vars->pos->pos_y + vars->pos->dir_x *
		movespeed)][(int)vars->pos->pos_x] == '3')
		damage(vars, (int)vars->pos->pos_x,
		(int)(vars->pos->pos_y + vars->pos->dir_x * movespeed));
	else if (vars->map->map[(int)(vars->pos->pos_y + vars->pos->dir_x *
		movespeed)][(int)vars->pos->pos_x] == '2')
		vars->points += 5;
}
