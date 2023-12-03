/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_speciation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/03 16:01:05 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

static void	_get_reclassify(t_kdo_neat *nn,
		t_kdo_species *species, t_list **reclassify)
{
	t_list	*current;
	t_list	*to_reclassify;
	float	score;

	if (2 <= species->genome_count)
	{
		current = species->genome;
		while (current->next)
		{
			score = kdo_compatibility_score(nn,
					species->genome->data, current->next->data);
			if (nn->params.compatibility_limit < score)
			{
				to_reclassify = current->next;
				current->next = current->next->next;
				ft_lstadd_front(reclassify, to_reclassify);
				species->genome_count--;
			}
			else
				current = current->next;
		}
	}
}

void	kdo_speciation(t_kdo_neat *nn)
{
	float	modifier_coef;
	t_list	*reclassify;
	t_list	*current;
	t_uint	i;

	i = 0;
	reclassify = NULL;
	while (i < nn->population.species_count)
		_get_reclassify(nn, nn->population.species + i++, &reclassify);
	current = reclassify;
	while (current)
	{
		kdo_push_to_species(nn,
			kdo_find_species(nn, current->data), current->data);
		current = current->next;
	}
	modifier_coef = (float)nn->population.species_count
		/ (float)nn->params.species_target_count - 1;
	nn->params.compatibility_limit
		+= nn->params.compatibility_modifer * modifier_coef;
}
