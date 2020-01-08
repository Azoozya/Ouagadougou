#include "header.h"

int main(void){
//	testLecture();
//	testCalcul();
	test_selection();

/*	serpent s2 = {"\x67\xc6\x69\x73\x51\xff\x4a\xec\x29\xcd\xba\xab\xf2\xfb\xe3\x46\x7c\xc2\x54\xf8\x1b\xe8\xe7\x8d\x76\x5a\x2e\x63\x33\x9f\xc9\x9a",660};
	serpent s3 = {"\x0b\xe1\x1a\x1c\x7f\x23\xf8\x29\xf8\xa4\x1b\x13\xb5\xca\x4e\xe8\x98\x32\x38\xe0\x79\x4d\x3d\x34\xbc\x5f\x4e\x77\xfa\xcb\x6c\x05",1302};

	printf("s2 score = %d\ns2 : ",s2.score);
	affiche(s2.gene);
	printf("\n\n");
	printf("s3 score = %d\ns3 : ",s3.score);
	affiche(s3.gene);
	printf("\n\n");

test_evaluation();
test_selection();
test_generationAleatoire();*/
//test_reproduction();
//test_mutation();

	return 1;

}




void testCalcul(void)
{
int i,expect;
serpent test[]={
	{"\x67\xc6\x69\x73\x51\xff\x4a\xec\x29\xcd\xba\xab\xf2\xfb\xe3\x46\x7c\xc2\x54\xf8\x1b\xe8\xe7\x8d\x76\x5a\x2e\x63\x33\x9f\xc9\x9a",660},
	{"\x66\x32\x0d\xb7\x31\x58\xa3\x5a\x25\x5d\x05\x17\x58\xe9\x5e\xd4\xab\xb2\xcd\xc6\x9b\xb4\x54\x11\x0e\x82\x74\x41\x21\x3d\xdc\x87",735},
	{"\x70\xe9\x3e\xa1\x41\xe1\xfc\x67\x3e\x01\x7e\x97\xea\xdc\x6b\x96\x8f\x38\x5c\x2a\xec\xb0\x3b\xfb\x32\xaf\x3c\x54\xec\x18\xdb\x5c",694},
	{"\x02\x1a\xfe\x43\xfb\xfa\xaa\x3a\xfb\x29\xd1\xe6\x05\x3c\x7c\x94\x75\xd8\xbe\x61\x89\xf9\x5c\xbb\xa8\x99\x0f\x95\xb1\xeb\xf1\xb3",646},
	{"\x05\xef\xf7\x00\xe9\xa1\x3a\xe5\xca\x0b\xcb\xd0\x48\x47\x64\xbd\x1f\x23\x1e\xa8\x1c\x7b\x64\xc5\x14\x73\x5a\xc5\x5e\x4b\x79\x63",MAX},
	{"\x3b\x70\x64\x24\x11\x9e\x09\xdc\xaa\xd4\xac\xf2\x1b\x10\xaf\x3b\x33\xcd\xe3\x50\x48\x47\x15\x5c\xbb\x6f\x22\x19\xba\x9b\x7d\xf5",543},
	{"\x0b\xe1\x1a\x1c\x7f\x23\xf8\x29\xf8\xa4\x1b\x13\xb5\xca\x4e\xe8\x98\x32\x38\xe0\x79\x4d\x3d\x34\xbc\x5f\x4e\x77\xfa\xcb\x6c\x05",1302},
	{"\xac\x86\x21\x2b\xaa\x1a\x55\xa2\xbe\x70\xb5\x73\x3b\x04\x5c\xd3\x36\x94\xb3\xaf\xe2\xf0\xe4\x9e\x4f\x32\x15\x49\xfd\x82\x4e\xa9",MAX},
	{"\x08\x70\xd4\xb2\x8a\x29\x54\x48\x9a\x0a\xbc\xd5\x0e\x18\xa8\x44\xac\x5b\xf3\x8e\x4c\xd7\x2d\x9b\x09\x42\xe5\x06\xc4\x33\xaf\xcd",MAX},
	{"\xa3\x84\x7f\x2d\xad\xd4\x76\x47\xde\x32\x1c\xec\x4a\xc4\x30\xf6\x20\x23\x85\x6c\xfb\xb2\x07\x04\xf4\xec\x0b\xb9\x20\xba\x86\xc3",MAX},
	{"\x3e\x05\xf1\xec\xd9\x67\x33\xb7\x99\x50\xa3\xe3\x14\xd3\xd9\x34\xf7\x5e\xa0\xf2\x10\xa8\xf6\x05\x94\x01\xbe\xb4\xbc\x44\x78\xfa",727}
	};

	for(i=0;i<sizeof(test)/sizeof(serpent);i++) {
		expect=test[i].score;
		calcul(&test[i]);
		if (expect != test[i].score) printf("Calcul ne fonctionne pas.\n");

		//Fonction du professeur, partie ci dessous ajouté par Mohamet
		else printf("Good\n");
	}
}


