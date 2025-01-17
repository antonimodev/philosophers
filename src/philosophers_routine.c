/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:49:39 by antonimo          #+#    #+#             */
/*   Updated: 2025/01/17 14:18:10 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    philo->last_meal_time = current_time();
    philo->args.timestamp = philo->last_meal_time;
    while (1)
    {
        //philo->params->dead para hacer la comprobacion de si ha muerto o no
        if (philo->current_state == EATING)
        {
            if (philo->args.philos_num == 1)
                usleep(philo->args.time_to_die * 1000); // revisar
            eating(philo);
            if (philo->args.eat_times &&
                philo->meals == philo->args.eat_times)
                break ;
        }
        else if (philo->current_state == SLEEPING)
            sleeping(philo);
        else if (philo->current_state == THINKING)
            thinking(philo);
    }
    return (NULL);
}
