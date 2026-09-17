//
//  MPSFunction.h
//  MPSFunctions
//
//  Created on 3/23/26.
//  Copyright © 2017 Apple. All rights reserved.

#ifndef MPSFunction_h
#define MPSFunction_h

#include <MPSFunctions/MPSFunctionTypes.h>

MPSF_AVAILABILITY_v1
@interface MPSFunction : NSObject <NSCopying, NSSecureCoding>

/*! @abstract part of the NSSecureCoding */
+(BOOL) supportsSecureCoding;

/*! @abstract This base class is virtual / incomplete. Use the appropriate -init function listed in the sub class*/
-(nonnull instancetype) init NS_UNAVAILABLE;

/*! @abstract   Called by NSCoder to decode MPSKernels
 *  @discussion This standard method doesn't allow for control over which device the object
 *              targets. By default this will be the Metal system default device. If you want
 *              another device, use the MPSKeyedUnarchiver or other <MPSDeviceProvider>
 *              to decode the function.*/
-(nullable instancetype) initWithCoder:(NSCoder * __nonnull)aDecoder;

/*!
 *  @abstract   Make a copy of this MPSFunction for a new device
 *  @discussion -copyWithZone: will call this API to make a copy of the
 *              MPSKernel on the same device.  This interface may also be
 *              called directly to make a copy of the MPSFunction on a new
 *              device.
 *  @param      zone        The NSZone in which to allocate the object
 *  @param      device      The device for the new MPSKernel. If nil, then use
 *                          self.device.
 *  @result     a pointer to a copy of this MPSKernel. This will fail, returning
 *              nil if the device is not supported. Devices must be
 *              MTLFeatureSet_iOS_GPUFamily2_v1 or later.
 */
- (nonnull instancetype) copyWithZone:(nullable NSZone *)zone
                               device:(nullable id <MTLDevice>) device;


/*! @abstract The name of the Metal Shading Language function built by this object */
@property (nonatomic, readonly, retain)  NSString * __nonnull      name;


/*! @abstract The device where the Metal Shading Language function will run */
@property (nonatomic, readonly, retain)  __nonnull id <MTLDevice>  device;


/*! A MTLFunction that you can link into your shader */
@property (nonatomic, readonly, retain, nullable) id <MTLFunction> function;

/*! The error produced when attempting to build the function */
@property (nonatomic, readonly, retain, nullable) NSError * error;


/*! @abstract Get a source level representation of the function prototype
 *  @discussion  If your application is building its shaders from source at run time, this string will
 *               declare the appropriate function prototypes for the conversion routine appropriate
 *               to the version of MetalHDR you are currently running.
 *
 *               Note: It is expected that most applications will not use this interface because they
 *               are building kernels offline from a .metallib. Such applications should simply:
 *
 *                  #include <MPSFunctions/MPSFunctions.h>
 *
 *               in their .metal file, and declare any functions produced by this object using
 *
 *                  MPSFUNCTION_DECLARE_COLOR_CONVERSION( _functionName );
 *
 *               or similar, depending on the type of the function created. The _functionName should
 *               match the name passed to the object -init method.
 *               */
-(NSString * __nonnull) functionPrototype;


@end


#endif /* MPSFunction_h */
