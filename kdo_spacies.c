/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_spacies.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/20 20:25:39 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

static void	kdo_push_to_spacies(t_kdo_neat *nn,
		t_kdo_spacies *spacies, t_kdo_genome *genome)
{
	t_list	*genome_element;

	genome_element = ft_lstnew(genome);
	if (!genome_element)
		kdo_neat_cleanup(nn, ERRLOC, EXIT_FAILURE);
	spacies->fitness_max = ft_max_double(spacies->fitness_max, genome->fitness);
	spacies->fitness_avg
		= (spacies->fitness_avg * spacies->genome_count + genome->fitness)
		/ (spacies->genome_count + 1);
	ft_lstadd_back(&spacies->genome, genome_element);
	spacies->genome_count++;
}

static t_uint	kdo_find_spacies(t_kdo_neat *nn, t_kdo_genome *genome)
{
	t_uint	spacies_index;
	float	spacies_score;
	t_uint	best_index;
	float	best_score;

	spacies_index = 0;
	best_index = 0;
	best_score = FLT_MAX;
	while (spacies_index < nn->population.spacies_count
		&& nn->population.spacies[spacies_index].genome_count)
	{
		spacies_score = kdo_compatibility_score(nn, genome,
				nn->population.spacies[spacies_index].genome->data);
		if (spacies_score < best_score)
		{
			best_score = spacies_score;
			best_index = spacies_index;
		}
		spacies_index++;
	}
	if (nn->params.compatibility_limit < best_score
		&& spacies_index != nn->population.spacies_count)
		return (spacies_index);
	return (best_index);
}

static void	kdo_get_reclassify(t_kdo_neat *nn,
		t_kdo_spacies *spacies, t_list **reclassify)
{
	t_list	*current;
	t_list	*to_reclassify;
	float	score;

	if (1 < spacies->genome_count)
	{
		current = spacies->genome;
		while (current->next)
		{
			score = kdo_compatibility_score(nn,
					spacies->genome->data, current->next->data);
			if (nn->params.compatibility_limit < score)
			{
				to_reclassify = current->next;
				current->next = current->next->next;
				ft_lstadd_front(reclassify, to_reclassify);
				spacies->genome_count--;
			}
			else
				current = current->next;
		}
	}
}

void	kdo_spacies(t_kdo_neat *nn)
{
	t_list	*reclassify;
	t_list	*current;
	t_uint	i;

	i = 0;
	reclassify = NULL;
	while (i < nn->population.spacies_count)
		kdo_get_reclassify(nn, nn->population.spacies + i++, &reclassify);
	current = reclassify;
	while (current)
	{
		i = kdo_find_spacies(nn, current->data);
		kdo_push_to_spacies(nn, nn->population.spacies + i, current->data);
		current = current->next;
	}
	ft_lstclear(&reclassify, NULL);
}
