/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:25:03 by antonimo          #+#    #+#             */
/*   Updated: 2025/01/21 13:43:38 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define UINT_MAX 4294967295
# define COLOR_RESET "\x1b[0m"
# define COLOR_RED "\x1b[31m"
# define COLOR_GREEN "\x1b[32m"
# define COLOR_BLUE "\x1b[34m"
# define BOLD "\033[1m"

typedef enum e_error
{
	SUCCESS,
	ERROR_ARGUMENTS,
	ERROR_INIT,
	ERROR_ROUTINE,
}					t_error;

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	FORK,
	DEAD,
	FINISH
}					t_state;

typedef struct s_args
{
	unsigned int	philos_num;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	time_to_die;
	unsigned int	timestamp;
	unsigned int	eat_times;
}					t_args;

typedef struct s_params
{
	bool			dead;
	pthread_t		monitor;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	meal_count_mutex;
	pthread_mutex_t	dead_mutex;
}					t_params;

typedef struct s_philo
{
	unsigned int	id;
	unsigned int	last_meal_time;
	unsigned int	meals;
	t_args			args;
	t_state			current_state;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_mutex;
	t_params		*params;
}					t_philo;

// ---------------------- ACTIONS ---------------------- //
// philosophers_actions_utils.c
void				print_status(t_philo *philo, unsigned int action);

// philosophers_eat.c
void				eating(t_philo *philo);
void				take_forks(t_philo *philo);
void				eat(t_philo *philo);
void				drop_forks(t_philo *philo);
void				meal_count(t_philo *philo);

// philosophers_sleep.c
void				sleeping(t_philo *philo);
void				rest(t_philo *philo);

// philosophers_think.c
void				thinking(t_philo *philo);
void				think(t_philo *philo);

// ---------------------- MUTEX ---------------------- //
// philosophers_mutex.c
pthread_mutex_t		*create_forks(unsigned int num_philos);
bool				init_mutex_array(pthread_mutex_t *forks,
						unsigned int philos_num);
bool				init_individual_mutexes(t_params *params);
bool				init_individual_mutex(pthread_mutex_t *mutex, char *msg);
void				destroy_mutex(t_params *params, t_args *args);

// ---------------------- PARSE ---------------------- //
// philosophers_parse_utils.c
unsigned int		ft_atoi(char *str);
bool				uint_limits(unsigned long num);
bool				is_number(void *param);

// philosophers_parse.c
bool				check_av(char **av, bool (*function)(void *));
unsigned int		*parse_values(int ac, char **av);

// ---------------------- SRC ---------------------- //
// philosophers_initialization.c
bool				init_philos(t_params *params, t_args *args,
						t_philo **philo);
bool				init_args(t_args *params, int ac, char **av);
bool				init_forks(t_params *params, t_args *args);
bool				init_philo_struct(t_params *params, t_args *args,
						t_philo **philo);

// philosophers_malloc.c
bool				malloc_philos_array(t_params *params, t_args *args,
						t_philo **philo);
bool				malloc_threads(t_params *params, t_args *args,
						t_philo *philo);

// philosophers_monitor.c
void				*monitor(void *arg);
bool				meals_done(t_philo *philo);
bool				is_death(t_philo *philo);

// philosophers_routine.c
void				*routine(void *philo);
void				set_start_routine(t_philo *philo);
bool				philo_exception(t_philo *philo);
bool				dead_status(t_philo *philo);

// philosophers_time.c
unsigned int		current_time(void);
unsigned int		time_diff(unsigned int time);

// philosophers.c
bool				start_routine(t_params *params, t_args *args,
						t_philo *philo);
void				wait_threads(t_params *params, t_args *args);
void				cleanup(t_params *params, t_args *args, t_philo *philo);

#endif