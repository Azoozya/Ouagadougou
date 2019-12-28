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
{
	int gene1, gene2, buffer;
	int* GeneTab;
	GeneTab = malloc(sizeof(int)*NBGENE-1);

	for(int index = 0; index < NBGENE/2; index++)
	{
		buffer = g->gene[index];
		gene1 = g->gene[index] >> 4;

		switch (buffer & 0x03){
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
	serpent *snake;
	int number_of_member = population->nombre;
	int check_evil = 1;

	for(int member_index = 0; member_index < number_of_member; member_index++)
	{
		snake = ((population->membres) + member_index);
		calcul(snake);
		if(snake->score == 0) check_evil = 0;
	}

	//MOYENNE + ECART-TYPE
	/* À faire */

	return check_evil;
}

void selection(groupe *population,groupe *parents)
{
}

void generationAleatoire(groupe *population)
{
}

void reproduction(groupe *population,groupe *parents)
{
}

void mutation (groupe *population)
{
}
