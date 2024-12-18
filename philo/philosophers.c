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
	t_params	params;
	// array de forks(tenedores)?

	//init_mutex(array de forks, &params);
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
bool	init_mutex(pthread_mutex_t *forks, int philos_num) // Aquí philos num es de la estructura de params
{
	int	i;

	i = 0;
	while (i < philos_num)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0) // el != 0 es por legibilidad, la funcion devuelve 0 en éxito
			return (false); // aquí podríamos hacer printf para decir que los mutex no han podido inicializar correctamente
		i++;
	}
	return (true);
}