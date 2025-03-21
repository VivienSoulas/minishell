#include "parsing.h"

void	free_strings(t_command *command)
{
	if (command->input_file)
		free(command->input_file);
	if (command->output_file)
		free(command->output_file);
	if (command->heredoc_delimiter)
		free(command->heredoc_delimiter);
	if (command->executable_path)
		free(command->executable_path);
}

void	command_cleanup(t_command **commands)
{
	int			i;
	int			j;

	i = 0;
	if (!commands)
		return ;
	while (commands[i])
	{
		free_strings(commands[i]);
		if (commands[i]->args)
		{
			j = 0;
			while (commands[i]->args[j])
			{
				free(commands[i]->args[j]);
				j++;
			}
			free(commands[i]->args);
		}
		free(commands[i]);
		i++;
	}
	free(commands);
}
