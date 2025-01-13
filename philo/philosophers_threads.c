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

unsigned int    get_current_time_ms(void)
{
    struct timeval current_time;

    gettimeofday(&current_time, NULL);
    return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000); // operacion para trasnformar a ms
}

unsigned int    get_time_diff_ms(unsigned int start_time) // para los prints
{
    return (get_current_time_ms() - start_time);
}

bool    is_death(t_philosopher *philo, unsigned int action)
{
    unsigned int time_diff;
    unsigned int action_time;
    unsigned int time_remaining;

    if (action == EATING)
        action_time = philo->params->time_to_eat;
    else if (action == SLEEPING)
        action_time = philo->params->time_to_sleep;
    
    time_diff = philo->elapsed_time;
    
    if (time_diff + action_time >= philo->params->time_to_die)
    {
        time_remaining = philo->params->time_to_die - time_diff;
        pthread_mutex_lock(philo->print_mutex);
        usleep(time_remaining * 1000); // Esperamos hasta el momento exacto de la muerte
        printf("elapsed time: %u id: %u died\n", 
               philo->elapsed_time, philo->id);
        philo->death = 1;
        pthread_mutex_unlock(philo->print_mutex);
        return (true);
    }
    return (false);
}
// En esta función falta añadir is_death
void    *philosopher_routine(void *arg)
{
    t_philosopher	*philo;

    philo = (t_philosopher *)arg;
    philo->last_meal_time = get_current_time_ms();
    philo->params->timestamp = get_current_time_ms();
    while (1) // bucle infinito con philo->meals como condicion de salida
    {
        philo->elapsed_time = get_time_diff_ms(philo->last_meal_time);
        if (philo->current_state == EATING)
		{
            if (is_death(philo, EATING))
                break ;
			eating(philo);
			if (philo->meals == philo->params->eat_times)
				break ; // salimos del bucle retornando null
		}
        else if (philo->current_state == SLEEPING)
        {
            if(is_death(philo, SLEEPING))
                break ;
			sleeping(philo);
        }
        else if (philo->current_state == THINKING)
            thinking(philo);
    }
    return (NULL);
}

void    eating(t_philosopher *philo)
{
    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(philo->right_fork);
    pthread_mutex_lock(philo->print_mutex);
    printf("time: %u id: %u has taken forks\n", get_time_diff_ms(philo->params->timestamp), philo->id);
    printf("time: %u id: %u is eating\n", get_time_diff_ms(philo->params->timestamp), philo->id);
    philo->last_meal_time = get_current_time_ms();
    philo->elapsed_time = 0;
    pthread_mutex_unlock(philo->print_mutex);
    usleep(philo->params->time_to_eat * 1000);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
	philo->meals++;
    /* philo->elapsed_time = get_time_diff_ms(philo->last_meal_time); */
    philo->current_state = SLEEPING;
}

void    sleeping(t_philosopher *philo)
{
    philo->elapsed_time = get_time_diff_ms(philo->last_meal_time);
    pthread_mutex_lock(philo->print_mutex);
    printf("time: %u id: %u is sleeping\n", get_time_diff_ms(philo->params->timestamp), philo->id);
    pthread_mutex_unlock(philo->print_mutex);
    usleep(philo->params->time_to_sleep * 1000);
    philo->current_state = THINKING;
}

void    thinking(t_philosopher *philo)
{
    pthread_mutex_lock(philo->print_mutex);
    printf("time: %u id: %u is thinking\n", get_time_diff_ms(philo->params->timestamp), philo->id);
    pthread_mutex_unlock(philo->print_mutex);
    philo->current_state = EATING;
}

// Revisar si vale o no, tenemos array de mutex en struct params
pthread_mutex_t *create_forks(unsigned int num_philos)
{
    pthread_mutex_t *forks;
    unsigned int i;

    forks = malloc(sizeof(pthread_mutex_t) * num_philos);
    if (!forks)
        return (NULL);

    i = 0;
    while (i < num_philos)
    {
        if (pthread_mutex_init(&forks[i], NULL) != 0)
        {
            while (i > 0)
                pthread_mutex_destroy(&forks[--i]);
            free(forks);
            return (NULL);
        }
        i++;
    }
    return (forks);
}
