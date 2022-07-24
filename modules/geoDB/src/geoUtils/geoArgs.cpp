#ifndef LIB_UTILS_EXPORTS
#define LIB_UTILS_EXPORTS
#endif // !LIB_UTILS_EXPORTS
#include"geoArgs.h"


CArgsExA::CArgsExA()
{
	argc = 0;
	argv = 0;
	arg_idx = 0;
	args = 0;
	len = 0;
	arg_len = 0;
}

CArgsExA::CArgsExA(
	const char * src,
	const char * delimiter,
	int arg_len,
	int maxlen,
	bool ignore_empty_fields
) {
	parse(src, delimiter, arg_len, maxlen, ignore_empty_fields);
}

CArgsExA::~CArgsExA()
{
	destroy();
}

void CArgsExA::destroy()
{
	if (args) {
		free(args);
		args = 0;
	}
	if (arg_idx) {
		delete arg_idx;
		arg_idx = 0;
	}
	if (argv) {
		delete argv;
		argv = 0;
	}
	argc = 0;
	len = 0;
	arg_len = 0;
}

bool CArgsExA::create(int max_argc, int maxlen)
{
	args = new char[maxlen];
	arg_idx = new int[max_argc];
	argv = new char *[max_argc];
	if (!arg_idx || !argv || !args) {
		destroy();
		return false;
	}
	len = maxlen;
	arg_len = max_argc;
	return true;
}

//把src的内容赋给args、argv、arg_idx、argc
int CArgsExA::parse(
	const char * src,
	const char * delimiter,
	int max_argc,
	int maxlen,
	bool ignore_empty_fields
) {
	if (!max_argc) {
		max_argc = MAX_ARGC;
	}
	if (!maxlen) {
		maxlen = MAX_LINE_LENGTH;
	}
	if (!delimiter) {
		delimiter = " \n";
	}

	// if buffer is reusable?
	if (arg_len < max_argc || maxlen < len) {
		destroy();
		if (!create(max_argc, maxlen)) {
			return 0;
		}
	}

	strncpy(args, src, len);
	args[len - 1] = '\0';

	int i;
	char in_quotation;
	char * p, *marker;

	for (i = 0; i<max_argc; i++) argv[i] = "";
	argc = 0;

	p = marker = args;
	in_quotation = false;
	while (*p) {
		if (in_quotation) {
			// in quatation mode, all demiliters are ignored
			// until a matching '"' is found
			if ('"' == *p) {
				in_quotation = FALSE;
				if (*marker == '"' && (strchr(delimiter, p[1]) || !p[1])) {
					/* remove leading and trailing ' " '  for this piece if
					this piece is surrounded by a pair of quote signs,
					note that if the quote signs are in middle of the
					string, then they are not removed.
					*/
					marker++;
					*p = 0;
				}
			}
		}
		else if ('"' == *p) {
			in_quotation = TRUE;
		}
		else if (strchr(delimiter, *p)) {
			// got an argument, emit it to the argument buffer
			*p = 0;
			if (p != marker || !ignore_empty_fields) {
				argv[argc] = marker;
				arg_idx[argc] = marker - args;
				argc++;
			}
			marker = p + 1;
		}
		p++;
	}
	if (p != marker) {
		argv[argc] = marker;
		arg_idx[argc] = marker - args;
		argc++;
	}

	return argc;
}



CArgsExW::CArgsExW()
{
	argc = 0;
	argv = 0;
	arg_idx = 0;
	args = 0;
	len = 0;
	arg_len = 0;
}

CArgsExW::CArgsExW(
	const wchar_t * src,
	const wchar_t * delimiter,
	int arg_len,
	int maxlen,
	bool ignore_empty_fields
) {
	parse(src, delimiter, arg_len, maxlen, ignore_empty_fields);
}

CArgsExW::~CArgsExW()
{
	destroy();
}

void CArgsExW::destroy()
{
	if (args) {
		free(args);
		args = 0;
	}
	if (arg_idx) {
		delete arg_idx;
		arg_idx = 0;
	}
	if (argv) {
		delete argv;
		argv = 0;
	}
	argc = 0;
	len = 0;
	arg_len = 0;
}

bool CArgsExW::create(int max_argc, int maxlen)
{
	args = new wchar_t[maxlen];
	arg_idx = new int[max_argc];
	argv = new wchar_t *[max_argc];
	if (!arg_idx || !argv || !args) {
		destroy();
		return false;
	}
	len = maxlen;
	arg_len = max_argc;
	return true;
}