void testLecture(void)
{
/*
  serpent test = {"\x67\xc6\x69\x73\x51\xff\x4a\xec\x29\xcd\xba\xab\xf2\xfb\xe3\x46\x7c\xc2\x54\xf8\x1b\xe8\xe7\x8d\x76\x5a\x2e\x63\x33\x9f\xc9\x9a",660};
  int *TestTab;

  TestTab = LectureGene(&test);
  affiche(test.gene);

  for (int index = 0; index < NBGENE-1 ; index ++)
	{
		if (index%2 == 0) printf("%d ",TestTab[index]);
		if (index%2 == 1) printf("%c ",TestTab[index]);
	}
	printf("\n\n");
	*/
}


void test_evaluation(void) // a Tester
{
	int success = 0;
	int fail = 1;
	serpent snake_test;
	serpent member_test[]={
		{"\x67\xc6\x69\x73\x51\xff\x4a\xec\x29\xcd\xba\xab\xf2\xfb\xe3\x46\x7c\xc2\x54\xf8\x1b\xe8\xe7\x8d\x76\x5a\x2e\x63\x33\x9f\xc9\x9a",660},
		{"\x66\x32\x0d\xb7\x31\x58\xa3\x5a\x25\x5d\x05\x17\x58\xe9\x5e\xd4\xab\xb2\xcd\xc6\x9b\xb4\x54\x11\x0e\x82\x74\x41\x21\x3d\xdc\x87",735},
		{"\x70\xe9\x3e\xa1\x41\xe1\xfc\x67\x3e\x01\x7e\x97\xea\xdc\x6b\x96\x8f\x38\x5c\x2a\xec\xb0\x3b\xfb\x32\xaf\x3c\x54\xec\x18\xdb\x5c",694},
		{"\x02\x1a\xfe\x43\xfb\xfa\xaa\x3a\xfb\x29\xd1\xe6\x05\x3c\x7c\x94\x75\xd8\xbe\x61\x89\xf9\x5c\xbb\xa8\x99\x0f\x95\xb1\xeb\xf1\xb3",646},
		{"\x05\xef\xf7\x00\xe9\xa1\x3a\xe5\xca\x0b\xcb\xd0\x48\x47\x64\xbd\x1f\x23\x1e\xa8\x1c\x7b\x64\xc5\x14\x73\x5a\xc5\x5e\x4b\x79\x63",MAX},
		{"\x3b\x70\x64\x24\x11\x9e\x09\xdc\xaa\xd4\xac\xf2\x1b\x10\xaf\x3b\x33\xcd\xe3\x50\x48\x47\x15\x5c\xbb\x6f\x22\x19\xba\x9b\x7d\xf5",543},
		{"\x0b\xe1\x1a\x1c\x7f\x23\xf8\x29\xf8\xa4\x1b\x13\xb5\xca\x4e\xe8\x98\x32\x38\xe0\x79\x4d\x3d\x34\xbc\x5f\x4e\x77\xfa\xcb\x6c\x05",1302},
		{"\xac\x86\x21\x2b\xaa\x1a\x55\xa2\xbe\x70\xb5\x73\x3b\x04\x5c\xd3\x36\x94\xb3\xaf\xe2\xf0\xe4\x9e\x4f\x32\x15\x49\xfd\x82\x4e\xa9",MAX},
		{"\x08\x70\xd4\xb2\x8a\x29\x54\x48\x9a\x0a\xbc\xd5\x0e\x18\xa8\x44\xac\x5b\xf3\x8e\x4c\xd7\x2d\x9b\x09\x42\xe5\x06\xc4\x33\xaf\xcd",MAX},
		{"\xa3\x84\x7f\x2d\xad\xd4\x76\x47\xde\x32\x1c\xec\x4a\xc4\x30\xf6\x20\x23\x85\x6c\xfb\xb2\x07\x04\xf4\xec\x0b\xb9\x20\xba\x86\xc3",MAX},
		{"\x3e\x05\xf1\xec\xd9\x67\x33\xb7\x99\x50\xa3\xe3\x14\xd3\xd9\x34\xf7\x5e\xa0\xf2\x10\xa8\xf6\x05\x94\x01\xbe\xb4\xbc\x44\x78\xfa",727}
		};

	groupe population_test;
	population_test.membres = member_test;
	population_test.nombre = 11;

	groupe population_generated;
	population_generated.nombre = 11;
	population_generated.membres = malloc(population_generated.nombre*sizeof(serpent));
	generationAleatoire(&population_generated);

	for (size_t rank = 0; rank < 11; rank++)
		{
		  snake_test = (population_generated.membres)[rank];
			calcul(&snake_test);
			if (snake_test.score == MAX)
				snake_test.score = 0;
		}

	fail = evaluation(&population_test);
	success = evaluation(&population_generated);

	if (success == 1 && fail == 1)
		printf("Evaluation ne détecte pas les groupes maléfiques.\n");
	else if (success == 0 && fail == 0)
		printf("Evaluation détecte tout les groupes comme maléfique.\n");
	else if (success == 1 && fail == 0)
		printf("Evaluation détecte tout à l'envers.\n");
	else if (success == 0 && fail == 1)
		printf("Evaluation est fonctionnelle.\n");
	else
		printf("Evaluation renvoie nawak %d:0 %d:1\n",fail,success);
	free(&population_test);
	free(&population_generated);
}

