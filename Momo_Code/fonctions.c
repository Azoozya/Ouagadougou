#include "header.h"

void affiche(unsigned char *gene)
{
	char code[]="+-*/";
	int i=0,res;
	// the last gene is useless
	while (i<(NBGENE-1)) {
		res=lire(gene,i);
		if (i%2)
			printf("%c ",code[res%4]);
		else
			printf("%d ",res);
		i=i+1;
	}
	printf("\n");
}

int* lecture_gene(serpent *g)
// Lis le gène passé en argument et traduit son expression pour la mettre dans un tableau de valeur
{
	int gene1, gene2, buffer;
	int* gene_tab;
	gene_tab = malloc(sizeof(int)*(NBGENE-1));

	for(int index = 0; index < NBGENE/2; index++)
	//À chaque char lu, on sépare ce dernier en deux pour différencier les opérandes (gene1) et les opérateurs (gene2)
	{
		buffer = g->gene[index];
		gene1 = g->gene[index] >> 4;

		switch (buffer & 0x03) //Pour pouvoir s'occuper seulement des bits traduisant l'opérateur
		{
			case 0 :
				gene2 = '+';
				break;
			case 1 :
				gene2 = '-';
				break;
			case 2 :
				gene2 = '*';
				break;
			case 3 :
				gene2 = '/';
				break;
		}

		gene_tab[2*index] = gene1;
		gene_tab[2*index + 1] = gene2;
	}
	return gene_tab;
}

void calcul(serpent *g)
/*Après avoir lu le gène grâce à LectureGene(), nous nous servons du tableau résultant pour pouvoir y calculer
directement le score dedans avec des décalages de valeurs et permettre la mise à jour de l'expression
dans le tableau (principalement pour effectuer les calculs prioritaires) */
{
	int check_error = 0;
	int result = 0;
	int gene_previous, gene_next, gene_buffer;
	int gene_index;
	int NONE_index = NBGENE - 2;
	int* tab_gene_lu = lecture_gene(g);

	//MULTIPLICATION + DIVISION
	gene_index = 1;
	while (gene_index < NONE_index && check_error != 1)
	{
		if(tab_gene_lu[gene_index] == '*' || tab_gene_lu[gene_index] == '/')
		{
			gene_previous = tab_gene_lu[gene_index - 1];
			gene_next = tab_gene_lu[gene_index + 1];

			if(tab_gene_lu[gene_index] == '/') //Calcul de la division
			{
				if (gene_next == 0) check_error = 1;
				else gene_buffer = gene_previous / gene_next;
			}
			else gene_buffer = gene_previous * gene_next; //Calcul de la multiplication

			//Mise du résultat dans le tableau + Décalage des valeurs du tableau + Affectation valeur VIDE aux derniers emplacements de la liste
			tab_gene_lu[gene_index - 1] = gene_buffer;
			for(int index_tab = gene_index; index_tab < NBGENE - 3; index_tab++) tab_gene_lu[index_tab] = tab_gene_lu[index_tab + 2];
			tab_gene_lu[NONE_index] = VIDE;
			tab_gene_lu[NONE_index - 1] = VIDE;
			NONE_index = NONE_index - 2;
		}

		if(tab_gene_lu[gene_index] != '*' && tab_gene_lu[gene_index] != '/') gene_index = gene_index + 2;
	}

	//ADDITION + SOUSTRACTION
	gene_index = 1;
	result = tab_gene_lu[gene_index - 1];
	while (gene_index < NONE_index && check_error != 1)
	{
		if (tab_gene_lu[gene_index] == '+') result += tab_gene_lu[gene_index + 1];
		if (tab_gene_lu[gene_index] == '-') result -= tab_gene_lu[gene_index + 1];
		gene_index = gene_index + 2;
	}

	//Synthèse de calcul
	if (check_error == 1) g->score = MAX;
	else g->score = abs(result - SEEK);

	free(tab_gene_lu);
}

int evaluation(groupe *population)
{
	serpent *snake, buffer;
	int check_evil = 1;
	float calcul_moyenne = 0.0;
	float calcul_variance = 0.0;
	float moyenne, ecart_type;

	for(int member_index = 0; member_index < population->nombre; member_index++)
	{
		snake = ((population->membres) + member_index);
		calcul(snake);
		if(snake->score == 0) check_evil = 0;

		calcul_moyenne = calcul_moyenne + snake->score;
	}

	//TRI DE LA POPULATION EN FONCTION DE LEUR SCORE (méthode BubbleSort)
	for(int index = 0; index < population->nombre-1; index++)
	{
		for(int member_index = 1; member_index < population->nombre; member_index++)
		{
			snake = ((population->membres) + member_index);
			if (snake->score < (*(snake-1)).score)
			{
				buffer = *snake;
				*snake = *(snake-1);
				*(snake-1) = buffer;
			}
		}
	}

	//MOYENNE + ECART-TYPE
	moyenne = calcul_moyenne / population->nombre;

	for(int member_index = 0; member_index < population->nombre; member_index++)
	{
		snake = ((population->membres) + member_index);
		calcul_variance = calcul_variance + (abs(snake->score - moyenne) * abs(snake->score - moyenne));
	}
	calcul_variance = calcul_variance / population->nombre;
	ecart_type = sqrtf(calcul_variance);

	if (check_evil == 0) printf("Serpent Maléfique Présent !\n");
	printf("Moyenne = %f\n",moyenne);
	printf("Écart-type = %f\n",ecart_type);

	return check_evil;
}

