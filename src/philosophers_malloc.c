/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_malloc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:19:25 by antonimo          #+#    #+#             */
/*   Updated: 2025/01/17 14:19:53 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool    malloc_philosophers_array(t_args *args, t_philo *philo)
{
    philo = malloc(args->philos_num * sizeof(t_philo));
    if (!philo)
    {
        printf("Error: Failed to allocate memory for philosophers\n"); // revisar mensaje
        return (false);
    }
    return (true);
}

bool	malloc_threads(t_params *params, t_args *args, t_philo *philo)
{
	params->threads = malloc(args->philos_num * sizeof(pthread_t)); // Modularize
	if (!params->threads)
	{
		free(params->forks);
		free(philo);
		return (false);
	}
	return (true);
}
