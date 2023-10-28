#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void oft_stack_print();
void oft_finalize();

// Define the function to be called when ctrl-c (SIGINT) signal is sent to process
void oft_signal_handler(int signum)
{
	if (signum == SIGINT || signum == SIGTERM) {
		fprintf(stdout,"Interrupt requested: halting!\n");
		// End program
		oft_finalize();
	} else {
		// Print signal type
		fprintf(stderr,"OFT caught signal %d\n",signum);
		// Print stacktrace
		oft_stack_print();
		// Abort program
		abort();
	}
}

void oft_set_signal_handlers()
{
	// Register signal handler
	signal(SIGINT, oft_signal_handler);
	signal(SIGTERM, oft_signal_handler);
	signal(SIGSEGV, oft_signal_handler);
	signal(SIGBUS, oft_signal_handler);
	signal(SIGFPE, oft_signal_handler);
}
/*
#include <stdint.h>
int64_t oft_realtime_tick()
{
	unsigned cycles_low, cycles_high;
	asm volatile ("CPUID\n\t"
	 "RDTSC\n\t"
	 "mov %%edx, %0\n\t"
	 "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low):: "%rax", "%rbx", "%rcx", "%rdx");
	return (int64_t) ( ((uint64_t)cycles_high << 32) | cycles_low );
}

int64_t oft_realtime_tock()
{
        unsigned cycles_low, cycles_high;
	asm volatile("RDTSCP\n\t"
	 "mov %%edx, %0\n\t"
	 "mov %%eax, %1\n\t"
	 "CPUID\n\t": "=r" (cycles_high), "=r" (cycles_low):: "%rax", "%rbx", "%rcx", "%rdx");
        return (int64_t) ( ((uint64_t)cycles_high << 32) | cycles_low );
}
*/
