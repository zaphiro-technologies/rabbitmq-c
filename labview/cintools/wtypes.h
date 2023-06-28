/* this ALWAYS GENERATED file contains the definitions for the interfaces */
#ifndef __wtypes_h__
#define __wtypes_h__

#ifndef NIDL_EXTERN_C
#ifdef __cplusplus
#define NIDL_EXTERN_C extern "C"
#else // __cplusplus
#define NIDL_EXTERN_C
#endif // __cplusplus
#endif // NIDL_EXTERN_C

#ifndef NIDL_INTERFACE
#if defined(WIN32) || (defined(PHARLAP) && PHARLAP)
#define NIDL_INTERFACE(x) struct __declspec(uuid(x))
#else // WIN32
#define NIDL_INTERFACE(x) struct
#endif // WIN32
#endif // NIDL_INTERFACE
/* Forward Declarations */

/* Header files for imported files */

/* Declarations */

#if defined(_WIN32) || defined(WIN32) || defined(__WIN32__) || defined(NI_DSC_WIN32)

#error "You should not be including this file on Windows!!!"

#else // defined(_WIN32) || defined(WIN32) || defined(__WIN32__) || defined(NI_DSC_WIN32)

#if defined(__OBJC__)
#include <objc/objc.h>
#endif
#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif // !FALSE
#ifndef _BYTE_DEFINED
#define _BYTE_DEFINED
typedef unsigned char BYTE;

#endif // !_BYTE_DEFINED
#ifndef _WORD_DEFINED
#define _WORD_DEFINED
typedef unsigned short WORD;

#endif // !_WORD_DEFINED
#ifndef _UINT_DEFINED
#define _UINT_DEFINED
typedef unsigned int UINT;

#endif // _UINT_DEFINED
#ifndef _INT_DEFINED
#define _INT_DEFINED
typedef int INT;

#endif // _INT_DEFINED
#if defined(NI_DSC_UNIX_VXWORKS) || defined(VXWORKS_PPC)
#ifndef _BOOL_DEFINED
#define _BOOL_DEFINED
typedef int BOOL;

#endif // _BOOL_DEFINED
#else
#if !defined(_BOOL_DEFINED) && !defined(__OBJC__)
#define _BOOL_DEFINED
#if __GNUC__ && __x86_64__
typedef int BOOL;
#else
typedef long BOOL;

#endif // gnuc-64
#endif // _BOOL_DEFINED
#endif // defined(NI_DSC_UNIX_VXWORKS) || defined(VXWORKS_PPC)
#ifndef _LONG_DEFINED
#define _LONG_DEFINED
#if __GNUC__ && __x86_64__
typedef int LONG;
#else
typedef long LONG;

#endif // gnu-64
typedef long LONG_PTR;

#endif // !_LONG_DEFINED
#ifndef _DWORD_DEFINED
   // This must define both DWORD and DWORD_PTR to be consistent with other places this is done
   #define _DWORD_DEFINED
   #if __GNUC__ && __x86_64__
      typedef unsigned int DWORD;
   #else
typedef unsigned long DWORD;

#endif // gnuc-64
typedef unsigned long DWORD_PTR;

#endif // !_DWORD_DEFINED
#if defined(NI_DSC_UNIX_VXWORKS) || defined(VXWORKS_PPC)
#define _NI_WINDOWS_HANDLE 1
#endif // defined(NI_DSC_UNIX_VXWORKS) || defined(VXWORKS_PPC)
#ifndef _HANDLE_DEFINED
#define _HANDLE_DEFINED
typedef void* HANDLE;

#endif // _HANDLE_DEFINED
typedef void* HMODULE;

typedef void* HINSTANCE;

typedef void* HRGN;

typedef void* HTASK;

typedef void* HKEY;

typedef void* HGLOBAL;

typedef void* HDESK;

typedef void* HMF;

typedef void* HEMF;

typedef void* HPEN;

typedef void* HRSRC;

typedef void* HSTR;

typedef void* HWINSTA;

typedef void* HKL;

typedef void* HGDIOBJ;

typedef HANDLE HDWP;

typedef WORD CLIPFORMAT;

#ifndef _LPWORD_DEFINED
#define _LPWORD_DEFINED
typedef WORD* LPWORD;

#endif // !_LPWORD_DEFINED
#ifndef _LPDWORD_DEFINED
#define _LPDWORD_DEFINED
typedef DWORD* LPDWORD;

