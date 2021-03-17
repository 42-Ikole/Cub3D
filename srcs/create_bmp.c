/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_bmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 14:37:05 by ikole          #+#    #+#                */
/*   Updated: 2020/03/04 09:15:28 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	size_converter(unsigned char *header, int size)
{
	int	i;
	int	shift;
	int	and;

	i = 0;
	shift = 0;
	and = 255;
	while (i < 4)
	{
		header[i] = (size & and) >> shift;
		shift += 8;
		and <<= 8;
		i++;
	}
}

void	bitmap_header(t_vars *vars, int fd, int paddy)
{
	unsigned char	header[54];
	int				size;

	ft_memset(header, 0, 54);
	size_converter(header + 0, 66);
	size_converter(header + 1, 77);
	size = 54 + (3 * (vars->screen_width + paddy) * vars->screen_height);
	size_converter(header + 2, size);
	size_converter(header + 10, 54);
	size_converter(header + 14, 40);
	size_converter(header + 18, vars->screen_width);
	size_converter(header + 22, vars->screen_height);
	size_converter(header + 26, 1);
	size_converter(header + 28, 24);
	if (write(fd, header, 54) == -1)
		ft_error(NULL, "Writing to the fluffy bmp image failed!!\n");
}

void	set_color(t_vars *vars, int fd, int paddy)
{
	char	*color;
	int		x;
	int		y;

	y = vars->screen_height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < vars->screen_width)
		{
			color = vars->img[0]->addr + (y *
			vars->img[0]->line_length + x *
			(vars->img[0]->bits_per_pixel / 8));
			if (write(fd, color, 3) == -1)
				ft_error(NULL, "WHOOPS, Writing to the image failed!\n");
			x++;
		}
		if (write(fd, "\0\0\0\0", paddy) == -1)
			ft_error(NULL, "Writing padding failed!\n");
		y--;
	}
}

void	bitmapper(t_vars *vars)
{
	int	fd;
	int paddy;

	paddy = (4 - ((3 * vars->screen_width) % 4)) % 4;
	fd = open("A_REALLY_FLUFFY_BMP_IMAGE_OF_MY_CUB3D_WHICH_IS_ALSO_FLUFFY.bmp",
	O_RDWR | O_CREAT | O_TRUNC, 0755);
	if (fd == -1)
		ft_error(NULL, "WHOOPSIEDAYSY, Creating a really fluffy bmp image \
		file failed!\n");
	bitmap_header(vars, fd, paddy);
	set_color(vars, fd, paddy);
	if (close(fd) == -1)
		ft_error(NULL, "Closing your really fluffy bmp image failed!!!!\n");
}

void	ft_save(t_vars *vars, char **str)
{
	vars->save = 1;
	parser(str, vars);
	init_img(vars);
	ft_makescene(vars);
	bitmapper(vars);
	exit(0);
}
