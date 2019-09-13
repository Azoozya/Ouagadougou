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

	delete_down(master);
	
	return 0;
}
