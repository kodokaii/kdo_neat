/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_spacies.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/24 16:13:57 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

static void	_get_reclassify(t_kdo_neat *nn,
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

static t_uint	_find_spacies(t_kdo_neat *nn, t_kdo_genome *genome)
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

static void	_update_spacies(t_kdo_spacies *spacies)
{
	t_list	*current;
	float	current_fitness;
	float	fitness_sum;
	float	fitness_max;

	fitness_max = 0;
	fitness_sum = 0;
	current = spacies->genome;
	while (current)
	{
		current_fitness = ((t_kdo_genome *)current->data)->fitness;
		fitness_sum += current_fitness;
		fitness_max = ft_max_double(fitness_max, current_fitness);
		current = current->next;
	}
	spacies->no_progress_count++;
	if (spacies->fitness_max < fitness_max)
		spacies->no_progress_count = 0;
	spacies->fitness_avg = fitness_sum / spacies->genome_count;
	spacies->fitness_max = fitness_max;
}

void	kdo_spacies(t_kdo_neat *nn)
{
	float	modifier_coef;
	t_list	*reclassify;
	t_list	*current;
	t_uint	i;

	i = 0;
	reclassify = NULL;
	while (i < nn->population.spacies_count)
		_get_reclassify(nn, nn->population.spacies + i++, &reclassify);
	current = reclassify;
	while (current)
	{
		i = _find_spacies(nn, current->data);
		kdo_push_to_spacies(nn, nn->population.spacies + i, current->data);
		current = current->next;
	}
	while (i < nn->population.spacies_count)
		_update_spacies(nn->population.spacies + i++);
	modifier_coef = (float)nn->spacies_target_count
		/ (float)kdo_spacies_fill_count(nn) - 1;
	nn->params.compatibility_limit
		-= nn->params.compatibility_modifer * modifier_coef;
	ft_lstclear(&reclassify, NULL);
}