#endif // !_LPDWORD_DEFINED
#ifndef _CHAR_DEFINED
#define _CHAR_DEFINED
typedef char CHAR;

#endif // _CHAR_DEFINED
typedef CHAR* LPSTR;

typedef const CHAR* LPCSTR;

#ifndef _WCHAR_DEFINED
#define _WCHAR_DEFINED
typedef wchar_t WCHAR;

typedef WCHAR TCHAR;

#endif // !_WCHAR_DEFINED
typedef WCHAR* LPWSTR;

typedef TCHAR* LPTSTR;

typedef const WCHAR* LPCWSTR;

typedef const TCHAR* LPCTSTR;

typedef HANDLE* LPHANDLE;

#ifndef _OLECHAR_DEFINED
#define _OLECHAR_DEFINED
typedef WCHAR OLECHAR;

typedef OLECHAR* LPOLESTR;

typedef const OLECHAR* LPCOLESTR;

#define OLESTR(str) L##str
#endif // _OLECHAR_DEFINED
typedef unsigned char UCHAR;

typedef short SHORT;

typedef unsigned short USHORT;

typedef DWORD ULONG;

typedef DWORD_PTR ULONG_PTR;

typedef double DOUBLE;

#ifndef _DWORDLONG_
typedef unsigned long long DWORDLONG;

typedef DWORDLONG* PDWORDLONG;

#endif // !_DWORDLONG_
#ifndef _ULONGLONG_
typedef long long LONGLONG;

typedef unsigned long long ULONGLONG;

typedef LONGLONG* PLONGLONG;

typedef ULONGLONG* PULONGLONG;

#endif // _ULONGLONG_
typedef union _LARGE_INTEGER {
      struct  {
         DWORD LowPart;
         LONG HighPart;
      } ;
      LONGLONG QuadPart;
} LARGE_INTEGER;

typedef LARGE_INTEGER* PLARGE_INTEGER;

typedef union _ULARGE_INTEGER {
      struct  {
         DWORD LowPart;
         DWORD HighPart;
      } ;
      ULONGLONG QuadPart;
} ULARGE_INTEGER;

#ifndef _FILETIME_
#define _FILETIME_
typedef struct _FILETIME {
   DWORD dwLowDateTime;
   DWORD dwHighDateTime;
} FILETIME;

#endif // !_FILETIME
#ifndef _SYSTEMTIME_
#define _SYSTEMTIME_
typedef struct _SYSTEMTIME {
   WORD wYear;
   WORD wMonth;
   WORD wDayOfWeek;
   WORD wDay;
   WORD wHour;
   WORD wMinute;
   WORD wSecond;
   WORD wMilliseconds;
} SYSTEMTIME;

#endif // !_SYSTEMTIME
#ifndef _NI_HRESULT_DEFINED_
#define _NI_HRESULT_DEFINED_
typedef LONG HRESULT;

typedef LONG SCODE;

#endif // !_NI_HRESULT_DEFINED_
typedef SCODE* PSCODE;

#ifndef GUID_DEFINED
#define GUID_DEFINED
typedef struct _GUID {
   DWORD Data1;
   WORD Data2;
   WORD Data3;
   BYTE Data4[8];
} GUID;

#endif // !GUID_DEFINED
#if !defined( __LPGUID_DEFINED__ )
#define __LPGUID_DEFINED__
typedef GUID* LPGUID;

#endif // !__LPGUID_DEFINED__
#if !defined( __IID_DEFINED__ )
#define __IID_DEFINED__
typedef GUID IID;

typedef IID* LPIID;

#define IID_NULL            GUID_NULL
#define IsEqualIID(riid1, riid2) IsEqualGUID(riid1, riid2)
typedef GUID CLSID;

typedef CLSID* LPCLSID;

#define CLSID_NULL          GUID_NULL
#define IsEqualCLSID(rclsid1, rclsid2) IsEqualGUID(rclsid1, rclsid2)
typedef GUID FMTID;

typedef FMTID* LPFMTID;

