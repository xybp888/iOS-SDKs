//
//  BEHostingHandle.h
//  BrowserEngineKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <BrowserEngineKit/BEMacros.h>
#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN


API_AVAILABLE(ios(17.4))
API_UNAVAILABLE(macos, watchos, tvos, visionos)
BROWSERENGINE_EXPORT
BROWSERENGINE_FINAL
NS_SWIFT_SENDABLE
NS_SWIFT_NAME(LayerHierarchyHandle)
@interface BELayerHierarchyHandle : NSObject <NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

#if BROWSERENGINEKIT_HAS_LIBXPC
+ (nullable BELayerHierarchyHandle *)handleWithXPCRepresentation:(nullable xpc_object_t)xpcRepresentation error:(NSError **)error NS_SWIFT_NAME(init(xpcRepresentation:));
- (xpc_object_t)createXPCRepresentation NS_SWIFT_NAME(createXPCRepresentation());
#endif

@end


NS_ASSUME_NONNULL_END
