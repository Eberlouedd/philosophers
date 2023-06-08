#ifndef PHILO_H
# define PHILO_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdint.h>
#include <sys/time.h>

typedef struct s_params{
    pthread_mutex_t		*fork;
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	int is_dead;
	int start;

}				t_params;

typedef struct s_philo{
	int num;
	pthread_t p;
    pthread_mutex_t		mutex;
	t_params *params;
	int time_since_meal;

}				t_philo;


char	*ft_strrejoin(int size, char **strs, char *sep, int start);
int	    ft_atoi(const char *nptr);
char	**ft_split(const char *str, char c);
t_philo **create_philo(t_params *params);
void 	start_agora(t_philo **philo, int n);
void 	mutex_detroyer(t_params *params);
int	get_time(void);
#endif