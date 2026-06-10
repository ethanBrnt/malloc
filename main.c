/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 17:46:39 by eburnet           #+#    #+#             */
/*   Updated: 2026/06/10 18:03:16 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "malloc.h"

#ifdef USE_REAL_MALLOC
	#include <stdlib.h>
	#include <malloc.h>
	#define show_alloc_mem() malloc_stats() 
#else
	#include "malloc.h"
#endif

// Déclaration de ton ft_printf (ajuste les includes ou la signature si nécessaire)
int ft_printf(const char *format, ...);

int main() {
	ft_printf("\n\n\n###### MALLOC ######\n");

	ft_printf("\n--- Test 1 : show mem initial ---\n");
	show_alloc_mem();

	ft_printf("\n\n--- Test 2 : malloc 0 ---\n");
	void *ptr0 = malloc(0);
	show_alloc_mem();
	free(ptr0);

	ft_printf("\n\n--- Test 3 : simple allocs ---\n");
	void *tiny = malloc(16);
	strcpy(tiny, "hello");
	ft_printf("strcpy tiny: %s\n", (char *)tiny);
	
	void *small = malloc(700);
	char *str = "Lorem ipsum dolor sit amet consectetur adipiscing elit quisque faucibus ex sapien vitae pellentesque semLorem ipsum dolor sit amet consectetur adipiscing elit quisque faucibus ex sapien vitae pellentesque semLorem ipsum dolor sit amet consectetur adipiscing elit quisque faucibus ex sapien vitae pellentesque semLorem ipsum dolor sit amet consectetur adipiscing elit quisque faucibus ex sapien vitae pellentesque semLorem ipsum dolor sit amet consectetur adipiscing elit quisque faucibus ex sapien vitae pellentesque sem";
	strcpy(small, str);
	ft_printf("strcpy small: %s\n", (char *)small);
	
	void *large = malloc(8096);
	char *str2 = "Lorem ipsum dolor sit amet consectetur adipiscing elit quisque faucibus ex sapien vitae pellentesque sem placerat in id cursus mi pretium tellus duis convallis tempus leo eu aenean sed diam urna tempor pulvinar vivamus fringilla lacus nec metus bibendum egestas iaculis massa nisl malesuada lacinia integer nunc posuere ut hendrerit semper vel class aptent taciti sociosqu ad litora torquent per conubia nostra inceptos himenaeos orci varius natoque penatibus et magnis dis parturient montes nascetur ridiculus mus donec rhoncus eros lobortis nulla molestie mattis scelerisque maximus eget fermentum odio phasellus non purus est efficitur laoreet mauris pharetra vestibulum fusce dictum risus blandit quis suspendisse aliquet nisi sodales consequat magna ante condimentum neque at luctus nibh finibus facilisis dapibus etiam interdum tortor ligula congue sollicitudin erat viverra ac tincidunt nam porta elementum a enim euismod quam justo lectus commodo augue arcu dignissim velit aliquam imperdiet mollis nullam volutpat porttitor ullamcorper rutrum gravida cras eleifend turpis fames primis vulputate ornare sagittis vehicula praesent dui felis venenatis ultrices proin libero feugiat tristique accumsan maecenas potenti ultricies habitant morbi senectus netus suscipit auctor curabitur facilisi cubilia curae hac habitasse platea dictumst lorem ipsum dolor sit amet consectetur adipiscing elit quisque faucibus ex sapien vitae pellentesque sem placerat in id cursus mi pretium tellus duis convallis tempus leo eu aenean sed diam urna tempor pulvinar vivamus fringilla lacus nec metus bibendum egestas iaculis massa nisl malesuada lacinia integer nunc posuere ut hendrerit semper vel class aptent taciti sociosqu ad litora torquent per conubia nostra inceptos himenaeos orci varius natoque penatibus et magnis dis parturient montes nascetur ridiculus mus donec rhoncus eros lobortis nulla molestie mattis scelerisque maximus eget fermentum odio phasellus non purus est efficitur laoreet mauris pharetra vestibulum fusce dictum risus blandit quis suspendisse aliquet nisi sodales consequat magna ante condimentum neque at luctus nibh finibus facilisis dapibus etiam interdum tortor ligula congue sollicitudin erat viverra ac tincidunt nam.Lorem ipsum dolor sit amet consectetur adipiscing elit quisque faucibus ex sapien vitae pellentesque sem placerat in id cursus mi pretium tellus duis convallis tempus leo eu aenean sed diam urna tempor pulvinar vivamus fringilla lacus nec metus bibendum egestas iaculis massa nisl malesuada lacinia integer nunc posuere ut hendrerit semper vel class aptent taciti sociosqu ad litora torquent per conubia nostra inceptos himenaeos orci varius natoque penatibus et magnis dis parturient montes nascetur ridiculus mus donec rhoncus eros lobortis nulla molestie mattis scelerisque maximus eget fermentum odio phasellus non purus est efficitur laoreet mauris pharetra vestibulum fusce dictum risus blandit quis suspendisse aliquet nisi sodales consequat magna ante condimentum neque at luctus nibh finibus facilisis dapibus etiam interdum tortor ligula congue sollicitudin erat viverra ac tincidunt nam porta elementum a enim euismod quam justo lectus commodo augue arcu dignissim velit aliquam imperdiet mollis nullam volutpat porttitor ullamcorper rutrum gravida cras eleifend turpis fames primis vulputate ornare sagittis vehicula praesent dui felis venenatis ultrices proin libero feugiat tristique accumsan maecenas potenti ultricies habitant morbi senectus netus suscipit auctor curabitur facilisi cubilia curae hac habitasse platea dictumst lorem ipsum dolor sit amet consectetur adipiscing elit quisque faucibus ex sapien vitae pellentesque sem placerat in id cursus mi pretium tellus duis convallis tempus leo eu aenean sed diam urna tempor pulvinar vivamus fringilla lacus nec metus bibendum egestas iaculis massa nisl malesuada lacinia integer nunc posuere ut hendrerit semper vel class aptent taciti sociosqu ad litora torquent per conubia nostra inceptos himenaeos orci varius natoque penatibus et magnis dis parturient montes nascetur ridiculus mus donec rhoncus eros lobortis nulla molestie mattis scelerisque maximus eget fermentum odio phasellus non purus est efficitur laoreet mauris pharetra vestibulum fusce dictum risus blandit quis suspendisse aliquet nisi sodales consequat magna ante condimentum neque at luctus nibh finibus facilisis dapibus etiam interdum tortor ligula congue sollicitudin erat viverra ac tincidunt nam.";
	strcpy(large, str2);
	ft_printf("strcpy large: %s\n", (char *)large);
	show_alloc_mem();

	ft_printf("\n--- Libération de toutes les allocations ---\n");
	free(tiny);
	free(small);
	free(large);
	show_alloc_mem();

	ft_printf("\n\n--- Test 4 : multiple allocs (tiny x 2, small x 2, large x2) ---\n");
	tiny = malloc(16);
	small = malloc(520);
	large = malloc(5096);
	void *tiny1 = malloc(16);
	void *small1 = malloc(513);
	void *large1 = malloc(5096);
	show_alloc_mem();

	ft_printf("\n--- Free all ---\n");
	free(tiny);
	free(small);
	free(large);
	free(tiny1);
	free(small1);
	free(large1);
	show_alloc_mem();

	ft_printf("\n\n--- Test 5 : alloc tiny x3 ---\n");
	void *tinyA = malloc(16);
	void *tinyB = malloc(16);
	void *tinyC = malloc(16);
	show_alloc_mem();

	ft_printf("\n--- Free 2nd tiny ---\n");
	free(tinyB);
	show_alloc_mem();

	ft_printf("\n--- Alloc new tiny ---\n");
	void *tinyD = malloc(16);
	show_alloc_mem();

	ft_printf("\n--- Free all ---\n");
	free(tinyA);
	free(tinyC);
	free(tinyD);
	show_alloc_mem();

	ft_printf("\n\n--- Test 6 : alloc small x3 ---\n");
	void *smallA = malloc(514);
	void *smallB = malloc(514);
	void *smallC = malloc(514);
	show_alloc_mem();

	ft_printf("\n--- Free 1st small ---\n");
	free(smallA);
	show_alloc_mem();

	ft_printf("\n--- Alloc new small ---\n");
	void *smallD = malloc(514);
	show_alloc_mem();

	ft_printf("\n--- Free all ---\n");
	free(smallB);
	free(smallC);
	free(smallD);
	show_alloc_mem();

	ft_printf("\n\n--- Test 7 : alloc large x3 ---\n");
	void *largeA = malloc(5096);
	void *largeB = malloc(5096);
	void *largeC = malloc(5096);
	show_alloc_mem();

	ft_printf("\n--- Free 3rd large ---\n");
	free(largeC);
	show_alloc_mem();

	ft_printf("\n--- Alloc new large ---\n");
	void *largeD = malloc(5096);
	show_alloc_mem();

	ft_printf("\n--- Free all ---\n");
	free(largeA);
	free(largeB);
	free(largeD);
	show_alloc_mem();

	ft_printf("\n\n--- Test 8 : more than 100 allocs ---\n");
	char *tab[250];
	for (size_t i = 0; i < 110; i++)
		tab[i] = malloc(sizeof(char) * 512);
	show_alloc_mem();
	
	ft_printf("\n--- Free all ---\n");
	for (size_t i = 0; i < 110; i++)
		free(tab[i]);
	show_alloc_mem();

	ft_printf("\n\n--- Test 9 : malloc to big value ---\n");
	char *tobig = malloc(1844674407379551615);
	if (!tobig)
		ft_printf("tobig is NULL\n");

	ft_printf("\n\n\n###### FREE ######\n");

	ft_printf("\n\n--- Test 1 : free NULL ---\n");
	free(NULL);

	ft_printf("\n\n--- Test 2 : double free ---\n");
	void *double_free = malloc(514);
	free(double_free);
	free(double_free);

	ft_printf("\n\n--- Test 3 : free invalid pointer ---\n");
	char c = 'a';
	free(&c);

	ft_printf("\n\n\n###### REALLOC ######\n");

	ft_printf("\n\n--- Test 1 : realloc > content check ---\n");
	void *realloc_content = malloc(16);
	ft_printf("strcpy: %s\n", strcpy(realloc_content, "hello world"));
	show_alloc_mem();
	realloc_content = realloc(realloc_content, 312);

	ft_printf("\n--- After realloc ---\nrealloced var: %s\n", (char *)realloc_content);
	show_alloc_mem();
	free(realloc_content);

	ft_printf("\n\n--- Test 2 : realloc < content check ---\n");
	realloc_content = malloc(26);
	ft_printf("strcpy: %s\n", strcpy(realloc_content, "hello"));
	show_alloc_mem();
	realloc_content = realloc(realloc_content, 6);

	ft_printf("\n--- After realloc ---\nrealloced var: %s\n", (char *)realloc_content);
	show_alloc_mem();
	free(realloc_content);

	ft_printf("\n\n--- Test 3 : realloc tiny -> small ---\n");
	void *realloc_tiny = malloc(16);
	ft_printf("%s\n", strcpy(realloc_tiny, "HEyy"));
	show_alloc_mem();
	realloc_tiny = realloc(realloc_tiny, 514);

	ft_printf("\n--- After realloc ---\n%s\n", (char *)realloc_tiny);
	show_alloc_mem();
	free(realloc_tiny);

	ft_printf("\n\n--- Test 4 : realloc small -> large ---\n");
	void *realloc_small = malloc(800);
	ft_printf("%s\n", strcpy(realloc_small, "Article evident arrived express highest men did boy. Mistress sensible entirely am so. Quick can manor smart money hopes worth too. Comfort produce husband boy her had hearing. Law others theirs passed but wishes. You day real less till dear read. Considered use dispatched melancholy sympathize discretion led. Oh feel if up to till like.Article evident arrived express highest men did boy. Mistress sensible entirely am so. Quick can manor smart money hopes worth too. Comfort produce husband boy her had hearing. Law others theirs passed but wishes. You day real less till dear read. Considered use dispatched melancholy sympathize discretion led. Oh feel if up to till like."));
	show_alloc_mem();
	realloc_small = realloc(realloc_small, 5096);

	ft_printf("\n--- After realloc ---\n%s\n", (char *)realloc_small);
	show_alloc_mem();
	free(realloc_small);

	ft_printf("\n\n--- Test 5 : realloc large -> tiny ---\n");
	void *realloc_large = malloc(5096);
	ft_printf("%s\n", strcpy(realloc_large, "Article evident arrived express highest men did boy. Mistress sensible entirely am so. Quick can manor smart money hopes worth too. Comfort produce husband boy her had hearing. Law others theirs passed but wishes. You day real less till dear read. Considered use dispatched melancholy sympathize discretion led. Oh feel if up to till like.Article evident arrived express highest men did boy. Mistress sensible entirely am so. Quick can manor smart money hopes worth too. Comfort produce husband boy her had hearing. Law others theirs passed but wishes. You day real less till dear read. Considered use dispatched melancholy sympathize discretion led. Oh feel if up to till like."));
	show_alloc_mem();
	realloc_large = realloc(realloc_large, 16);

	ft_printf("\n--- After realloc ---\n%s\n", (char *)realloc_large);
	show_alloc_mem();
	free(realloc_large);

	ft_printf("\n\n--- Test 6 : realloc ptr NULL ---\n");
	show_alloc_mem();
	void *realloc_null = realloc(NULL, 16);
	ft_printf("\n--- After realloc ---\n");
	show_alloc_mem();
	ft_printf("free\n");
	free(realloc_null);

	ft_printf("\n\n--- Test 7 : realloc avec 0 ---\n");
	void *realloc_zero = malloc(16);
	show_alloc_mem();
	realloc_zero = realloc(realloc_zero, 0);
	ft_printf("\n--- After realloc ---\n");
	show_alloc_mem();

	ft_printf("\n\n--- Test 8 : realloc avec same size ---\n");
	void *realloc_same_size = malloc(16);
	memset(realloc_same_size, 'A', 16);
	show_alloc_mem();
	realloc_same_size = realloc(realloc_same_size, 16);

	ft_printf("\n--- After realloc ---\n%s\n", (char *)realloc_same_size);
	show_alloc_mem();
	free(realloc_same_size);

	ft_printf("\n--- Last Free ---\n");
	free(realloc_same_size);
	show_alloc_mem();


	ft_printf("\n=== Fin des tests ===\n");
	return 0;
}

/* 
cc -g3 main.c -L. -lft_malloc -o test
LD_LIBRARY_PATH=. ./test

cc -g3 -DUSE_REAL_MALLOC main.c libft/libft.a -o test_classic
./test_classic


env LD_LIBRARY_PATH=. gdb ./test
run
bt
frame <num>
print <var>
*/
