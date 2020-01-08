#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <getopt.h>

#ifndef NBPOPULATION
#define NBPOPULATION 100
#endif

#ifndef NBPARENTS
#define NBPARENTS 50
#endif

#define MAX 2000000
#define SEEK 666

#ifndef NBGENE
#define NBGENE 64
#endif

#ifndef VIDE
#define VIDE 666000000
#endif

typedef struct {
	unsigned char gene[NBGENE/2];
	int score;
} serpent;

typedef struct {
	serpent *membres;
	int nombre;
} groupe;

#ifndef lire
#define lire(gene,i)    (i%2)?(gene[i/2]&0xF):(gene[i/2]>>4)
#endif

void affiche(unsigned char *gene);
void calcul(serpent *g);
void selection(groupe *population,groupe *parents);
int evaluation(groupe *population);
void generationAleatoire(groupe *population);
void reproduction(groupe *population,groupe *parents);
void mutation (groupe *population);
int* lecture_gene(serpent *g);

void affiche_groupe_test(groupe* population,unsigned char range);
float eval_mutation(groupe* population_before,groupe* population_after);
void copy_snakes(groupe* population_dst,groupe* population_src);
// -------------------TESTS-------------------//
void testCalcul(void);
void testLecture(void);
void test_evaluation(void);
void test_selection(void);
void test_generationAleatoire(void);
void test_reproduction(void);
void test_mutation(void);
