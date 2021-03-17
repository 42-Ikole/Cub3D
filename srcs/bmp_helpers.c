/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp_helpers.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 09:16:57 by ikole          #+#    #+#                */
/*   Updated: 2020/03/03 09:17:07 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	*ft_memset(void *ptr, int x, size_t n)
{
	size_t	i;
	char	*c;

	i = 0;
	c = ptr;
	while (i != n)
	{
		c[i] = (char)x;
		i++;
	}
	return (ptr);
}
