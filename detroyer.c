/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detroyer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:36:51 by kyacini           #+#    #+#             */
/*   Updated: 2023/06/26 04:26:41 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void mutex_detroyer(t_fac *params){
    int i;

    i = 0;
    pthread_mutex_destroy(&(params->mutex_dead));
    pthread_mutex_destroy(&(params->mutex_pass));
    pthread_mutex_destroy(&(params->mutex_print));
    while(i < params->number_of_philosophers){
        pthread_mutex_destroy(&(params->fork[i]));
        i++;
    }
}

void mutex_detroyer_philo(t_philo **p){
    int i;
    int n;

    i = 0;
    n = p[0]->fac->number_of_philosophers;
    while(i < n){
        pthread_mutex_destroy(&(p[i]->mutex_tsm));
        pthread_mutex_destroy(&(p[i]->mutex_eat));
        i++;
    }
}

void free_philo_tab(t_philo **philo, int nb)
{
    int i;

    i = 0;
    while (i < nb)
    {
        free(philo[i]);
        i++;
    }
    free(philo);
}