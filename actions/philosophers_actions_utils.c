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
        printf(BOLD COLOR_GREEN "%ums %u is eating\n" COLOR_RESET,
                time_diff(philo->params->timestamp), philo->id);
    else if (action == SLEEPING)
        printf("%ums %u is sleeping\n", 
                time_diff(philo->params->timestamp), philo->id);
    else if (action == THINKING)
        printf("%ums %u is thinking\n", 
                time_diff(philo->params->timestamp), philo->id);
    else if (action == FORK)
        printf("%ums %u has taken a fork\n", 
                time_diff(philo->params->timestamp), philo->id);
    else if (action == DEAD)
        printf(COLOR_RED "%ums %u died\n" COLOR_RESET, 
                time_diff(philo->params->timestamp), philo->id);
    else if (action == FINISH)
        printf(BOLD COLOR_BLUE "%ums  All philosophers have eaten %u times\n" COLOR_RESET, 
                time_diff(philo->params->timestamp), philo->params->eat_times);
}
