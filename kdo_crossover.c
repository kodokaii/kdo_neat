/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_crossover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/01 00:30:08 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

void	kdo_crossover(t_kdo_neat *nn)
{
	t_kdo_population	tmp_population;
	t_uint				i;

	i = 0;
	tmp_population = nn->population;
	nn->population = nn->old_population;
	nn->old_population = tmp_population;
	kdo_reset_population(&nn->population);
	while (i < nn->old_population.species_count)
	{
		kdo_crossover_species(nn, nn->old_population.species + i);
		i++;
	}
}
