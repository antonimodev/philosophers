/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_eat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:49:39 by antonimo          #+#    #+#             */
/*   Updated: 2025/01/16 14:22:54 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    eating(t_philosopher *philo)
{
	take_forks(philo);
	eat(philo);
	drop_forks(philo);
    meal_count(philo);
    philo->current_state = SLEEPING;
}

void    take_forks(t_philosopher *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(philo->left_fork);
    }
    else if (philo->id % 2 != 0)
    {
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->right_fork);
    }
    pthread_mutex_lock(philo->print_mutex);
    print_status(philo, FORK);
    pthread_mutex_unlock(philo->print_mutex);
}

void    eat(t_philosopher *philo)
{
    philo->last_meal_time = current_time();
    pthread_mutex_lock(philo->print_mutex);
    print_status(philo, EATING);
    pthread_mutex_unlock(philo->print_mutex);
    usleep(philo->params->time_to_eat * 1000);
}

void    drop_forks(t_philosopher *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
    }
    else if (philo->id % 2 != 0)
    {
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
    }
}

void meal_count(t_philosopher *philo)
{
    if (philo->params->eat_times)
        philo->meals++;
}