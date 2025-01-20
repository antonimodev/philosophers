/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_monitor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:49:39 by antonimo          #+#    #+#             */
/*   Updated: 2025/01/20 14:36:53 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (is_death(philo) || meals_done(philo))
			break ;
	}
	return (NULL);
}

bool	meals_done(t_philo *philo)
{
	unsigned int	i;
	if (!philo->args.eat_times)
		return (false);
	i = 0;
	while (i < philo->args.philos_num)
	{
		pthread_mutex_lock(&philo->params->meal_count_mutex);
		if (philo[i].meals < philo->args.eat_times)
		{
			pthread_mutex_unlock(&philo->params->meal_count_mutex);
			return (false);
		}
		i++;
		pthread_mutex_unlock(&philo->params->meal_count_mutex);
	}
	print_status(philo, FINISH);
	return (true);
}

bool is_death(t_philo *philo)
{
    unsigned int i;
    unsigned int new_time;

    i = 0;
    while (i < philo->args.philos_num)
    {
        pthread_mutex_lock(&philo->params->last_meal_mutex);
        new_time = time_diff(philo[i].last_meal_time); // calculamos el tiempo transcurrido desde la ultima comida
        pthread_mutex_unlock(&philo->params->last_meal_mutex);
        if (new_time >= philo[i].args.time_to_die) // +2 para tener margen
        {
            pthread_mutex_lock(&philo[i].params->dead_mutex); // lockeo de recurso muerte
            philo[i].params->dead = true;
            pthread_mutex_unlock(&philo[i].params->dead_mutex); // unlockeo de recurso muerte
            pthread_mutex_lock(philo[i].print_mutex);
            print_status(&philo[i], DEAD);
            pthread_mutex_unlock(philo[i].print_mutex);
            return (true);
        }
        i++;
    }
    return (false);
}
