#include "header.h"


#define lire(gene,i)    (i%2)?(gene[i/2]&0xF):(gene[i/2]>>4);

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

int* LectureGene(serpent *g)
// Lis le gène passé en argument et traduit son expression pour la mettre dans un tableau de valeur
{
	int gene1, gene2, buffer;
	int* GeneTab;
	GeneTab = malloc(sizeof(int)*NBGENE-1);

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

		GeneTab[2*index] = gene1;
		GeneTab[2*index + 1] = gene2;
	}
	return GeneTab;
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
	int* tab_gene_lu = LectureGene(g);

	//MULTIPLICATION + DIVISION
	gene_index = 1;
	while (gene_index < NONE_index && check_error != 1)
	{
		if(tab_gene_lu[gene_index] == '*')
		{
			//Calcul du produit
			gene_previous = tab_gene_lu[gene_index - 1];
			gene_next = tab_gene_lu[gene_index + 1];
			gene_buffer = gene_previous * gene_next;
		}

		if(tab_gene_lu[gene_index] == '/')
		{
			//Calcul de la division
			gene_previous = tab_gene_lu[gene_index - 1];
			gene_next = tab_gene_lu[gene_index + 1];
			if (gene_next == 0) check_error = 1;
			else gene_buffer = gene_previous / gene_next;
		}

		if(tab_gene_lu[gene_index] == '*' || tab_gene_lu[gene_index] == '/')
		{
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
		if (tab_gene_lu[gene_index] == '+') result = result + tab_gene_lu[gene_index + 1];
		if (tab_gene_lu[gene_index] == '-') result = result - tab_gene_lu[gene_index + 1];
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
	float calcul_moyenne = 0;
	float calcul_variance = 0;
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
		calcul_variance = calcul_variance + powf(abs(snake->score - moyenne), 2);
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
	for (int member_index = 0; member_index < population->nombre; member_index++)
	{
		snake = ((population->membres) + member_index);
		for(int gene_index = 0; gene_index < NBGENE/2; gene_index++)
		{
			srand(time(0));
			*((snake->gene) + gene_index) = rand();
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

void mutation (groupe *population)
{
	serpent *snake;
	unsigned char *geneX;
	unsigned char buffer;
	int muted = 1000; // Définit le taux de mutation. À 1000, le taux est de 0.001
	for (int member_index = 0; member_index < population->nombre; member_index++)
	{
		snake = ((population->membres) + member_index);
		for (int gene_index = 0; gene_index < NBGENE / 2; gene_index++)
		{
			geneX = ((snake->gene) + gene_index);
			for (int mutation_index = 0; mutation_index < 8; mutation_index++)
			{
				srand(time(0));
				if(rand()%muted == 0)
				{
					buffer = 0x80 >> mutation_index;
					if((*geneX & mutation_index) == mutation_index) *geneX = *geneX & ~buffer;
					else *geneX = *geneX | buffer;
				}
			}
		}
	}
}