void selection(groupe *population,groupe *parents)
//Méthode de selection élitiste, Tableau population normalement déjà trié dans evaluation()
{
	for (int index = 0; index < parents->nombre; index++)
				*((parents->membres) + index) = *((population->membres) + index);
	}

void generationAleatoire(groupe *population)
{
	serpent *snake;
	srand(time(0));
	for (int member_index = 0; member_index < population->nombre; member_index++)
	{
		snake = ((population->membres) + member_index);
		for(int gene_index = 0; gene_index < NBGENE/2; gene_index++)
		{
			*((snake->gene) + gene_index) = (unsigned char)rand();
		}
	}
}

void reproduction(groupe *population,groupe *parents)
{
	unsigned int indic_parents = 0;
	unsigned int indic_gene = 1;
	unsigned char buffer;
	serpent *snake_child, *snake_parents;
	unsigned char *genome_parent1, *genome_parent2;


	for(int child_index = 0; child_index < population->nombre; child_index++)
	{
		//population n'est pas malloc
		snake_child = ((population->membres) + child_index);
		snake_child->score = MAX; // Valeur par défaut

		snake_parents = ((parents->membres) + indic_parents);
		genome_parent1 = snake_parents->gene;
		genome_parent2 = (snake_parents + 1)->gene;

		if (indic_gene%2 == 1)
		{
			buffer = (genome_parent1[indic_gene/2] & 0xf0) + (genome_parent2[indic_gene/2] & 0x0f);
			for(int gene_rank = 0; gene_rank < indic_gene/2; gene_rank++) *((snake_child->gene) + gene_rank) = genome_parent1[gene_rank];
			*((snake_child->gene) + indic_gene/2) = buffer;
			for(int gene_rank = indic_gene/2 + 1; gene_rank < NBGENE/2; gene_rank++) *((snake_child->gene) + gene_rank) = genome_parent2[gene_rank];
		}
		else
		{
			for(int gene_rank = 0; gene_rank < indic_gene/2; gene_rank++) *((snake_child->gene) + gene_rank) = genome_parent1[gene_rank];
			for(int gene_rank = indic_gene/2; gene_rank < NBGENE/2; gene_rank++) *((snake_child->gene) + gene_rank) = genome_parent2[gene_rank];
		}

		indic_parents = indic_parents + 2;
		indic_gene++;
		if(indic_parents >= parents->nombre) indic_parents = 0;
		if (indic_gene >= NBGENE) indic_gene = 0;
	}

}

void mutation(groupe *population)
{
	serpent *snake;
	unsigned char *geneX;
	unsigned char buffer;
	srand(time(0));
	int muted = 1000; // Définit le taux de mutation. À 1000, le taux est de 0.001
	for (int member_index = 0; member_index < population->nombre; member_index++)
	{
		snake = ((population->membres) + member_index);
		for (int gene_index = 0; gene_index < NBGENE / 2; gene_index++)
		{
			geneX = ((snake->gene) + gene_index);
			for (int mutation_index = 0; mutation_index < 8; mutation_index++)
			{
				// A revoir
				if(rand()%muted == 0)
				{
					buffer = 0x80 >> mutation_index;
					*geneX = *geneX^buffer;
				}
			}
		}
	}
}

float eval_mutation(groupe* population_before,groupe* population_after)
{
	float to_return = 0.0;
	unsigned int total = 0; //Compter le nombre de bit que l'on a traité
	unsigned int counter = 0; //Compter le nombre de bit qui ont muté
	unsigned char buffer_b = '\0';
	unsigned char buffer_a = '\0';
	serpent before;
	serpent after;
	unsigned int subrank;
	for (size_t rank = 0; rank < population_before->nombre; rank++)
	{
		before = (population_before->membres)[rank];
		after = (population_after->membres)[rank];
		for (int index = 0 ; index < NBGENE/2 ; index++)
			{
			subrank = 0x80;
			buffer_b = (before.gene)[index];
			buffer_a = (after.gene)[index];
			for(int bit = 0 ; bit < 8 ; bit++)
				{
					if((buffer_b&subrank) != (buffer_a&subrank))
						counter++;
					total++;
					subrank = subrank >> 1;
				}
		}
	}
	to_return = ((float)counter)/total;
	return to_return;
}

//On suppose que les 2 groupes aient le même nombre de membres
void copy_snakes(groupe* population_dst,groupe* population_src)
{
	for (size_t rank = 0; rank < population_dst->nombre; rank++)
	 {
		 strncpy((char*)((population_dst->membres)[rank]).gene,(char*)((population_src->membres)[rank]).gene,NBGENE/2);
	 }
}
