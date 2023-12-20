#ifndef _EXILE_CRITICAL_SHARED_H_
#define _EXILE_CRITICAL_SHARED_H_

#define EXILE_PRIVATE

#include <exile/core/critical.h>
#include <exile/core/module.h>
#include <exile/core/assert.h>

extern exNativeModule mdl;

typedef void(*PFNexCriticalInit)();

#endif