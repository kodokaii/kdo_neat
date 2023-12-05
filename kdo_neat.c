/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_neat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/05 03:40:43 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"
#include <time.h>

static void	_loop(t_kdo_neat *nn)
{
	nn->generation_being++;
	kdo_crossover(nn);
	kdo_mutate(nn);
	kdo_speciation(nn);
	kdo_run(nn);
	kdo_update_fitness(nn);
}

void	kdo_neat(t_kdo_neat_params *params)
{
	t_kdo_neat		nn;

	ft_srand(time(NULL));
	kdo_init(&nn, params);
	while (nn.population.fitness_max < nn.params.fitness_target)
		_loop(&nn);
	kdo_print_population(&nn.population, STDOUT_FILENO);
	if (params->save)
		kdo_save(&nn);
	kdo_neat_cleanup(&nn, "Good !\n", EXIT_SUCCESS);
}
