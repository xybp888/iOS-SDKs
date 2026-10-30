/*
 *  CMLogItem.h
 *  CoreMotion
 *
 *  Copyright (c) 2010 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>

#import <CoreMotion/CMAvailability.h>

NS_ASSUME_NONNULL_BEGIN

COREMOTION_EXPORT API_AVAILABLE(ios(4.0))
@interface CMLogItem : NSObject <NSSecureCoding, NSCopying>
{
@private
	id _internalLogItem;
}

/*
 *  timestamp
 *  
 *  Discussion:
 *    Mach absolute time at which the item is valid.
 *
 */
@property(readonly, nonatomic) NSTimeInterval timestamp;

@end

NS_ASSUME_NONNULL_END
