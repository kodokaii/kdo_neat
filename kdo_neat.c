/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_neat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/29 22:50:35 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"
#include <time.h>

static void	_loop(t_kdo_neat *nn)
{
	nn->generation_being++;
	kdo_run(nn);
	kdo_speciation(nn);
	kdo_update_fitness(nn);
	kdo_print_population(&nn->population, STDOUT_FILENO);
	ft_printf("SP_NB == %d\n", kdo_spacies_fill_count(nn));
	kdo_crossover(nn);
	kdo_mutate(nn);
}

void	kdo_neat(t_kdo_neat_params *params)
{
	t_kdo_neat	nn;

	ft_srand(time(NULL));
	kdo_init(&nn, params);
	while (1)
		_loop(&nn);
	kdo_neat_cleanup(&nn, "Good !\n", EXIT_SUCCESS);
}
