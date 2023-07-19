/* this ALWAYS GENERATED file contains the definitions for the interfaces */
#ifndef __ILVTypeInterface_h__
#define __ILVTypeInterface_h__

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

#ifndef __ILVTypeDescriptor_FWD_DEFINED__
#define __ILVTypeDescriptor_FWD_DEFINED__
typedef struct ILVTypeDescriptor ILVTypeDescriptor;
#endif  /* __ILVTypeDescriptor_FWD_DEFINED__ */

#ifndef __ILVBooleanTypeDescriptor_FWD_DEFINED__
#define __ILVBooleanTypeDescriptor_FWD_DEFINED__
typedef struct ILVBooleanTypeDescriptor ILVBooleanTypeDescriptor;
#endif  /* __ILVBooleanTypeDescriptor_FWD_DEFINED__ */

#ifndef __ILVNumericTypeDescriptor_FWD_DEFINED__
#define __ILVNumericTypeDescriptor_FWD_DEFINED__
typedef struct ILVNumericTypeDescriptor ILVNumericTypeDescriptor;
#endif  /* __ILVNumericTypeDescriptor_FWD_DEFINED__ */

#ifndef __ILVArrayTypeDescriptor_FWD_DEFINED__
#define __ILVArrayTypeDescriptor_FWD_DEFINED__
typedef struct ILVArrayTypeDescriptor ILVArrayTypeDescriptor;
#endif  /* __ILVArrayTypeDescriptor_FWD_DEFINED__ */

#ifndef __ILVStringTypeDescriptor_FWD_DEFINED__
#define __ILVStringTypeDescriptor_FWD_DEFINED__
typedef struct ILVStringTypeDescriptor ILVStringTypeDescriptor;
#endif  /* __ILVStringTypeDescriptor_FWD_DEFINED__ */

#ifndef __ILVClusterTypeDescriptor_FWD_DEFINED__
#define __ILVClusterTypeDescriptor_FWD_DEFINED__
typedef struct ILVClusterTypeDescriptor ILVClusterTypeDescriptor;
#endif  /* __ILVClusterTypeDescriptor_FWD_DEFINED__ */


/* Header files for imported files */

#include "unknwn.h"

/* Declarations */

// ==================================================================
// NI CONFIDENTIAL													
// (c) Copyright 2006-2008 by National Instruments Corp.				
// All rights reserved.												
//																	
// @file		ILVTypeInterface.idl									
// @brief	Interface definitions for LabVIEW types.				
//			The files ILVTypeInterface_i.c and ILVTypeInterface.h	
//			are generated using this ILVTypeInterface.idl.			
// ==================================================================
#include "extcode.h"
#ifndef _fundtypes_H
typedef char int8_t;

typedef short int int16_t;

typedef int int32_t;

typedef long long int64_t;

typedef unsigned char uint8_t;

typedef unsigned short int uint16_t;

typedef unsigned int uint32_t;

typedef unsigned long long uint64_t;

typedef char int_least8_t;

typedef short int int_least16_t;

typedef int int_least32_t;

typedef long long int_least64_t;

typedef unsigned char uint_least8_t;

typedef unsigned short int uint_least16_t;

typedef unsigned int uint_least32_t;

typedef unsigned long long uint_least64_t;

typedef char int_fast8_t;

typedef int int_fast16_t;

typedef int int_fast32_t;

typedef long long int_fast64_t;

typedef unsigned char uint_fast8_t;

typedef unsigned int uint_fast16_t;

typedef unsigned int uint_fast32_t;

typedef unsigned long long uint_fast64_t;

typedef int intptr_t;

typedef unsigned int uintptr_t;

typedef long long intmax_t;

typedef unsigned long long uintmax_t;

typedef char int8;

typedef unsigned char uInt8;

typedef uInt8 uChar;

typedef short int int16;

typedef unsigned short int uInt16;

typedef int int32;

typedef unsigned int uInt32;

typedef float float32;

typedef double float64;

typedef struct  {
   int32 mlo;
   int32 mhi;
   int16 e;
} floatExt;

typedef long long int64;

typedef unsigned long long uInt64;

typedef struct  {
   float32 re;
   float32 im;
} cmplx64;

typedef struct  {
   float64 re;
   float64 im;
} cmplx128;

typedef struct  {
   floatExt re;
   floatExt im;
} cmplxExt;

typedef int32 Bool32;

typedef int32 HRESULT;

typedef int32 SCODE;

typedef int ptrdiff_t;

typedef unsigned int size_t;

typedef int32 MgErr;

#endif // ifndef _fundtypes
/* Generated header for interface ILVTypeDescriptor */

typedef enum  {
   kCompareDefaultCheck = 0,
   kCompareAllNameCheck = 1,
   kCompareSubNameCheck = 2,
   kCompareNoTypeDefCheck = 8,
} CompareWithOptionMasks;
NIDL_EXTERN_C const IID IID_ILVTypeDescriptor;

