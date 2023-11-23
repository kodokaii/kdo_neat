/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/23 22:59:29 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

void	kdo_feed_forward_link(t_kdo_link *link, float input)
{
	if (link->enable)
		link->to->input += input * link->weight;
}

void	kdo_crossover_link(t_kdo_link *link1, t_kdo_link *link2,
		t_kdo_link *link_child)
{
	if (ft_randf() < 0.5)
		*link_child = *link1;
	else
		*link_child = *link2;
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
