#include "philo.h"

void mutex_detroyer(t_params *params){
    int i;

    i = 0;
    while(i < params->number_of_philosophers){
        pthread_mutex_destroy(&(params->fork[i]));
        i++;
    }
}