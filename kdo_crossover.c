/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_crossover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/29 22:42:03 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

void	kdo_crossover(t_kdo_neat *nn)
{
	t_kdo_population	tmp;
	t_uint				i;

	i = 0;
	tmp = nn->population;
	nn->population = nn->old_population;
	nn->old_population = tmp;
	kdo_reset_population(&nn->population);
	while (i < nn->old_population.spacies_count)
	{
		kdo_crossover_spacies(nn,
			nn->population.spacies + i, nn->old_population.spacies + i);
		i++;
	}
}
