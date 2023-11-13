/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/14 00:11:26 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

t_kdo_link	*kdo_get_link(t_kdo_genome_buf *buf, t_kdo_node *to)
{
	t_kdo_link	link;

	link.to = to;
	link.weight = (ft_randf() * 2) - 1;
	link.enable = FT_TRUE;
	return (ft_buf_write(buf->link, (t_buf){&link, sizeof(t_kdo_link)},
		buf->link_count * sizeof(t_kdo_link)));
}

void	kdo_mutate
