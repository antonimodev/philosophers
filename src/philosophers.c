/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:41:52 by antonimo          #+#    #+#             */
/*   Updated: 2025/01/10 14:25:10 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int ac, char **av)
{
    t_params		params;
    t_philosopher	*philo; // no tiene memset

    ac--;
    av++;
    if (ac == 4 || ac == 5)
    {
        memset(&params, 0, sizeof(t_params));
        if (!init_params(&params, ac, av))
            return (2);
        params.forks = malloc(params.philos_num * sizeof(pthread_mutex_t));
        if (!params.forks || !init_mutex_array(params.forks, params.philos_num))
        {
            free(params.forks);
            printf("Error: Failed to initialize mutexes\n"); // revisar mensaje
            return (2);
        }
        init_mutex(&params.print_mutex);
        if (!init_philosophers_array(&params, &philo)) // lleva malloc
            return (2);
        init_philosophers(&params, philo);
        params.philosophers = malloc(params.philos_num * sizeof(pthread_t));
		if (!params.philosophers)
        {
            free(params.forks);
            free(philo);
			return(2); // hay que liberar tambien creo
        }
        if (!start_routine(&params, philo))
            return (2);
        pthread_join(params.monitor, NULL);
        // Cleanup
        destroy_mutex(&params);
        free(philo);
        free(params.philosophers);
    }
    else
    {
        printf("Error: invalid number of arguments\n");
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", av[-1]);
    }
    return (0);
}

void    init_philosophers(t_params *params, t_philosopher *philo)
{
    unsigned int i;

    i = 0;
    while (i < params->philos_num)
    {
        philo[i].id = i + 1; // debe empezar en 1
        philo[i].params = params;
        philo[i].left_fork = &params->forks[i];
        philo[i].right_fork = &params->forks[(i + 1) % params->philos_num]; // el modulo es para que sea circular
        philo[i].print_mutex = &params->print_mutex;
        philo[i].meals = 0;
        philo[i].elapsed_time = 0;
        philo[i].last_meal_time = current_time();
        if (philo[i].id % 2 == 0)
            philo[i].current_state = EATING;
        else
            philo[i].current_state = SLEEPING;
        i++;
    }
}

bool    init_mutex(pthread_mutex_t *mutex) // general pero inicializa print_mutex
{
    if (pthread_mutex_init(mutex, NULL) != 0)
    {
        printf("Error: Failed to initialize mutex\n"); // revisar mensaje
        return (false);
    }
    return (true);
}

bool    init_philosophers_array(t_params *params, t_philosopher **philo)
{
    *philo = malloc(params->philos_num * sizeof(t_philosopher));
    if (!*philo)
    {
        printf("Error: Failed to allocate memory for philosophers\n"); // revisar mensaje
        return (false);
    }
    return (true);
}

bool    start_routine(t_params *params, t_philosopher *philo) // empieza los hilos
{
    unsigned int i;

    i = 0;
    // Create threads for philosophers
    while (i < params->philos_num)
    {
        if (pthread_create(&params->philosophers[i], NULL, routine, &philo[i]) != 0)
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

void    destroy_mutex(t_params *params)
{
    unsigned int i;

    i = 0;
    while (i < params->philos_num)
    {
        pthread_mutex_destroy(&params->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&params->print_mutex);
}
