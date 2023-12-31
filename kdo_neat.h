/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_neat.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/05 20:38:55 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KDO_NEAT_H
# define KDO_NEAT_H

# include "libft/libft.h"

struct			s_kdo_link;
struct			s_kdo_node;
struct			s_kdo_neat;
typedef float	(*t_kdo_activation_func)(float in);
typedef float	(*t_kdo_fitness_func)(struct s_kdo_neat *, t_uint, void *);

typedef enum e_node_type
{
	INPUT_NODE,
	HIDDEN_NODE,
	OUTPUT_NODE,
}	t_node_type;

typedef struct s_kdo_save_link
{
	t_uint	to_id;
	float	weight;
	t_bool	enable;
}	t_kdo_save_link;

typedef struct s_kdo_save_node
{
	t_uint		link_count;
	float		bias;
	t_uint		activation_index;
	t_uint		layer;
	t_node_type	type;
	t_uint		id;
}	t_kdo_save_node;

typedef struct s_kdo_save_genome
{
	t_uint	node_count;
	t_uint	link_count;
	float	fitness;
}	t_kdo_save_genome;

typedef struct s_kdo_save_population
{
	t_uint				genome_count;
	t_uint				node_count;
	t_uint				link_count;
	t_uint				input_count;
	t_uint				output_count;
}	t_kdo_save_population;

typedef struct s_kdo_save_neat
{
	t_kdo_save_population	population;
	t_kdo_save_genome		*genome;
	t_kdo_save_node			*node;
	t_kdo_save_link			*link;
	t_uint					genome_index;
	t_uint					node_index;
	t_uint					link_index;
}	t_kdo_save_neat;

typedef struct s_kdo_link
{
	struct s_kdo_node	*to;
	float				weight;
	t_bool				enable;
}	t_kdo_link;

typedef struct s_kdo_node
{
	t_list				*link;
	t_uint				link_count;
	float				input;
	float				output;
	float				bias;
	t_uint				activation_index;
	t_uint				layer;
	t_node_type			type;
	t_uint				id;
}	t_kdo_node;

typedef struct s_kdo_genome
{
	t_list	*node;
	t_uint	node_count;
	t_uint	link_count;
	float	fitness;
}	t_kdo_genome;

typedef struct s_kdo_compatibility
{
	float	same_link;
	float	same_node;
	float	diff_link;
	float	diff_node;
	float	diff_weight;
	float	diff_bias;
}	t_kdo_compatibility;

typedef struct s_kdo_species
{
	t_list	*genome;
	t_uint	genome_count;
	t_uint	no_progress_count;
	float	fitness_max;
	float	fitness_avg;
}	t_kdo_species;

typedef struct s_kdo_population
{
	t_alloc				alloc;
	t_kdo_genome		*genome;
	t_kdo_species		*species;
	t_uint				genome_count;
	t_uint				species_count;
	float				fitness_max;
	float				fitness_avg;
}	t_kdo_population;

typedef struct s_kdo_neat_params
{
	float					link_coef;
	float					node_coef;
	float					weight_coef;
	float					bias_coef;
	float					weight_cap;
	float					compatibility_limit;
	float					compatibility_modifer;
	float					dropoff_age;
	float					survival_limit;
	float					weight_shift_coef;
	float					mutate_link_prob;
	float					weight_shift_prob;
	float					weight_random_prob;
	float					link_toggle_prob;
	float					link_add_prob;
	float					mutate_node_prob;
	float					bias_shift_coef;
	float					bias_shift_prob;
	float					function_change_prob;
	float					node_add_prob;
	float					fitness_target;
	t_uint					species_target_count;
	t_uint					genome_target_count;
	t_uint					input_count;
	t_uint					output_count;
	t_kdo_fitness_func		fitness_func;
	t_kdo_activation_func	*activation_func;
	t_uint					activation_func_count;
	t_kdo_save_neat			*load;
	t_kdo_save_neat			*save;
	void					*ptr;
}	t_kdo_neat_params;

typedef struct s_kdo_neat
{
	t_kdo_population		population;
	t_kdo_population		old_population;
	t_kdo_neat_params		params;
	float					*input;
	float					*output;
	t_uint					generation_being;
	t_uint					max_node_count;
	t_uint					max_link_count;
}	t_kdo_neat;

void			kdo_neat(t_kdo_neat_params *params);
t_kdo_neat		kdo_load_best_genome(t_kdo_save_neat *save,
					t_kdo_activation_func *activation_func,
					t_uint activation_func_count);
int				kdo_write_save(t_kdo_save_neat *save, char *file_name);
int				kdo_read_save(t_kdo_save_neat *save, char *file_name);

void			kdo_print_link(t_kdo_link *link, int fd);
void			kdo_print_node(t_kdo_node *node, int fd);
void			kdo_print_genome(t_kdo_genome *genome, int fd);
void			kdo_print_species(t_kdo_species *species, int fd);
void			kdo_print_population(t_kdo_population *pop, int fd);

t_kdo_link		*kdo_get_link(t_kdo_neat *nn, t_kdo_node *to);
void			kdo_add_link(t_kdo_neat *nn, t_kdo_genome *genome_from,
					t_kdo_node *node_from, t_kdo_link *link);
