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

void    sleeping(t_philosopher *philo)
{
    rest(philo);
    philo->current_state = THINKING;
}

void    rest(t_philosopher *philo)
{
    pthread_mutex_lock(philo->print_mutex);
    print_status(philo, SLEEPING);
    pthread_mutex_unlock(philo->print_mutex);
    usleep(philo->params->time_to_sleep * 1000);
}