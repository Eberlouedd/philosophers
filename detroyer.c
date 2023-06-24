/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detroyer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:36:51 by kyacini           #+#    #+#             */
/*   Updated: 2023/06/24 15:23:27 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void mutex_detroyer(t_fac *params){
    int i;

    i = 0;
    while(i < params->number_of_philosophers){
        pthread_mutex_destroy(&(params->fork[i]));
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