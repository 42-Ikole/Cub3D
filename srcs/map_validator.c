/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validator.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/13 08:59:21 by ikole          #+#    #+#                */
/*   Updated: 2020/03/03 20:51:30 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	map_validator(t_vars *vars, int x, int y)
{
	if (x == 0 || x == vars->map->m_width || y == 0 || y == vars->map->m_height
	|| vars->map->map[y][x] == '8')
		ft_error(NULL, "Invalid map, not boxed in by walls!\n");
	else if (vars->map->map[y][x] == '0')
		vars->map->map[y][x] = '4';
	else if (vars->map->map[y][x] == '2')
		vars->map->map[y][x] = '5';
	if (vars->map->map[y][x + 1] == '0' || vars->map->map[y][x + 1] == '2' ||
	vars->map->map[y][x + 1] == '8')
		map_validator(vars, x + 1, y);
	if (vars->map->map[y][x - 1] == '0' || vars->map->map[y][x - 1] == '2' ||
	vars->map->map[y][x - 1] == '8')
		map_validator(vars, x - 1, y);
	if (vars->map->map[y + 1][x] == '0' || vars->map->map[y + 1][x] == '2' ||
	vars->map->map[y + 1][x] == '8')
		map_validator(vars, x, y + 1);
	if (vars->map->map[y - 1][x] == '0' || vars->map->map[y - 1][x] == '2' ||
	vars->map->map[y - 1][x] == '8')
		map_validator(vars, x, y - 1);
	map_validator_diagonal(vars, x, y);
}

void	map_validator_diagonal(t_vars *vars, int x, int y)
{
	if (vars->map->map[y + 1][x + 1] == '0' ||
	vars->map->map[y + 1][x + 1] == '2' || vars->map->map[y + 1][x + 1] == '8')
		map_validator(vars, x + 1, y + 1);
	if (vars->map->map[y + 1][x - 1] == '0' ||
	vars->map->map[y + 1][x - 1] == '2' || vars->map->map[y + 1][x - 1] == '8')
		map_validator(vars, x - 1, y + 1);
	if (vars->map->map[y - 1][x + 1] == '0' ||
	vars->map->map[y - 1][x + 1] == '2' || vars->map->map[y - 1][x + 1] == '8')
		map_validator(vars, x + 1, y - 1);
	if (vars->map->map[y - 1][x - 1] == '0' ||
	vars->map->map[y - 1][x - 1] == '2' || vars->map->map[y - 1][x - 1] == '8')
		map_validator(vars, x - 1, y - 1);
}

void	validate_map(t_vars *vars)
{
	int x;
	int y;

	if (!vars->pos->pos_x || !vars->pos->pos_y)
		ft_error(vars, "No spawn position given!\n");
	map_validator(vars, vars->pos->pos_x, vars->pos->pos_y);
	y = 0;
	while (y < vars->map->m_height)
	{
		x = 0;
		while (x <= vars->map->m_width)
		{
			if (vars->map->map[y][x] == '4')
				vars->map->map[y][x] = '0';
			else if (vars->map->map[y][x] == '5')
				vars->map->map[y][x] = '2';
			x++;
		}
		y++;
	}
}
