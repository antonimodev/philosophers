/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_threads.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:49:39 by antonimo          #+#    #+#             */
/*   Updated: 2024/12/17 12:39:01 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// pthread_create(&params->philosopher, NULL, life_cycle, params);

/*REVISAR:
- Recibe params para hacer el cálculo de si tiene tiempo para la acción correspondiente
- Debería recibir la acción que corresponde para que pueda calcular en función de si es comer o dormir
- No sé si el mutex debe ser utilizado para hacer este printf o ya es pasarse*/
bool	on_time(unsigned int last_meal, t_params *params, \
				pthread_mutex_t *print_mutex, //acción que hace)
{
	struct timeval time;	
	gettimeofday(&time, NULL);
	if (time.tv_usec - last_meal > params->time_to_die)
	{
		pthread_mutex_lock(print_mutex); // necesario?
		printf("Philosopher %u died by starvation\n", philo_id);
		pthread_mutex_unlock(print_mutex);
		return false;
	}
	return true;
}

void	*life_cycle(void *params)
{
    t_params		*placeholder;
    t_philosopher	philosopher;
    pthread_mutex_t	print_mutex; // para printf es necesario?
    struct timeval	time;

    pthread_mutex_init(&print_mutex, NULL);
    gettimeofday(&time, NULL);
    placeholder = (t_params *)params;
    philosopher.last_meal = time.tv_usec;
    while (1)
    {
        if (estado == comer)
        {
            if (!on_time(philosopher.last_meal, placeholder->time_to_die, philosopher.philo_id, &print_mutex))
                return (NULL);
            pthread_mutex_lock(&VARIABLE_MUTEX); // debería de ser el tenedor izq y drcho?
            pthread_mutex_lock(&print_mutex); // es necesario en todos los printf?
            printf("esta comiendo\n");
            pthread_mutex_unlock(&print_mutex);
            usleep(placeholder->time_to_eat);
            pthread_mutex_unlock(&VARIABLE_MUTEX);
        }
        if (estado == dormir)
        {
            pthread_mutex_lock(&print_mutex);
            printf("esta durmiendo\n");
            pthread_mutex_unlock(&print_mutex);
            usleep(placeholder->time_to_sleep);
        }
        if (estado == pensar)
        {
            pthread_mutex_lock(&print_mutex);
            printf("esta pensando\n");
            pthread_mutex_unlock(&print_mutex);
        }
    }
    pthread_mutex_destroy(&print_mutex);
    return (NULL);
}

typedef struct s_philosopher
{
	unsigned int	philo_id;
	unsigned int	last_meal;
	/* pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork; */
}	t_philosopher;

