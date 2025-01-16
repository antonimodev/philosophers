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

# define UINT_MAX		4294967295
# define COLOR_RESET	"\x1b[0m"
# define COLOR_RED		"\x1b[31m"
# define COLOR_GREEN	"\x1b[32m"
# define COLOR_BLUE		"\x1b[34m"
# define BOLD			"\033[1m"

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	FORK,
	DEAD,
	FINISH
}	t_state;

typedef struct s_params
{
	unsigned int	philos_num; // NECESARIO PARA SABER EL NUMERO DE FILOSOFOS
	unsigned int	timestamp; // NECESARIO PARA IMPRIMIR EL TIEMPO
	unsigned int	time_to_eat; // NECESARIO
	unsigned int	time_to_sleep; // NECESARIO
	unsigned int	time_to_die; // NECESARIO
	unsigned int	dead; // NECESARIO PARA SABER SI HA MUERTO UN FILOSOFO -- Plantemiento de sustituir death por finish
	unsigned int	eat_times; // NECESARIO PARA ARG OPCIONAL
	bool			eat_arg; // NECESARIO PARA AUMENTAR MEALS
	pthread_t		monitor; // NECESARIO PARA CREAR EL HILO MONITOR - Pendiente
	pthread_t		*philosophers; // NECESARIO PARA CREAR LOS HILOS
	pthread_mutex_t	*forks; // NECESARIO, ARRAY DE TENEDORES (MUTEX)
	pthread_mutex_t	print_mutex; // NECESARIO PARA IMPRIMIR
}	t_params;

typedef struct s_philosopher
{
    unsigned int    id; // NECESARIO PARA IDENTIFICAR CADA FILOSOFO
    unsigned int    last_meal_time; // NECESARIO PARA CONTABILIZAR EN FORMATO 00:00:00
	unsigned int	meals; // NECESARIO PARA CONTABILIZAR LAS COMIDAS
	unsigned int	elapsed_time; // NECESARIO PARA CONTABILIZAR EL TIEMPO TRANSCURRIDO
    t_state         current_state; // NECESARIO PARA CAMBIAR LOS ESTADOS EN LA RUTINA
    pthread_mutex_t *left_fork; // NECESARIO, APUNTA AL ARRAY DE FORKS DE PARAMS
    pthread_mutex_t *right_fork; // NECESARIO, APUNTA AL ARRAY DE FORKS DE PARAMS
    pthread_mutex_t *print_mutex; // CREO QUE NO ES NECESARIO, PODRIAMOS USAR EL DE PARAMS
    t_params        *params; // NECESARIO PARA ACCEDER A LOS PARAMETROS
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
bool			init_mutex_array(pthread_mutex_t *forks, int philos_num);

// ---------------------- SRC ---------------------- //
// philosophers_routine.c
void			*routine(void *philo);

// philosophers_time.c
unsigned int	current_time(void);
unsigned int	time_diff(unsigned int time);

// ---------------------- MONITOR ---------------------- //
// philosophers_monitor.c
void			*monitor(void *arg);
bool			meals_done(t_philosopher *philo);
bool			is_death(t_philosopher *philo);

// ---------------------- MAIN ---------------------- // habra que ponerlo en otro archivo, no en main
// philosophers.c
void			init_philosophers(t_params *params, t_philosopher *philo);
bool			malloc_philosophers_array(t_params *params, t_philosopher **philo);
bool			start_routine(t_params *params, t_philosopher *philo);
bool			init_mutex(pthread_mutex_t *mutex);
void			destroy_mutex(t_params *params);
void			cleanup(t_params *params, t_philosopher *philo);

#endif