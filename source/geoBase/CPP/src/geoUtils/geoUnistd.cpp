#ifndef LIB_UTILS_EXPORTS
#define LIB_UTILS_EXPORTS
#endif // !LIB_UTILS_EXPORTS

#include<stdlib.h>
#include <direct.h>

#include<fcntl.h>
#include<mutex>
#include"geoUnistd.h"

#include"geoStdio.h"
#include"geoErrno.h"
#include "geoTime.h"

#if !defined (_WIN32)
#include <unistd.h>
#else

#endif

//R_OK 4 /* Test for read permission. */
//W_OK 2 /* Test for write permission. */
//X_OK 1 /* Test for execute permission. */
//F_OK 0 /* Test for existence. */

int GEO_CALL geo_access(const char *path, int amode)
{

#if defined(_WIN32)
	return ::_access(path, amode & 6);
#else
	return ::access(path, amode);

#endif 
}


#if defined (_UNICODE)
int GEO_CALL geo_access(const wchar_t *path, int amode)
{
#if defined(_WIN32)
	return ::_waccess(path, amode & 6);
#else
	return ::access(GeoW2A(path).char_rep(), amode);
#endif
}
#endif 



 int GEO_CALL geo_chdir(const char *path)
{

#if defined (_WIN32)
	return ::_chdir(path);
#else
	reutrn ::chdir(path);
#endif 
}

#if defined (_UNICODE)
 int GEO_CALL geo_chdir(const wchar_t *path)
{
#if defined (_WIN32)
	return ::_wchdir(path);
#else 
	return ::geo_chdir(GeoW2A(path).char_rep());
#endif 
}
#endif 


 int GEO_CALL geo_rmdir(const char *path)
 {
#if defined (_WIN32)
	 return ::_rmdir(path);
#else
	 reutrn ::rmdir(path);
#endif
 }

#if defined (_UNICODE)
 int GEO_CALL geo_rmdir(const wchar_t *path)
 {
#if defined (_WIN32)

	 return ::_wrmdir(path);
#else
	 GeoW2A n_path(path);
	 return geo_rmdir(n_path.char_rep());
#endif 
 }
#endif

 int GEO_CALL geo_close(HANDLE handle)
 {
#if defined (_WIN32)
	 return ::CloseHandle(handle) == FALSE ? -1:0;
#else
	 return ::close(handle);
#endif 
 }


 HANDLE GEO_CALL geo_dup(HANDLE handle)
 {
#if defined (_WIN32)
	 HANDLE new_fd;
	 if (::DuplicateHandle(::GetCurrentProcess(),
		 handle,
		 ::GetCurrentProcess(),
		 &new_fd,
		 0,
		 TRUE,
		 DUPLICATE_SAME_ACCESS))
		 return new_fd;
	 else
		 return INVALID_HANDLE_VALUE;
#else
	 reuturn ::dup(handle);
#endif 
 }
 HANDLE GEO_CALL geo_dup(HANDLE handle, pid_t pid)
 {
#if defined (_WIN32)
	 HANDLE new_fd;
	 HANDLE hTargetProcess = ::OpenProcess(PROCESS_DUP_HANDLE,
		 FALSE,
		 pid);
	 if (::DuplicateHandle(::GetCurrentProcess(),
		 handle,
		 hTargetProcess,
		 &new_fd,
		 0,
		 TRUE,
		 DUPLICATE_SAME_ACCESS))
	 {
		 ::CloseHandle(hTargetProcess);
		 return new_fd;
	 }
	 else
		 return INVALID_HANDLE_VALUE;
	 /*NOTREACHED*/
#else
	 GEO_UNUSED_ARG(pid);
	 reuturn::dup(handle);
#endif 
 }

  int GEO_CALL geo_fsync(HANDLE handle)
 {

# if defined (_WIN32)
	 return ::FlushFileBuffers(handle);
# else
	 return::fsync(handle);
# endif 
 }

  int GEO_CALL geo_ftruncate(HANDLE handle, off_t offset)
 {
#if defined (_WIN32)
	 LARGE_INTEGER loff;
	 loff.QuadPart = offset;
	 if (::SetFilePointerEx(handle, loff, 0, FILE_BEGIN))
		 return ::SetEndOfFile(handle);
	 else
		 return (-1);
#else
	 return ::ftruncate(handle, offset);
#endif
 }


 char * GEO_CALL geo_getcwd(char *buf, size_t size)
  {
#if defined (_WIN32)
	  return ::_getcwd(buf, static_cast<int> (size));
#else
	  return ::getcwd(buf, size);
#endif 
  }

