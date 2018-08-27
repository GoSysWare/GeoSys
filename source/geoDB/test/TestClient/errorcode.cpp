/**ͳһ��ʽ��A-BB-CC
A:���󼶱���1����ϵͳ������2������񼶴���;
B:��Ŀ��ģ������;
C:���������*/

/**�������˵��
(20502)
2: ���񼶴���1Ϊϵͳ������
05: ����ģ�����
02: ����������*/
#define UV_ERRNO_MAP(XX)                                                  \
    XX(    0, UNKNOWN,                "unknown error")                    \
    XX(    1, OK,                     "success")                          \
    XX(10201, SYS_EOF,                "end of file")                      \
    XX(10202, SYS_INVALID_SOCKET,     "invalid socket fd")                \
    XX(10401, CLI_INVALID_PASSWORD,   "invalid password")

/** ö�� */
#define UV_ERRNO_GEN(val, name, s) UV_##name = val,
typedef enum {
	UV_ERRNO_MAP(UV_ERRNO_GEN)
	UV_MAX_ERRORS
} uv_result_code;
#undef UV_ERRNO_GEN

#define UV_STRERROR_GEN(val, name, s) case UV_##name : return s;
/** ��ȡ���������� */
const char* uv_code_desc(uv_result_code code) {
	switch (code) {
		UV_ERRNO_MAP(UV_STRERROR_GEN)
	default:
		return "unknown error";
	}
}
#undef UV_STRERROR_GEN

#define UV_ERR_NAME_GEN(val, name, s) case UV_##name : return #name;
/** ��ȡ���������� */
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