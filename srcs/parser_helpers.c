/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_helpers.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 13:00:03 by ikole          #+#    #+#                */
/*   Updated: 2020/03/11 10:00:53 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		ft_error(t_vars *vars, char *str)
{
	if (vars && vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	write(2, "\e[0;31mError\e[0m\n\e[0;33m", 24);
	write(2, str, ft_strlen(str));
	exit(-1);
}

char	*ft_strdup(const char *str)
{
	int		len;
	char	*dup;

	len = 0;
	while (str[len])
		len++;
	dup = malloc(sizeof(char) * len + 1);
	if (!dup)
		ft_error(NULL, "Whoops strdup malloc failed!\n");
	len = 0;
	while (str[len])
	{
		dup[len] = str[len];
		len++;
	}
	dup[len] = '\0';
	return (dup);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	int		i;
	size_t	j;

	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		ft_error(NULL, "whoops, substr malloc failed!\n");
	i = start;
	j = 0;
	while (s[i] != '\0' && j != len && (unsigned int)ft_strlen(s) > start)
	{
		substr[j] = s[i];
		i++;
		j++;
	}
	substr[j] = '\0';
	return (substr);
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*one;
	unsigned char	*two;

	if (n == 0)
		return (0);
	i = 0;
	one = (unsigned char*)s1;
	two = (unsigned char*)s2;
	while (one[i] == two[i] && one[i] && two[i] && i < n - 1)
		i++;
	return (one[i] - two[i]);
}
