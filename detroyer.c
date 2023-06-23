/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detroyer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:36:51 by kyacini           #+#    #+#             */
/*   Updated: 2023/06/23 18:13:16 by kyacini          ###   ########.fr       */
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