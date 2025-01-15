/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_threads.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:49:39 by antonimo          #+#    #+#             */
/*   Updated: 2025/01/10 14:49:24 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		if (is_death(philo) || meals_done(philo))
			break ;
	}
	return (NULL);
}

bool	meals_done(t_philosopher *philo)
{
	unsigned int	i;

	if (!philo->params->eat_arg)
		return (false);
	i = 0;
	while (i < philo->params->philos_num)
	{
		if (philo[i].meals < philo->params->eat_times)
			return (false);
		i++;
	}
	print_status(philo, FINISH);
	return (true);
}

bool	is_death(t_philosopher *philo)
{
	unsigned int	i;
	unsigned int	new_time;

	i = 0;
	while (i < philo->params->philos_num)
		{
			new_time = philo[i].elapsed_time; // toma de referencia el tiempo transcurrido del filosofo
			new_time = time_diff(philo[i].last_meal_time); // calculamos el tiempo transcurrido desde la ultima comida
			if (new_time >= philo[i].params->time_to_die)
			{
				philo->params->dead = 1;
				pthread_mutex_lock(philo[i].print_mutex);
				print_status(&philo[i], DEAD);
				pthread_mutex_unlock(philo[i].print_mutex); // revisar si desbloquear aqui
				return (true);
			}
			i++;
		}
		return (false);
}
