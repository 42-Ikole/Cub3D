/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 14:16:10 by ikole          #+#    #+#                */
/*   Updated: 2020/03/07 10:35:18 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static int	realloc_map(t_vars *vars, char ***map, int x, int y)
{
	map[0] = malloc(sizeof(char *) * vars->map->m_height + 1);
	if (!map)
		ft_error(vars, "Whooops, malloccing the map  failed!\n");
	while (y < vars->map->m_height)
	{
		map[0][y] = malloc(sizeof(char) * vars->map->m_width + 1);
		if (!map[0][y])
			ft_error(vars, "Whoops, mallocing a row in the map failed!\n");
		x = 0;
		while (x < vars->map->m_width)
		{
			map[0][y][x] = '0';
			x++;
		}
		map[0][y][x] = '\0';
		x = 0;
		while (vars->map->map[y][x])
		{
			map[0][y][x] = vars->map->map[y][x];
			x++;
		}
		free(vars->map->map[y]);
		y++;
	}
	return (y);
}

static int	map_status(t_vars *vars, char **line)
{
	int i;

	i = 0;
	if (vars->map->status == 2)
		ft_error(vars, "Whoops, looks like you have an empty line in\
		your map!\n");
	if (!line[0][0])
		vars->map->status = 2;
	else
		vars->map->status = 1;
	while (line[0][i])
		i++;
	return (i);
}

static void	fill_map_two(t_vars *vars, char line, int m_index, int y)
{
	if (line == '3')
	{
		init_sprite_pos(vars, m_index, 1);
		if (!vars->sprite[1]->width)
			ft_error(vars, "You specified a specified a second sprite in\
			your map but not in the definition!\n");
		vars->map->map[y][m_index] = '3';
	}
	else if (line == 'N' && !vars->pos->pos_x)
		spawn_north(vars, m_index, y);
	else if (line == 'E' && !vars->pos->pos_x)
		spawn_east(vars, m_index, y);
	else if (line == 'S' && !vars->pos->pos_x)
		spawn_south(vars, m_index, y);
	else if (line == 'W' && !vars->pos->pos_x)
		spawn_west(vars, m_index, y);
	else
		ft_error(vars, "This is not a valid map!\n");
}

static void	fill_map(t_vars *vars, char *line, int m_index, int y)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			vars->map->map[y][i] = '8';
		else if (line[i] == '1')
			vars->map->map[y][m_index] = '1';
		else if (line[i] == '0')
			vars->map->map[y][m_index] = '0';
		else if (line[i] == '2')
		{
			init_sprite_pos(vars, m_index, 0);
			vars->map->map[y][m_index] = '2';
		}
		else
			fill_map_two(vars, line[i], m_index, y);
		i++;
		m_index++;
	}
	vars->map->map[y][m_index] = '\0';
}

void		check_map(t_vars *vars, char *line)
{
	int		i;
	int		y;
	char	**map;

	y = 0;
	i = map_status(vars, &line);
	if (i > vars->map->m_width)
		vars->map->m_width = i;
	if (vars->map->m_height > 0)
	{
		y = realloc_map(vars, &map, 0, 0);
		free(vars->map->map);
		vars->map->map = map;
	}
	vars->map->map[y] = malloc(sizeof(int) * vars->map->m_width);
	if (!vars->map->map[y])
		ft_error(vars, "Whoops, Mallocing the last new row of your\
		map failed!\n");
	fill_map(vars, line, 0, y);
	vars->map->m_height++;
}