void			kdo_link_load(t_kdo_neat *nn, t_kdo_genome *genome_from,
					t_kdo_node *node_from);
void			kdo_feed_forward_link(t_kdo_link *link, float input);
void			kdo_crossover_link(t_kdo_link *link1, t_kdo_link *link2);
void			kdo_mutate_link(t_kdo_neat *nn, t_kdo_link *link);
void			kdo_save_link(t_kdo_neat *nn, t_kdo_link *link_src);

t_kdo_node		*kdo_get_node(t_kdo_neat *nn,
					t_uint layer, t_node_type type, t_uint id);
void			kdo_node_init(t_kdo_neat *nn,
					t_kdo_genome *genome_from, t_kdo_node *node);
t_bool			kdo_node_is_link(t_kdo_node *node_from, t_kdo_node *node_to);
t_kdo_node		*kdo_find_node_id(t_kdo_genome *genome, t_uint id);
void			kdo_add_node(t_kdo_neat *nn,
					t_kdo_genome *genome_from, t_kdo_node *node);
void			kdo_node_load(t_kdo_neat *nn, t_kdo_genome *genome_from);
void			kdo_feed_forward_node(t_kdo_neat *nn, t_kdo_node *node);
void			kdo_crossover_node(t_kdo_node *node1, t_kdo_node *node2);
void			kdo_mutate_node(t_kdo_neat *nn, t_kdo_node *node);
void			kdo_save_node(t_kdo_neat *nn, t_kdo_node *node_src);

t_kdo_genome	*kdo_get_genome(t_kdo_neat *nn);
void			kdo_genome_init(t_kdo_neat *nn, t_kdo_genome *genome);
void			kdo_genome_load(t_kdo_neat *nn, t_kdo_genome *genome_dst);
void			kdo_feed_forward_genome(t_kdo_neat *nn, t_kdo_genome *genome);
void			kdo_crossover_genome(t_kdo_genome *genome1,
					t_kdo_genome *genome2);
void			kdo_mutate_genome(t_kdo_neat *nn, t_kdo_genome *genome);
void			kdo_save_genome(t_kdo_neat *nn, t_kdo_genome *genome_src);

t_kdo_species	*kdo_get_species(t_kdo_neat *nn);
void			kdo_push_to_species(t_kdo_neat *nn,
					t_kdo_species *species, t_kdo_genome *genome);
t_kdo_species	*kdo_find_species(t_kdo_neat *nn, t_kdo_genome *genome);
void			kdo_update_species(t_kdo_neat *nn, t_kdo_species *species);
float			kdo_compatibility_score(t_kdo_neat *nn,
					t_kdo_genome *genome1, t_kdo_genome *genome2);
void			kdo_crossover_species(t_kdo_neat *nn,
					t_kdo_species *species_src);

void			kdo_reset_population(t_kdo_population *population);
int				kdo_population_alloc(t_kdo_neat *nn,
					t_kdo_population *population);
void			kdo_population_load(t_kdo_neat *nn);
void			kdo_population_init(t_kdo_neat *nn);
void			kdo_save_population(t_kdo_neat *nn);

void			kdo_init(t_kdo_neat *nn, t_kdo_neat_params *params);
void			kdo_run(t_kdo_neat *nn);
float			*kdo_feed_forward(t_kdo_neat *nn, t_uint genome_being);
void			kdo_speciation(t_kdo_neat *nn);
void			kdo_update_fitness(t_kdo_neat *nn);
void			kdo_crossover(t_kdo_neat *nn);
void			kdo_mutate(t_kdo_neat *nn);
void			kdo_save(t_kdo_neat *nn);

t_list			*kdo_get_random_link(t_kdo_node *node);
t_list			*kdo_get_random_node(t_kdo_genome *genome);
t_list			*kdo_get_node_free_link(t_kdo_genome *genome);
t_list			*kdo_get_no_linked_node(t_list *node_from);
t_list			*kdo_get_linked_node(t_kdo_genome *genome);
void			kdo_add_random_link(t_kdo_neat *nn, t_kdo_genome *genome);
void			kdo_add_random_node(t_kdo_neat *nn, t_kdo_genome *genome);

void			kdo_set_input(t_kdo_neat *nn, float *input);
t_kdo_genome	*kdo_dup_genome(t_kdo_neat *nn, t_kdo_genome *genome_src);
void			kdo_layer_propagation(t_kdo_link *link, t_uint layer);

int				kdo_link_layer_cmp(t_kdo_link *link1, t_kdo_link *link2);
int				kdo_link_id_cmp(t_kdo_link *link1, t_kdo_link *link2);
int				kdo_node_layer_cmp(t_kdo_node *node1, t_kdo_node *node2);
int				kdo_node_id_cmp(t_kdo_node *node1, t_kdo_node *node2);
int				kdo_genome_fitness_cmp(t_kdo_genome *genome1,
					t_kdo_genome *genome2);

float			kdo_identity(float in);
float			kdo_step(float in);
float			kdo_relu(float in);
float			kdo_softsign(float in);
float			kdo_sigmoid(float in);

void			kdo_free_save(t_kdo_save_neat *save);
void			kdo_free_population(t_kdo_population *population);
void			kdo_neat_cleanup(t_kdo_neat *nn, char *str_error, int error);

#endif
