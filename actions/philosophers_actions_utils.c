/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_actions_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:49:39 by antonimo          #+#    #+#             */
/*   Updated: 2025/01/27 11:27:56 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_status(t_philo *philo, unsigned int action)
{
	if (!dead_status(philo))
	{
		if (action == EATING)
			printf(BOLD COLOR_GREEN "%u %u is eating\n" COLOR_RESET, \
				get_timestamp(philo), philo->id);
		else if (action == SLEEPING)
			printf("%u %u is sleeping\n", get_timestamp(philo),
				philo->id);
		else if (action == THINKING)
			printf("%u %u is thinking\n", get_timestamp(philo),
				philo->id);
		else if (action == FORK)
			printf("%u %u has taken a fork\n", get_timestamp(philo),
				philo->id);
		else if (action == FINISH)
		{
			printf(BOLD COLOR_BLUE "%u All philosophers have eaten: ", \
			get_timestamp(philo));
			printf("%u times\n", philo->args.eat_times);
		}
	}
	if (action == DEAD)
		printf(COLOR_RED "%u %u died\n" COLOR_RESET,
			get_timestamp(philo), philo->id);
}

unsigned int	get_timestamp(t_philo *philo)
{
	unsigned int	res;

	pthread_mutex_lock(&philo->params->timestamp_mutex);
	res = time_diff(philo->params->timestamp);
	pthread_mutex_unlock(&philo->params->timestamp_mutex);
	return (res);
}
