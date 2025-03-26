#include "../minishell.h"

/*function used for debugging purposes , prints the whole content
of the p_comm struct used to parse the initial command*/

void print_t_comm(t_comm *cmd)
{
    if (cmd == NULL)
        return;

    printf("p_com:\n");
    if (cmd->p_com)
    {
        for (int i = 0; cmd->p_com[i] != NULL; i++)
        {
            printf("[ %s ]\n", cmd->p_com[i]);
        }
    }

    printf("commande: ['%s']\n", cmd->commande);

    printf("infile:\n");
    t_chars *current_infile = cmd->infile; 
    while (current_infile)
    {
        printf("[ %s ]\n", current_infile->str);
        current_infile = current_infile->next;
    }

    printf("outfile:\n");
    t_chars *current_outfile = cmd->outfile; 
    while (current_outfile)
    {
        printf("[ %s ]\n", current_outfile->str);
        current_outfile = current_outfile->next;
    }
}