#if defined (_UNICODE) 
 wchar_t * GEO_CALL geo_getcwd(wchar_t *buf, size_t size)
  {
#  if defined (WIN32)
	  return ::_wgetcwd(buf, static_cast<int> (size));
#  else
	  char *narrow_buf = new char[size];
	  char *result = 0;
	  result = geo_getcwd(narrow_buf, size);
	  GeoA2W wide_buf(result);
	  delete[] narrow_buf;
	  if (result != 0)
		  geo_strsncpy(buf, wide_buf.wchar_rep(), size);
	  return result == 0 ? 0 : buf;
#  endif 
  }
#endif



  int GEO_CALL geo_hostname(char name[], size_t maxnamelen)
  {
#if defined (_WIN32)
	  if (::gethostname(name,maxnamelen) == 0)
	  {
		  return 0;
	  }
	  else
	  {
		  return ::GetComputerNameA(name, LPDWORD(&maxnamelen)) == FALSE ? -1 : 0;
	  }
#else 
	  return gethostname(name, maxnamelen);
#endif 
  }

#if defined (_UNICODE)
   int geo_hostname(wchar_t name[], size_t maxnamelen)
  {
#if defined (_WIN32)
	  return GetComputerNameW(name, LPDWORD(&maxnamelen)) == FALSE ? -1 : 0;
#else 
	  char *char_name = 0;
	  GEO_NEW_RETURN(char_name, char[maxnamelen], -1);
	  int result = geo_hostname(char_name, maxnamelen);
	  geo_strcpy(name, GeoA2W(char_name).wchar_rep());
	  delete[] char_name;
	  return result;
#endif
  }
