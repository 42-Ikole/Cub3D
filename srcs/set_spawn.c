/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_spawn.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/03 14:24:52 by ikole          #+#    #+#                */
/*   Updated: 2020/03/03 14:29:10 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	spawn_north(t_vars *vars, int m_index, int y)
{
	vars->pos->pos_x = (double)m_index + 0.5;
	vars->pos->pos_y = (double)vars->map->m_height + 0.5;
	vars->map->map[y][m_index] = '0';
	vars->pos->dir_x = 0;
	vars->pos->dir_y = -1;
	vars->pos->plane_x = 0.66;
	vars->pos->plane_y = 0;
}

void	spawn_east(t_vars *vars, int m_index, int y)
{
	vars->pos->pos_x = (double)m_index + 0.5;
	vars->pos->pos_y = (double)vars->map->m_height + 0.5;
	vars->map->map[y][m_index] = '0';
	vars->pos->dir_x = 1;
	vars->pos->dir_y = 0;
	vars->pos->plane_x = 0;
	vars->pos->plane_y = 0.66;
}

void	spawn_south(t_vars *vars, int m_index, int y)
{
	vars->pos->pos_x = (double)m_index + 0.5;
	vars->pos->pos_y = (double)vars->map->m_height + 0.5;
	vars->map->map[y][m_index] = '0';
	vars->pos->dir_x = 0;
	vars->pos->dir_y = 1;
	vars->pos->plane_x = -0.66;
	vars->pos->plane_y = 0;
}

void	spawn_west(t_vars *vars, int m_index, int y)
{
	vars->pos->pos_x = (double)m_index + 0.5;
	vars->pos->pos_y = (double)vars->map->m_height + 0.5;
	vars->map->map[y][m_index] = '0';
	vars->pos->dir_x = -1;
	vars->pos->dir_y = 0;
	vars->pos->plane_x = 0;
	vars->pos->plane_y = -0.66;
}
