//
//  NSFileProviderModifyItemOptions.h
//
//  Copyright © 2019-2022 Apple Inc. All rights reserved.
//

#import <FileProvider/NSFileProviderDefines.h>

typedef NS_OPTIONS(NSUInteger, NSFileProviderModifyItemOptions) {
    /**
     We're moving the item to a location where it may refer to an item that already exists. This may happen
     when two directories are being merged together. When this happens some items may be merged to the
     same directory and we end up in a situation where the merged contains may also exist.

     This is similar to NSFileProviderCreateItemMayAlreadyExist
     */
    NSFileProviderModifyItemMayAlreadyExist = 1 << 0,
} FILEPROVIDER_API_AVAILABILITY_V3_IOS;
