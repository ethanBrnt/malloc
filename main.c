/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:13:11 by eburnet           #+#    #+#             */
/*   Updated: 2025/049/09 14:59:26 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "malloc.h"

typedef struct {
	int thread_id;
	int num_allocs;
	size_t alloc_size;
	int use_realloc;
} ThreadArgs;

void *thread_function(void *arg) {
	ThreadArgs *args = (ThreadArgs *)arg;
	void **ptrs = malloc(args->num_allocs * sizeof(void *));
	if (!ptrs) {
		ft_putstr("malloc failed in thread\n");
		return NULL;
	}

	for (int i = 0; i < args->num_allocs; i++) {
		if (args->use_realloc && i > 0) {
			ptrs[i] = realloc(ptrs[i-1], args->alloc_size * (i + 1));
		} else {
			ptrs[i] = malloc(args->alloc_size);
		}
		if (!ptrs[i]) {
			ft_putstr("malloc/realloc failed in thread\n");
			break;
		}
		usleep(10);
	}

	for (int i = 0; i < args->num_allocs; i++) {
		if (ptrs && ptrs[i]) {
			free(ptrs[i]);
		}
	}

	free(ptrs);
	return NULL;
}

int main() {
	ft_putstr("\n--- Test 1 : show mem initial ---\n");
	show_alloc_mem();


	ft_putstr("\n--- Test 2 : malloc 0 ---\n");
	void *ptr0 = malloc(0);
	show_alloc_mem();
	free(ptr0);


	ft_putstr("\n--- Test 3 : simple allocs ---\n");
	void *tiny = malloc(16);
	strcpy(tiny, "hello");
	ft_putstr("strcpy tiny: ");
	ft_putstr((char *)tiny);
	ft_putstr("\n");
	
	void *small = malloc(700);
	char *str = "Lorem ipsum dolor sit amet consectetur adipiscing elit quisque faucibus ex sapien vitae pellentesque semLorem ipsum dolor sit amet consectetur adipiscing elit quisque faucibus ex sapien vitae pellentesque semLorem ipsum dolor sit amet consectetur adipiscing elit quisque faucibus ex sapien vitae pellentesque semLorem ipsum dolor sit amet consectetur adipiscing elit quisque faucibus ex sapien vitae pellentesque semLorem ipsum dolor sit amet consectetur adipiscing elit quisque faucibus ex sapien vitae pellentesque sem";
	strcpy(small, str);
	ft_putstr("strcpy small: ");
	ft_putstr((char *)small);
	ft_putstr("\n");
	
	void *large = malloc(8096);
	char *str2 = "Lorem ipsum dolor sit amet consectetur adipiscing elit quisque faucibus ex sapien vitae pellentesque sem placerat in id cursus mi pretium tellus duis convallis tempus leo eu aenean sed diam urna tempor pulvinar vivamus fringilla lacus nec metus bibendum egestas iaculis massa nisl malesuada lacinia integer nunc posuere ut hendrerit semper vel class aptent taciti sociosqu ad litora torquent per conubia nostra inceptos himenaeos orci varius natoque penatibus et magnis dis parturient montes nascetur ridiculus mus donec rhoncus eros lobortis nulla molestie mattis scelerisque maximus eget fermentum odio phasellus non purus est efficitur laoreet mauris pharetra vestibulum fusce dictum risus blandit quis suspendisse aliquet nisi sodales consequat magna ante condimentum neque at luctus nibh finibus facilisis dapibus etiam interdum tortor ligula congue sollicitudin erat viverra ac tincidunt nam porta elementum a enim euismod quam justo lectus commodo augue arcu dignissim velit aliquam imperdiet mollis nullam volutpat porttitor ullamcorper rutrum gravida cras eleifend turpis fames primis vulputate ornare sagittis vehicula praesent dui felis venenatis ultrices proin libero feugiat tristique accumsan maecenas potenti ultricies habitant morbi senectus netus suscipit auctor curabitur facilisi cubilia curae hac habitasse platea dictumst lorem ipsum dolor sit amet consectetur adipiscing elit quisque faucibus ex sapien vitae pellentesque sem placerat in id cursus mi pretium tellus duis convallis tempus leo eu aenean sed diam urna tempor pulvinar vivamus fringilla lacus nec metus bibendum egestas iaculis massa nisl malesuada lacinia integer nunc posuere ut hendrerit semper vel class aptent taciti sociosqu ad litora torquent per conubia nostra inceptos himenaeos orci varius natoque penatibus et magnis dis parturient montes nascetur ridiculus mus donec rhoncus eros lobortis nulla molestie mattis scelerisque maximus eget fermentum odio phasellus non purus est efficitur laoreet mauris pharetra vestibulum fusce dictum risus blandit quis suspendisse aliquet nisi sodales consequat magna ante condimentum neque at luctus nibh finibus facilisis dapibus etiam interdum tortor ligula congue sollicitudin erat viverra ac tincidunt nam.Lorem ipsum dolor sit amet consectetur adipiscing elit quisque faucibus ex sapien vitae pellentesque sem placerat in id cursus mi pretium tellus duis convallis tempus leo eu aenean sed diam urna tempor pulvinar vivamus fringilla lacus nec metus bibendum egestas iaculis massa nisl malesuada lacinia integer nunc posuere ut hendrerit semper vel class aptent taciti sociosqu ad litora torquent per conubia nostra inceptos himenaeos orci varius natoque penatibus et magnis dis parturient montes nascetur ridiculus mus donec rhoncus eros lobortis nulla molestie mattis scelerisque maximus eget fermentum odio phasellus non purus est efficitur laoreet mauris pharetra vestibulum fusce dictum risus blandit quis suspendisse aliquet nisi sodales consequat magna ante condimentum neque at luctus nibh finibus facilisis dapibus etiam interdum tortor ligula congue sollicitudin erat viverra ac tincidunt nam porta elementum a enim euismod quam justo lectus commodo augue arcu dignissim velit aliquam imperdiet mollis nullam volutpat porttitor ullamcorper rutrum gravida cras eleifend turpis fames primis vulputate ornare sagittis vehicula praesent dui felis venenatis ultrices proin libero feugiat tristique accumsan maecenas potenti ultricies habitant morbi senectus netus suscipit auctor curabitur facilisi cubilia curae hac habitasse platea dictumst lorem ipsum dolor sit amet consectetur adipiscing elit quisque faucibus ex sapien vitae pellentesque sem placerat in id cursus mi pretium tellus duis convallis tempus leo eu aenean sed diam urna tempor pulvinar vivamus fringilla lacus nec metus bibendum egestas iaculis massa nisl malesuada lacinia integer nunc posuere ut hendrerit semper vel class aptent taciti sociosqu ad litora torquent per conubia nostra inceptos himenaeos orci varius natoque penatibus et magnis dis parturient montes nascetur ridiculus mus donec rhoncus eros lobortis nulla molestie mattis scelerisque maximus eget fermentum odio phasellus non purus est efficitur laoreet mauris pharetra vestibulum fusce dictum risus blandit quis suspendisse aliquet nisi sodales consequat magna ante condimentum neque at luctus nibh finibus facilisis dapibus etiam interdum tortor ligula congue sollicitudin erat viverra ac tincidunt nam porta elementum a enim euismod quam justo lectus commodo augue arcu dignissim velit aliquam imperdiet mollis nullam volutpat porttitor ullamcorper rutrum gravida cras eleifend turpis fames primis vulputate ornare sagittis vehicula praesent dui felis venenatis ultrices proin libero feugiat tristique accumsan maecenas potenti ultricies habitant morbi senectus netus suscipit auctor curabitur facilisi cubilia curae hac habitasse platea dictumst lorem ipsum dolor sit amet consectetur adipiscing elit quisque faucibus ex sapien vitae pellentesque sem placerat in id cursus mi pretium tellus duis convallis tempus leo eu aenean sed diam urna tempor pulvinar vivamus fringilla lacus nec metus bibendum egestas iaculis massa nisl malesuada lacinia integer nunc posuere ut hendrerit semper vel class aptent taciti sociosqu ad litora torquent per conubia nostra inceptos himenaeos orci varius natoque penatibus et magnis dis parturient montes nascetur ridiculus mus donec rhoncus eros lobortis nulla molestie mattis scelerisque maximus eget fermentum odio phasellus non purus est efficitur laoreet mauris pharetra vestibulum fusce dictum risus blandit quis suspendisse aliquet nisi sodales consequat magna ante condimentum neque at luctus nibh finibus facilisis dapibus etiam interdum tortor ligula congue sollicitudin erat viverra ac tincidunt nam.";
	strcpy(large, str2);
	ft_putstr("strcpy large: ");
	ft_putstr((char *)large);
	ft_putstr("\n");
	show_alloc_mem();

	ft_putstr("\n--- Libération de toutes les allocations ---\n");
	free(tiny);
	free(small);
	free(large);
	show_alloc_mem();

	ft_putstr("\n--- Test 4 : multiple allocs (tiny x 2, small x 2, large x2) ---\n");
	tiny = malloc(16);
	small = malloc(520);
	large = malloc(5096);
	void *tiny1 = malloc(16);
	void *small1 = malloc(513);
	void *large1 = malloc(5096);
	show_alloc_mem();

	ft_putstr("\n--- Libération de toutes les allocations ---\n");
	free(tiny);
	free(small);
	free(large);
	free(tiny1);
	free(small1);
	free(large1);
	show_alloc_mem();


	ft_putstr("\n--- Test 5 : alloc tiny x3 ---\n");
	void *tinyA = malloc(16);
	void *tinyB = malloc(16);
	void *tinyC = malloc(16);
	show_alloc_mem();

	ft_putstr("\n--- Free tiny 2 ---\n");
	free(tinyB);
	show_alloc_mem();

	ft_putstr("\n--- Alloc tiny ---\n");
	void *tinyD = malloc(16);
	show_alloc_mem();

	ft_putstr("\n--- Free all ---\n");
	free(tinyA);
	free(tinyC);
	free(tinyD);
	show_alloc_mem();


	ft_putstr("\n--- Test 6 : same small ---\n");
	void *smallA = malloc(514);
	void *smallB = malloc(514);
	void *smallC = malloc(514);
	show_alloc_mem();

	ft_putstr("\n--- Free small 2 ---\n");
	free(smallB);
	show_alloc_mem();

	ft_putstr("\n--- Alloc small ---\n");
	void *smallD = malloc(514);
	show_alloc_mem();

	ft_putstr("\n--- Free all ---\n");
	free(smallA);
	free(smallC);
	free(smallD);
	show_alloc_mem();


	ft_putstr("\n--- Test 7 : same large ---\n");
	void *largeA = malloc(5096);
	void *largeB = malloc(5096);
	void *largeC = malloc(5096);
	show_alloc_mem();

	ft_putstr("\n--- Free large 2 ---\n");
	free(largeB);
	show_alloc_mem();

	ft_putstr("\n--- Alloc large ---\n");
	void *largeD = malloc(5096);
	show_alloc_mem();

	ft_putstr("\n--- Free all ---\n");
	free(largeA);
	free(largeC);
	free(largeD);
	show_alloc_mem();


	ft_putstr("\n--- Test 8 : realloc tiny -> small ---\n");
	void *realloc_tiny = malloc(16);
	show_alloc_mem();
	realloc_tiny = realloc(realloc_tiny, 514);
	show_alloc_mem();
	free(realloc_tiny);


	ft_putstr("\n--- Test 9 : realloc small -> large ---\n");
	void *realloc_small = malloc(514);
	show_alloc_mem();
	realloc_small = realloc(realloc_small, 5096);
	show_alloc_mem();
	free(realloc_small);


	ft_putstr("\n--- Test 10 : realloc large -> tiny ---\n");
	void *realloc_large = malloc(5096);
	show_alloc_mem();
	realloc_large = realloc(realloc_large, 16);
	show_alloc_mem();
	free(realloc_large);


	ft_putstr("\n--- Test 11 : realloc NULL ---\n");
	void *realloc_null = realloc(NULL, 16);
	show_alloc_mem();
	ft_putstr("free\n");
	free(realloc_null);


	ft_putstr("\n--- Test 12 : realloc avec 0 ---\n");
	void *realloc_zero = malloc(16);
	show_alloc_mem();
	realloc_zero = realloc(realloc_zero, 0);
	show_alloc_mem();


	// ft_putstr("\n--- Test 13 : Allocations parallèles (tiny, small, large) ---\n");
	// const int NUM_THREADS = 3;
	// pthread_t threads[NUM_THREADS];
	// ThreadArgs args[NUM_THREADS];

	// for (int i = 0; i < NUM_THREADS; i++) {
	// 	args[i].thread_id = i;
	// 	args[i].num_allocs = 5;
	// 	args[i].alloc_size = (i == 0) ? 16 : (i == 1) ? 514 : 4096; // tiny, small, large
	// 	args[i].use_realloc = 0;
	// 	pthread_create(&threads[i], NULL, thread_function, &args[i]);
	// }

	// for (int i = 0; i < NUM_THREADS; i++) {
	// 	pthread_join(threads[i], NULL);
	// }
	// show_alloc_mem();

	// ft_putstr("\n--- Test 14 : Réallocations parallèles ---\n");
	// for (int i = 0; i < NUM_THREADS; i++) {
	// 	args[i].thread_id = i;
	// 	args[i].num_allocs = 5;
	// 	args[i].alloc_size = 16;
	// 	args[i].use_realloc = 1;
	// 	pthread_create(&threads[i], NULL, thread_function, &args[i]);
	// }

	// for (int i = 0; i < NUM_THREADS; i++) {
	// 	pthread_join(threads[i], NULL);
	// }
	// show_alloc_mem();


	ft_putstr("\n--- Test 14 : more than 100 allocs ---\n");
	char *tab[250];
	for (size_t i = 0; i < 110; i++)
	{
		tab[i] = malloc(sizeof(char) * 512);
	}
	show_alloc_mem();
	ft_putstr("\n--- Free all ---\n");
	for (size_t i = 0; i < 110; i++)
	{
		free(tab[i]);
	}
	show_alloc_mem();

	ft_putstr("\n=== Fin des tests ===\n");
	return 0;
}

/* 
cc -g3 main.c -L. -lft_malloc -o test 
LD_LIBRARY_PATH=. ./test

cp main.c main_classic.c
cc -g3 main_classic.c libft/libft.a -o test_classic

env LD_LIBRARY_PATH=. gdb ./test
run
bt
frame <num>
print <var>
*/
