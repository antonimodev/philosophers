/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:41:52 by antonimo          #+#    #+#             */
/*   Updated: 2024/12/17 14:22:19 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_params params;

	ac--;
	av++;
	if (ac == 4 || ac == 5)
	{
		memset(&params, 0, sizeof(t_params));
		if (!init_params(&params, ac, av))
			return (2);
		/* life_cycle(&params); // probandolo aun */
		printf("GUCCI\n"); // comprobación
	}
	else
		printf("Error: invalid number of arguments\n");
	return (2);
}
