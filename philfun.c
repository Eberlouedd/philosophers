#include "philo.h"

t_philo **create_philo(t_params *params)
{
    int i = 0;
    t_philo **philo;

    philo = malloc(params->number_of_philosophers * sizeof(t_philo *));
    while (i < params->number_of_philosophers)
    {
        t_philo *p;
        p = malloc(sizeof(t_philo));
        p->num = i+1;
        pthread_mutex_init(&(params->fork[i]), NULL);
        pthread_mutex_init(&(p->mutex), NULL);
        p->params = params;
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
        printf("%ld %d dort\n ", (long)(clock() - p->params->start / CLOCKS_PER_SEC * 1000), p->num);
        usleep(p->params->time_to_sleep);
    }
    while(1)
    {
        if(p->num % 2 == 0)
        {
            pthread_mutex_lock(&(p->params->fork[p->num-1]));
            if(p->num == p->params->number_of_philosophers)
                pthread_mutex_lock(&(p->params->fork[0]));
            else
                pthread_mutex_lock(&(p->params->fork[p->num]));
            printf("%ld %d mange\n ", (long)(clock() - p->params->start / CLOCKS_PER_SEC * 1000), p->num);
            usleep(p->params->time_to_eat);
            p->time_since_meal = clock() / CLOCKS_PER_SEC * 1000;
        }
        else
        {
            
            pthread_mutex_lock(&(p->params->fork[p->num]));
            pthread_mutex_lock(&(p->params->fork[p->num-1]));
            printf("%ld %d mange\n ", (long)(clock() - p->params->start / CLOCKS_PER_SEC * 1000), p->num);
            usleep(p->params->time_to_eat);
            p->time_since_meal = clock() / CLOCKS_PER_SEC * 1000;
        }
        if(p->num == p->params->number_of_philosophers)
                pthread_mutex_unlock(&(p->params->fork[0]));
        else
            pthread_mutex_unlock(&(p->params->fork[p->num]));
        pthread_mutex_unlock(&(p->params->fork[p->num-1]));
        printf("%ld %d dort\n ", (long)(clock() - p->params->start / CLOCKS_PER_SEC * 1000), p->num);
        usleep(p->params->time_to_sleep);
    }
        
}

void *check(void *args)
{
    t_philo **p;
    int nb;
    int i;

    p = (t_philo**) args;
    nb = p[0]->params->number_of_philosophers;
    i = 0;
    while (i < nb)
    {
        if((clock()/ CLOCKS_PER_SEC * 1000) - p[i]->time_since_meal > p[i]->params->time_to_die)
        {
            printf("%d is dead\n", i + 1);
            exit(0);
        }
        i++;
        if(i == nb-1)
            i = 0;
    }
}
void start_agora(t_philo **philo, int n){

    int i;
    pthread_t checker;

    i = 0;
    philo[0]->params->start = clock() / CLOCKS_PER_SEC * 1000;
    while (i < n)
    {
        pthread_create(&(philo[i]->p), NULL, philo_essence, philo[i]);
        i++;
    }
    i = -1;
    pthread_create(&checker, NULL, check, philo);
	while (++i < n)
		pthread_join(philo[i]->p, NULL);
    pthread_join(checker, NULL);
}