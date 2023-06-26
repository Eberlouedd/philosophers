#include "philo.h"

void even_thinking(t_philo *p)
{
    if(p->num % 2 == 0)
    {
        if(!return_dead_state(p))
            mutex_print("is thinking", p);
        usleep(300);
    }
}

void even_eat(t_philo *p)
{
    pthread_mutex_lock(&(p->fac->fork[p->num-1]));
    if(!return_dead_state(p))
        mutex_print("has taken a fork", p);
    if(p->num == p->fac->number_of_philosophers)
        pthread_mutex_lock(&(p->fac->fork[0]));
    else
        pthread_mutex_lock(&(p->fac->fork[p->num]));
    if(!return_dead_state(p))
    {
        mutex_print("has taken a fork", p);
        mutex_print("is eating", p);
    }
    usleep(p->fac->time_to_eat * 1000);
    pthread_mutex_lock(&(p->mutex_eat));
    p->nb_eat++;
    pthread_mutex_unlock(&(p->mutex_eat));
    pthread_mutex_lock(&(p->mutex_tsm));
    p->time_since_meal = get_time();
    pthread_mutex_unlock(&(p->mutex_tsm));
}


void philo_pass(t_philo *p)
{
    if(!return_dead_state(p) && p->think == 1)
        mutex_print("is thinking", p);
    usleep(10000);
    if(p->fac->pass + 2 > p->fac->number_of_philosophers)
        p->fac->pass = 1;
    else
        p->fac->pass += 2;
    p->think = 0;
}

void odd_eat(t_philo *p)
{
    p->think = 1;
    if(p->num == p->fac->number_of_philosophers)
        pthread_mutex_lock(&(p->fac->fork[0]));
    else
        pthread_mutex_lock(&(p->fac->fork[p->num]));
    if(!return_dead_state(p))
        mutex_print("has taken a fork", p);
    pthread_mutex_lock(&(p->fac->fork[p->num-1]));
    if(!return_dead_state(p))
    {
        mutex_print("has taken a fork", p);
        mutex_print("is eating", p);
    }
    usleep(p->fac->time_to_eat * 1000);
    pthread_mutex_lock(&(p->mutex_eat));
    p->nb_eat++;
    pthread_mutex_unlock(&(p->mutex_eat));
    pthread_mutex_lock(&(p->mutex_tsm));
    p->time_since_meal = get_time();
    pthread_mutex_unlock(&(p->mutex_tsm));
}

void philo_put_fork(t_philo *p)
{
    if(p->num % 2 == 0)
    {
        if(p->num == p->fac->number_of_philosophers)
            pthread_mutex_unlock(&(p->fac->fork[0]));
        else
            pthread_mutex_unlock(&(p->fac->fork[p->num]));
        pthread_mutex_unlock(&(p->fac->fork[p->num-1]));
    }
    else
    {
        pthread_mutex_unlock(&(p->fac->fork[p->num-1]));
        if(p->num == p->fac->number_of_philosophers)
            pthread_mutex_unlock(&(p->fac->fork[0]));
        else
            pthread_mutex_unlock(&(p->fac->fork[p->num]));
    }
}