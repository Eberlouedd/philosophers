/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philfun.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:36:25 by kyacini           #+#    #+#             */
/*   Updated: 2023/06/23 18:12:15 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo **create_philo(t_fac *params)
{
    int i = 0;
    t_philo **philo;
    int s;

    s = get_time();
    philo = malloc(params->number_of_philosophers * sizeof(t_philo *));
    while (i < params->number_of_philosophers)
    {
        t_philo *p;
        p = malloc(sizeof(t_philo));
        p->num = i+1;
        p->time_since_meal = get_time();
        p->start = s;
        p->pass = 1;
        pthread_mutex_init(&(params->fork[i]), NULL);
        p->fac = params;
        philo[i] = p;
        i++;
    }
    return(philo);
}

void *philo_essence(void *args){

}

void *check(void *args)
{

}

void start_agora(t_philo **philo, int n){

    
}