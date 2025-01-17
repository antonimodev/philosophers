/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:41:52 by antonimo          #+#    #+#             */
/*   Updated: 2025/01/17 14:37:17 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int ac, char **av)
{
    t_args      args;
    t_params    params;
    t_philo     *philo;

    ac--;
    av++;
    if (ac == 4 || ac == 5)
    {
        // -- ARGS -- //
        if (!init_philos(&params, &args, &philo, ac, av)) // INICIALIZA TODO
            return (2);
        if (!start_routine(&params, &args, philo))
            return (2);
        wait_threads(&params, &args); // puede que lo metamos en cleanup
        cleanup(&params, &args, philo);
    }
    else
    {
        printf("Error: invalid number of arguments\n");
        printf("Usage: 'number_of_philosophers' 'time_to_die' 'time_to_eat' 'time_to_sleep' '[number_of_times_each_philosopher_must_eat]'\n");
    }
    return (0);
}

void    wait_threads(t_params *params, t_args *args)
{
    unsigned int i;

    i = 0;
    pthread_join(params->monitor, NULL);
    while (i < args->philos_num)
    {
        pthread_join(params->threads[i], NULL);
        i++;
    }
}

bool    start_routine(t_params *params, t_args *args, t_philo *philo) // empieza los hilos
{
    unsigned int i;

    i = 0;
    // Create threads for philosophers
    while (i < args->philos_num)
    {
        if (pthread_create(&params->threads[i], NULL, routine, &philo[i]) != 0) // revisar si se puede modularizar
        {
            printf("Error: Failed to create thread for routine %d\n", i + 1);
            return (false);
        }
        i++;
    }
    // Create thread for monitor
    if (pthread_create(&params->monitor, NULL, monitor, philo) != 0)
    {
        printf("Error: Failed to create thread for monitor\n");
        return (false);
    }
    return (true);
}

void cleanup(t_params *params, t_args *args, t_philo *philo)
{
    destroy_mutex(params, args);
    free(philo);
    free(params->threads);
    free(params->forks);
}