int CArgsExW::parse(
	const wchar_t * src,
	const wchar_t * delimiter,
	int max_argc,
	int maxlen,
	bool ignore_empty_fields
) {
	if (!max_argc) {
		max_argc = MAX_ARGC;
	}
	if (!maxlen) {
		maxlen = MAX_LINE_LENGTH;
	}
	if (!delimiter) {
		delimiter = L" \n";
	}

	// if buffer is reusable?
	if (arg_len != max_argc || maxlen != len) {
		destroy();
		if (!create(max_argc, maxlen)) {
			return 0;
		}
	}

	wcsncpy(args, src, len);
	args[len - 1] = '\0';

	int i;
	wchar_t in_quotation;
	wchar_t * p, *marker;

	for (i = 0; i<max_argc; i++) {
		argv[i] = L"";
	}
	argc = 0;

	p = marker = args;
	in_quotation = false;
	while (*p) {
		if (in_quotation) {
			// in quatation mode, all demiliters are ignored
			// until a matching '"' is found
			if ('"' == *p) {
				in_quotation = FALSE;
				if (*marker == '"' && (wcschr(delimiter, p[1]) || !p[1])) {
					/* remove leading and trailing ' " '  for this piece if
					this piece is surrounded by a pair of quote signs,
					note that if the quote signs are in middle of the
					string, then they are not removed.
					*/
					marker++;
					*p = 0;
				}
			}
		}
		else if ('"' == *p) {
			in_quotation = TRUE;
		}
		else if (wcschr(delimiter, *p)) {
			// got an argument, emit it to the argument buffer
			*p = 0;
			if (p != marker || !ignore_empty_fields) {
				argv[argc] = marker;
				arg_idx[argc] = marker - args;
				argc++;
			}
			marker = p + 1;
		}
		p++;
	}
	if (p != marker) {
		argv[argc] = marker;
		arg_idx[argc] = marker - args;
		argc++;
	}

	return argc;
}


GEO_UITLS_API
int GEO_CALL parse_arg_exA(const char * cmd_line, CArgsA * args, char * delimiter)
{
	int i;
	char in_quotation;
	char * p, *marker;

#undef utils_argv
#undef utils_argc

#define utils_argv (args->argv)
#define utils_argc (args->argc)

	if (!delimiter) delimiter = " \n";

	strncpy(args->args, cmd_line, sizeof(args->args));
	args->args[sizeof(args->args) - 1] = 0;
	for (i = 0; i<MAX_ARGC; i++) utils_argv[i] = "";
	utils_argc = 0;

	utils_argc = 0;
	p = marker = args->args;
	in_quotation = FALSE;
	while (*p) {
		if (in_quotation) {
			// in quatation mode, all demiliters are ignored
			// until a matching '"' is found
			if ('"' == *p) {
				in_quotation = FALSE;
				if (*marker == '"' && (strchr(delimiter, p[1]) || !p[1])) {
					/* remove leading and trailing ' " '  for this piece if
					this piece is surrounded by a pair of quote signs,
					note that if the quote signs are in middle of the
					string, then they are not removed.
					*/
					marker++;
					*p = 0;
				}
			}
		}
		else if ('"' == *p) {
			in_quotation = TRUE;
		}
		else if (strchr(delimiter, *p)) {
			// got an argument, emit it to the argument buffer
			*p = 0;
			if (p != marker) {
				args->argv[utils_argc] = marker;
				args->arg_idx[utils_argc] = marker - args->args;
				utils_argc++;
			}
			marker = p + 1;
		}
		p++;
	}
	if (p != marker) {
		args->argv[utils_argc] = marker;
		args->arg_idx[utils_argc] = marker - args->args;
		utils_argc++;
	}
	return utils_argc;
}

/*
parse_arg_ey 和 parse_arg_ex 不同，在于它将连续出现的分割符号的处理方式不同
举例来说：
parse_arg_ex(",,,,,",&args,",");
得到零个参数，因为strtok将所有的‘,’都忽略了
而parse_arg_ey(",,,,,",&args,",");
则得到5个参数，每个参数都是空字符串
*/

