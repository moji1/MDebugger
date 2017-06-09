/*
 * LTTngUMLRTEvent.h
 *
 *  Created on: Dec 3, 2016
 *      Author: mojtababagherzadeh
 */

/*#ifndef LTTNGUMLRTEVENT_H_
#define LTTNGUMLRTEVENT_H_
#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER umlrtevent_provider
#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./LTTngUMLRTEvent.h"
#if !defined(LTTNGUMLRTEVENT_H_) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define LTTNGUMLRTEVENT_H_
#include <lttng/tracepoint.h>
TRACEPOINT_EVENT(
	umlrtevent_provider,
	umlrtevent_tracepoint,
    TP_ARGS(
        char*, event_str_arg
    ),
    TP_FIELDS(
        ctf_string(event_str_field, event_str_arg)
    )
)
#include <lttng/tracepoint-event.h>
#endif /* _HELLO_TP_H */


