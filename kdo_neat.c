/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_neat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/28 14:46:32 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

static void	_loop(t_kdo_neat *nn)
{
	nn->generation_being++;
	kdo_run(nn);
	kdo_speciation(nn);
	kdo_update_fitness(nn);
	kdo_crossover(nn);
	kdo_mutate(nn);
}

void	kdo_neat(t_kdo_neat_params *params)
{
	t_kdo_neat	nn;

	kdo_init(&nn, params);
	while (1)
		_loop(&nn);
}
