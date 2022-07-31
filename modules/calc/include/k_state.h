#ifndef k_state_h
#define k_state_h

// #ifdef __cplusplus
// extern "C" {
// #endif

//									stop/run
//									connect/disconnect
//							????	sync/async
//									IO collision/not collision
#define S_UNKNOWN 0
#define S_PRIMARY 1
#define S_STANDBY 2
//#define S_ARBITRATING 3
void state_init();
void state_check();
void state_decrease_peer_life();
void state_full_peer_life();

// #ifdef __cplusplus
// }
// #endif
#endif
