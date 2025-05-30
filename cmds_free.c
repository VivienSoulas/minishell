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

	i = -1;
	if (!commands || !*commands)
		return ;
	while (commands[++i])
	{
		free_strings(commands[i]);
		if (commands[i]->args)
		{
			j = -1;
			while (commands[i]->args[++j])
			{
				free(commands[i]->args[j]);
				commands[i]->args[j] = NULL;
			}
			free(commands[i]->args);
			commands[i]->args = NULL;
		}
		free(commands[i]);
		commands[i] = NULL;
	}
	free(commands);
	commands = NULL;
}
