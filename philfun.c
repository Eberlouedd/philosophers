/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philfun.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:36:25 by kyacini           #+#    #+#             */
/*   Updated: 2023/06/24 18:01:43 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo **create_philo(t_fac *fac)
{
     int i = 0;
    t_philo **philo;

    philo = malloc(fac->number_of_philosophers * sizeof(t_philo *));
    while (i < fac->number_of_philosophers)
    {
        t_philo *p;
        p = malloc(sizeof(t_philo));
        p->num = i+1;
        p->nb_eat = 0;
        p->time_since_meal = get_time();
        p->fac = fac;
        philo[i] = p;
        i++;
    }
    return(philo);
}

void *philo_essence(void *args){
    t_philo *p;

    p = (t_philo *) args;
    if(p->num % 2 == 0)
    {
        mutex_print("is thinking", p);
        usleep(5000);
    }
    while((p->nb_eat < p->fac->number_of_times_each_philosopher_must_eat || p->fac->number_of_times_each_philosopher_must_eat == -1))
    {
        if (p->num % 2 == 0)
        {
            pthread_mutex_lock(&(p->fac->fork[p->num-1]));
            mutex_print("has taken a fork", p);
            if(p->num == p->fac->number_of_philosophers)
                pthread_mutex_lock(&(p->fac->fork[0]));
            else
                pthread_mutex_lock(&(p->fac->fork[p->num]));
            mutex_print("has taken a fork", p);
            mutex_print("is eating", p);
            usleep(p->fac->time_to_eat * 1000);
            p->nb_eat++;
            p->time_since_meal = get_time();
        }
        else
        {
            pthread_mutex_lock(&(p->fac->mutex_pass));
            if(p->num == p->fac->pass && p->fac->number_of_philosophers % 2 != 0)
            {
                mutex_print("is thinking", p);
                usleep(6000);
                if(p->fac->pass + 2 > p->fac->number_of_philosophers)
                    p->fac->pass = 1;
                else
                    p->fac->pass += 2;
            }
            pthread_mutex_unlock(&(p->fac->mutex_pass));
            if(p->num == p->fac->number_of_philosophers)
                pthread_mutex_lock(&(p->fac->fork[0]));
            else
                pthread_mutex_lock(&(p->fac->fork[p->num]));
            mutex_print("has taken a fork", p);
            pthread_mutex_lock(&(p->fac->fork[p->num-1]));
            mutex_print("has taken a fork", p);
            mutex_print("is eating", p);
            usleep(p->fac->time_to_eat * 1000);
            p->nb_eat++;
            p->time_since_meal = get_time();
        }
        if(!p->fac->is_dead)
            mutex_print("is sleeping", p);
        if(p->num == p->fac->number_of_philosophers)
            pthread_mutex_unlock(&(p->fac->fork[0]));
        else
            pthread_mutex_unlock(&(p->fac->fork[p->num]));
        pthread_mutex_unlock(&(p->fac->fork[p->num-1]));
        usleep(p->fac->time_to_sleep * 1000);
    }
    pthread_exit(NULL);
}

void *check(void *args)
{
    t_philo **p;
    int nb;
    int i;
    int eaten;

    eaten = 0;
    p = (t_philo**) args;
    nb = p[0]->fac->number_of_philosophers;
    i = 0;
    while (i < nb && !p[0]->fac->is_dead && (eaten < p[i]->fac->number_of_times_each_philosopher_must_eat || p[i]->fac->number_of_times_each_philosopher_must_eat == -1))
    {
        if((get_time()) - p[i]->time_since_meal > p[i]->fac->time_to_die && (p[i]->nb_eat < p[i]->fac->number_of_times_each_philosopher_must_eat || p[i]->fac->number_of_times_each_philosopher_must_eat == -1))
        {
            pthread_mutex_lock(&(p[i]->fac->mutex_dead));
            p[0]->fac->is_dead = 1;
            mutex_print("died", p[i]);
            pthread_mutex_unlock(&(p[i]->fac->mutex_dead));
            mutex_detroyer(p[0]->fac);
        }
        i++;
        if(i == nb)
            i = 0;
        if(p[i]->nb_eat >= p[i]->fac->number_of_times_each_philosopher_must_eat)
            eaten++;
    }
    pthread_exit(NULL);
}

void start_agora(t_fac *fac){
    int i;
    pthread_t checker;
    t_philo **philo;

    fac->start = get_time();
    pthread_mutex_init(&(fac->mutex_print), NULL);
    pthread_mutex_init(&(fac->mutex_pass), NULL);
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
    free_philo_tab(philo, fac->number_of_philosophers);
}