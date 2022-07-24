#include <stdio.h>
#include <stdlib.h>

#include "modules/calc/include/k_config.h"
#include "modules/calc/include/k_datatype.h"
#include "modules/calc/include/k_util.h"
#include <time.h>

static unsigned int clock_prev;
static unsigned int clock_this;

#ifdef _WIN32
static unsigned int clock_ms()
{
	return clock();
}

void k_clk_init()
{
	clock_this=clock_ms();
	clock_prev=clock_this;
}

void k_clk_do()
{
	clock_prev=clock_this;
	clock_this=clock();
}

Int clk_cycle_ms()
{
	return clock_this-clock_prev;
}

Time clk_cycle()
{
	return (Time)(clock_this-clock_prev)/1000.;
}

Time clk_now()
{
	return 0.;
}
#endif

#ifdef _LINUX
static struct timeval t_prev;
static struct timeval t_this;

void k_clk_init()
{
	gettimeofday(&t_this, NULL);
	t_prev = t_this; 
}

void k_clk_do()
{
	t_prev = t_this; 
	gettimeofday(&t_this, NULL);
}

Int clk_cycle_ms()
{
	long sec,usec;
	sec = t_this.tv_sec - t_prev.tv_sec;
	usec = t_this.tv_usec - t_prev.tv_usec;
	return (1000 * sec + 0.001 * usec);
}

Time clk_cycle()
{
	long sec,usec;
	sec = t_this.tv_sec - t_prev.tv_sec;
	usec = t_this.tv_usec - t_prev.tv_usec;
	return (sec + 0.000001 * usec);
}

Time clk_now()
{
	return 0.;
}
#endif


void *k_malloc(size_t s)
{
	return malloc(s);
}

void k_free(void *p)
{
	free(p);
}

