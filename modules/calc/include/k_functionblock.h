#ifndef k_functionblock_h
#define k_functionblock_h
// #ifdef __cplusplus
// extern "C" {
// #endif

#include "k_config.h"
#include "k_datatype.h"
#include "k_evdata.h"

// typedef void (*fbrun)(void *);

#define PIN_NO_LOCK 0
#define PIN_HAS_LOCK 1

#define PININPUT 1
#define PINOUTPUT 2
#define PINPROPERTY 3


#define FB_EXEC		0x00   		// 一般执行的功能块
#define FB_INIT		0x01 << 1   // 初始化才执行一次的功能块
#define FB_UINIT 	0x01 << 2   // 初始化才执行一次的功能块

#define FB_COM		0x00   // 一般功能块
#define FB_IO		0x01 << 8   // IO功能块
#define FB_AI		0x01 << 9   // AI功能块

typedef struct  PinFlag
{
	int32_t signal:1;
	int32_t reserve:31;
}pin_flag;

using fb_function = std::function<void(void*)>;

//FB的头定义
typedef struct FBHead{
	std::string libname; 
	std::string fcname;
	std::string fbname;
	u_int64_t cycle_time;		// 上次执行周期总时长
	u_int64_t begin_time;		// 本次开始执行时间 = now
	u_int64_t expend_time;		// 任务执行消耗时长
	const void * owner;			// 所属的program
    int flag;			
	fb_function run;
} fbhead_t;

typedef struct Pin{
	std::string pinname;
	int s;		// 是否有被引用
	v_type t;	// 内置类型
	std::string u;	// 次级类型，主要用作Any类型限定
	std::string i;	// 初始化值
	vam_t v;	// 管脚的值
	apollo::cyber::base::ReentrantRWLock *l;
} pin_t;

typedef struct FB{
	fbhead_t h;
	std::vector<pin_t> ins;
	std::vector<pin_t> outs;
	std::vector<pin_t> props;
} fb_t;

 void fb_init_pin(pin_t *pin);
 
void fb_reset(fb_t *p_fb);
fb_t *fb_new(fb_t *p_source);
void fb_delete(fb_t *p_fb);
pin_t *fb_getpin(fb_t *p_fb, int pintype, unsigned int n);
int fb_setpin(fb_t *p_fb, int pintype, unsigned int n, value_tm v);
int fb_setpin(fb_t *p_fb, int pintype, unsigned int n, vam_t v) ;

std::string fb_pins_to_string(fb_t *p_fb);
std::string fb_vars_to_string(fb_t *p_fb);
void fb_dump(fb_t *p_fb);

// #ifdef __cplusplus
// }
// #endif
#endif
