#ifndef helper_h
#define helper_h
// #ifdef __cplusplus
// extern "C" {
// #endif

#define MAXARGCOUNT	 32
#define MAXARGLENGTH 128

typedef struct Arg
{
	char d[MAXARGLENGTH];
} arg_t;

typedef struct Args
{
	int c;
	arg_t v[MAXARGCOUNT];
} args_t;

void str2args(char d, char *str, int len, args_t *args);
void args2str(char d, args_t *args, char *str, int len);

// #ifdef __cplusplus
// extern "C" {
// #endif
#endif