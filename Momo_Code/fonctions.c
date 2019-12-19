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
			printf("0x%x ",res);
		i=i+1;
	}
	printf("\n");
}

unsigned char* LectureGene(serpent *g)
{
	unsigned char gene1, gene2, buffer;
	unsigned char* GeneTab;
	GeneTab = malloc(sizeof(char)*NBGENE-1);

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
	int verif_erreur = 0;
	int result = 0;
	char gene_previous, gene_next, gene_buffer;
	int gene_index;
	int NONE_index = NBGENE - 1;
	unsigned char tab_gene_lu[] = LectureGene(g);

	//MULTIPLICATION
	gene_index = 1;
	while (gene_index < NBGENE - 2 && tab_gene_lu[gene_index] != VIDE)
	{
		if(tab_gene_lu[gene_index] == '*')
		{
			//Calcul du produit
			gene_previous = tab_gene_lu[gene_index - 1];
			gene_next = tab_gene_lu[gene_index + 1];
			gene_buffer = gene_previous * gene_next;

			//Mise du résultat dans le tableau + Décalage des valeurs du tableau + Affectation valeur VIDE aux derniers emplacements de la liste
			tab_gene_lu[gene_index - 1] = gene_buffer;
			for(int index_tab = gene_index; index_tab < NBGENE - 3; index_tab++) tab_gene_lu[index_tab] = tab_gene_lu[index_tab + 2];
			tab_gene_lu[NONE_index] = VIDE;
			tab_gene_lu[NONE_index - 1] = VIDE;
			NONE_index = NONE_index - 2;
		}
		gene_index = gene_index + 2;
	}

	//DIVISION ENTIERE
	gene_index = 1;
	while (gene_index < NBGENE - 2 && tab_gene_lu[gene_index] != VIDE && verif_erreur != 1)
	{
		if(tab_gene_lu[gene_index] == '/')
		{
			//Calcul de la division
			gene_previous = tab_gene_lu[gene_index - 1];
			gene_next = tab_gene_lu[gene_index + 1];
			if (gene_next == 0) verif_erreur = 1;
			else gene_buffer = gene_previous / gene_next;

			//Mise du résultat dans le tableau + Décalage des valeurs du tableau + Affectation valeur VIDE aux derniers emplacements de la liste
			if (verif_erreur != 1){
				tab_gene_lu[gene_index - 1] = gene_buffer;
				for(int index_tab = gene_index; index_tab < NBGENE - 3; index_tab++) tab_gene_lu[index_tab] = tab_gene_lu[index_tab + 2];
				tab_gene_lu[NONE_index] = VIDE;
				tab_gene_lu[NONE_index - 1] = VIDE;
				NONE_index = NONE_index - 2;
			}
		}
		gene_index = gene_index + 2;
	}

	//ADDITION + SOUSTRACTION
	gene_index = 1;
	while (gene_index < NBGENE - 2 && tab_gene_lu[gene_index] != VIDE && verif_erreur != 1)
	{
			//Calcul de la somme / différence
			gene_previous = tab_gene_lu[gene_index - 1];
			gene_next = tab_gene_lu[gene_index + 1];
			if (tab_gene_lu[gene_index] == '+') gene_buffer = gene_previous + gene_next;
			if (tab_gene_lu[gene_index] == '-') gene_buffer = gene_previous - gene_next;

			//Mise du résultat dans le tableau + Décalage des valeurs du tableau + Affectation valeur VIDE aux derniers emplacements de la liste
			if (verif_erreur != 1){
				tab_gene_lu[gene_index - 1] = gene_buffer;
				for(int index_tab = gene_index; index_tab < NBGENE - 3; index_tab++) tab_gene_lu[index_tab] = tab_gene_lu[index_tab + 2];
				tab_gene_lu[NONE_index] = VIDE;
				tab_gene_lu[NONE_index - 1] = VIDE;
				NONE_index = NONE_index - 2;
			}
		gene_index = gene_index + 2;
	}

	if (verif_erreur != 1) result = tab_gene_lu[0];
	else result = MAX;

	g->score = result;
}

void selection(groupe *population,groupe *parents)
{
}

int evaluation(groupe *population)
{
	return 0;
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
