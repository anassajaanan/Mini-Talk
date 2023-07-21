#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>


void	send_data(int server_pid, char data)
{
	for (int i = 0; i < 8; i++)
	{
		int mask = 1 << i;
		if ((data & mask) == 0)
		{
			kill(server_pid, SIGUSR2);
		}
		else
		{
			kill(server_pid, SIGUSR1);
		}
		usleep(100);
	}
}

int	is_numeric(const char *str)
{
	if (*str && (*str == '+'))
		str++;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int main(int argc, char **argv)
{
	int		i;
	char	*data;
	int		server_pid;
	
	if (argc < 3)
	{
		printf("Usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	if (!is_numeric(argv[1]))
	{
		printf("Invalid server PID: %s\n", argv[1]);
		return (1);
	}
	server_pid = atoi(argv[1]);
	i = 2;
	while (i < argc)
	{
		data = argv[i];
		while (*data)
		{
			send_data(server_pid, *data);
			data++;
		}
		send_data(server_pid, ' ');
		i++;
	}
	send_data(server_pid, '\n');
	return (0);
}