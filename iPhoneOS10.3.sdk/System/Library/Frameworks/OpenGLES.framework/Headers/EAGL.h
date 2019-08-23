/*
    Copyright:  (c) 2006-2013 Apple Inc. All rights reserved.
*/

#ifndef _EAGL_H_
#define _EAGL_H_

#include <Foundation/Foundation.h>

#ifdef __cplusplus
#define EAGL_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define EAGL_EXTERN extern __attribute__((visibility ("default")))
#endif

#define EAGL_EXTERN_CLASS __attribute__((visibility("default")))

/************************************************************************/
/* EAGL API Version                                                     */
/************************************************************************/
#define EAGL_MAJOR_VERSION   1
#define EAGL_MINOR_VERSION   0


/************************************************************************/
/* EAGL Enumerated values                                               */
/************************************************************************/

/* EAGL rendering API */
typedef NS_ENUM(NSUInteger, EAGLRenderingAPI)
{
	kEAGLRenderingAPIOpenGLES1 = 1,
	kEAGLRenderingAPIOpenGLES2 = 2,
	kEAGLRenderingAPIOpenGLES3 = 3,
};


/************************************************************************/
/* EAGL Functions                                                       */
/************************************************************************/

EAGL_EXTERN void EAGLGetVersion(unsigned int* major, unsigned int* minor);

/************************************************************************/
/* EAGL Sharegroup                                                      */
/************************************************************************/

EAGL_EXTERN_CLASS
@interface EAGLSharegroup : NSObject
{
@package
	struct _EAGLSharegroupPrivate *_private;
}

@property (copy, nonatomic) NSString* debugLabel NS_AVAILABLE_IOS(6_0);

@end

/************************************************************************/
/* EAGL Context                                                         */
/************************************************************************/

EAGL_EXTERN_CLASS
@interface EAGLContext : NSObject
{
@public
	struct _EAGLContextPrivate *_private;
}

- (instancetype) init NS_UNAVAILABLE;
- (instancetype) initWithAPI:(EAGLRenderingAPI) api;
- (instancetype) initWithAPI:(EAGLRenderingAPI) api sharegroup:(EAGLSharegroup*) sharegroup NS_DESIGNATED_INITIALIZER;

+ (BOOL)            setCurrentContext:(EAGLContext*) context;
+ (EAGLContext*)    currentContext;

@property (readonly) EAGLRenderingAPI   API;
@property (readonly) EAGLSharegroup*    sharegroup;

@property (copy, nonatomic) NSString* debugLabel NS_AVAILABLE_IOS(6_0);
@property (getter=isMultiThreaded, nonatomic) BOOL multiThreaded NS_AVAILABLE_IOS(7_1);
@end


#endif /* _EAGL_H_ */

