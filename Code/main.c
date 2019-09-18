#include "header.h"

int main(int argc,char* argv[])
{
	mp* master = create_master_pointer();

	//             EXEMPLE
	//char* CHANGE_ME;
	//do {
	//	CHANGE_ME = malloc(sizeof(char));
	//	if (test_succes(CHANGE_ME) == YES)
	//		add_pointer_master((void*)CHANGE_ME ,master);
	//} while(test_succes(CHANGE_ME) != YES);

	groupe exemple;
	exemple.membres = NULL;
	exemple.nombre = 0;

	unsigned char* scores = new_born(&exemple,master);
	for(int rank = 0 ; rank < NBPOPULATION ; rank++)
		printf("Score : %x\n",scores[rank]);
	delete_down(master);
	return 0;
}
