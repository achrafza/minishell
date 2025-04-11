#include "../minishell.h"

void free1d(void *array) 
{
    if (array != NULL)
        free(array);
}

void free2d(char **array) 
{
    int i;

    if (array == NULL)
        return;
    i = 0;
    while (array[i] != NULL) {
        free(array[i]);
        array[i] = NULL;
        i++;
    }
    free(array);
}

void free_chars(t_chars *list)
{
    t_chars *tmp;
    
    while (list)
    {
        tmp = list;
        list = list->next;
        free(tmp->str);
        free(tmp);
    }
}

void free_ints_list(t_ints *head) {
	t_ints *tmp;

	while (head) 
    {
		tmp = head->next;
		free(head);
		head = tmp;
	}
}

void free_commande(t_comm *com)  
{
    if (!com)
        return;
   
    if (com->p_com)
    {
        for (int i = 0; com->p_com[i]; i++)
            free(com->p_com[i]);  
        free(com->p_com);        
    }
    
    //dont free this here for now, it segv when i free it the
    /*if (com->commande)
        free(com->commande);*/
    
    if (com->redirections)
        free_chars(com->redirections);
    
    if (com->heardoc)
        free_chars(com->heardoc);
}

void free_all_commande(t_comm *comms, int size)
{
	int i;

	if (!comms)
		return;
	i = 0;
	while (i < size)
	{
		free_commande(&comms[i]);
		i++;
	}
	free(comms);
}