/* {09a66b9c-3683-4f5c-b4ce-b7e428fc3914} */
NIDL_INTERFACE("09a66b9c-3683-4f5c-b4ce-b7e428fc3914") ILVTypeDescriptor : public IUnknown
{
public:
   virtual MgErr NIDL_STDMETHODCALLTYPE Compare(
      ILVTypeDescriptor* type,
      int32* retVal) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE CompareWithOptions(
      ILVTypeDescriptor* type,
      int32 compareOptions,
      int32* retVal) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE GetTypeCode(
      int16* typeCode) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE GetInternalLVTypeDescriptor(
      void** ppInternalTypeDesc) = 0;
} ;

/* Generated header for interface ILVBooleanTypeDescriptor */

NIDL_EXTERN_C const IID IID_ILVBooleanTypeDescriptor;

/* {234324fe-6e30-4cca-98f0-155793f2c682} */
NIDL_INTERFACE("234324fe-6e30-4cca-98f0-155793f2c682") ILVBooleanTypeDescriptor : public ILVTypeDescriptor
{
public:
} ;

/* Generated header for interface ILVNumericTypeDescriptor */

typedef enum  {
   kNonNumericInterfaceCode = 0,
   kInt8InterfaceCode = 1,
   kInt16InterfaceCode = 2,
   kInt32InterfaceCode = 3,
   kInt64InterfaceCode = 4,
   kUInt8InterfaceCode = 5,
   kUInt16InterfaceCode = 6,
   kUInt32InterfaceCode = 7,
   kUInt64InterfaceCode = 8,
   kFloat32InterfaceCode = 9,
   kFloat64InterfaceCode = 10,
   kFloatExtInterfaceCode = 11,
   kComplex64InterfaceCode = 12,
   kComplex128InterfaceCode = 13,
   kComplexExtInterfaceCode = 14,
} NumericInterfaceCode;
NIDL_EXTERN_C const IID IID_ILVNumericTypeDescriptor;

/* {da09ad59-f1b8-46b3-aba0-4b48c98a8afb} */
NIDL_INTERFACE("da09ad59-f1b8-46b3-aba0-4b48c98a8afb") ILVNumericTypeDescriptor : public ILVTypeDescriptor
{
public:
   virtual MgErr NIDL_STDMETHODCALLTYPE GetNumericCode(
      NumericInterfaceCode* numericCode) = 0;
   virtual Bool32 NIDL_STDMETHODCALLTYPE IsEnum(void) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE GetEnumNumElements(
      uInt32* numElements) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE GetEnumElementName(
      uInt32 position,
      const uChar** elementName,
      size_t* elementNameLength) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE GetEnumElementNameILVString(
      uInt32 position,
      ILVString** elementName) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE GetEnumElementNumber(
      const uChar* elementName,
      size_t elementNameLength,
      uInt32* position) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE GetEnumElementNumberILVString(
      ILVString* elementName,
      uInt32* position) = 0;
} ;

/* Generated header for interface ILVArrayTypeDescriptor */

NIDL_EXTERN_C const IID IID_ILVArrayTypeDescriptor;

/* {c2d6f738-f5b3-4db1-a1fa-5672fdeaf60f} */
NIDL_INTERFACE("c2d6f738-f5b3-4db1-a1fa-5672fdeaf60f") ILVArrayTypeDescriptor : public ILVTypeDescriptor
{
public:
   virtual MgErr NIDL_STDMETHODCALLTYPE GetElementTypeDescriptor(
      ILVTypeDescriptor** elementTypeDescriptor) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE GetNumDimensions(
      uInt32* numDimensions) = 0;
} ;

/* Generated header for interface ILVStringTypeDescriptor */

NIDL_EXTERN_C const IID IID_ILVStringTypeDescriptor;

/* {7b4ef86e-e843-41f4-a4d8-88a2f2372365} */
NIDL_INTERFACE("7b4ef86e-e843-41f4-a4d8-88a2f2372365") ILVStringTypeDescriptor : public ILVTypeDescriptor
{
public:
   virtual Bool32 NIDL_STDMETHODCALLTYPE IsVariableSize(void) = 0;
   virtual Bool32 NIDL_STDMETHODCALLTYPE IsBoundedSize(void) = 0;
   virtual Bool32 NIDL_STDMETHODCALLTYPE IsFixedSize(void) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE GetCapacity(
      size_t* size) = 0;
} ;

/* Generated header for interface ILVClusterTypeDescriptor */

NIDL_EXTERN_C const IID IID_ILVClusterTypeDescriptor;

/* {fc873d27-ad8e-45da-bd26-e3f42c3d8157} */
NIDL_INTERFACE("fc873d27-ad8e-45da-bd26-e3f42c3d8157") ILVClusterTypeDescriptor : public ILVTypeDescriptor
{
public:
   virtual MgErr NIDL_STDMETHODCALLTYPE GetNumElements(
      uInt32* numElements) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE GetNumElementsRecursive(
      uInt32* numElements) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE GetElementTypeDescriptor(
      uInt32 position,
      ILVTypeDescriptor** elementTypeDescriptor) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE GetElementName(
      uInt32 position,
      ILVString** name) = 0;
   virtual MgErr NIDL_STDMETHODCALLTYPE GetElementIndex(
      ILVString* name,
      int32* index) = 0;
} ;



#endif /* __ILVTypeInterface_h__ */
