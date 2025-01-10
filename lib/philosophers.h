/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:25:03 by antonimo          #+#    #+#             */
/*   Updated: 2025/01/10 14:16:32 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <stdbool.h>

# define UINT_MAX 4294967295

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING
}	t_state;

typedef struct s_params
{
	unsigned int	philos_num;
	unsigned int	eat_times;
	unsigned int	time_to_eat;
	unsigned int	time_to_die;
	unsigned int	time_to_sleep;
	pthread_t		*philosophers;
	pthread_mutex_t	*forks; // pa comer
	pthread_mutex_t	print_mutex; // pa imprimi
}	t_params;

typedef struct s_philosopher
{
    unsigned int    id;
    unsigned int    last_meal_time;
	unsigned int	death;
    t_state         current_state;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *print_mutex; // turno de palabra
    t_params        *params;
}   t_philosopher;

// parse.c
bool			check_av(char **av, bool (*function)(void *));
bool			init_params(t_params *params, int ac, char **av);
unsigned int	*parse_values(int ac, char **av);

// philosophers_utils.c
bool			uint_limits(unsigned long num);
bool			is_number(void *param);
unsigned int	ft_atoi(char *str);

// philosophers_threads.c
void			life_cycle(t_params *params);
unsigned int	get_current_time_ms(void);
unsigned int	get_time_diff_ms(unsigned int start_time);
bool			check_death_time(t_philosopher *philo);
void			update_last_meal_time(t_philosopher *philo);
void			*philosopher_routine(void *arg);
void			eating(t_philosopher *philo);
void			sleeping(t_philosopher *philo);
void			thinking(t_philosopher *philo);
pthread_mutex_t	*create_forks(unsigned int num_philos);
// Add prototype at the top of header file
bool			init_mutex(pthread_mutex_t *forks, int philos_num);

#endif