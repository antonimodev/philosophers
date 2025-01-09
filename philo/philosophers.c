/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:41:52 by antonimo          #+#    #+#             */
/*   Updated: 2025/01/09 14:16:37 by antonimo         ###   ########.fr       */
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
			return (2); // Return 2 represents error output
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
    t_params		params;
    t_philosopher	*philosophers; // no tiene memset
    unsigned int	i;

	i = 0;
    ac--;
    av++;
    if (ac == 4 || ac == 5)
    {
		// Initialize t_params struct
        memset(&params, 0, sizeof(t_params));
        if (!init_params(&params, ac, av))
            return (2);
        
        // Initialize FORKS (mutexes)
        params.forks = malloc(params.philos_num * sizeof(pthread_mutex_t));
		// If malloc or ft fails, it returns 2 (error)
        if (!params.forks || !init_mutex(params.forks, params.philos_num)) // name to plural, 2nd param -> "num" instead
        {
            printf("Error: Failed to initialize mutexes\n");
            return (2);
        }

        // Initialize PRINT mutex
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
        while (i < params.philos_num)
        {
            philosophers[i].id = i + 1; // legibilidad, en lugar de filosofo 0, es filosofo 1
            philosophers[i].params = &params;
            philosophers[i].left_fork = &params.forks[i];
            philosophers[i].right_fork = &params.forks[(i + 1) % params.philos_num]; // el modulo es para que sea circular
            philosophers[i].print_mutex = &params.print_mutex;
            philosophers[i].current_state = THINKING;
			i++;
        }

        // Create threads for each philosopher
        params.philosophers = malloc(params.philos_num * sizeof(pthread_t));
		/* if (!params.philosophers)
			cuidao con liberar y return 2 */
		i = 0;
        while (i < params.philos_num)
        {
            if (pthread_create(&params.philosophers[i], NULL, philosopher_routine, &philosophers[i]) != 0)
            {
                printf("Error: Failed to create thread for philosopher %d\n", i + 1);
                return (2);
            }
			i++;
        }

        // Wait for threads to finish
		i = 0;
        while (i < params.philos_num)
        {
            pthread_join(params.philosophers[i], NULL); // el programa principal espera a que los hilos terminen, si no existiese
														// esta funcion, el programa terminaria antes interrumpiendo los hilos
			i++;
        }

        // Cleanup
        for (i = 0; i < params.philos_num; i++)
        {
            pthread_mutex_destroy(&params.forks[i]);
        }
        pthread_mutex_destroy(&params.print_mutex);
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

// Función que inicializa un array de mutex, se podría hacer de propósito general
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