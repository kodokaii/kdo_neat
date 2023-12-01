/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_neat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/01 20:39:09 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"
#include <time.h>

size_t	g_species_sum = 0;

static void	_loop(t_kdo_neat *nn)
{
	nn->generation_being++;
	kdo_run(nn);
	kdo_speciation(nn);
	kdo_update_fitness(nn);
	g_species_sum += nn->population.species_count;
	kdo_crossover(nn);
	kdo_mutate(nn);
}

void	kdo_neat(t_kdo_neat_params *params)
{
	t_kdo_neat	nn;

	ft_srand(time(NULL));
	kdo_init(&nn, params);
	while (nn.old_population.fitness_max < nn.params.fitness_target)
		_loop(&nn);
	ft_printf("AVG: %d\n", g_species_sum / nn.generation_being);
	kdo_print_population(&nn.old_population, STDOUT_FILENO);
	kdo_neat_cleanup(&nn, "Good !\n", EXIT_SUCCESS);
}
