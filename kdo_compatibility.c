/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_compatibility.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/26 23:34:51 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

static float	_diff_weight(t_kdo_link *link1, t_kdo_link *link2)
{
	return (ft_abs_float(link1->weight - link2->weight));
}

static float	_diff_bias(t_kdo_node *node1, t_kdo_node *node2)
{
	return (ft_abs_float(node1->bias - node2->bias));
}

static void	_compatibility_node(t_kdo_compatibility *comp,
		t_kdo_node *node1, t_kdo_node *node2)
{
	t_list	*current1;
	t_list	*current2;
	int		cmp;

	current1 = node1->link;
	current2 = node2->link;
	while (current1 && current2)
	{
		cmp = kdo_link_id_cmp(current1->data, current2->data);
		if (cmp == 0)
		{
			comp->diff_weight
				+= _diff_weight(current1->data, current2->data);
			comp->same_link += 1.0f;
		}
		if (cmp <= 0)
			current1 = current1->next;
		if (0 <= cmp)
			current2 = current2->next;
	}
}

static void	_compatibility_genome(t_kdo_compatibility *comp,
		t_kdo_genome *genome1, t_kdo_genome *genome2)
{
	t_list	*current1;
	t_list	*current2;
	int		cmp;

	ft_lstsort(&genome1->node, kdo_node_id_cmp);
	ft_lstsort(&genome2->node, kdo_node_id_cmp);
	current1 = genome1->node;
	current2 = genome2->node;
	while (current1 && current2)
	{
		cmp = kdo_node_id_cmp(current1->data, current2->data);
		if (cmp == 0)
		{
			_compatibility_node(comp, current1->data, current2->data);
			comp->diff_bias
				+= _diff_bias(current1->data, current2->data);
			comp->same_node += 1.0f;
		}
		if (cmp <= 0)
			current1 = current1->next;
		if (0 <= cmp)
			current2 = current2->next;
	}
}

float	kdo_compatibility_score(t_kdo_neat *nn,
		t_kdo_genome *genome1, t_kdo_genome *genome2)
{
	t_kdo_compatibility	comp;
	float				delta;

	comp.same_link = 0.0f;
	comp.same_node = 0.0f;
	comp.diff_weight = 0.0f;
	comp.diff_bias = 0.0f;
	_compatibility_genome(&comp, genome1, genome2);
	comp.diff_link = (float)(genome1->link_count + genome2->link_count)
		- 2.0f * comp.same_link;
	comp.diff_node = (float)(genome1->node_count + genome2->node_count)
		- 2.0f * comp.same_node;
	comp.diff_weight /= comp.same_link;
	comp.diff_bias /= comp.same_node;
	delta = nn->params.link_coef * comp.diff_link / nn->max_link_count
		+ nn->params.node_coef * comp.diff_node / nn->max_node_count
		+ nn->params.weight_coef * comp.diff_weight
		+ nn->params.bias_coef * comp.diff_bias;
	return (delta);
}
