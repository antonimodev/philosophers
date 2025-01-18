/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_mutex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:49:39 by antonimo          #+#    #+#             */
/*   Updated: 2025/01/17 14:40:14 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
// Revisar si vale o no, tenemos array de mutex en struct params
pthread_mutex_t *create_forks(unsigned int num_philos)
{
    pthread_mutex_t *forks;
    unsigned int i;

    forks = malloc(sizeof(pthread_mutex_t) * num_philos);
    if (!forks)
        return (NULL);

    i = 0;
    while (i < num_philos)
    {
        if (pthread_mutex_init(&forks[i], NULL) != 0)
        {
            while (i > 0)
                pthread_mutex_destroy(&forks[--i]);
            free(forks);
            return (NULL);
        }
        i++;
    }
    return (forks);
}

// Función que inicializa un array de mutex, se podría hacer de propósito general
bool	init_mutex_array(pthread_mutex_t *forks, unsigned int philos_num) // Aquí philos num es de la estructura de params
{
	unsigned int	i;

	i = 0;
	while (i < philos_num)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0) // el != 0 es por legibilidad, la funcion devuelve 0 en éxito
			return (false); // aquí podríamos hacer printf para decir que los mutex no han podido inicializar correctamente
		i++;
	}
	return (true);
}

bool    init_print_mutex(pthread_mutex_t *mutex) // general pero inicializa print_mutex
{
    if (pthread_mutex_init(mutex, NULL) != 0)
    {
        printf("Error: Failed to initialize print mutex\n"); // revisar mensaje
        return (false);
    }
    return (true);
}

bool    init_dead_mutex(pthread_mutex_t *mutex) // general pero inicializa print_mutex
{
    if (pthread_mutex_init(mutex, NULL) != 0)
    {
        printf("Error: Failed to initialize dead mutex\n"); // revisar mensaje
        return (false);
    }
    return (true);
}

void    destroy_mutex(t_params *params, t_args *args)
{
    unsigned int i;

    i = 0;
    while (i < args->philos_num)
    {
        pthread_mutex_destroy(&params->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&params->print_mutex);
}
