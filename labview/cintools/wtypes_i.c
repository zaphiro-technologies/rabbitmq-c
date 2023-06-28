/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


#ifdef __cplusplus
extern "C"{
#endif


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
#if __GNUC__ && __x86_64__
	unsigned int x;
#else
	unsigned long x;
#endif // gcc-64
	unsigned short s1;
	unsigned short s2;
	unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED


#ifdef __cplusplus
}
#endif
