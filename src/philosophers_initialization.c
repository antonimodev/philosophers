/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_initialization.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:24:37 by antonimo          #+#    #+#             */
/*   Updated: 2025/01/20 14:43:55 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


bool	init_philos(t_params *params, t_args *args, t_philo **philo, \
					int ac, char **av)
{
	if (!init_args(args, ac, av) ||
		!init_forks(params, args) || // tiene malloc
		!init_individual_mutexes(params) ||
		!init_philo_struct(params, args, philo)) // contiene philosophers_array y malloc_threads que tiene malloc
		return (false);
	return (true);
}

bool    init_forks(t_params *params, t_args *args)
{
	memset(params, 0, sizeof(t_params));
    params->forks = malloc(args->philos_num * sizeof(pthread_mutex_t)); // Malloc for forks
	
    if (!params->forks || !init_mutex_array(params->forks, args->philos_num)) // Init forks mutexes
    {
        free(params->forks);
        printf("Error: Failed to initialize mutexes\n");
        return (false);
    }
    return (true);
}

bool    init_philo_struct(t_params *params, t_args *args, t_philo **philo)
{
    unsigned int	i;

    if (!malloc_philosophers_array(args, philo) ||
        !malloc_threads(params, args, *philo))
            return (false);
    i = 0;
    while (i < args->philos_num)
    {
        (*philo)[i].id = i + 1;
        (*philo)[i].args = *args;
        (*philo)[i].params = params;
        (*philo)[i].left_fork = &params->forks[i];
        (*philo)[i].right_fork = &params->forks[(i + 1) % args->philos_num];
        (*philo)[i].print_mutex = &params->print_mutex;
        (*philo)[i].meals = 0;
        (*philo)[i].last_meal_time = current_time();
        if ((*philo)[i].id % 2 == 0)
            (*philo)[i].current_state = EATING;
        else
            (*philo)[i].current_state = SLEEPING;
        i++;
    }
	return (true);
}