#endif 


 off_t GEO_CALL geo_lseek(HANDLE handle, off_t offset, int whence)
   {
#if defined (_WIN32)
	   LONG low_offset = GEO_LOW_PART(offset);
	   LONG high_offset = GEO_HIGH_PART(offset);
	   DWORD const result =
		   ::SetFilePointer(handle, low_offset, &high_offset, whence);
	   if (result == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
		   return (static_cast<off_t> (-1));
	   else
		   return result;
#else
	   return ::lseek(handle, offset, whence);
#endif
   }

 off_t GEO_CALL geo_llseek(HANDLE handle, off_t offset, int whence)
 {
#if defined (_WIN32)
	 LARGE_INTEGER l_offset;
	 l_offset.QuadPart = offset;
	 LONG low_offset = l_offset.LowPart;
	 LONG high_offset = l_offset.HighPart;

	 l_offset.LowPart = ::SetFilePointer(handle,
		 low_offset,
		 &high_offset,
		 whence);
	 if (l_offset.LowPart == INVALID_SET_FILE_POINTER &&
		 GetLastError() != NO_ERROR)
		 return static_cast<off_t> (-1);
	 l_offset.HighPart = high_offset;
	 return l_offset.QuadPart;
# else
	return ::llseek(handle, offset, whence);
#endif
 }

 ssize_t GEO_CALL geo_read(HANDLE handle, void *buf, size_t len)
 {
#if defined (_WIN32)
	 DWORD ok_len;
	 if (::ReadFile(handle, buf, static_cast<DWORD> (len), &ok_len, 0))
		 return (ssize_t)ok_len;
	 else
		 return (-1);
#else

	 ssize_t result;

	  ::read(handle, buf, len);
# if !(defined (EAGAIN) && defined (EWOULDBLOCK) && EAGAIN == EWOULDBLOCK)
	 if (result == -1
#  if !defined (EAGAIN) || !defined (EWOULDBLOCK)
		 && EAGAIN != EWOULDBLOCK
#  endif  /* !EAGAIN || !EWOULDBLOCK */
		 && errno == EAGAIN)
	 {
		 errno = EWOULDBLOCK;
	 }
# endif
	 return result;
#endif 
 }

 int  GEO_CALL geo_pipe(HANDLE fds[])
 {
# if defined (_WIN32)
	return ::CreatePipe(&fds[0], &fds[1], 0, 0);
# else
	 return ::pipe(fds);
# endif 
 }
int GEO_CALL geo_sleep(u_int mseconds)
 {
#if defined (_WIN32)
	 ::Sleep(mseconds );
	 return 0;
#else
	 return ::usleep(mseconds * 1000L);
#endif
 }

HANDLE GEO_CALL geo_open(const char *filename,
	int mode,
	mode_t perms,
	LPSECURITY_ATTRIBUTES sa)
{

#if defined (_WIN32)
	std::mutex m;
	std::unique_lock<std::mutex> thread_lock(m, std::defer_lock);
	DWORD access = GENERIC_READ;
	if (GEO_BIT_ENABLED(mode, O_WRONLY))
		access = GENERIC_WRITE;
	else if (GEO_BIT_ENABLED(mode, O_RDWR))
		access = GENERIC_READ | GENERIC_WRITE;

	DWORD creation = OPEN_EXISTING;

	if ((mode & (_O_CREAT | _O_EXCL)) == (_O_CREAT | _O_EXCL))
		creation = CREATE_NEW;
	else if ((mode & (_O_CREAT | _O_TRUNC)) == (_O_CREAT | _O_TRUNC))
		creation = CREATE_ALWAYS;
	else if (GEO_BIT_ENABLED(mode, _O_CREAT))
		creation = OPEN_ALWAYS;
	else if (GEO_BIT_ENABLED(mode, _O_TRUNC))
		creation = TRUNCATE_EXISTING;

	DWORD flags = 0;

	if (GEO_BIT_ENABLED(mode, _O_TEMPORARY))
		flags |= FILE_FLAG_DELETE_ON_CLOSE | FILE_ATTRIBUTE_TEMPORARY;

	if (GEO_BIT_ENABLED(mode, FILE_FLAG_WRITE_THROUGH))
		flags |= FILE_FLAG_WRITE_THROUGH;
	if (GEO_BIT_ENABLED(mode, FILE_FLAG_OVERLAPPED))
		flags |= FILE_FLAG_OVERLAPPED;
	if (GEO_BIT_ENABLED(mode, FILE_FLAG_NO_BUFFERING))
		flags |= FILE_FLAG_NO_BUFFERING;
	if (GEO_BIT_ENABLED(mode, FILE_FLAG_RANDOM_ACCESS))
		flags |= FILE_FLAG_RANDOM_ACCESS;
	if (GEO_BIT_ENABLED(mode, FILE_FLAG_SEQUENTIAL_SCAN))
		flags |= FILE_FLAG_SEQUENTIAL_SCAN;
	if (GEO_BIT_ENABLED(mode, FILE_FLAG_DELETE_ON_CLOSE))
		flags |= FILE_FLAG_DELETE_ON_CLOSE;
	if (GEO_BIT_ENABLED(mode, FILE_FLAG_BACKUP_SEMANTICS))
		flags |= FILE_FLAG_BACKUP_SEMANTICS;
	if (GEO_BIT_ENABLED(mode, FILE_FLAG_POSIX_SEMANTICS))
		flags |= FILE_FLAG_POSIX_SEMANTICS;

	if (GEO_BIT_ENABLED(mode, _O_APPEND))
	{
		thread_lock.lock();
	}

	DWORD shared_mode = perms;
	SECURITY_ATTRIBUTES sa_buffer;
	SECURITY_DESCRIPTOR sd_buffer;

	HANDLE h = ::CreateFileA(filename,
		access,
		shared_mode,
		geo_default_win32_sa_r
		(sa, &sa_buffer, &sd_buffer),
		creation,
		flags,
		0);

	if (GEO_BIT_ENABLED(mode, _O_APPEND))
	{
		LONG high_size = 0;
		if (h != INVALID_HANDLE_VALUE
			&& ::SetFilePointer(h,
				0,
				&high_size,
				FILE_END) == INVALID_SET_FILE_POINTER
			&& GetLastError() != NO_ERROR)
		{
			thread_lock.unlock();
				return (INVALID_HANDLE_VALUE);
		}
		thread_lock.unlock();
	}
	return h;
#else
	GEO_UNUSED_ARG(sa);
	return (::open(filename, mode, perms));
#endif 
}

#ifdef _UNICODE
HANDLE GEO_CALL geo_open(const wchar_t *filename,
	int mode,
	mode_t perms,
	LPSECURITY_ATTRIBUTES sa)
{

#if defined (_WIN32)
	std::mutex m;
	std::unique_lock<std::mutex> thread_lock(m, std::defer_lock);
	DWORD access = GENERIC_READ;
	if (GEO_BIT_ENABLED(mode, O_WRONLY))
		access = GENERIC_WRITE;
	else if (GEO_BIT_ENABLED(mode, O_RDWR))
		access = GENERIC_READ | GENERIC_WRITE;

	DWORD creation = OPEN_EXISTING;

	if ((mode & (_O_CREAT | _O_EXCL)) == (_O_CREAT | _O_EXCL))
		creation = CREATE_NEW;
	else if ((mode & (_O_CREAT | _O_TRUNC)) == (_O_CREAT | _O_TRUNC))
		creation = CREATE_ALWAYS;
	else if (GEO_BIT_ENABLED(mode, _O_CREAT))
		creation = OPEN_ALWAYS;
	else if (GEO_BIT_ENABLED(mode, _O_TRUNC))
		creation = TRUNCATE_EXISTING;

	DWORD flags = 0;

	if (GEO_BIT_ENABLED(mode, _O_TEMPORARY))
		flags |= FILE_FLAG_DELETE_ON_CLOSE | FILE_ATTRIBUTE_TEMPORARY;

	if (GEO_BIT_ENABLED(mode, FILE_FLAG_WRITE_THROUGH))
		flags |= FILE_FLAG_WRITE_THROUGH;
	if (GEO_BIT_ENABLED(mode, FILE_FLAG_OVERLAPPED))
		flags |= FILE_FLAG_OVERLAPPED;
	if (GEO_BIT_ENABLED(mode, FILE_FLAG_NO_BUFFERING))
		flags |= FILE_FLAG_NO_BUFFERING;
	if (GEO_BIT_ENABLED(mode, FILE_FLAG_RANDOM_ACCESS))
		flags |= FILE_FLAG_RANDOM_ACCESS;
	if (GEO_BIT_ENABLED(mode, FILE_FLAG_SEQUENTIAL_SCAN))
		flags |= FILE_FLAG_SEQUENTIAL_SCAN;
	if (GEO_BIT_ENABLED(mode, FILE_FLAG_DELETE_ON_CLOSE))
		flags |= FILE_FLAG_DELETE_ON_CLOSE;
	if (GEO_BIT_ENABLED(mode, FILE_FLAG_BACKUP_SEMANTICS))
		flags |= FILE_FLAG_BACKUP_SEMANTICS;
	if (GEO_BIT_ENABLED(mode, FILE_FLAG_POSIX_SEMANTICS))
		flags |= FILE_FLAG_POSIX_SEMANTICS;

	if (GEO_BIT_ENABLED(mode, _O_APPEND))
	{
		thread_lock.lock();
	}

	DWORD shared_mode = perms;
	SECURITY_ATTRIBUTES sa_buffer;
	SECURITY_DESCRIPTOR sd_buffer;

	HANDLE h = ::CreateFileW(filename,
		access,
		shared_mode,
		geo_default_win32_sa_r
		(sa, &sa_buffer, &sd_buffer),
		creation,
		flags,
		0);

	if (GEO_BIT_ENABLED(mode, _O_APPEND))
	{
		LONG high_size = 0;
		if (h != INVALID_HANDLE_VALUE
			&& ::SetFilePointer(h,
				0,
				&high_size,
				FILE_END) == INVALID_SET_FILE_POINTER
			&& GetLastError() != NO_ERROR)
		{
			thread_lock.unlock();
			return (INVALID_HANDLE_VALUE);
		}
		thread_lock.unlock();
	}
	return h;
#else
	GEO_UNUSED_ARG(sa);
	return (::open(GeoW2A(filename).char_rep(), mode, perms));
#endif 
}
#endif // _UNICODE


 int GEO_CALL geo_truncate(const geoTChar *filename,off_t offset)
{
#if defined (_WIN32)
	HANDLE handle = geo_open(filename,O_WRONLY, DEFAULT_FILE_PERMS);

#  if !defined (ACE_LACKS_WIN32_SETFILEPOINTEREX)
	LARGE_INTEGER loffset;
	loffset.QuadPart = offset;
#else
	LONG low_offset = ACE_LOW_PART(offset);
	LONG high_offset = ACE_HIGH_PART(offset);
#endif

	if (handle == INVALID_HANDLE_VALUE)
		return (-1);

	else if (::SetFilePointerEx(handle,
		loffset,
		0,
		FILE_BEGIN))
	{
		BOOL result = ::SetEndOfFile(handle);
		::CloseHandle(handle);
		return result == FALSE ? -1 : 0;
	}
	else
	{
		::CloseHandle(handle);
		return (-1);
	}
	/* NOTREACHED */
#else
	return ::truncate(GEO_TEXT_ALWAYS_CHAR(filename), offset);
#endif 
}

  ssize_t GEO_CALL geo_write(HANDLE handle, const void *buf, size_t nbyte)
 {
#if defined (_WIN32)
	 DWORD bytes_written; 
	 DWORD short_nbyte = static_cast<DWORD> (nbyte);
	 if (::WriteFile(handle, buf, short_nbyte, &bytes_written, 0))
		 return (ssize_t)bytes_written;
	 else
		 return (-1);
#else
	 return ::write(handle, buf, nbyte);
#endif 
 }


  int GEO_CALL geo_fstat(HANDLE handle, Geo_stat *stp)
  {
#if defined (_WIN32)

	  BY_HANDLE_FILE_INFORMATION fdata;

	  if (::GetFileInformationByHandle(handle, &fdata) == FALSE)
	  {
		  set_errno_to_last_error();
		  return -1;
	  }
	  else if (fdata.nFileSizeHigh != 0)
	  {
		  errno = EINVAL;
		  return -1;
	  }
	  else
	  {
		  stp->st_size = fdata.nFileSizeLow;
		  stp->st_atime = FileTimeToUnixTime(fdata.ftLastAccessTime);
		  stp->st_mtime = FileTimeToUnixTime(fdata.ftLastWriteTime);
		  stp->st_ctime = FileTimeToUnixTime(fdata.ftCreationTime);
		  stp->st_nlink = static_cast<short> (fdata.nNumberOfLinks);
		  stp->st_dev = stp->st_rdev = 0; // No equivalent conversion.
		  stp->st_mode = S_IXOTH | S_IROTH |
			  (fdata.dwFileAttributes & FILE_ATTRIBUTE_READONLY ? 0 : S_IWOTH) |
			  (fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? S_IFDIR : S_IFREG);
	  }
	  return 0;
#else

	  return (::fstat(handle, stp);
# endif
  }

  off_t GEO_CALL geo_filesize(HANDLE handle)
  {
#if defined (_WIN32)
# if defined (_WIN64)
	  LARGE_INTEGER size;
	  return(::GetFileSizeEx(handle, &size)? size.QuadPart: (set_errno_to_last_error(), -1));
# else
	  DWORD const size = ::GetFileSize(handle, 0);
	  return(size != INVALID_FILE_SIZE? static_cast<off_t> (size): (set_errno_to_last_error(), -1));
# endif  
#else 
	  geo_stat sb;
	  return geo_fstat(handle, &sb) == -1 ?static_cast<off_t> (-1) : sb.st_size;
#endif
  }


  off_t GEO_CALL geo_filesize(const geoTChar *filename)
  {

	  HANDLE const h = geo_open(filename, O_RDONLY);
	  if (h != INVALID_HANDLE_VALUE)
	  {
		  off_t size = geo_filesize(h);
		  geo_close(h);
		  return size;
	  }
	  else
		  return -1;
  }
  int GEO_CALL geo_mkdir(const char *path, mode_t mode)
  {
#if defined (_WIN32)

	  GEO_UNUSED_ARG(mode);
	  return ::_mkdir(path);
#else
	  return ::mkdir(path, mode);
#endif
  }

#if defined (_UNICODE)
  int GEO_CALL geo_mkdir(const wchar_t *path, mode_t mode)
  {
#if defined (_WIN32)

	  GEO_UNUSED_ARG(mode);
	  return ::_wmkdir(path);
#else
	  return ::geo_mkdir(GeoW2A(path).char_rep(), mode);
#endif
  }
#endif
 
   int GEO_CALL geo_stat(const char *file, Geo_stat *stp)
  {
	  return GEO_STAT_FUNC_NAME(file, stp);
  }

#if defined (_UNICODE)
 int  GEO_CALL geo_stat(const wchar_t *file, Geo_stat *stp)
   {
	   GeoW2A nfile(file);
	   return geo_stat(nfile.char_rep(), stp);
   }
#endif 

struct tm * GEO_CALL geo_localtime_r(const time_t *t, struct tm *res)
{
#if defined _WIN32
	errno_t ___ = localtime_s(res, t);
	if (___ != 0) {
		errno = ___;
		res = 0;
	}
	return res;
#else
	return(struct tm *)::localtime_r(t, res);
#endif 
}

 pid_t GEO_CALL  geo_getpid(void)
{
#if defined (_WIN32)
	return ::GetCurrentProcessId();
#else
	return ::getpid()
#endif
}