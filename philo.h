/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:37:01 by kyacini           #+#    #+#             */
/*   Updated: 2023/06/23 19:08:18 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdint.h>
#include <sys/time.h>

typedef struct s_fac{
	int number_of_philosophers;
	int time_to_eat;
	int time_to_die;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	int is_dead;
    pthread_mutex_t		*fork;

}				t_fac;

typedef struct s_philo{
	int num;
	pthread_t p;
	t_fac *fac;
	int time_since_meal;
	int start;
	int pass;
	int nb_eat;

}				t_philo;


char	*ft_strrejoin(int size, char **strs, char *sep, int start);
int	    ft_atoi(const char *nptr);
char	**ft_split(const char *str, char c);
t_philo **create_philo(t_fac *params);
void 	start_agora(t_philo **philo, int n);
void 	mutex_detroyer(t_fac *params);
int	get_time(void);
void	free_double_char(char	**str);

#endif