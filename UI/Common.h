#ifndef __COMMON_H__
#define __COMMON_H__

#include <wtf/Assertions.h>

#define LOG_CHANNEL_PREFIX Log
extern WTFLogChannel LogUILogPrint;

#define UI_LOG_VERBOSE(...) LOG_VERBOSE(UILogPrint,  __VA_ARGS__)

#endif /*__COMMON_H__*/


