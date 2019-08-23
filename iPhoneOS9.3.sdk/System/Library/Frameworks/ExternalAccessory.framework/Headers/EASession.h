//
//  EASession.h
//  ExternalAccessory
//
//  Copyright (c) 2008-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class EAAccessory;

EA_EXTERN_CLASS_AVAILABLE(3_0) @interface EASession : NSObject {
@private
    EAAccessory *_accessory;
    uint32_t _sessionID;
    NSString *_protocolString;
    NSInputStream *_inputStream;
    NSOutputStream *_outputStream;
    BOOL _openCompleted;
}

- (instancetype)initWithAccessory:(EAAccessory *)accessory forProtocol:(NSString *)protocolString __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

@property (nonatomic, readonly) EAAccessory *accessory __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
@property (nonatomic, readonly) NSString *protocolString __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
@property (nonatomic, readonly, nullable) NSInputStream *inputStream __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
@property (nonatomic, readonly, nullable) NSOutputStream *outputStream __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
@end

NS_ASSUME_NONNULL_END
