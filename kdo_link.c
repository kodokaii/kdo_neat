/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/15 21:18:20 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

t_kdo_link	*kdo_get_link(t_kdo_neat *nn, t_kdo_node *to)
{
	t_kdo_link	*link;

	link = ft_buf_alloc(&nn->population.genome_buf.link,
			nn->population.genome_buf.link_count * sizeof(t_kdo_link),
			sizeof(t_kdo_link));
	if (!link)
		kdo_neat_cleanup(nn, ERRLOC, EXIT_FAILURE);
	link->to = to;
	link->weight = (ft_randf() * 2) - 1;
	link->enable = FT_TRUE;
	nn->population.genome_buf.link_count++;
	return (link);
}

void	kdo_mutate_link(t_kdo_neat *nn, t_kdo_link *link)
{
	float	rng;

	rng = ft_randf();
	if (rng <= nn->params.link_toggle_prob)
		link->enable = !link->enable;
	if (rng <= nn->params.weight_random_prob)
		link->weight = (ft_randf() * 2) - 1;
	else if (rng <= nn->params.weight_shift_prob)
		link->weight += ((ft_randf_norm() * 2) - 1) / 10;
}

void	kdo_feed_forward_link(t_kdo_link *link, float input)
{
	link->to->input += input * link->weight;
}

void	kdo_add_link(t_kdo_neat *nn, t_kdo_node *node, t_kdo_link *link)
{
	t_list	*link_element;

	link_element = ft_lstnew(link);
	if (!link_element)
		kdo_neat_cleanup(nn, ERRLOC, EXIT_FAILURE);
	ft_lstsort_merge(&node->link, link_element, kdo_link_cmp);
	node->link_count++;
}
