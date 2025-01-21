/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_mutex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:49:39 by antonimo          #+#    #+#             */
/*   Updated: 2025/01/21 13:30:34 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_mutex_t	*create_forks(unsigned int num_philos)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

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

bool	init_mutex_array(pthread_mutex_t *forks, unsigned int philos_num)
{
	unsigned int	i;

	i = 0;
	while (i < philos_num)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (false);
		i++;
	}
	return (true);
}

bool	init_individual_mutexes(t_params *params)
{
	if (!init_individual_mutex(&params->print_mutex, "print")
		|| !init_individual_mutex(&params->last_meal_mutex, "last meal")
		|| !init_individual_mutex(&params->meal_count_mutex, "meal count")
		|| !init_individual_mutex(&params->dead_mutex, "dead"))
		return (false);
	return (true);
}

bool	init_individual_mutex(pthread_mutex_t *mutex, char *msg)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		printf("Error: Failed to initialize %s mutex\n", msg);
		return (false);
	}
	return (true);
}

void	destroy_mutex(t_params *params, t_args *args)
{
	unsigned int	i;

	i = 0;
	while (i < args->philos_num)
	{
		pthread_mutex_destroy(&params->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&params->last_meal_mutex);
	pthread_mutex_destroy(&params->meal_count_mutex);
	pthread_mutex_destroy(&params->dead_mutex);
	pthread_mutex_destroy(&params->print_mutex);
}
