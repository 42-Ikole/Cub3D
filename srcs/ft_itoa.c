/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/04 18:32:32 by ikole          #+#    #+#                */
/*   Updated: 2020/03/05 09:11:58 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static int		ft_ilen(int n)
{
	int i;

	i = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n > 9)
	{
		i++;
		n /= 10;
	}
	return (i + 1);
}

static	char	*ft_itoa_too(int calc, int n, int i, char *ret)
{
	if (calc < 0)
	{
		ret[0] = '-';
		calc *= -1;
	}
	i--;
	while (calc > 0)
	{
		ret[i] = (calc % 10) + 48;
		calc = calc / 10;
		i--;
	}
	if (n == 0)
		ret[0] = '0';
	return (ret);
}

char			*ft_itoa(int n)
{
	char	*ret;
	int		i;
	int		calc;

	i = ft_ilen(n);
	calc = n;
	ret = malloc(sizeof(char) * i + 1);
	if (!ret)
		ft_error(NULL, "WHOA, malloc in itoa failed!\n");
	if (calc == -2147483648)
	{
		calc = -214748364;
		ret[i - 1] = '8';
		i--;
	}
	ret[(n == -2147483648) ? i + 1 : i] = '\0';
	return (ft_itoa_too(calc, n, i, ret));
}
