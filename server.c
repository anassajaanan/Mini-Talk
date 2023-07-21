#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>

char data_byte = 0;
int bits_count = 0;


void	signal_handler(int signal_number)
{
	if (signal_number == SIGUSR1)
	{
		int mask  = 1 << bits_count;
		data_byte |= mask;
	}
	else if (signal_number == SIGUSR2)
	{
		int mask  = 1 << bits_count;
		data_byte &= ~mask;
	}
	else {
        // Received an unknown signal
        printf("Received an unknown signal: %d\n", signal_number);
        return;
    }

	bits_count++;

	if (bits_count == 8)
	{
		printf("%c", (char)data_byte);
		fflush(stdout);
		bits_count = 0;
		data_byte = 0;
	}
}

int main(int argc, char **argv)
{
	
	printf("The server PID is : %d\n", getpid());

	while (argc == 1)
	{
		signal(SIGUSR1, signal_handler);
		signal(SIGUSR2, signal_handler);
		pause();
	}
	return (0);

}