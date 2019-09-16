#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define ERROR 63336
#define NONE 36663
#define YES 333
#define NO 4444
#define MAX_TRY 100
#define LOW_QUARTET 15
#define HIGH_QUARTET 240

#ifndef NBPOPULATION
#define NBPOPULATION 1000
#endif

#ifndef NBPARENTS
#define NBPARENTS 50
#endif

#define MAX 65535
#define SEEK 666

#ifndef NBGENE
#define NBGENE 64
#endif

typedef struct {
	unsigned char gene[NBGENE/2];
	int score;
} serpent;

typedef struct {
	serpent *membres;
	int nombre;
} groupe;

/* split , chaque cellules contient 1 opérateur et 1 opérande */
typedef struct split split;
struct split
{
  short operande;
  short operator;
  split* next;
  split* previous;
};

/* master_pointer */
typedef struct mp mp;
struct mp
{
  void* pointer;
  mp* previous;
  mp* next;
};

/* fonctions */
typedef struct REPLACE_ME REPLACE_ME;
struct REPLACE_ME
{
    REPLACE_ME* previous;
    REPLACE_ME* next;
};

/* master_pointer */
mp* create_master_pointer(void);
int add_pointer_master(void* pointer,mp* master);
mp* reach_last_cell(mp* head);
void delete_down(mp* head);

/* fonctions */
void delete_up_and_down(REPLACE_ME* cell);
int test_succes(void* name);
split* init_split_buffer(mp* master);
void split_gene_raw(unsigned char* list,split* raw);
unsigned char* merge_gen(mp* master);
split* first_evaluation(split* raw);
int evaluation(split* raw);
/* main (devrait être vide) */
unsigned char conversion(unsigned char Input);
void afficher(split* buffer);
short calcul(short operande1,short operator,short operande2);
/* test */
