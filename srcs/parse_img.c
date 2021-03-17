/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_img.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 13:02:55 by ikole          #+#    #+#                */
/*   Updated: 2020/03/06 11:44:13 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	check_img_too(t_vars *vars, char *line, int side, char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (*line || fd == -1)
		ft_error(vars, "Invalid texture path!\n");
	if (close(fd) == -1)
		ft_error(vars, "Whoops, trying to close texture failed!\n");
	vars->texture[side]->img = mlx_xpm_file_to_image(vars->mlx, path,
	&vars->texture[side]->width, &vars->texture[side]->height);
	if (!vars->texture[side]->img)
		ft_error(vars, "Whoops, creating the texture failed!\n");
	vars->texture[side]->addr = mlx_get_data_addr(vars->texture[side]->img,
	&vars->texture[side]->bits_per_pixel, &vars->texture[side]->line_length,
	&vars->texture[side]->endian);
	free(path);
}

void		check_img(t_vars *vars, char *line, int side, int i)
{
	int		j;
	char	*path;

	if ((side == 5 || side == 6) && (vars->map->ceiling != -1 ||
	vars->map->floor != -1))
		ft_error(vars, "You have specified a color already for\
		floor or celing!\n");
	if (vars->texture[side]->width)
		ft_error(vars, "Whoops you seem to have a texture redefinition!\n");
	while (line[i] == ' ')
		i++;
	j = i;
	while (line[j])
		j++;
	path = ft_substr(line, i, j - i);
	if (!path)
		ft_error(vars, "whoops, a malloc went wrong!\n");
	check_img_too(vars, line + j, side, path);
}

static void	check_sprite_too(t_vars *vars, char *line, int count, char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (*line || fd == -1)
		ft_error(vars, "Invalid sprite path!\n");
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
}

void		check_sprite(t_vars *vars, char *line, int count, int i)
{
	int			j;
	char		*path;

	if (vars->sprite[count]->width)
		ft_error(vars, "Whoops you seem to have a sprite redefinition!\n");
	while (line[i] == ' ')
		i++;
	j = i;
	while (line[j])
		j++;
	path = ft_substr(line, i, j - i);
	if (!path)
		ft_error(vars, "whoops, a malloc went wrong!\n");
	check_sprite_too(vars, line + j, count, path);
}

void		init_sprite_pos(t_vars *vars, int m_index, int type)
{
	int		j;
	double	**sprite_pos;

	j = 0;
	vars->sprite_count++;
	sprite_pos = malloc(sizeof(double*) * vars->sprite_count);
	if (!sprite_pos)
		ft_error(vars, "mallocing sprite_pos fialed!\n");
	while (j < vars->sprite_count - 1)
	{
		sprite_pos[j] = vars->sprite_pos[j];
		j++;
	}
	sprite_pos[j] = malloc(sizeof(double) * 4);
	if (!sprite_pos[j])
		ft_error(vars, "mallocing sprite_pos[j] fialed!\n");
	sprite_pos[j][0] = m_index + 0.5;
	sprite_pos[j][1] = vars->map->m_height + 0.5;
	sprite_pos[j][2] = 1;
	sprite_pos[j][3] = type;
	if (vars->sprite_count > 1)
		free(vars->sprite_pos);
	vars->sprite_pos = sprite_pos;
}
