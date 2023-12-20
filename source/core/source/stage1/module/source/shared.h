#define EXILE_PRIVATE
#include <exile/core/module.h>
#include <exile/core/API.h>

#define LRETURN_IF_FAILED(pred, code)\
	if(pred == EX_ERROR)\
	{\
		code\
		return EX_ERROR;\
	}