void affiche_groupe_test(groupe* population,unsigned char range) //isOk
{
	serpent snake;
	if (range > population->nombre)
		range = population->nombre;
	for (size_t index = 0; index < range; index++)
	 {
		 	snake = (population->membres)[index];
			for (size_t rank_gene = 0; rank_gene < NBGENE; rank_gene++)
					printf("%x",lire(snake.gene,rank_gene));
			printf("\n");
	 }
}

void test_selection(void)
{
	groupe test_population;
	groupe test_parents;
	int success = 1;
	int error = 0;
	test_population.nombre = NBPOPULATION;
	test_parents.nombre = NBPARENTS;
	test_parents.membres = malloc(sizeof(serpent) * NBPARENTS);
	test_population.membres = malloc(sizeof(serpent) * NBPOPULATION);
	serpent *snake_pop, *snake_parents;

	generationAleatoire(&test_population);
	evaluation(&test_population);

	selection(&test_population, &test_parents);

	for(int index = 0; index < NBPARENTS; index++)
	{
		snake_pop = ((test_population.membres) + index);
		snake_parents = ((test_parents.membres) + index);
		if (strcmp(snake_pop->gene, snake_parents->gene) != 0)
		{
			success = 0;
			error++;
		}
	}

	if (success == 1) printf("selection() fonctionnel\n");
	else printf("selection() non fonctionnel, nombre d'erreurs : %d\n",error);
	free(test_parents.membres);
	free(test_population.membres);
}

void test_generationAleatoire(void) //isOk
{
	groupe population;
	serpent* snake;
	population.nombre = NBPARENTS;
	population.membres = malloc(population.nombre*sizeof(serpent));
	generationAleatoire(&population);
	affiche_groupe_test(&population,NBPARENTS);
	free(population.membres);
}

void test_reproduction(void)
{
	groupe parents;
	groupe enfants;
	serpent children;
	serpent mother;
	serpent father;
	unsigned int error = 0;
	unsigned int subrank = 0;
	parents.nombre = NBPARENTS;
	enfants.nombre = NBPARENTS;
	parents.membres = malloc(parents.nombre*sizeof(serpent));
	generationAleatoire(&parents);
	reproduction(&enfants,&parents);

	for(int rank = 0 ; rank < enfants.nombre ; rank++)
		{
			children = (enfants.membres)[rank];
			father = (parents.membres)[(2*rank)%NBPARENTS];
			mother = (parents.membres)[(2*rank+1)%NBPARENTS];
			subrank = 0;
			while ( (children.gene)[subrank] == (father.gene)[subrank])
				 subrank++;
			for (size_t index = subrank; index < NBGENE/2; index++)
			 {
				 if ((children.gene)[index] != (mother.gene)[subrank])
				 		error++;
			 }
		}
	if (error > 0)
		printf("Reproduction ne fonctionne pas (%d erreurs).\n",error);
	else
		printf("Reproduction est fonctionnelle.\n");
}

void test_mutation(void) //isOk
{
	groupe population;
	groupe population_muted;
	population.nombre = NBPARENTS;
	population_muted.nombre = NBPARENTS;
	population.membres = malloc(population.nombre*sizeof(serpent));
  population_muted.membres = malloc(population_muted.nombre *sizeof(serpent));

	generationAleatoire(&population);
	copy_snakes(&population_muted,&population);
	mutation(&population_muted);
	printf("On obtient un pourcentage de mutation de :%f\n",eval_mutation(&population,&population_muted));
	affiche_groupe_test(&population,1);
	affiche_groupe_test(&population_muted,1);
	free(population.membres);
	free(population_muted.membres);
}
