//
//  SceneKitTypes.h
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>
#import <GLKit/GLKMathTypes.h>


/*! @header SceneKitTypes
 @abstract Various types and utility functions used throughout SceneKit
 */

#define SCN_ENABLE_METAL (!TARGET_IPHONE_SIMULATOR)

#if SCN_ENABLE_METAL
#import <Metal/Metal.h>
#endif

typedef struct SCNVector3 {
    float x, y, z;
} SCNVector3;

typedef struct SCNVector4 {
    float x, y, z, w;
} SCNVector4;

typedef struct SCNMatrix4 {
    float m11, m12, m13, m14;
    float m21, m22, m23, m24;
    float m31, m32, m33, m34;
    float m41, m42, m43, m44;
} SCNMatrix4;

typedef SCNVector4 SCNQuaternion;

SCN_EXTERN const SCNMatrix4 SCNMatrix4Identity NS_AVAILABLE(10_10, 8_0);
SCN_EXTERN const SCNVector3 SCNVector3Zero NS_AVAILABLE(10_10, 8_0);
SCN_EXTERN const SCNVector4 SCNVector4Zero NS_AVAILABLE(10_10, 8_0);

/*! Returns true if 'a' is exactly equal to 'b'. */
SCN_EXTERN bool SCNVector3EqualToVector3 (SCNVector3 a, SCNVector3 b);

/*! Returns true if 'a' is exactly equal to 'b'. */
SCN_EXTERN bool SCNVector4EqualToVector4 (SCNVector4 a, SCNVector4 b);

/*! Returns an initialized SCNVector3 */
NS_INLINE SCNVector3 SCNVector3Make(float x, float y, float z) {
    SCNVector3 v = {x, y, z};
    return v;
}

/*! Returns an initialized SCNVector4 */
NS_INLINE SCNVector4 SCNVector4Make(float x, float y, float z, float w) {
    SCNVector4 v = {x, y, z, w};
    return v;
}

NS_INLINE SCNMatrix4 SCNMatrix4MakeTranslation(float x, float y, float z) {
    SCNMatrix4 m = SCNMatrix4Identity;
    m.m41 = x;
    m.m42 = y;
    m.m43 = z;
    return m;
}

NS_INLINE SCNMatrix4 SCNMatrix4MakeScale(float sx, float sy, float sz) {
    SCNMatrix4 m = SCNMatrix4Identity;
    m.m11 = sx;
    m.m22 = sy;
    m.m33 = sz;
    return m;
}

NS_INLINE SCNMatrix4 SCNMatrix4Translate(SCNMatrix4 mat, float x, float y, float z) {
    mat.m41 += x;
    mat.m42 += y;
    mat.m43 += z;
    return mat;
}

SCN_EXTERN SCNMatrix4 SCNMatrix4MakeRotation(float angle, float x, float y, float z) NS_AVAILABLE(10_10, 8_0);
SCN_EXTERN SCNMatrix4 SCNMatrix4Scale(SCNMatrix4 mat, float x, float y, float z) NS_AVAILABLE(10_10, 8_0);
SCN_EXTERN SCNMatrix4 SCNMatrix4Rotate(SCNMatrix4 mat, float angle, float x, float y, float z) NS_AVAILABLE(10_10, 8_0);

SCN_EXTERN SCNMatrix4 SCNMatrix4Invert(SCNMatrix4 mat) NS_AVAILABLE(10_10, 8_0);
SCN_EXTERN SCNMatrix4 SCNMatrix4Mult(SCNMatrix4 matA, SCNMatrix4 matB) NS_AVAILABLE(10_10, 8_0);
SCN_EXTERN bool       SCNMatrix4IsIdentity(SCNMatrix4 mat) NS_AVAILABLE(10_10, 8_0);
SCN_EXTERN bool       SCNMatrix4EqualToMatrix4(SCNMatrix4 matA, SCNMatrix4 matB) NS_AVAILABLE(10_10, 8_0);

/* GLKit bridge */
NS_INLINE SCNVector3 SCNVector3FromGLKVector3(GLKVector3 vector) {
    SCNVector3 v = (SCNVector3){vector.v[0], vector.v[1], vector.v[2]};
    return v;
}

NS_INLINE GLKVector3 SCNVector3ToGLKVector3(SCNVector3 vector) {
    GLKVector3 v = {{(float)vector.x, (float)vector.y, (float)vector.z}};
    return v;
}

NS_INLINE SCNVector4 SCNVector4FromGLKVector4(GLKVector4 vector) {
    SCNVector4 v = (SCNVector4){vector.v[0], vector.v[1], vector.v[2], vector.v[3]};
    return v;
}

NS_INLINE GLKVector4 SCNVector4ToGLKVector4(SCNVector4 vector) {
    GLKVector4 v = {{vector.x, vector.y, vector.z, vector.w}};
    return v;
}

SCN_EXTERN GLKMatrix4 SCNMatrix4ToGLKMatrix4(SCNMatrix4 mat) NS_AVAILABLE(10_10, 8_0);
SCN_EXTERN SCNMatrix4 SCNMatrix4FromGLKMatrix4(GLKMatrix4 mat) NS_AVAILABLE(10_10, 8_0);
    
//SIMD bridge
#import <SceneKit/SceneKit_simd.h>
    
#ifdef __OBJC__
    
NS_ASSUME_NONNULL_BEGIN

/*! @category NSValue(SceneKitAdditions)
 @abstract Adds methods to wrap vectors in NSValue objects.
 */

@interface NSValue (SceneKitAdditions)

+ (NSValue *)valueWithSCNVector3:(SCNVector3)v;
+ (NSValue *)valueWithSCNVector4:(SCNVector4)v;
+ (NSValue *)valueWithSCNMatrix4:(SCNMatrix4)v NS_AVAILABLE(10_10, 8_0);

@property(nonatomic, readonly) SCNVector3 SCNVector3Value;
@property(nonatomic, readonly) SCNVector4 SCNVector4Value;
@property(nonatomic, readonly) SCNMatrix4 SCNMatrix4Value NS_AVAILABLE(10_10, 8_0);

@end

//domain for errors from SceneKit API.
SCN_EXTERN NSString * const SCNErrorDomain;

// NSError codes in SCNErrorDomain.
enum {
	SCNProgramCompilationError = 1
};

NS_ASSUME_NONNULL_END
    
#endif /* __OBJC__ */
