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
