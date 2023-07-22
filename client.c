/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:49:03 by aajaanan          #+#    #+#             */
/*   Updated: 2023/07/22 09:40:29 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signal_number, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signal_number == SIGUSR1)
		ft_putstr_fd("🎉 Your message has been successfully \
received by the server! 🎉\n", 1);
	else
		ft_putstr_fd("🚨 An error occurred \
while sending your message to the server! 🚨\n", 1);
}

void	send_character_signal(int server_pid, char data)
{
	int	i;
	int	mask;

	i = 0;
	while (i < 8)
	{
		mask = 1 << i;
		if ((data & mask) == 0)
		{
			kill(server_pid, SIGUSR2);
		}
		else
		{
			kill(server_pid, SIGUSR1);
		}
		usleep(100);
		i++;
	}
}

void	send_message_to_server(int argc, char **argv, int server_pid)
{
	int		arg_index;
	char	*current_arg;

	arg_index = 2;
	while (arg_index < argc)
	{
		current_arg = argv[arg_index];
		while (*current_arg)
		{
			send_character_signal(server_pid, *current_arg);
			current_arg++;
		}
		send_character_signal(server_pid, ' ');
		arg_index++;
	}
	send_character_signal(server_pid, '\n');
	send_character_signal(server_pid, '\0');
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					server_pid;

	if (argc < 3)
	{
		ft_putstr_fd("Usage: ./client <server_pid> <message>\n", 2);
		return (1);
	}
	if (!is_numeric(argv[1]))
	{
		ft_putstr_fd("Invalid server PID: ", 2);
		ft_putstr_fd(argv[1], 2);
		return (1);
	}
	sa.sa_sigaction = signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	server_pid = atoi(argv[1]);
	send_message_to_server(argc, argv, server_pid);
	return (0);
}
