#ifndef k_state_h
#define k_state_h

#ifdef __cplusplus
extern "C" {
#endif

//									stop/run
//									connect/disconnect
//							????	sync/async
//									IO collision/not collision
#define S_UNKNOWN 0
#define S_PRIMARY 1
#define S_STANDBY 2
//#define S_ARBITRATING 3
void sta_init();
void sta_check();
void sta_decrease_peer_life();
void sta_full_peer_life();

#ifdef __cplusplus
}
#endif
#endif
