/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philfun.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:36:25 by kyacini           #+#    #+#             */
/*   Updated: 2023/06/26 07:43:12 by skhali           ###   ########.fr       */
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
        pthread_mutex_init(&(p->mutex_tsm), NULL);
        pthread_mutex_init(&(p->mutex_eat), NULL);
        p->fac = fac;
        philo[i] = p;
        i++;
    }
    return(philo);
}

void *philo_essence(void *args){
    t_philo *p;

    p = (t_philo *) args;
    even_thinking(p);
    while(!return_dead_state(p)
        &&(p->nb_eat < p->fac->number_of_times_each_philosopher_must_eat
			|| p->fac->number_of_times_each_philosopher_must_eat == -1))
    {
        if (p->num % 2 == 0)
            even_eat(p);
        else
            odd_eat(p);
        if(p->fac->number_of_philosophers != 1)
        {
            philo_put_fork(p);
            if(!return_dead_state(p))
                mutex_print("is sleeping", p);
            usleep(p->fac->time_to_sleep * 1000);
            if(!return_dead_state(p))
                mutex_print("is thinking", p);
            usleep(100);
        }
    }
    return(NULL);
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
        if((get_time()) - return_time_state(p[i]) > p[i]->fac->time_to_die && (return_nb_eat(p[i]) < p[i]->fac->number_of_times_each_philosopher_must_eat || p[i]->fac->number_of_times_each_philosopher_must_eat == -1))
        {
            pthread_mutex_lock(&(p[i]->fac->mutex_dead));
            p[0]->fac->is_dead = 1;
            mutex_print("died", p[i]);
            pthread_mutex_unlock(&(p[i]->fac->mutex_dead));
        }
        i++;
        if(i == nb)
            i = 0;
        pthread_mutex_lock(&(p[i]->mutex_eat));
        if(p[i]->nb_eat >= p[i]->fac->number_of_times_each_philosopher_must_eat)
            eaten++;
        pthread_mutex_unlock(&(p[i]->mutex_eat));
    }
    return(NULL);
}

void start_agora(t_fac *fac){
    int i;
    pthread_t checker;
    t_philo **philo;

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