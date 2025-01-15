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

void    thinking(t_philosopher *philo)
{
    think(philo);
    philo->current_state = EATING;
}

void    think(t_philosopher *philo)
{
    pthread_mutex_lock(philo->print_mutex);
    print_status(philo, THINKING);
    pthread_mutex_unlock(philo->print_mutex);
}