#define FMTID_NULL          GUID_NULL
#define IsEqualFMTID(rfmtid1, rfmtid2) IsEqualGUID(rfmtid1, rfmtid2)
#ifndef _REFGUID_DEFINED
#define _REFGUID_DEFINED
#define REFGUID const GUID &
#endif // !_REFGUID_DEFINED
#ifndef _REFIID_DEFINED
#define _REFIID_DEFINED
#define REFIID const IID &
#endif // !_REFIID_DEFINED
#ifndef _REFCLSID_DEFINED
#define _REFCLSID_DEFINED
#define REFCLSID const CLSID &
#endif // !_REFCLSID_DEFINED
#endif // !__IID_DEFINED__
#ifndef _LCID_DEFINED
#define _LCID_DEFINED
typedef DWORD LCID;

#endif // !_LCID_DEFINED
typedef void* HICON;

typedef void* HWND;

#ifndef _HCURSOR_DEFINED
#define _HCURSOR_DEFINED
typedef HICON HCURSOR;

#endif // !_HCURSOR_DEFINED
#if !defined(EXTERN_C)
#if defined(__cplusplus)
#define EXTERN_C extern "C"
#else // __cplusplus
#define EXTERN_C
#endif // __cplusplus
#endif // EXTERN_C
#define WINAPI
#define STDAPICALLTYPE
#define CDECL
#ifndef TYPENAME
#define TYPENAME typename
#endif // TYPENAME
#define STDAPI EXTERN_C HRESULT STDAPICALLTYPE
#ifndef _BSTR_DEFINED
#define _BSTR_DEFINED
typedef OLECHAR* BSTR;

typedef BSTR* LPBSTR;

#endif // _BSTR_DEFINED
/* 0 == FALSE, -1 == TRUE */
typedef short VARIANT_BOOL;

/* ANSI C/C++ reserve bool as keyword */
#define _VARIANT_BOOL    /##/
#define VARIANT_TRUE ((VARIANT_BOOL)0xffff)
#define VARIANT_FALSE ((VARIANT_BOOL)0)
typedef unsigned short VARTYPE;

/*
 * VARENUM usage key,
 *
 * * [V] - may appear in a VARIANT
 * * [T] - may appear in a TYPEDESC
 * * [P] - may appear in an OLE property set
 * * [S] - may appear in a Safe Array
 *
 *
 *  VT_EMPTY            [V]   [P]     nothing
 *  VT_NULL             [V]   [P]     SQL style Null
 *  VT_I2               [V][T][P][S]  2 byte signed int
 *  VT_I4               [V][T][P][S]  4 byte signed int
 *  VT_R4               [V][T][P][S]  4 byte real
 *  VT_R8               [V][T][P][S]  8 byte real
 *  VT_CY               [V][T][P][S]  currency
 *  VT_DATE             [V][T][P][S]  date
 *  VT_BSTR             [V][T][P][S]  OLE Automation string
 *  VT_DISPATCH         [V][T][P][S]  IDispatch *
 *  VT_ERROR            [V][T][P][S]  SCODE
 *  VT_BOOL             [V][T][P][S]  True=-1, False=0
 *  VT_VARIANT          [V][T][P][S]  VARIANT *
 *  VT_UNKNOWN          [V][T]   [S]  IUnknown *
 *  VT_DECIMAL          [V][T]   [S]  16 byte fixed point
 *  VT_RECORD           [V]   [P][S]  user defined type
 *  VT_I1               [V][T][P][s]  signed char
 *  VT_UI1              [V][T][P][S]  unsigned char
 *  VT_UI2              [V][T][P][S]  unsigned short
 *  VT_UI4              [V][T][P][S]  unsigned short
 *  VT_I8                  [T][P]     signed 64-bit int
 *  VT_UI8                 [T][P]     unsigned 64-bit int
 *  VT_INT              [V][T][P][S]  signed machine int
 *  VT_UINT             [V][T]   [S]  unsigned machine int
 *  VT_VOID                [T]        C style void
 *  VT_HRESULT             [T]        Standard return type
 *  VT_PTR                 [T]        pointer type
 *  VT_SAFEARRAY           [T]        (use VT_ARRAY in VARIANT)
 *  VT_CARRAY              [T]        C style array
 *  VT_USERDEFINED         [T]        user defined type
 *  VT_LPSTR               [T][P]     null terminated string
 *  VT_LPWSTR              [T][P]     wide null terminated string
 *  VT_FILETIME               [P]     FILETIME
 *  VT_BLOB                   [P]     Length prefixed bytes
 *  VT_STREAM                 [P]     Name of the stream follows
 *  VT_STORAGE                [P]     Name of the storage follows
 *  VT_STREAMED_OBJECT        [P]     Stream contains an object
 *  VT_STORED_OBJECT          [P]     Storage contains an object
 *  VT_BLOB_OBJECT            [P]     Blob contains an object 
 *  VT_CF                     [P]     Clipboard format
 *  VT_CLSID                  [P]     A Class ID
 *  VT_VECTOR                 [P]     simple counted array
 *  VT_ARRAY            [V]           SAFEARRAY*
 *  VT_BYREF            [V]           void* for local use
 *  VT_BSTR_BLOB                      Reserved for system use
 */
