/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_initialization.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:24:37 by antonimo          #+#    #+#             */
/*   Updated: 2025/01/23 11:00:22 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	init_philos(t_params *params, t_args *args, t_philo **philo)
{
	if (!init_forks(params, args)
		|| !init_individual_mutexes(params)
		|| !init_philo_struct(params, args, philo))
		return (false);
	return (true);
}

bool	init_args(t_args *args, int ac, char **av)
{
	unsigned int	*values;

	memset(args, 0, sizeof(t_args));
	if (!check_av(av, is_number))
		return (false);
	values = parse_values(ac, av);
	if (!values[0])
	{
		free(values);
		return (false);
	}
	args->philos_num = values[0];
	args->time_to_die = values[1];
	args->time_to_eat = values[2];
	args->time_to_sleep = values[3];
	if (ac == 5)
		args->eat_times = values[4];
	free(values);
	return (true);
}

bool	init_forks(t_params *params, t_args *args)
{
	memset(params, 0, sizeof(t_params));
	params->forks = malloc(args->philos_num * sizeof(pthread_mutex_t));
	if (!params->forks || !init_mutex_array(params->forks, args->philos_num))
	{
		free(params->forks);
		printf("Error: Failed to initialize forks mutexes\n");
		return (false);
	}
	return (true);
}

bool	init_philo_struct(t_params *params, t_args *args, t_philo **philo)
{
	unsigned int	i;

	if (!malloc_philos_array(params, args, philo)
		|| !malloc_threads(params, args, *philo))
		return (false);
	i = 0;
	while (i < args->philos_num)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].args = *args;
		(*philo)[i].params = params;
		(*philo)[i].left_fork = &params->forks[i];
		(*philo)[i].right_fork = &params->forks[(i + 1) % args->philos_num];
		(*philo)[i].print_mutex = &params->print_mutex;
		(*philo)[i].meals = 0;
		(*philo)[i].last_meal_time = current_time();
		if ((*philo)[i].id % 2 == 0)
			(*philo)[i].current_state = EATING;
		else
			(*philo)[i].current_state = SLEEPING;
		i++;
	}
	return (true);
}
