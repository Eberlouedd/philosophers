/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:36:25 by kyacini           #+#    #+#             */
/*   Updated: 2023/06/27 22:11:22 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

t_philo	**create_philo(t_fac *fac)
{
	int		i;
	t_philo	**philo;

	i = 0;
	philo = malloc(fac->number_of_philosophers * sizeof(t_philo *));
	while (i < fac->number_of_philosophers)
	{
		philo[i] = create_philosophe(fac, i);
		if (!philo[i])
			return (NULL);
		i++;
	}
	return (philo);
}

void	*philo_essence(void *args)
{
	t_philo	*p;

	p = (t_philo *) args;
	even_thinking(p);
	while (!return_dead_state(p)
		&& (p->nb_eat < p->fac->has_to_eat
			|| p->fac->has_to_eat == -1))
	{
		if (p->num % 2 == 0)
			even_eat(p);
		else
			odd_eat(p);
		if (p->fac->number_of_philosophers != 1)
		{
			philo_put_fork(p);
			if (!return_dead_state(p))
				mutex_print("is sleeping", p);
			ft_usleep(p, p->fac->time_to_sleep * 1000);
			if (!return_dead_state(p))
				mutex_print("is thinking", p);
			usleep(400);
		}
	}
	return (NULL);
}

void	*check(void *args)
{
	t_philo	**p;
	int		nb;
	int		i;
	int		eaten;

	eaten = 0;
	p = (t_philo **) args;
	nb = p[0]->fac->number_of_philosophers;
	i = 0;
	while (i < nb && !p[0]->fac->is_dead
		&& (eaten < p[i]->fac->has_to_eat || p[i]->fac->has_to_eat == -1))
	{
		if ((get_time()) - return_time_state(p[i]) > p[i]->fac->time_to_die
			&& (return_nb_eat(p[i]) < p[i]->fac->has_to_eat
				|| p[i]->fac->has_to_eat == -1))
			change_for_death(p[i]);
		i++;
		if (i == nb)
			i = 0;
		pthread_mutex_lock(&(p[i]->mutex_eat));
		if (p[i]->nb_eat >= p[i]->fac->has_to_eat)
			eaten++;
		pthread_mutex_unlock(&(p[i]->mutex_eat));
	}
	return (NULL);
}

void	start_agora(t_fac *fac)
{
	int			i;
	pthread_t	checker;
	t_philo		**philo;

	fac->start = get_time();
	pthread_mutex_init(&(fac->mutex_print), NULL);
	pthread_mutex_init(&(fac->mutex_dead), NULL);
	philo = create_philo(fac);
	i = 0;
	while (i < fac->number_of_philosophers)
	{
		pthread_create(&(philo[i]->p), NULL, philo_essence, philo[i]);
		i++;
	}
	i = -1;
	pthread_create(&checker, NULL, check, philo);
	while (++i < fac->number_of_philosophers)
		pthread_join(philo[i]->p, NULL);
	pthread_join(checker, NULL);
	mutex_detroyer_philo(philo);
	free_philo_tab(philo, fac->number_of_philosophers);
	mutex_detroyer(fac);
}
