/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:49:39 by antonimo          #+#    #+#             */
/*   Updated: 2025/01/21 13:13:33 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	set_start_routine(philo);
	if (philo_exception(philo))
		return (NULL);
	while (!dead_status(philo))
	{
		if (philo->current_state == EATING)
		{
			eating(philo);
			if (philo->args.eat_times && philo->meals == philo->args.eat_times)
				break ;
		}
		else if (philo->current_state == SLEEPING)
			sleeping(philo);
		else if (philo->current_state == THINKING)
			thinking(philo);
	}
	return (NULL);
}

void	set_start_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->last_meal_mutex);
	philo->last_meal_time = current_time();
	philo->args.timestamp = philo->last_meal_time;
	pthread_mutex_unlock(&philo->params->last_meal_mutex);
	if (philo->id % 2 != 0)
		usleep(300);
}

bool	philo_exception(t_philo *philo)
{
	if (philo->args.philos_num == 1)
	{
		usleep(philo->args.time_to_die * 1000);
		return (true);
	}
	return (false);
}

bool	dead_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->params->dead_mutex);
	if (philo->params->dead)
	{
		pthread_mutex_unlock(&philo->params->dead_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->params->dead_mutex);
	return (false);
}
