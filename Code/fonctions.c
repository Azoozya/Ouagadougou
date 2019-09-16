#include "header.h"

//Libère chacune des cellules d'une liste chaînée de n'importe quel cellule , voir modèle de structure REPLACE_ME
void delete_up_and_down(REPLACE_ME* cell)
{
  if (cell != NULL)
    {
      if( cell->previous == NULL && cell->next == NULL)
        {
          free(cell);
        }
  REPLACE_ME* down = cell->next;
  REPLACE_ME* up = cell->previous;
  REPLACE_ME* buffer = NULL;
  while (down != NULL || up != NULL)
    {
      if( down != NULL && up != NULL)
        {
          buffer = down->next;
          free(down);
          down = buffer;

          buffer = up->previous;
          free(up);
          up = buffer;
      }
      if( down == NULL && up != NULL)
        {
          buffer = up->previous;
          free(up);
          up = buffer;
        }
      if( down != NULL && up == NULL)
        {
          buffer = down->next;
          free(down);
          down = buffer;
        }

    }
  }
}

int test_succes(void* name)
{
  if (name == NULL)
    return NO;
  else
    return YES;
}

split* init_split_buffer(mp* master)
{
  split* to_return;
  split* previous = NULL;
  split* cell = NULL;
  for(int rank = 0 ; rank < NBGENE/2 ; rank++)
    {
      do {
        cell = malloc(sizeof(split));
        if (test_succes(cell) == YES)
          add_pointer_master((void*)cell ,master);
      } while(test_succes(cell) != YES);

      cell->previous = previous;
      cell->next = NULL;
      cell->operande = 100;
      cell->operator = 100;
      previous = cell;

      if(rank == 0)
          to_return = cell;
      else
          cell->previous->next = cell;
    }
  return to_return;
}

//On ignore ce qu'il pourrait potentiellement contenir
void split_gene_raw(char* list,split* raw)
{
    split* buffer = raw;
    for(int rank = 0 ; rank < NBGENE/2 ; rank++)
      {
        if(rank == (NBGENE/2)-1)
          {
            buffer->operande = (short)((list[rank]&HIGH_QUARTET)>>4);
            buffer->operator = 100;
          }
        else
          {
            buffer->operande = (short)((list[rank]&HIGH_QUARTET)>>4);
            buffer->operator = (short)(list[rank]&LOW_QUARTET);
          }
        buffer = buffer->next;
      }
}

void first_evaluation(split* raw)
{
  split* buffer = raw;
  short operande1 = 0;
  short operande2 = 0;
  short operator = 0;
  short result = 0;
  while (buffer != NULL)
    {
      if(buffer->operator == '+' || buffer->operator == '-' || buffer->operator == 0 || buffer->operator == 1)
        buffer = buffer->next;
      else if (buffer->operator != '\0')
        {
          operande1 = buffer->operande;
          operator = buffer->operator;
          operande2 = buffer->next->operande;
          result = calcul(operande1,operator,operande2);
          if(test_succes(buffer->next) == YES)
            {
              buffer->next->previous = buffer->previous;
              
            }

          buffer->previous->next = buffer->next;
          buffer = buffer->next;
        }
    }
}

char* merge_gen(mp* master)
{
  char* to_return = NULL;
  return to_return;
}


char conversion(char Input)
{
	switch (Input)
		{
		case '+':
			return 0;
			break;
		case '-':
			return 1;
			break;
		case '*':
			return 2;
			break;
		case '/':
			return 3;
			break;
		case 'A':
			return 10;
			break;
		case 'B':
			return 11;
			break;
		case 'C':
			return 12;
			break;
		case 'D':
			return 13;
			break;
		case 'E':
			return 14;
			break;
		case 'F':
			return 15;
			break;

		case 0:
			return '+';
			break;
		case 1:
			return '-';
			break;
		case 2:
			return '*';
			break;
		case 3:
			return '/';
			break;
		case 10:
			return 'A';
			break;
		case 11:
			return 'B';
			break;
		case 12:
			return 'C';
			break;
		case 13:
			return 'D';
			break;
		case 14:
			return 'E';
			break;
		case 15:
			return 'F';
			break;

		default:
			return '\0';
			break;
		}
}

void afficher(split* buffer)
{
	split* bubuffer = buffer;
	while (bubuffer != NULL)
	 {
		 printf("Operande : %d:%c , Operator : %d:%c\n",bubuffer->operande,bubuffer->operande,bubuffer->operator,bubuffer->operator);
		 bubuffer = bubuffer->next;
	 }
}

short calcul(short operande1,short operator,short operande2)
{
	switch (operator)
	{
		case '+':
			return operande1+operande2;
			break;
		case 0:
			return operande1+operande2;
			break;
		case '-':
			return operande1-operande2;
			break;
		case 1:
			return operande1-operande2;
			break;
		case '*':
			return operande1*operande2;
			break;
		case 2:
			return operande1*operande2;
			break;
		case '/':
      if(operande2 == 0 || operande2 == '0')
        return MAX;
      else
			  return operande1/operande2;
			break;
		case 3:
        if(operande2 == 0 || operande2 == '0')
          return MAX;
        else
          return operande1/operande2;
        break;
		default:
			return '\0';
			break;
	}
}
