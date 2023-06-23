/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:36:14 by kyacini           #+#    #+#             */
/*   Updated: 2023/06/23 19:08:34 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (int)1000) + (tv.tv_usec / 1000));
}

int valide_entry(char **entry, int n)
{
    if(ft_atoi(entry[0]) == 0 || ft_atoi(entry[0]) > 2147483647 
        || ft_atoi(entry[1]) == 0 || ft_atoi(entry[1]) > 2147483647
            || ft_atoi(entry[2]) == 0 || ft_atoi(entry[2]) > 2147483647
                || ft_atoi(entry[3]) == 0 || ft_atoi(entry[3]) > 2147483647)
                    return 0;
    if (n == 6)
        if (ft_atoi(entry[4]) == 0 || ft_atoi(entry[4]) > 2147483647)
            return (0);
    return (1);
}

t_fac *affect_struct(char **entry, int n)
{
    t_fac *structur;

    structur = malloc(sizeof(t_fac));
    if(!structur)
        return (NULL);
    structur->number_of_philosophers = ft_atoi(entry[0]);
    structur->fork = malloc(ft_atoi(entry[0]) * sizeof(pthread_mutex_t));
    if(!structur->fork)
        return (NULL);
    structur->time_to_die = ft_atoi(entry[1]);
    structur->time_to_eat = ft_atoi(entry[2]);
    structur->time_to_sleep = ft_atoi(entry[3]);
    structur->is_dead = 0;
    if (n == 6)
        structur->number_of_times_each_philosopher_must_eat = ft_atoi(entry[4]);
    else
        structur->number_of_times_each_philosopher_must_eat = -1;
    return(structur);
}

t_fac *parsing(char **arg, int n)
{
    char *str;
    char **verified;
    t_fac *res;
    int i = 0;

    str = ft_strrejoin(n, arg, " ", 1);
    while (str[i])
    {
        if((str[i] > '9' || str[i] < '0') && str[i] != ' ')
        {
            free(str);
            return NULL;
        }
        i++;
    }
    verified = ft_split(str, ' ');
    free(str);
    if(!valide_entry(verified, n))
    {
        free_double_char(verified);
        return(NULL);
    }
    res = affect_struct(verified, n);
    free_double_char(verified);
    return (res);
}

int main(int argc, char **argv)
{
    t_fac *fac;

    if(argc <  5 || argc > 6)
        return (0);
    fac = parsing(argv, argc);
    if (!fac)
        return (0);
    // start_agora(create_philo(params), params->number_of_philosophers);
    printf("oui");
    free(fac->fork);
    free(fac);
    return(0);
}