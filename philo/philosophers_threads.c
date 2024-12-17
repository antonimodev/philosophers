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

pthread_create(&params->philosopher, NULL, life_cycle, params); 

void	*life_cycle(void *params)
{
	t_params *placeholder;

	placeholder = params;

	if (estado = comer)
		//Evaluar gettimeofday -> empieza a contar mi ultima comida
		pthread_mutex_lock(&VARIABLE_MUTEX);
		pthread_mutex_lock(&VARIABLE_MUTEX);
		printf("esta comiendo");
		usleep(placeholder->time_to_eat);
		pthread_mutex_unlock(&VARIABLE_MUTEX);
		pthread_mutex_unlock(&VARIABLE_MUTEX);

	if (estado = dormir)
		printf("esta durmiendo");
		usleep(placeholder->time_to_sleep);
		//Evaluar gettimeofday -> checkea cuanto paso desde la ultima comida
	
	if (estado = pensar)
		printf("esta pensando");
		//Evaluar gettimeofday -> checkea cuanto paso desde la ultima comida
}

typedef struct s_philosopher
{
	unsigned int	philo_id;
	unsigned int	last_meal;
	/* pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork; */
}	t_philosopher;

