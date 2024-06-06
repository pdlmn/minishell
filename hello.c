#include <signal.h>
#include <sys/ioctl.h>
#include <stdio.h>

static void	handle_signal(int signal, siginfo_t *siginfo, void *context)
{
	(void)context;
	(void)siginfo;
	if (signal == SIGINT)
	{
		printf("hello\n");
	}
}

void	attach_signal_handlers()
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	sa_sigint.sa_sigaction = handle_signal;
	sa_sigquit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_sigint, 0);
	sigaction(SIGQUIT, &sa_sigquit, 0);
}

int main ()
{
	attach_signal_handlers();
	while (1) {}
}
