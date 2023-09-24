/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 19:22:06 by rtakashi          #+#    #+#             */
/*   Updated: 2023/09/24 19:26:13 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_2d(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		ft_free(strs[i]);
		i++;
	}
	ft_free(strs);
	return ;
}