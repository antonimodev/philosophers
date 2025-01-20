/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:25:03 by antonimo          #+#    #+#             */
/*   Updated: 2025/01/17 14:40:03 by antonimo         ###   ########.fr       */
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

typedef struct s_args
{
	unsigned int	philos_num; // NECESARIO PARA SABER EL NUMERO DE FILOSOFOS
	unsigned int	time_to_eat; // NECESARIO
	unsigned int	time_to_sleep; // NECESARIO
	unsigned int	time_to_die; // NECESARIO
	//timestamp no es un args, es contador de tiempo del programa
	unsigned int	timestamp; // NECESARIO PARA IMPRIMIR EL TIEMPO
	unsigned int	eat_times; // NECESARIO PARA ARG OPCIONAL
}	t_args;

typedef struct s_params
{
	bool			dead; // NECESARIO PARA SABER SI HA MUERTO
	pthread_t		monitor; // NECESARIO PARA CREAR EL HILO MONITOR
	pthread_t		*threads; // NECESARIO PARA CREAR LOS HILOS
	pthread_mutex_t	*forks; // NECESARIO, ARRAY DE TENEDORES (MUTEX)
	pthread_mutex_t	print_mutex; // NECESARIO PARA IMPRIMIR
	pthread_mutex_t dead_mutex; // NECESARIO PARA CREAR EL MUTEX DE DEAD - Solo se usa en monitor de momento
}	t_params;

typedef struct s_philo
{
    unsigned int    id; // NECESARIO PARA IDENTIFICAR CADA FILOSOFO
    unsigned int    last_meal_time; // NECESARIO PARA CONTABILIZAR EN FORMATO 00:00:00
	unsigned int	meals; // NECESARIO PARA CONTABILIZAR LAS COMIDAS
    t_args			args; // Copia de los times y los philos_num
	t_state         current_state; // NECESARIO PARA CAMBIAR LOS ESTADOS EN LA RUTINA
    pthread_mutex_t *left_fork; // NECESARIO, APUNTA AL ARRAY DE FORKS DE PARAMS
    pthread_mutex_t *right_fork; // NECESARIO, APUNTA AL ARRAY DE FORKS DE PARAMS
    pthread_mutex_t *print_mutex; // CREO QUE NO ES NECESARIO, PODRIAMOS USAR EL DE PARAMS
    t_params        *params; // NO se si es necesario, no deben compartir recursos
}   t_philo;


// ---------------------- ACTIONS ---------------------- //
// philosophers_actions_utils.c
void			print_status(t_philo *philo, unsigned int action);

// philosophers_eat.c
void			eating(t_philo *philo);
void			take_forks(t_philo *philo);
void			eat(t_philo *philo);
void			drop_forks(t_philo *philo);
void			meal_count(t_philo *philo);

// philosophers_sleep.c
void			sleeping(t_philo *philo);
void			rest(t_philo *philo);

// philosophers_think.c
void			thinking(t_philo *philo);
void			think(t_philo *philo);

// ---------------------- MUTEX ---------------------- //
// philosophers_mutex.c
pthread_mutex_t	*create_forks(unsigned int num_philos);
bool			init_mutex_array(pthread_mutex_t *forks, unsigned int philos_num);
bool			init_print_mutex(pthread_mutex_t *mutex);
bool			init_dead_mutex(pthread_mutex_t *mutex);
void			destroy_mutex(t_params *params, t_args *args);

// ---------------------- PARSE ---------------------- //
// philosophers_parse_utils.c
unsigned int	ft_atoi(char *str);
bool			uint_limits(unsigned long num);
bool			is_number(void *param);

// philosophers_parse.c
bool			check_av(char **av, bool (*function)(void *));
bool			init_args(t_args *params, int ac, char **av);
unsigned int	*parse_values(int ac, char **av);

// ---------------------- SRC ---------------------- //
// philosophers_routine.c
void			*routine(void *philo);
bool			dead_status(t_philo *philo);

// philosophers_time.c
unsigned int	current_time(void);
unsigned int	time_diff(unsigned int time);

// philosophers_malloc.c
bool			malloc_philosophers_array(t_args *params, t_philo **philo);
bool			malloc_threads(t_params *params, t_args *args, t_philo *philo);

// philosophers_initialization.c
bool			init_philos(t_params *params, t_args *args, t_philo **philo, int ac, char **av);
bool			init_forks(t_params *params, t_args *args);
bool			init_philo_struct(t_params *params, t_args *args, t_philo **philo);

// philosophers_monitor.c
void			*monitor(void *arg);
bool			meals_done(t_philo *philo);
bool			is_death(t_philo *philo);

// philosophers.c
bool			start_routine(t_params *params, t_args *args, t_philo *philo);
void			cleanup(t_params *params, t_args *args, t_philo *philo);
void			wait_threads(t_params *params, t_args *args);

#endif