typedef enum VARENUM {
   VT_EMPTY = 0,
   VT_NULL = 1,
   VT_I2 = 2,
   VT_I4 = 3,
   VT_R4 = 4,
   VT_R8 = 5,
   VT_CY = 6,
   VT_DATE = 7,
   VT_BSTR = 8,
   VT_DISPATCH = 9,
   VT_ERROR = 10,
   VT_BOOL = 11,
   VT_VARIANT = 12,
   VT_UNKNOWN = 13,
   VT_DECIMAL = 14,
   VT_I1 = 16,
   VT_UI1 = 17,
   VT_UI2 = 18,
   VT_UI4 = 19,
   VT_I8 = 20,
   VT_UI8 = 21,
   VT_INT = 22,
   VT_UINT = 23,
   VT_VOID = 24,
   VT_HRESULT = 25,
   VT_PTR = 26,
   VT_SAFEARRAY = 27,
   VT_CARRAY = 28,
   VT_USERDEFINED = 29,
   VT_LPSTR = 30,
   VT_LPWSTR = 31,
   VT_RECORD = 36,
   VT_FILETIME = 64,
   VT_BLOB = 65,
   VT_STREAM = 66,
   VT_STORAGE = 67,
   VT_STREAMED_OBJECT = 68,
   VT_STORED_OBJECT = 69,
   VT_BLOB_OBJECT = 70,
   VT_CF = 71,
   VT_CLSID = 72,
   VT_BSTR_BLOB = 4095,
   VT_VECTOR = 4096,
   VT_ARRAY = 8192,
   VT_BYREF = 16384,
   VT_RESERVED = 32768,
   VT_ILLEGAL = 65535,
   VT_ILLEGALMASKED = 4095,
   VT_TYPEMASK = 4095,
} VARENUM;

#endif // defined(_WIN32) || defined(WIN32) || defined(__WIN32__) || defined(NI_DSC_WIN32)
#ifdef __cplusplus
 extern "C++" {
     namespace _wtypes {
         template <bool> struct StaticAssertionFailure;
         template <> struct StaticAssertionFailure<true>{};
         template<int> struct StaticAssertTest{};
     }
     #define _WTYPES_STATIC_ASSERT(condition) \
         typedef ::_wtypes::StaticAssertTest<sizeof(::_wtypes::StaticAssertionFailure<(condition)>)> \
             _WTYPES_STATIC_ASSERT_JOIN(_wtypes_StaticAssertTypedef_,__LINE__)
     #define _WTYPES_STATIC_ASSERT_JOIN( X, Y ) _WTYPES_DO_STATIC_ASSERT_JOIN( X, Y )
     #define _WTYPES_DO_STATIC_ASSERT_JOIN( X, Y ) X##Y
     #define _BITS__WTYPES_  /8

#if !defined(__OBJC__)
     _WTYPES_STATIC_ASSERT(            sizeof(BOOL) == 32 _BITS__WTYPES_);
#endif

     _WTYPES_STATIC_ASSERT(           sizeof(DWORD) == 32 _BITS__WTYPES_);
     _WTYPES_STATIC_ASSERT(        sizeof(LONGLONG) == 64 _BITS__WTYPES_);
     _WTYPES_STATIC_ASSERT(       sizeof(ULONGLONG) == 64 _BITS__WTYPES_);
     _WTYPES_STATIC_ASSERT(   sizeof(LARGE_INTEGER) == 64 _BITS__WTYPES_);
     _WTYPES_STATIC_ASSERT(  sizeof(ULARGE_INTEGER) == 64 _BITS__WTYPES_);
     #undef _BITS__WTYPES_
     #undef _WTYPES_DO_STATIC_ASSERT_JOIN
     #undef _WTYPES_STATIC_ASSERT_JOIN
     #undef _WTYPES_STATIC_ASSERT
 }
#endif // __cplusplus


#endif /* __wtypes_h__ */
