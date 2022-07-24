/**统一格式：A-BB-CC
A:错误级别，如1代表系统级错误，2代表服务级错误;
B:项目或模块名称;
C:具体错误编号*/

/**错误代码说明
(20502)
2: 服务级错误（1为系统级错误）
05: 服务模块代码
02: 具体错误代码*/
#define UV_ERRNO_MAP(XX)                                                  \
    XX(    0, UNKNOWN,                "unknown error")                    \
    XX(    1, OK,                     "success")                          \
    XX(10201, SYS_EOF,                "end of file")                      \
    XX(10202, SYS_INVALID_SOCKET,     "invalid socket fd")                \
    XX(10401, CLI_INVALID_PASSWORD,   "invalid password")

/** 枚举 */
#define UV_ERRNO_GEN(val, name, s) UV_##name = val,
typedef enum {
	UV_ERRNO_MAP(UV_ERRNO_GEN)
	UV_MAX_ERRORS
} uv_result_code;
#undef UV_ERRNO_GEN

#define UV_STRERROR_GEN(val, name, s) case UV_##name : return s;
/** 获取错误码描述 */
const char* uv_code_desc(uv_result_code code) {
	switch (code) {
		UV_ERRNO_MAP(UV_STRERROR_GEN)
	default:
		return "unknown error";
	}
}
#undef UV_STRERROR_GEN

#define UV_ERR_NAME_GEN(val, name, s) case UV_##name : return #name;
/** 获取错误码名称 */
const char* uv_code_name(uv_result_code code) {
	switch (code) {
		UV_ERRNO_MAP(UV_ERR_NAME_GEN)
	default:
		return "unknown name";
	}
}
#undef UV_ERR_NAME_GEN

//int main(int argc, char* argv[])
//{
//	uv_result_code code = uv_result_code::UV_SYS_EOF;
//	const char* name = uv_code_name(code);
//	const char* desc = uv_code_desc(code);
//
//	return 0;
//}