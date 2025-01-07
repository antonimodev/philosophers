/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:41:52 by antonimo          #+#    #+#             */
/*   Updated: 2024/12/17 14:22:19 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* int	main(int ac, char **av)
{
	t_params	params;
	pthread_mutex_t *forks;

	ac--;
	av++;
	if (ac == 4 || ac == 5)
	{
		memset(&params, 0, sizeof(t_params));
		if (!init_params(&params, ac, av))
			return (2);
		forks = malloc(params.philos_num * sizeof(pthread_mutex_t));
		if (!forks || !init_mutex(forks, params.philos_num))
		{
			printf("Error: Failed to initialize mutexes\n");
			return (2);
		}
		params.forks = forks;
		// life_cycle(&params); Uncomment when life_cycle is implemented
		printf("GUCCI\n"); // comprobación
	}
	else
		printf("Error: invalid number of arguments\n");
	return (2);
} */

int main(int ac, char **av)
{
    t_params params;
    pthread_mutex_t *forks;
    t_philosopher *philosophers;
    unsigned int i;

    ac--;
    av++;
    if (ac == 4 || ac == 5)
    {
        // Initialize parameters and mutexes
        memset(&params, 0, sizeof(t_params));
        if (!init_params(&params, ac, av))
            return (2);
        
        // Initialize forks (mutexes)
        forks = malloc(params.philos_num * sizeof(pthread_mutex_t));
        if (!forks || !init_mutex(forks, params.philos_num))
        {
            printf("Error: Failed to initialize mutexes\n");
            return (2);
        }
        params.forks = forks;

        // Initialize print mutex
        if (pthread_mutex_init(&params.print_mutex, NULL) != 0)
        {
            printf("Error: Failed to initialize print mutex\n");
            return (2);
        }

        // Create philosophers
        philosophers = malloc(params.philos_num * sizeof(t_philosopher));
        if (!philosophers)
        {
            printf("Error: Failed to allocate philosophers\n");
            return (2);
        }

        // Initialize philosophers
        for (i = 0; i < params.philos_num; i++)
        {
            philosophers[i].id = i + 1;
            philosophers[i].params = &params;
            philosophers[i].left_fork = &forks[i];
            philosophers[i].right_fork = &forks[(i + 1) % params.philos_num];
            philosophers[i].print_mutex = &params.print_mutex;
            philosophers[i].current_state = THINKING;
        }

        // Create threads for each philosopher
        params.philosophers = malloc(params.philos_num * sizeof(pthread_t));
        for (i = 0; i < params.philos_num; i++)
        {
            if (pthread_create(&params.philosophers[i], NULL, philosopher_routine, &philosophers[i]) != 0)
            {
                printf("Error: Failed to create thread for philosopher %d\n", i + 1);
                return (2);
            }
        }

        // Wait for threads to finish
        for (i = 0; i < params.philos_num; i++)
        {
            pthread_join(params.philosophers[i], NULL);
        }

        // Cleanup
        for (i = 0; i < params.philos_num; i++)
        {
            pthread_mutex_destroy(&forks[i]);
        }
        pthread_mutex_destroy(&params.print_mutex);
        free(forks);
        free(philosophers);
        free(params.philosophers);
    }
    else
    {
        printf("Error: invalid number of arguments\n");
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", av[-1]);
    }
    return (0);
}


bool	init_mutex(pthread_mutex_t *forks, int philos_num) // Aquí philos num es de la estructura de params
{
	int	i;

	i = 0;
	while (i < philos_num)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0) // el != 0 es por legibilidad, la funcion devuelve 0 en éxito
			return (false); // aquí podríamos hacer printf para decir que los mutex no han podido inicializar correctamente
		i++;
	}
	return (true);
}