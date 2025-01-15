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
    while (1)
    {
        if (philo->current_state == EATING)
        {
            eating(philo);
            if (philo->params->eat_arg &&
                philo->meals == philo->params->eat_times)
                break ;
        }
        else if (philo->current_state == SLEEPING)
            sleeping(philo);
        else if (philo->current_state == THINKING)
            thinking(philo);
    }
    return (NULL);
}
