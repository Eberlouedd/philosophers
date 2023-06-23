#include "philo.h"

void even_philo(t_philo *p)
{
    pthread_mutex_lock(&(p->params->fork[p->num-1]));
    printf("%d %d has taken a fork\n", (int)(get_time() - p->start), p->num);
    if(p->num == p->params->number_of_philosophers)
        pthread_mutex_lock(&(p->params->fork[0]));
    else
        pthread_mutex_lock(&(p->params->fork[p->num]));
    printf("%d %d has taken a fork\n", (int)(get_time() - p->start), p->num);
    usleep(300);
    if(!p->params->is_dead)
        printf("%d %d is eating\n ", (int)(get_time() - p->start), p->num);
    usleep(p->params->time_to_eat * 1000);
    p->nb_eat++;
    p->time_since_meal = get_time();
}

void odd_philo(t_philo *p)
{
    if(p->num == p->params->number_of_philosophers)
        pthread_mutex_lock(&(p->params->fork[0]));
    else
        pthread_mutex_lock(&(p->params->fork[p->num]));
    printf("%d %d has taken a fork\n", (int)(get_time() - p->start), p->num);
    pthread_mutex_lock(&(p->params->fork[p->num-1]));
    printf("%d %d has taken a fork\n", (int)(get_time() - p->start), p->num);
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

void after_eat(t_philo *p)
{
    if(!p->params->is_dead)
        printf("%d %d is sleeping\n ", get_time() - p->start, p->num);
    if(p->num == p->params->number_of_philosophers)
        pthread_mutex_unlock(&(p->params->fork[0]));
    else
        pthread_mutex_unlock(&(p->params->fork[p->num]));
    pthread_mutex_unlock(&(p->params->fork[p->num-1]));
    usleep(p->params->time_to_sleep * 1000);
}

void tour_pass(t_philo *p)
{
    printf("%d %d is thinking\n ", get_time() - p->start, p->num);
    usleep(6000);
    if(p->pass + 2 > p->params->number_of_philosophers)
        p->pass = 1;
    else
        p->pass += 2;
}

void even_entry(t_philo *p)
{
    printf("%d %d is thinking\n ", get_time() - p->start, p->num);
    usleep(5000);
}