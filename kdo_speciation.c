/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_speciation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/29 22:14:08 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

static void	_get_reclassify(t_kdo_neat *nn,
		t_kdo_spacies *spacies, t_list **reclassify)
{
	t_list	*current;
	t_list	*to_reclassify;
	float	score;

	if (2 <= spacies->genome_count)
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

void	kdo_speciation(t_kdo_neat *nn)
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
		kdo_push_to_spacies(nn,
			kdo_find_spacies(nn, current->data), current->data);
		current = current->next;
	}
	modifier_coef = (float)nn->params.spacies_target_count
		/ (float)kdo_spacies_fill_count(nn) - 1;
	nn->params.compatibility_limit
		-= nn->params.compatibility_modifer * modifier_coef;
	ft_lstclear(&reclassify, NULL);
}