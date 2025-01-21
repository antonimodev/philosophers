/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_malloc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:19:25 by antonimo          #+#    #+#             */
/*   Updated: 2025/01/21 13:05:48 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	malloc_philos_array(t_params *params, t_args *args, t_philo **philo)
{
	*philo = malloc(args->philos_num * sizeof(t_philo));
	if (!*philo)
	{
		free(params->forks);
		printf("Error: Failed to allocate memory for philosophers\n");
		return (false);
	}
	return (true);
}

bool	malloc_threads(t_params *params, t_args *args, t_philo *philo)
{
	params->threads = malloc(args->philos_num * sizeof(pthread_t));
	if (!params->threads)
	{
		free(params->forks);
		free(philo);
		return (false);
	}
	return (true);
}