GEO_UITLS_API
int GEO_CALL parse_arg_eyA(const char * cmd_line, CArgsA * args, char * delimiter)
{
	int i;
	char in_quotation;
	char * p, *marker;

#undef utils_argv
#undef utils_argc

#define utils_argv (args->argv)
#define utils_argc (args->argc)
	if (!delimiter) delimiter = " \n";

	strncpy(args->args, cmd_line, sizeof(args->args));
	args->args[sizeof(args->args) - 1] = 0;
	for (i = 0; i<MAX_ARGC; i++) {
		utils_argv[i] = "";
	}

	utils_argc = 0;
	p = marker = args->args;
	in_quotation = FALSE;
	while (*p) {
		if (in_quotation) {
			// in quatation mode, all demiliters are ignored
			// until a matching '"' is found
			if ('"' == *p) {
				in_quotation = FALSE;
			}
		}
		else if ('"' == *p) {
			in_quotation = TRUE;
		}
		else if (strchr(delimiter, *p)) {
			*p = 0;
			args->argv[utils_argc] = marker;
			args->arg_idx[utils_argc] = marker - args->args;
			utils_argc++;
			marker = p + 1;
		};
		p++;
	};
	args->argv[utils_argc] = marker;
	args->arg_idx[utils_argc] = marker - args->args;
	utils_argc++;
	return utils_argc;
}



GEO_UITLS_API
int GEO_CALL  parse_arg_exW(const wchar_t * cmd_line, CArgsW * args, wchar_t * delimiter)
{
	int i;
	char in_quotation;
	wchar_t * p, *marker;

#undef utils_argv
#undef utils_argc

#define utils_argv (args->argv)
#define utils_argc (args->argc)

	if (!delimiter) delimiter = L" \n";

	wcsncpy(args->args, cmd_line, sizeof(args->args));
	args->args[sizeof(args->args) - 1] = 0;
	for (i = 0; i<MAX_ARGC; i++) {
		utils_argv[i] = L"";
	}
	utils_argc = 0;

	utils_argc = 0;
	p = marker = args->args;
	in_quotation = FALSE;
	while (*p) {
		if (in_quotation) {
			// in quatation mode, all demiliters are ignored
			// until a matching '"' is found
			if ('"' == *p) {
				in_quotation = FALSE;
				if (*marker == '"' && (wcschr(delimiter, p[1]) || !p[1])) {
					/* remove leading and trailing ' " '  for this piece if
					this piece is surrounded by a pair of quote signs,
					note that if the quote signs are in middle of the
					string, then they are not removed.
					*/
					marker++;
					*p = 0;
				}
			}
		}
		else if ('"' == *p) {
			in_quotation = TRUE;
		}
		else if (wcschr(delimiter, *p)) {
			// got an argument, emit it to the argument buffer
			*p = 0;
			if (p != marker) {
				args->argv[utils_argc] = marker;
				args->arg_idx[utils_argc] = marker - args->args;
				utils_argc++;
			}
			marker = p + 1;
		}
		p++;
	};
	if (p != marker) {
		args->argv[utils_argc] = marker;
		args->arg_idx[utils_argc] = marker - args->args;
		utils_argc++;
	}
	return utils_argc;
}

/*
parse_arg_ey 和 parse_arg_ex 不同，在于它将连续出现的分割符号的处理方式不同
举例来说：
parse_arg_ex(L",,,,,L",&args,L",L");
得到零个参数，因为strtok将所有的‘,’都忽略了
而parse_arg_ey(L",,,,,L",&args,L",L");
则得到5个参数，每个参数都是空字符串
*/
GEO_UITLS_API
 int  GEO_CALL parse_arg_eyW(const wchar_t * cmd_line, CArgsW * args, wchar_t * delimiter)
{
	int i;
	char in_quotation;
	wchar_t * p, *marker;

#undef utils_argv
#undef utils_argc

#define utils_argv (args->argv)
#define utils_argc (args->argc)
	if (!delimiter) delimiter = L" \n";

	wcsncpy(args->args, cmd_line, sizeof(args->args));
	args->args[sizeof(args->args) - 1] = 0;
	for (i = 0; i<MAX_ARGC; i++) {
		utils_argv[i] = L"";
	}

	utils_argc = 0;
	p = marker = args->args;
	in_quotation = FALSE;
	while (*p) {
		if (in_quotation) {
			// in quatation mode, all demiliters are ignored
			// until a matching '"' is found
			if ('"' == *p) {
				in_quotation = FALSE;
			}
		}
		else if ('"' == *p) {
			in_quotation = TRUE;
		}
		else if (wcschr(delimiter, *p)) {
			*p = 0;
			args->argv[utils_argc] = marker;
			args->arg_idx[utils_argc] = marker - args->args;
			utils_argc++;
			marker = p + 1;
		};
		p++;
	};
	args->argv[utils_argc] = marker;
	args->arg_idx[utils_argc] = marker - args->args;
	utils_argc++;
	return utils_argc;
}