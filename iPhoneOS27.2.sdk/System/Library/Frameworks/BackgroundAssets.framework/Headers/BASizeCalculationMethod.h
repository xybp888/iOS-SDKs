//
//  BASizeCalculationMethod.h
//  Background Assets
//
//  Created by Gabriel Jacoby-Cooper on 8/7/26.
//

#import <Foundation/Foundation.h>

/// Methods for calculating a file’s size.
typedef NS_ENUM(NSInteger, BASizeCalculationMethod) {
    
    /// A calculation method that counts the number of bytes in a file.
    ///
    /// The result of a “logical” size calculation for a file may be greater or less than the actual number of bytes that a file takes up on disk due to file-system features like alignment or compression.
    BASizeCalculationMethodLogical,
    
    /// A calculation method that counts the number of bytes that the file system allocated for a file.
    ///
    /// The result of an “allocated” size calculation for a file roughly corresponds to the number of bytes that would newly be made available if the file were removed.
    BASizeCalculationMethodAllocated
    
} API_AVAILABLE(ios(27.2), macos(27.2), tvos(27.2), visionos(27.2)) API_UNAVAILABLE(watchos) NS_SWIFT_NAME(SizeCalculationMethod);
