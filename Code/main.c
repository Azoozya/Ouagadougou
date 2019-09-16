#include "header.h"

int main(int argc,char* argv[])
{
	mp* master = create_master_pointer();

	//             EXEMPLE
	//char* CHANGE_ME;
	//do {
	//	CHANGE_ME = malloc(sizeof(char));
	//	if (test_succes(CHANGE_ME) == YES)
	//		add_pointer_master((void*)lama ,master);
	//} while(test_succes(CHANGE_ME) != YES);
	split* raw = init_split_buffer(master);
	int score = 0;
	afficher(raw);
	unsigned char* exemple = (unsigned char*)"\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x12\x10\x11\x23";
	split_gene_raw(exemple,raw);
	afficher(raw);
	score = evaluation(raw);
	afficher(raw);
	printf("\n SCORE : %d\n",score);
	delete_down(master);
	return 0;
}
