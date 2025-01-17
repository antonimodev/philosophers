/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_think.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:49:39 by antonimo          #+#    #+#             */
/*   Updated: 2025/01/17 13:35:05 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    thinking(t_philo *philo)
{
    think(philo);
    philo->current_state = EATING;
}

void    think(t_philo *philo)
{
    pthread_mutex_lock(philo->print_mutex);
    print_status(philo, THINKING);
    pthread_mutex_unlock(philo->print_mutex);
}
