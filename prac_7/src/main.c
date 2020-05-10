#include	<stdio.h>
#include	<signal.h>

#define	INPUTLEN	100

main(int ac, char *av[])
{
	void    sig_handler(int);
	char	input[INPUTLEN];
	int	nchars;
	
	signal( SIGINT, sig_handler );		/* set handler */
	signal( SIGQUIT, sig_handler );		/* set handler */
	
	do {
		printf("\nType a message\n");
		nchars = read(0, input, (INPUTLEN-1));
		if ( nchars == -1 )
			perror("read returned an error");
		else {
			input[nchars] = '\0';
			printf("You typed: %s", input);
		}
	} 
	while( strncmp( input , "quit" , 4 ) != 0 );
}

void sig_handler(int sig_num) {
	
	switch (sig_num) {
		case SIGINT: {
			printf(" Received signal %d .. waiting\n", sig_num );
			sleep(2);
			printf("  Leaving inthandler \n");
		} break;
		
		case SIGQUIT: {
			printf(" Received signal %d .. waiting\n", sig_num );
			sleep(3);
			printf("  Leaving quithandler \n");
		} break;
		
		default: {
			printf("Unhandled signal received\r\n");
			sleep(3);
		}
	}
}
