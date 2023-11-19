/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_spacies.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/20 00:42:30 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

static t_uint	kdo_push_to_spacies(t_kdo_neat *nn,
		t_kdo_spacies *spacies, t_kdo_genome *genome)
{
	t_list	*genome_element;

	genome_element = ft_lstnew(genome);
	if (!genome_element)
		kdo_neat_cleanup(nn, ERRLOC, EXIT_FAILURE);
	spacies->fitness_max = ft_max_double(spacies->fitness_max, genome->fitness);
	spacies->fitness_avg = (spacies->fitness_avg * spacies->genome_count + genome->fitness)
		/ (spacies->genome_count + 1);
	ft_lstadd_back(&spacies->genome, genome_element);
	spacies->genome_count++;
}

static t_uint	kdo_find_spacies(t_kdo_neat *nn, t_kdo_genome *genome)
{
	t_uint	spacies_index;
	float	spacies_score;
	t_uint	best_compatibility_index;
	float	best_compatibility_score;

	spacies_index = 0;
	best_compatibility_index = 0;
	best_compatibility_score = FLT_MAX;
	while (spacies_index < nn->population.spacies_count
		&& nn->population.spacies[spacies_index].genome_count)
	{
		spacies_score = kdo_compatibility_score(nn, genome,
				nn->population.spacies[spacies_index].genome->data);
		if (spacies_score < best_compatibility_score)
		{
			best_compatibility_score = spacies_score;
			best_compatibility_index = spacies_index;
		}
		spacies_index++;
	}
	if (nn->params.compatibility_limit < best_compatibility_score
		&& spacies_index != nn->population.spacies_count)
		return (spacies_index);
	return (best_compatibility_index);
}
