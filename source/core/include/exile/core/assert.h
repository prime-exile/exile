#ifndef _EXILE_CORE_ASSERT_H_
#define _EXILE_CORE_ASSERT_H_

#include <exile/core/critical.h>
#include <exile/core/cme/cme.h>
#include <exile/core/cme/dump.h>
#include <exile/core/assertNew.h>


#define EX_s1FatalAssert(pred, code, msg)\
	if(pred) {\
		code\
		exCMEAssertCollectStacktrace();\
		exPanic(msg);\
	}

#define EX_s1FatalAssertF(pred, code, msg, ...)\
	if(pred) {\
		code\
		exCMEAssertCollectStacktrace();\
		exPanicF(msg, __VA_ARGS__);\
	}

#if defined(EXILE_DEV)
#define EX_s1Assert(pred, code, msg)\
	if(pred) {\
		if(exPanic(msg))\
		{\
			code\
		}\
	}

#define EX_s1AssertR(pred, code, value, msg)\
	if(pred) {\
		if(exPanic(msg))\
		{\
			code\
		} else return value;\
	}


#define EX_s1AssertF(pred, code, msg, ...)\
	if(pred) {\
		if(exPanic(msg))\
		{\
			code\
		}\
	}

#define EX_s1AssertFR(pred, code, value, msg, ...)\
	if(pred) {\
		if(exPanicF(msg, __VA_ARGS__))\
		{\
			code\
		} else return value;\
	}
#else
#define EX_s1Assert(pred, code, msg)\
	if(pred) {\
		code\
		exCMEAssertCollectStacktrace();\
		exPanic(msg);\
	}

#define EX_s1AssertR(pred, code, value, msg)\
	if(pred) {\
		code\
		exCMEAssertCollectStacktrace();\
		exPanic(msg);\
		return value;\
	}


#define EX_s1AssertF(pred, code, msg, ...)\
	if(pred) {\
		code\
		exCMEAssertCollectStacktrace();\
		exPanicF(msg, __VA_ARGS__);\
	}

#define EX_s1AssertFR(pred, code, value, msg, ...)\
	if(pred) {\
		code\
		exCMEAssertCollectStacktrace();\
		exPanicF(msg, __VA_ARGS__);\
		return value;\
	}
#endif



#endif