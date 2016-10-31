
#include "geoUtils.h"
#include "geoWchar.h"

#include"geoLogMsg.h"
#ifdef _WIN32
#include<Windows.h>
GEO_OSVERSIONINFO  win32_versioninfo_;
HINSTANCE win32_resource_module_;
std::ostream * g_log_output;

#ifdef __GNUC__
//在动态库调用main函数执行之前执行
static void init_lib(void) __attribute__((constructor));
//在动态库关闭main函数退出执行
static void unit_lib(void) __attribute__((destructor));
#endif

static void init_lib(void)
{
	g_log_output = new std::ofstream("geologfile.txt"); 
	GEO_LOG->msg_ostream(g_log_output, 1);    
	GEO_LOG->open();
}
static void unit_lib(void)
{

}

BOOL WINAPI DllMain(
	HINSTANCE hinstDLL,  // handle to the DLL module
	DWORD fdwReason,     // reason for calling function
	LPVOID lpvReserved   // reserved
)
{
	TCHAR * cmd;
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:

		init_lib();
#   pragma warning(push)
#   pragma warning(disable:4996)
		win32_versioninfo_.dwOSVersionInfoSize =sizeof(GEO_OSVERSIONINFO);
		GEO_GetVersionEx(&win32_versioninfo_);
#   pragma warning(pop)


		win32_resource_module_ = hinstDLL;

		break;
	case DLL_THREAD_DETACH:



		break;
	}
	return 1;
}
#endif
