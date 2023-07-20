#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>


void	send_data(int server_pid, char c)
{
	int result1 = kill(server_pid, SIGUSR1);
	if (result1 == 0)
	{
		printf("Start Transmission\n");
	}
	else
	{
		printf("Error\n");
	}

	int signal_num = (int)c;
	for (int i = 0; i < signal_num; i++)
	{
		if (kill(server_pid, SIGUSR2) == -1) {
            perror("Error sending data signal");
            exit(1);
        }
		usleep(1000);
	}

	result1 = kill(server_pid, SIGUSR1);
	if (result1 == 0)
	{
		printf("Start Transmission\n");
	}
}

int main(int argc, char **argv)
{
	if (argc == 3)
	{
		int pid = atoi(argv[1]);
		char data = argv[2][0];

		send_data(pid, data);
	}
}