/* this ALWAYS GENERATED file contains the definitions for the interfaces */
#ifndef __unknwn_h__
#define __unknwn_h__

#if defined(_WIN32) || defined(WIN32) || defined(__WIN32__) || defined(NI_DSC_WIN32)
#define NIDL_STDMETHODCALLTYPE __stdcall
#else // WIN32
#define NIDL_STDMETHODCALLTYPE
#endif // WIN32

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

#ifndef __IUnknown_FWD_DEFINED__
#define __IUnknown_FWD_DEFINED__
typedef struct IUnknown IUnknown;
#endif  /* __IUnknown_FWD_DEFINED__ */

#ifndef __IClassFactory_FWD_DEFINED__
#define __IClassFactory_FWD_DEFINED__
typedef struct IClassFactory IClassFactory;
#endif  /* __IClassFactory_FWD_DEFINED__ */


/* Header files for imported files */

#include "wtypes.h"

/* Declarations */

#if defined(_WIN32) || defined(WIN32) || defined(__WIN32__) || defined(NI_DSC_WIN32)

#error "You should not be including this file on Windows!!!"

#else // defined(_WIN32) || defined(WIN32) || defined(__WIN32__) || defined(NI_DSC_WIN32)

/* Generated header for interface IUnknown */

typedef IUnknown* LPUNKNOWN;
NIDL_EXTERN_C const IID IID_IUnknown;

/* {00000000-0000-0000-c000-000000000046} */
NIDL_INTERFACE("00000000-0000-0000-c000-000000000046") IUnknown
{
public:
   virtual HRESULT NIDL_STDMETHODCALLTYPE QueryInterface(
      REFIID riid,
      void** ppvObject) = 0;
   virtual ULONG NIDL_STDMETHODCALLTYPE AddRef(void) = 0;
   virtual ULONG NIDL_STDMETHODCALLTYPE Release(void) = 0;
} ;

/* Generated header for interface IClassFactory */

typedef IClassFactory* LPCLASSFACTORY;
NIDL_EXTERN_C const IID IID_IClassFactory;

/* {00000001-0000-0000-c000-000000000046} */
NIDL_INTERFACE("00000001-0000-0000-c000-000000000046") IClassFactory : public IUnknown
{
public:
   virtual HRESULT NIDL_STDMETHODCALLTYPE CreateInstance(
      IUnknown* pUnkOuter,
      REFIID riid,
      void** ppvObject) = 0;
   virtual HRESULT NIDL_STDMETHODCALLTYPE RemoteCreateInstance(
      REFIID riid,
      IUnknown** ppvObject) = 0;
   virtual HRESULT NIDL_STDMETHODCALLTYPE LockServer(
      BOOL fLock) = 0;
   virtual HRESULT NIDL_STDMETHODCALLTYPE RemoteLockServer(
      BOOL fLock) = 0;
} ;

#endif // defined(_WIN32) || defined(WIN32) || defined(__WIN32__) || defined(NI_DSC_WIN32)


#endif /* __unknwn_h__ */
