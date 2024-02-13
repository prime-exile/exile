#include <exile.window/window.h>
#include <exile/core/API.h>

exPFN_WindowCreate exWindowCreate = 0;
exPFN_WindowClose exWindowClose = 0;
exPFN_WindowShouldClose exWindowShouldClose = 0;
exPFN_WindowUpdate exWindowUpdate = 0;