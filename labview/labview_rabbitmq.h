#ifndef LABVIEW_RABBITMQ_H
#define LABVIEW_RABBITMQ_H

#if defined(__GNUC__) && __GNUC__ >= 4
#define LABVIEW_PUBLIC_FUNCTION __attribute__((visibility("default")))
#define LABVIEW_PUBLIC_VARIABLE __attribute__((visibility("default"))) extern
#define LABVIEW_CALL
#else
#define LABVIEW_PUBLIC_FUNCTION
#define LABVIEW_PUBLIC_VARIABLE extern
#define LABVIEW_CALL
#endif

#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1)
#define LABVIEW_DEPRECATED(function) function __attribute__((__deprecated__))
#elif defined(_MSC_VER)
#define LABVIEW_DEPRECATED(function) __declspec(deprecated) function
#else
#define LABVIEW_DEPRECATED(function)
#endif

#endif /* LABVIEW_RABBITMQ_H */
