/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:06:56 by kyacini           #+#    #+#             */
/*   Updated: 2023/06/24 17:27:46 by skhali           ###   ########.fr       */
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

void mutex_print(char *str, t_philo *p)
{
	pthread_mutex_lock(&(p->fac->mutex_print));
    printf("%d %d %s\n", get_time() - p->fac->start, p->num, str);
    pthread_mutex_unlock(&(p->fac->mutex_print));
}
