/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:36:51 by kyacini           #+#    #+#             */
/*   Updated: 2023/06/27 22:51:07 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	mutex_detroyer(t_fac *params)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&(params->mutex_dead));
	pthread_mutex_destroy(&(params->mutex_print));
	while (i < params->number_of_philosophers)
	{
		pthread_mutex_destroy(&(params->fork[i]));
		i++;
	}
}

void	mutex_detroyer_philo(t_philo **p)
{
	int	i;
	int	n;

	i = 0;
	n = p[0]->fac->number_of_philosophers;
	while (i < n)
	{
		pthread_mutex_destroy(&(p[i]->mutex_tsm));
		pthread_mutex_destroy(&(p[i]->mutex_eat));
		i++;
	}
}

void	free_philo_tab(t_philo **philo, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		free(philo[i]);
		i++;
	}
	free(philo);
}

void	ft_usleep(t_philo *p, int time)
{
	int	n;
	int	i;

	i = 0;
	if (time < 0)
		time *= -1;
	n = time / 50000;
	while (i < n)
	{
		if (!return_dead_state(p))
			usleep(50000);
		else
			break ;
		i++;
	}
	if (!return_dead_state(p))
		usleep(time % 50000);
}
