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
	afficher(raw);
	char* exemple = "\xD2\xD2\xD2\xD2\xD2\xD2\xD2\xD2\xD2\xD2\xD2\xD2\xD2\xD2\xD2\xD2\xD2\xD2\xD2\xD2\xD2\xD2\xD2\xD2\xD2\xD2\xD2\xD2\xD0\xD1\xD2\xD3";
	split_gene_raw(exemple,raw);
	afficher(raw);
	first_evaluation(raw);
	afficher(raw);
	delete_down(master);
	return 0;
}
