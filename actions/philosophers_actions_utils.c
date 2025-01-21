/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_actions_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:49:39 by antonimo          #+#    #+#             */
/*   Updated: 2025/01/21 13:24:12 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_status(t_philo *philo, unsigned int action)
{
	if (!dead_status(philo))
	{
		if (action == EATING)
			printf(BOLD COLOR_GREEN "%u %u is eating\n" COLOR_RESET, \
				time_diff(philo->args.timestamp), philo->id);
		else if (action == SLEEPING)
			printf("%u %u is sleeping\n", time_diff(philo->args.timestamp),
				philo->id);
		else if (action == THINKING)
			printf("%u %u is thinking\n", time_diff(philo->args.timestamp),
				philo->id);
		else if (action == FORK)
			printf("%u %u has taken a fork\n", time_diff(philo->args.timestamp),
				philo->id);
		else if (action == FINISH)
		{
			printf(BOLD COLOR_BLUE "%u All philosophers have eaten: ", \
			time_diff(philo->args.timestamp));
			printf("%u times\n", philo->args.eat_times);
		}
	}
	if (action == DEAD)
		printf(COLOR_RED "%u %u died\n" COLOR_RESET,
			time_diff(philo->args.timestamp), philo->id);
}
