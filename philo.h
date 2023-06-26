/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:37:01 by kyacini           #+#    #+#             */
/*   Updated: 2023/06/26 06:18:22 by skhali           ###   ########.fr       */
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
	int pass;
	int start;
    pthread_mutex_t		*fork;
    pthread_mutex_t		mutex_print;
    pthread_mutex_t		mutex_pass;
    pthread_mutex_t		mutex_dead;
}				t_fac;

typedef struct s_philo{
	int num;
	pthread_t p;
	t_fac *fac;
	int time_since_meal;
	int nb_eat;
    pthread_mutex_t		mutex_tsm;
    pthread_mutex_t		mutex_eat;
	int think;
}				t_philo;


char	*ft_strrejoin(int size, char **strs, char *sep, int start);
int	    ft_atoi(const char *nptr);
char	**ft_split(const char *str, char c);
t_philo **create_philo(t_fac *params);
void 	start_agora(t_fac *fac);
void 	mutex_detroyer(t_fac *params);
int	get_time(void);
void	free_double_char(char	**str);
void free_philo_tab(t_philo **philo, int nb);
void mutex_print(char *str, t_philo *p);
void even_thinking(t_philo *p);
void even_eat(t_philo *p);
void philo_pass(t_philo *p);
void odd_eat(t_philo *p);
void philo_put_fork(t_philo *p);
int return_dead_state(t_philo *p);
int return_time_state(t_philo *p);
void mutex_detroyer_philo(t_philo **p);
int return_nb_eat(t_philo *p);

#endif