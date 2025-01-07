/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_threads.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:49:39 by antonimo          #+#    #+#             */
/*   Updated: 2024/12/17 12:39:01 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// pthread_create(&params->philosopher, NULL, life_cycle, params);

/*REVISAR:
- Recibe params para hacer el cálculo de si tiene tiempo para la acción correspondiente
- Debería recibir la acción que corresponde para que pueda calcular en función de si es comer o dormir
- No sé si el mutex debe ser utilizado para hacer este printf o ya es pasarse*/

unsigned int    get_current_time_ms(void)
{
    struct timeval current_time;
    
    gettimeofday(&current_time, NULL);
    return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

unsigned int    get_time_diff_ms(unsigned int start_time)
{
    return (get_current_time_ms() - start_time);
}

bool    check_death_time(t_philosopher *philo)
{
    unsigned int time_diff;
    
    time_diff = get_time_diff_ms(philo->last_meal_time);
    if (time_diff >= philo->params->time_to_die)
    {
        pthread_mutex_lock(philo->print_mutex);
        printf("%u %u died\n", time_diff, philo->id);
        return (true);
    }
    return (false);
}

void    update_last_meal_time(t_philosopher *philo)
{
    philo->last_meal_time = get_current_time_ms();
}

void    *philosopher_routine(void *arg)
{
    t_philosopher *philo;
    
    philo = (t_philosopher *)arg;
    update_last_meal_time(philo);
    philo->current_state = THINKING;
    
    while (1)
    {
        if (check_death_time(philo))
            return (NULL);
        if (philo->current_state == EATING)
            eating(philo);
        else if (philo->current_state == SLEEPING)
            sleeping(philo);
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
    printf("%u %u is eating\n", get_time_diff_ms(philo->last_meal_time), philo->id);
    pthread_mutex_unlock(philo->print_mutex);
    
    update_last_meal_time(philo);
    usleep(philo->params->time_to_eat * 1000);
    
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    philo->current_state = SLEEPING;
}

void    sleeping(t_philosopher *philo)
{
    pthread_mutex_lock(philo->print_mutex);
    printf("%u %u is sleeping\n", philo->id);
    pthread_mutex_unlock(philo->print_mutex);
    usleep(philo->params->time_to_sleep * 1000);
    philo->current_state = THINKING;
}

void    thinking(t_philosopher *philo)
{
    pthread_mutex_lock(philo->print_mutex);
    printf("%u %u is thinking\n", philo->id);
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
