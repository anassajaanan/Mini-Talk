/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:48:55 by aajaanan          #+#    #+#             */
/*   Updated: 2023/07/22 10:00:15 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_global_state	g_state = {0, 0};

// Function to send acknowledgment signal to the client
void	send_acknowledgment(int client_pid)
{
	if (kill(client_pid, SIGUSR1) == -1)
	{
		ft_putstr_fd("Error sending acknowledgment signal\n", 2);
		exit(1);
	}
}

// Function to process a completed byte
void	process_completed_byte(int client_pid)
{
	if (g_state.data_byte == '\0')
		send_acknowledgment(client_pid);
	ft_putchar_fd((char)g_state.data_byte, 1);
	g_state.bits_count = 0;
	g_state.data_byte = 0;
}

// Function to handle signals
void	signal_handler(int signal_number, siginfo_t *info, void *context)
{
	int	mask;
	int	client_pid;

	(void)context;
	client_pid = info->si_pid;
	if (signal_number == SIGUSR1)
	{
		mask = 1 << g_state.bits_count;
		g_state.data_byte |= mask;
	}
	else if (signal_number == SIGUSR2)
	{
		mask = 1 << g_state.bits_count;
		g_state.data_byte &= ~mask;
	}
	else
	{
		ft_putstr_fd("Received an unknown signal\n", 2);
		return ;
	}
	g_state.bits_count++;
	if (g_state.bits_count == 8)
		process_completed_byte(client_pid);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	(void)argv;
	ft_putstr_fd("The server PID is : ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (argc == 1)
	{
		pause();
	}
	return (0);
}
