/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:41:52 by antonimo          #+#    #+#             */
/*   Updated: 2025/01/21 13:43:31 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_args		args;
	t_params	params;
	t_philo		*philo;

	if (ac != 5 && ac != 6)
	{
		printf("Error: invalid number of arguments\n");
		printf("Usage: 'number_of_philosophers' 'time_to_die' 'time_to_eat' \
		 'time_to_sleep' '[number_of_times_each_philosopher_must_eat]'\n");
		return (2);
	}
	ac--;
	av++;
	if (!init_args(&args, ac, av) || !init_philos(&params, &args, &philo))
		return (ERROR_INIT);
	if (!start_routine(&params, &args, philo))
		return (ERROR_ROUTINE);
	wait_threads(&params, &args);
	cleanup(&params, &args, philo);
	return (SUCCESS);
}

bool	start_routine(t_params *params, t_args *args, t_philo *philo)
{
	unsigned int	i;

	i = 0;
	while (i < args->philos_num)
	{
		if (pthread_create(&params->threads[i], NULL, routine, &philo[i]) != 0)
		{
			printf("Error: Failed to create thread for philo's routine %d\n", \
			i + 1);
			cleanup(params, args, philo);
			return (false);
		}
		i++;
	}
	if (pthread_create(&params->monitor, NULL, monitor, philo) != 0)
	{
		printf("Error: Failed to create thread for monitor\n");
		cleanup(params, args, philo);
		return (false);
	}
	return (true);
}

void	wait_threads(t_params *params, t_args *args)
{
	unsigned int	i;

	i = 0;
	pthread_join(params->monitor, NULL);
	while (i < args->philos_num)
	{
		pthread_join(params->threads[i], NULL);
		i++;
	}
}

void	cleanup(t_params *params, t_args *args, t_philo *philo)
{
	destroy_mutex(params, args);
	free(philo);
	free(params->threads);
	free(params->forks);
}
