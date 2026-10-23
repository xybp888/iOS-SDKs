//
//  CKDatabaseOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKOperation.h>

@class CKDatabase;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The abstract base class for operations that act upon databases in CloudKit.
///
/// Database operations typically involve fetching and saving records and other database objects, as well as executing queries on the contents of the database. Use this class's ``database`` property to tell the operation which database to use when you execute it. Don't subclass this class or create instances of it. Instead, create instances of one of its concrete subclasses.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKDatabaseOperation : CKOperation

/// The database that the operation uses.
///
/// For operations that you execute in a custom queue, use this property to specify the target database. Setting the database also sets the corresponding container, which it inherits from ``CKOperation``. If this property's value is `nil`, the operation targets the user's private database.
///
/// The default value is `nil`.
@property (nullable, strong, nonatomic) CKDatabase *database;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
