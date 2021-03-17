/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_animation_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 09:56:56 by ikole          #+#    #+#                */
/*   Updated: 2020/03/05 19:01:21 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	check_last_line(t_vars *vars, char *line)
{
	while (*line == ' ')
		line++;
	if (*line != '\0')
		ft_error(vars, "Too many arguments for animation!\n");
}

static void	check_animation_too(t_vars *vars, char *line, int count, char *path)
{
	int fd;

	if (!*line && count != 3)
		ft_error(vars, "Not enough sprites given, need three for animation!\n");
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_error(vars, "Invalid path for animation!\n");
	if (close(fd) == -1)
		ft_error(vars, "Whoops, closing sprite file failed!\n");
	vars->sprite[count]->img = mlx_xpm_file_to_image(vars->mlx, path,
	&vars->sprite[count]->width, &vars->sprite[count]->height);
	if (!vars->sprite[count]->img)
		ft_error(vars, "Whoops, creating the texture failed!\n");
	vars->sprite[count]->addr = mlx_get_data_addr(vars->sprite[count]->img,
	&vars->sprite[count]->bits_per_pixel, &vars->sprite[count]->line_length,
	&vars->sprite[count]->endian);
	free(path);
	if (count < 3)
		check_animation(vars, line, count + 1, 0);
	else
		check_last_line(vars, line);
}

void		check_animation(t_vars *vars, char *line, int count, int i)
{
	int			j;
	char		*path;

	if (vars->sprite[count]->width)
		ft_error(vars, "Whoops you seem to have a sprite redefinition!\n");
	while (line[i] == ' ')
		i++;
	j = i;
	while (line[j] != ' ' && line[j])
		j++;
	if (j > 4 && ft_strncmp(line + (j - 4), ".xpm", 4))
		ft_error(vars, "invalid file extension, use .xpm \
		for textures and sprites!\n");
	path = ft_substr(line, i, j - i);
	if (!path)
		ft_error(vars, "whoops, a malloc went wrong!\n");
	while (line[j] == ' ')
		j++;
	check_animation_too(vars, line + j, count, path);
}
