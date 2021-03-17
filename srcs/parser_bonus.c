/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_bonus.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 19:58:04 by ikole          #+#    #+#                */
/*   Updated: 2020/03/07 11:17:20 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		ft_atoi(char *str)
{
	long res;
	long sgn;

	res = 0;
	sgn = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == 45)
		sgn = -1;
	if (*str == 43 || *str == 45)
		str++;
	while (*str >= 48 && *str <= 57)
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return ((int)(res * sgn));
}

void	linecheck(t_vars *vars, char *line, int i)
{
	if (line[i] == 'S')
		check_sprite(vars, line, 0, i + 1);
	else if (line[i] == 'C' && line[i + 1] == 'E')
		check_img(vars, line, 4, i + 2);
	else if (line[i] == 'F' && line[i + 1] == 'O')
		check_img(vars, line, 5, i + 2);
	else if (line[i] == 'F')
		check_color(vars, line, 'F', i + 1);
	else if (line[i] == 'C')
		check_color(vars, line, 'C', i + 1);
	else if (vars->screen_width != -1 && vars->texture[0]->width &&
	vars->texture[1]->width && vars->texture[2]->width &&
	vars->texture[3]->width && ((vars->map->floor != -1 &&
	vars->map->ceiling != -1) || (vars->texture[4]->width &&
	vars->texture[5]->width)) && vars->sprite[0]->width)
		check_map(vars, line);
	else if (vars->map->m_width == -1)
		ft_error(vars, "Map is not the last element or not all\
		arguments are given!\n");
}

void	checkline(t_vars *vars, char *line)
{
	int i;

	i = 0;
	if (line[i] == '\0' && vars->map->status != 1)
		return ;
	while (line[i] == ' ')
		i++;
	if (i > 0 && line[i] == '\0')
		ft_error(vars, "WHOA THERE, FAKE empty line!\n");
	else if (line[i] == 'R')
		check_res(vars, line, i + 1);
	else if (line[i] == 'N' && line[i + 1] == 'O')
		check_img(vars, line, 2, i + 2);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		check_img(vars, line, 1, i + 2);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		check_img(vars, line, 0, i + 2);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		check_img(vars, line, 3, i + 2);
	else if (line[i] == 'A')
		check_animation(vars, line, 1, i + 1);
	else
		linecheck(vars, line, i);
	i++;
}

void	readline(t_vars *vars, char **args)
{
	int		ret;
	char	*line;
	int		fd;

	ret = 1;
	fd = open(*args, O_RDONLY);
	if (fd == -1)
		ft_error(vars, "Invalid .cub file!\n");
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			ft_error(vars, "Whoops, something went wrong reading\
			from the file!\n");
		checkline(vars, line);
		free(line);
	}
	if (close(fd) == -1)
		ft_error(vars, "failed to close .cub file!\n");
}

int		parser(char **args, t_vars *vars)
{
	int	i;
	int j;

	i = 0;
	args++;
	j = ft_strlen(*args);
	if (j < 4 || ft_strncmp(*args + (j - 4), ".cub", 4))
		ft_error(vars, "invalid file extension, use .cub instead!\n");
	readline(vars, args);
	vars->sprite_order = malloc(sizeof(int) * vars->sprite_count);
	if (!vars->sprite_order)
		ft_error(vars, "Mallocing for sprite order failed!\n");
	if (vars->sprite_count > 0)
	{
		vars->sprite_distance = malloc(sizeof(int) * vars->sprite_count);
		if (!vars->sprite_count)
			ft_error(vars, "Mallocing for sprite_distance failed!\n");
	}
	vars->map->m_height--;
	vars->map->m_width--;
	validate_map(vars);
	return (1);
}
