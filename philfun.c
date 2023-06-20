#include "philo.h"

t_philo **create_philo(t_params *params)
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
        printf("%d %d is thinking\n ", get_time() - p->start, p->num);
        usleep(5000);
    }
    while(!p->params->is_dead && (p->nb_eat < p->params->number_of_times_each_philosopher_must_eat || p->params->number_of_times_each_philosopher_must_eat == -1))
    {
        if(p->num % 2 == 0)
        {
            pthread_mutex_lock(&(p->params->fork[p->num-1]));
            if(p->num == p->params->number_of_philosophers)
                pthread_mutex_lock(&(p->params->fork[0]));
            else
                pthread_mutex_lock(&(p->params->fork[p->num]));
            usleep(300);
            if(!p->params->is_dead)
                printf("%d %d is eating\n ", (int)(get_time() - p->start), p->num);
            usleep(p->params->time_to_eat * 1000);
            p->nb_eat++;
            p->time_since_meal = get_time();
        }
        else
        {
            if(p->params->number_of_philosophers % 2 != 0 && p->num == p->pass)
            {
                printf("%d %d is thinking\n ", get_time() - p->start, p->num);
                usleep(6000);
                if(p->pass + 2 > p->params->number_of_philosophers)
                    p->pass = 1;
                else
                    p->pass += 2;
                continue;
            }
            else
            {
                if(p->num == p->params->number_of_philosophers)
                    pthread_mutex_lock(&(p->params->fork[0]));
                else
                    pthread_mutex_unlock(&(p->params->fork[p->num]));
                pthread_mutex_lock(&(p->params->fork[p->num-1]));
                usleep(300);
                if(!p->params->is_dead)
                    printf("%d %d is eating\n ", get_time() - p->start, p->num);
                usleep(p->params->time_to_eat * 1000);
                p->nb_eat++;
                p->time_since_meal = get_time();
                if(p->pass + 2 > p->params->number_of_philosophers)
                    p->pass = 1;
                else
                    p->pass += 2;
            }
        }
        usleep(300);
        if(!p->params->is_dead)
            printf("%d %d is sleeping\n ", get_time() - p->start, p->num);
        if(p->num == p->params->number_of_philosophers)
            pthread_mutex_unlock(&(p->params->fork[0]));
        else
            pthread_mutex_unlock(&(p->params->fork[p->num]));
        pthread_mutex_unlock(&(p->params->fork[p->num-1]));
        usleep(p->params->time_to_sleep * 1000);
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
    nb = p[0]->params->number_of_philosophers;
    i = 0;
    while (i < nb && !p[0]->params->is_dead && (eaten < p[i]->params->number_of_times_each_philosopher_must_eat || p[i]->params->number_of_times_each_philosopher_must_eat == 1))
    {
        if((get_time()) - p[i]->time_since_meal > p[i]->params->time_to_die && (p[i]->nb_eat < p[i]->params->number_of_times_each_philosopher_must_eat || p[i]->params->number_of_times_each_philosopher_must_eat == -1))
        {
            p[0]->params->is_dead = 1;
            printf("%d %d died\n", get_time() - p[0]->start, i + 1);
            mutex_detroyer(p[0]->params);
        }
        i++;
        if(i == nb)
            i = 0;
        if(p[i]->nb_eat >= p[i]->params->number_of_times_each_philosopher_must_eat)
            eaten++;
    }
}

void start_agora(t_philo **philo, int n){

    int i;
    pthread_t checker;

    i = 0;
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