/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:49:39 by antonimo          #+#    #+#             */
/*   Updated: 2025/01/16 13:19:17 by antonimo         ###   ########.fr       */
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
        //!philo->params->dead para hacer la comprobacion de si ha muerto o no
        if (philo->current_state == EATING)
        {
            if (philo->params->philos_num == 1)
                usleep(philo->params->time_to_die * 1000); // revisar
            eating(philo);
            if (philo->params->eat_times &&
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
