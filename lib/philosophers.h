/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:25:03 by antonimo          #+#    #+#             */
/*   Updated: 2024/12/17 14:21:30 by antonimo         ###   ########.fr       */
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

typedef struct s_params
{
	unsigned int	philos_num;
	unsigned int	eat_times;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	time_to_die;
	pthread_t		*philosophers;
}	t_params;

// parse.c
bool			check_av(char **av, bool (*function)(void *));
bool			init_params(t_params *params, int ac, char **av);
unsigned int	*parse_values(int ac, char **av);

// philosophers_utils.c
bool	uint_limits(unsigned long num);
bool	is_number(void *param);
int		ft_atoi(char *str);


// philosophers_treads.c
/* void	life_cycle(t_params *params); */

#endif