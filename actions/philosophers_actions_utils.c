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

void    print_status(t_philosopher *philo, unsigned int action)
{
    // Es posible que aquí podamos poner el pthread_mutex_lock
    if (action == EATING)
        printf("time: %u  ID: %u is eating\n", 
                time_diff(philo->params->timestamp), philo->id);
    else if (action == SLEEPING)
        printf("time: %u  ID: %u is sleeping\n", 
                time_diff(philo->params->timestamp), philo->id);
    else if (action == THINKING)
        printf("time: %u  ID: %u is thinking\n", 
                time_diff(philo->params->timestamp), philo->id);
    else if (action == FORK)
        printf("time: %u  ID: %u has taken a fork\n", 
                time_diff(philo->params->timestamp), philo->id);
    else if (action == DEAD)
        printf("time: %u  ID: %u died\n", 
                time_diff(philo->params->timestamp), philo->id);
}