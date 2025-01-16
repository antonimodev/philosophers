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

void    *routine(void *arg)
{
    t_philosopher *philo;

    philo = (t_philosopher *)arg;
    philo->last_meal_time = current_time();
    philo->params->timestamp = philo->last_meal_time;
    while (!philo->params->dead)
    {
        if (philo->current_state == EATING)
        {
            if (philo->params->philos_num == 1)
                usleep(philo->params->time_to_die * 1000); // revisar
            eating(philo);
            if (philo->params->eat_arg &&
                philo->meals == philo->params->eat_times)
                break ;
            if (philo->id % 2 == 0)
                usleep(1000);
        }
        else if (philo->current_state == SLEEPING)
            sleeping(philo);
        else if (philo->current_state == THINKING)
            thinking(philo);
    }
    return (NULL);
}
