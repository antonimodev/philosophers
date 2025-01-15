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
	THINKING,
	FORK,
	DEAD
}	t_state;

typedef struct s_params
{
	unsigned int	philos_num;
	unsigned int	timestamp; // añadido para imprimir en consola
	unsigned int	time_to_eat;
	unsigned int	time_to_die;
	unsigned int	time_to_sleep;
	unsigned int	eat_times;
	bool			eat_arg;
	pthread_t		*philosophers;
	pthread_mutex_t	*forks; // pa comer
	pthread_mutex_t	print_mutex; // pa imprimi
}	t_params;

typedef struct s_philosopher
{
    unsigned int    id;
    unsigned int    last_meal_time;
	unsigned int	meals;
	unsigned int	death;
	unsigned int	elapsed_time;
    t_state         current_state;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *print_mutex; // turno de palabra
    t_params        *params;
}   t_philosopher;


// ---------------------- ACTIONS ---------------------- //
// philosophers_actions_utils.c
void			print_status(t_philosopher *philo, unsigned int action);

// philosophers_eat.c
void			eating(t_philosopher *philo);
void			take_forks(t_philosopher *philo);
void			eat(t_philosopher *philo);
void			drop_forks(t_philosopher *philo);
void			meal_count(t_philosopher *philo);

// philosophers_sleep.c
void			sleeping(t_philosopher *philo);
void			rest(t_philosopher *philo);

// philosophers_think.c
void			thinking(t_philosopher *philo);
void			think(t_philosopher *philo);

// ---------------------- PARSE ---------------------- //
// philosophers_parse.c
bool			check_av(char **av, bool (*function)(void *));
bool			init_params(t_params *params, int ac, char **av);
unsigned int	*parse_values(int ac, char **av);

// philosophers_parse_utils.c
unsigned int	ft_atoi(char *str);
bool			uint_limits(unsigned long num);
bool			is_number(void *param);

// ---------------------- MUTEX ---------------------- //
// philosophers_mutex.c
pthread_mutex_t	*create_forks(unsigned int num_philos);
bool			init_mutex(pthread_mutex_t *forks, int philos_num);

// ---------------------- SRC ---------------------- //
// philosophers_routine.c
void			*routine(void *philo);

// philosophers_time.c
unsigned int	current_time(void);
unsigned int	time_diff(unsigned int time);


#endif