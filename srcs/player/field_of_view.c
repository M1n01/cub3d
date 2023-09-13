/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_of_view.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:59:36 by minabe            #+#    #+#             */
/*   Updated: 2023/09/13 16:16:16 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_game *game, t_ray *ray);
static void	init_step_and_side_distance(t_game *game, t_ray *ray);
static void	degital_differential_analyzer(t_game *game, t_ray *ray);
static void	calculate_perpendicular_wall_distance(t_ray *ray);

void	calculate_ray(t_game *game, t_ray *ray)
{
	init_ray(game, ray);
	init_step_and_side_distance(game, ray);
	degital_differential_analyzer(game, ray);
	calculate_perpendicular_wall_distance(ray);
}

static void	init_ray(t_game *game, t_ray *ray)
{
	double	camera_x;

	camera_x = 2 * ray->x / (double)WIN_WIDTH - 1;
	ray->map.x = game->player.pos.x;
	ray->map.y = game->player.pos.y;
	ray->dir.x = game->player.dir.x + game->player.plane.x * camera_x;
	ray->dir.y = game->player.dir.y + game->player.plane.y * camera_x;
	if (game->player.dir.x == 0)
		ray->delta_distance.x = DBL_MAX;
	else
		ray->delta_distance.x = fabs(1 / ray->dir.x);
	if (game->player.dir.y == 0)
		ray->delta_distance.y = DBL_MAX;
	else
		ray->delta_distance.y = fabs(1 / ray->dir.y);
	ray->hit = false;
	ray->perpendicular_wall_distance = 0;
}

static void	init_step_and_side_distance(t_game *game, t_ray *ray)
{
	if (game->player.dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_distance.x = (game->player.pos.x - ray->map.x) * ray->delta_distance.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_distance.x = (ray->map.x + 1.0 - game->player.pos.x) * ray->delta_distance.x;
	}
	if (game->player.dir.y < 0)
	{
		ray->step.y = 1;
		ray->side_distance.y = (game->player.pos.y - ray->map.y) * ray->delta_distance.y;
	}
	else
	{
		ray->step.y = -1;
		ray->side_distance.y = (ray->map.y + 1.0 - game->player.pos.y) * ray->delta_distance.y;
	}
}

static void	degital_differential_analyzer(t_game *game, t_ray *ray)
{
	while (ray->hit == false)
	{
		if (ray->side_distance.x < ray->side_distance.y)
		{
			ray->side_distance.x += ray->delta_distance.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_distance.y += ray->delta_distance.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (game->map->map[(int)ray->map.y][(int)ray->map.x] == '1')
			ray->hit = true;
	}
}

static void	calculate_perpendicular_wall_distance(t_ray *ray)
{
	if (FISH_EYE_EFFECT)
	{
		if (ray->side == 0)
			ray->perpendicular_wall_distance = (ray->map.x - ray->pos.x + (1 - ray->step.x) / 2) / ray->dir.x;
		else
			ray->perpendicular_wall_distance = (ray->map.y - ray->pos.y + (1 - ray->step.y) / 2) / ray->dir.y;
		return ;
	}
	if (ray->side == 0)
		ray->perpendicular_wall_distance = ray->side_distance.x - ray->delta_distance.x;
	else
		ray->perpendicular_wall_distance = ray->side_distance.y - ray->delta_distance.y;
}