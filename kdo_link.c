/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/05 20:43:25 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

void	kdo_link_load(t_kdo_neat *nn, t_kdo_genome *genome_from,
		t_kdo_node *node_from)
{
	t_kdo_save_node	*node_src;
	t_kdo_save_link	*link_src;
	t_kdo_link		*link_dst;
	t_uint			i;

	i = 0;
	node_src = nn->params.load->node + nn->params.load->node_index;
	while (i++ < node_src->link_count)
	{
		link_src = nn->params.load->link + nn->params.load->link_index;
		link_dst = kdo_get_link(nn,
				kdo_find_node_id(genome_from, link_src->to_id));
		link_dst->weight = link_src->weight;
		link_dst->enable = link_src->enable;
		kdo_add_link(nn, genome_from, node_from, link_dst);
		nn->params.load->link_index++;
	}
	nn->params.load->node_index++;
}

void	kdo_feed_forward_link(t_kdo_link *link, float input)
{
	if (link->enable)
		link->to->input += input * link->weight;
}

void	kdo_crossover_link(t_kdo_link *link1, t_kdo_link *link2)
{
	if (ft_randf() < 0.5)
	{
		link1->weight = link2->weight;
		link1->enable = link2->enable;
	}
}

void	kdo_mutate_link(t_kdo_neat *nn, t_kdo_link *link)
{
	float	rng;

	rng = ft_randf();
	if (rng <= nn->params.weight_random_prob)
		link->weight = (ft_randf() * 2) - 1;
	else if (rng <= nn->params.weight_shift_prob
		&& -(nn->params.weight_cap) < link->weight
		&& link->weight < nn->params.weight_cap)
		link->weight += ((ft_randf_norm() * 2) - 1)
			* nn->params.weight_shift_coef;
	if (ft_randf() <= nn->params.link_toggle_prob)
		link->enable = !link->enable;
}

void	kdo_save_link(t_kdo_neat *nn, t_kdo_link *link_src)
{
	t_kdo_save_link	*link_dst;

	link_dst = nn->params.save->link + nn->params.save->link_index;
	link_dst->to_id = link_src->to->id;
	link_dst->weight = link_src->weight;
	link_dst->enable = link_src->enable;
	nn->params.save->link_index++;
}
