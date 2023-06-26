/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:06:56 by kyacini           #+#    #+#             */
/*   Updated: 2023/06/26 06:18:09 by skhali           ###   ########.fr       */
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

int return_dead_state(t_philo *p)
{
	int state;

	state = 1;
	pthread_mutex_lock(&(p->fac->mutex_dead));
	state = p->fac->is_dead;
	pthread_mutex_unlock(&(p->fac->mutex_dead));
	return state;
}

int return_time_state(t_philo *p)
{
	int time;

	pthread_mutex_lock(&(p->mutex_tsm));
	time = p->time_since_meal;
	pthread_mutex_unlock(&(p->mutex_tsm));
	return time;
}

int return_nb_eat(t_philo *p)
{
	int eat;

	pthread_mutex_lock(&(p->mutex_eat));
	eat = p->nb_eat;
	pthread_mutex_unlock(&(p->mutex_eat));
	return eat;
}