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
        even_entry(p);
    while(!p->params->is_dead && (p->nb_eat < p->params->number_of_times_each_philosopher_must_eat || p->params->number_of_times_each_philosopher_must_eat == -1))
    {
        if(p->num % 2 == 0)
            even_philo(p);
        else
        {
            if(p->params->number_of_philosophers % 2 != 0 && p->num == p->pass)
            {
                tour_pass(p);
                continue;
            }
            else
                odd_philo(p);
        }
        usleep(300);
        after_eat(p);
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
    pthread_exit(NULL);
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