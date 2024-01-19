#ifndef _EXILE_CORE_ASSERT_NEW_H_
#define _EXILE_CORE_ASSERT_NEW_H_

#include <exile/core/critical.h>
#include <exile/core/cme/cme.h>
#include <exile/core/assertCME.h>


#pragma region Fatal assert

/*
	TO DO:
	may be setup default handler? for fatal assert
*/


#define exAssertFatalF(pred, code, msg, ...)\
	if(pred)\
	{\
		code\
		exCMEDump();\
		exPanicF(msg, __VA_ARGS__);\
	}\

#define exAssertFatal(pred, code, msg)\
	if(pred)\
	{\
		code\
		exCMEDump();\
		exPanic(msg);\
	}\

#pragma endregion

#pragma region General assert


#define exAssert(pred, code, msg)\
	if(pred)\
	{\
		code\
		exCMEDump();\
		exPanic(msg);\
	}\

#define exAssertR(pred, code, value, msg)\
	if(pred)\
	{\
		code\
		exCMEDump();\
		exPanic(msg);\
		return value;\
	}\

#define exAssertF(pred, code, msg, ...)\
	if(pred)\
	{\
		code\
		exCMEDump();\
		exPanicF(msg, __VA_ARGS__);\
	}\

#define exAssertFR(pred, code, value, msg, ...)\
	if(pred)\
	{\
		code\
		exCMEDump();\
		exPanicF(msg, __VA_ARGS__);\
		return value;\
	}\

#pragma endregion

#pragma region Warning assert

#define exAssertWarn(pred, code, msg)\
	exAssert(pred, code, msg);

#define exAssertWarnR(pred, code, returnValue, msg)\
	exAssertR(pred, code, returnValue, msg);

#define exAssertWarnF(pred, code, msg, ...)\
	exAssertF(pred, code, msg, __VA_ARGS__);

#define exAssertWarnFR(pred, returnValue, msg, ...)\
	exAssertR(pred, code, returnValue, msg, __VA_ARGS__);

#pragma endregion

#pragma region Debug assert

#define exAssertDebug(pred, code, msg)\
	exAssert(pred, code, msg);

#define exAssertDebugR(pred, code, value, msg)\
	exAssertR(pred, code, value, msg);

#define exAssertDebugF(pred, code, msg, ...)\
	exAssertF(pred, code, msg, __VA_ARGS__);

#define exAssertDebugFR(pred, code, value, msg, ...)\
	exAssertFR(pred, code, value, msg, __VA_ARGS__);

#pragma endregion


#endif
