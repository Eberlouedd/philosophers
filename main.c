#include "philo.h"

t_params *parsing(char **arg, int n)
{
    char *str;
    char **verified;
    t_params *res;
    int i = 0;

    res = malloc(sizeof(t_params*));
    str = ft_strrejoin(n, arg, " ", 1);
    while (str[i])
    {
        if((str[i] > '9' || str[i] < '0') && str[i] != ' ')
            return NULL;
        i++;
    }
    verified = ft_split(str, ' ');
    free(str);
    res->number_of_philosophers = ft_atoi(verified[0]);
    res->fork = malloc(ft_atoi(verified[0]) * sizeof(pthread_mutex_t));
    res->time_to_die = ft_atoi(verified[1]);
    res->time_to_eat = ft_atoi(verified[2]);
    res->time_to_sleep = ft_atoi(verified[3]);
    if (n == 6)
        res->number_of_times_each_philosopher_must_eat = ft_atoi(verified[4]);
    free(verified);
    return (res);
    
}

int main(int argc, char **argv)
{
    t_params *params;
    if(argc <  5 || argc > 6)
        return (0);
    params = parsing(argv, argc);
    if (!params)
        return (0);
    start_agora(create_philo(params), params->number_of_philosophers);
}