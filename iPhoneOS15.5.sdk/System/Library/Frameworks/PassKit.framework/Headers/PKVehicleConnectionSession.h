//
//  PKVehicleConnectionSession.h
//  PKVehicleConnectionSession
//
//  Copyright © 2021 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class PKSecureElementPass;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(15.4))
typedef NS_ENUM(NSInteger, PKVehicleConnectionErrorCode) {
    PKVehicleConnectionErrorCodeUnknown = 0,
    PKVehicleConnectionErrorCodeSessionUnableToStart,
    PKVehicleConnectionErrorCodeSessionNotActive
};

API_AVAILABLE(ios(15.4))
typedef NS_ENUM(NSInteger, PKVehicleConnectionSessionConnectionState) {
    PKVehicleConnectionSessionConnectionStateDisconnected = 0,
    PKVehicleConnectionSessionConnectionStateConnected,
    PKVehicleConnectionSessionConnectionStateConnecting,
    PKVehicleConnectionSessionConnectionStateFailedToConnect
};

API_AVAILABLE(ios(15.4))
@protocol PKVehicleConnectionDelegate <NSObject>

- (void)sessionDidChangeConnectionState:(PKVehicleConnectionSessionConnectionState)newState;

// Called when the session receives the message from the destination.
- (void)sessionDidReceiveData:(NSData *)data;

@end

API_AVAILABLE(ios(15.4))
@interface PKVehicleConnectionSession : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;


@property (nonatomic, weak, readonly) id<PKVehicleConnectionDelegate>delegate;
@property (nonatomic, assign, readonly) PKVehicleConnectionSessionConnectionState connectionStatus;

// Factory method that returns in the completion handler a session in the PKVehicleConnectionSessionConnectionStateConnecting state for the given passUniqueIdentifier
+ (void)sessionForPass:(PKSecureElementPass *)pass
              delegate:(id<PKVehicleConnectionDelegate>)delegate
            completion:(void(^)(PKVehicleConnectionSession * _Nullable session, NSError * _Nullable error))completion;

// Send data to the car
- (BOOL)sendData:(NSData *)message error:(NSError **)error;

// Invalidate this session. Session will also invalidate on dealloc
- (void)invalidate;

@end

NS_ASSUME_NONNULL_END
