/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:06:56 by kyacini           #+#    #+#             */
/*   Updated: 2023/06/23 19:09:23 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "philo.h"
void	free_double_char(char	**str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}