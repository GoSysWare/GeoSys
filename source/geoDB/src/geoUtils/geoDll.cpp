#ifndef LIB_UTILS_EXPORTS
#define LIB_UTILS_EXPORTS
#endif // !LIB_UTILS_EXPORTS

#include"geoDll.h"
#include"geoWchar.h"
#include<vector>
#include<iterator>

GeoDll::GeoDll()
	: mOpenMode(0),
	mHandle(nullptr)
{
	memset(mDllName, 0, PATH_MAX);

}

GeoDll::GeoDll(const geoTChar  *dll_name,int open_mode)
	: mOpenMode(open_mode),
	mHandle(nullptr)
{
	memset(mDllName, 0, PATH_MAX);

}

GeoDll::~GeoDll()
{
	this->close();

}

int GeoDll::open(geoTChar * dll_filename, int open_mode, SHLIB_HANDLE handle)
{

	if (!dll_filename)
	{
		return -1;
	}

	if (this->mHandle)
	{
		if (strcmp(this->mDllName, dll_filename) == 0)
			return 0;
		else
			this->close();
	}

	strncpy(mDllName, dll_filename, strlen(dll_filename) + 1);

	this->mOpenMode = open_mode;

	if (this->mHandle == nullptr)
	{
		if (handle)
			this->mHandle = handle;
		else
		{
			std::vector<geoStdTString> dll_names;
			//各种情况下的自动处理各种格式的动态库
			getDllNames(dll_filename, dll_names);

			std::vector<geoStdTString>::iterator  name_iter= dll_names.begin();
			geoStdTString *name = 0;
			while (name_iter != dll_names.end())
			{
#ifdef _WIN32
				GEO_UNUSED_ARG(open_mode);
				this->mHandle = GEO_LoadLibrary(name_iter->c_str());
#else
				this->mHandle = ::dlopen(GEO_TEXT_ALWAYS_CHAR(name_iter->c_str()), mOpenMode);
#endif // _WIN32
				//加载成功，则退出
				if (mHandle != 0) break;
				name_iter++;
			}
			//一直没打开动态库
			if (mHandle == nullptr)
			{
				//todo：输出错误信息
				return -1;
			}
		}	
	}
	return 0;
	
}

void
GeoDll::getDllNames(const geoTChar *dll_name,
	std::vector<geoStdTString> &try_names)
{
	// Build the array of DLL names to try on this platform by applying the
	// proper prefixes and/or suffixes to the specified dll_name.
	geoStdTString base(dll_name);
	geoStdTString base_dir, base_file, base_suffix;

	// 1. Separate the dll_name into the dir part and the file part. We
	// only decorate the file part to determine the names to try loading.
	geoStdTString::size_type pos = base.rfind(DIRECTORY_SEPARATOR_CHAR);
	if (pos != geoStdTString::npos)
	{
		base_dir = base.substr(0, pos + 1);
		base_file = base.substr(pos + 1);
	}
	else
		base_file = base;

	// 2. Locate the file suffix, if there is one. Move the '.' and the
	// suffix to base_suffix.
	if ((pos = base_file.rfind(GEO_TEXT('.'))) != geoStdTString::npos)
	{
		base_suffix = base_file.substr(pos);
		base_file = base_file.substr(0, pos);
	}
	if ((try_names.max_size() - try_names.size()) < 5)
		try_names.resize(try_names.max_size() + 5);

	geoStdTString suffix(GEO_DLL_SUFFIX);
	geoStdTString prefix(GEO_DLL_PREFIX);

	for (size_t i = 0; i < 5 && try_names.size() < try_names.max_size(); ++i)
	{
		geoStdTString try_this;
		size_t const j = try_names.size();
		switch (i)
		{
		case 0:        // Prefix + name + decorator + suffix
		case 1:        // Prefix + name + suffix
		case 2:        // Name + decorator + suffix
		case 3:        // Name + suffix
			if (
				base_suffix.length() > 0
				)
				break;
			try_this = base_dir;
			if (i < 2)
				try_this += prefix;
			try_this += base_file;
			if (base_suffix.length() > 0)
				try_this += base_suffix;
			else
			{
				try_this += suffix;
			}
			break;
		case 4:
			try_this = dll_name;
			break;
		}

		if (try_this.length())
		{
			try_names.resize(j + 1);
			try_names[j]=try_this;
		}
	}
	return;
}
void * GeoDll::symbol(const geoTChar *sym_name)
{
	void *sym = 0;
	if (this->mHandle)
	{
#if defined (_WIN32)

		sym = ::GetProcAddress(mHandle, sym_name);
#else
		sym = ::dlsym(mHandle, sym_name);
#endif
		if (sym == nullptr)
		{
			//todo: 错误信息
			return nullptr;
		}
		return sym;
	}
	return nullptr;
}

int GeoDll::close()
{
	int ret = -1;
	if (this->mHandle)
	{
#if defined (_WIN32)
		BOOL b = ::FreeLibrary(mHandle);
		ret = (b == FALSE) ? -1 : 0;
#else
		ret = ::dlclose(handle);
#endif

	}
	return ret;
}