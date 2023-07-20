#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>

int total = 0;
int first = 1;

void	signal_handler(int signal_number)
{
	if (signal_number == SIGUSR1 && first)
	{
		printf("Start Transmission\n");
		first = 0;
	}
	else if (signal_number == SIGUSR1 && !first)
	{
		printf("Received %c signals\n", (char)total);
		printf("End of Transmission\n");
		total = 0;
		first = 1;
	}
	else if (signal_number == SIGUSR2)
	{
		total++;
	}
}

int main(int argc, char **argv)
{
	
	printf("%d\n", getpid());

	while (argc == 1)
	{
		signal(SIGUSR1, signal_handler);
		signal(SIGUSR2, signal_handler);
		pause();
	}
	return (0);

}