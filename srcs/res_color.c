/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   res_color.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 17:36:51 by ikole          #+#    #+#                */
/*   Updated: 2020/03/04 15:05:39 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void		check_res_two(t_vars *vars, char *line, int i)
{
	int sw;
	int sh;

	while (line[i] >= '0' && line[i] <= '9')
		i++;
	if (line[i] != '\0')
		ft_error(vars, "WHOA, invalid screenheight!\n");
	if (vars->screen_width <= 0 || vars->screen_height <= 0)
		ft_error(vars, "Whoops, negative screensize is not allowed or\
	possible for that matter!\n");
	mlx_get_screen_size(vars->mlx, &sw, &sh);
	if (vars->screen_width > sw && !vars->save)
		vars->screen_width = sw;
	if (vars->screen_height > sh + 45 && !vars->save)
		vars->screen_height = sh - 45;
	vars->z_buffer = malloc(sizeof(double) * vars->screen_width);
	if (!vars->z_buffer)
		ft_error(vars, "Whoops, mallocing the Z_buffer failed!\n");
}

void		check_res(t_vars *vars, char *line, int i)
{
	if (vars->screen_height != -1)
		ft_error(vars, "you have already given a resolution!\n");
	while (line[i] == ' ')
		i++;
	if (line[i] >= '0' && line[i] <= '9')
	{
		vars->screen_width = ft_atoi(line + i);
		while (line[i] >= '0' && line[i] <= '9')
			i++;
	}
	else
		ft_error(vars, "Invalid screen width!\n");
	while (line[i] == ' ')
		i++;
	if (line[i] >= '0' && line[i] <= '9')
		vars->screen_height = ft_atoi(line + i);
	else
		ft_error(vars, "Invalid screen height!\n");
	check_res_two(vars, line, i);
}

static void	check_color_two(t_vars *vars, char *line, char c, int rgb[3])
{
	int i;

	i = 0;
	if (line[i] != ',')
		ft_error(vars, "whoops something isn't right in your green value!\n");
	i++;
	if (!(line[i] >= '0' && line[i] <= '9'))
		ft_error(vars, "You have not specified a value for blue!\n");
	rgb[2] = ft_atoi(line + i);
	if (rgb[2] < 0 || rgb[2] > 255)
		ft_error(vars, "Invalid value for blue!\n");
	while ((line[i] >= '0' && line[i] <= '9') || line[i] == ' ')
		i++;
	if (line[i] != '\0')
		ft_error(vars, "You put something after you blue value!\n");
	if (c == 'C' && vars->map->ceiling == -1)
		vars->map->ceiling = (rgb[0] << 16) + (rgb[1] << 8) + rgb[2];
	else if (c == 'C')
		ft_error(vars, "Whoops, ceiling color is already given!\n");
	else if (c == 'F' && vars->map->floor == -1)
		vars->map->floor = (rgb[0] << 16) + (rgb[1] << 8) + rgb[2];
	else
		ft_error(vars, "Whoops, floor color is already given!\n");
}

void		check_color(t_vars *vars, char *line, char c, int i)
{
	int rgb[3];

	if (vars->texture[4]->width || vars->texture[5]->width)
		ft_error(vars, "You have specified a texture for floor or ceiling!\n");
	while (line[i] == ' ')
		i++;
	if (!(line[i] >= '0' && line[i] <= '9'))
		ft_error(vars, "You have not specified a value for red!\n");
	rgb[0] = ft_atoi(line + i);
	if (rgb[0] < 0 || rgb[0] > 255)
		ft_error(vars, "Invalid value for red!\n");
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	if (line[i] != ',')
		ft_error(vars, "whoops something isn't right in your red value!\n");
	i++;
	if (!(line[i] >= '0' && line[i] <= '9'))
		ft_error(vars, "You have not specified a value for green!\n");
	rgb[1] = ft_atoi(line + i);
	if (rgb[1] < 0 || rgb[1] > 255)
		ft_error(vars, "Invalid value for green!\n");
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	check_color_two(vars, line + i, c, rgb);
}
