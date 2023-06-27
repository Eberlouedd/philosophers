/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:10:48 by kyacini           #+#    #+#             */
/*   Updated: 2023/06/27 22:18:38 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	change_for_death(t_philo *p)
{
	pthread_mutex_lock(&(p->fac->mutex_dead));
	p->fac->is_dead = 1;
	mutex_print("died", p);
	pthread_mutex_unlock(&(p->fac->mutex_dead));
}

void	odd_take_first_fork(t_philo *p)
{
	if (p->num == p->fac->number_of_philosophers)
		pthread_mutex_lock(&(p->fac->fork[0]));
	else
		pthread_mutex_lock(&(p->fac->fork[p->num]));
}

t_philo	*create_philosophe(t_fac *fac, int i)
{
	t_philo	*p;

	p = malloc(sizeof(t_philo));
	if (!p)
		return (NULL);
	p->num = i + 1;
	p->nb_eat = 0;
	p->time_since_meal = get_time();
	pthread_mutex_init(&(p->mutex_tsm), NULL);
	pthread_mutex_init(&(p->mutex_eat), NULL);
	p->fac = fac;
	return (p);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

int	test_limit(char *str)
{
	int		num;
	char	*buff;

	num = ft_atoi(str);
	buff = ft_itoa(num);
	if (ft_strcmp(buff, str))
	{
		free(buff);
		return (0);
	}
	free(buff);
	return (1);
}
