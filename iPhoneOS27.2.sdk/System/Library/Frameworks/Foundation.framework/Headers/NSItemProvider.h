/*	NSItemProvider.h
        Copyright (c) 2013-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSArray.h>


#if __OBJC2__


NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class NSItemProvider, NSProgress;


/// Specifications that control which categories of processes can see an item.
typedef NS_ENUM(NSInteger, NSItemProviderRepresentationVisibility) {
    /// All processes can see this representation.
    NSItemProviderRepresentationVisibilityAll = 0,                                  // All processes can see this representation
    /// Only processes from the same dev team can see this representation.
    NSItemProviderRepresentationVisibilityTeam                                      // Only processes from the same dev team can see this representation
    API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0)) API_UNAVAILABLE(macos) = 1,
    /// Only processes from the same group can see this representation.
    NSItemProviderRepresentationVisibilityGroup                                     // Only processes from the same group can see this representation
    API_AVAILABLE(macos(10.13)) API_UNAVAILABLE(ios, watchos, tvos) = 2 ,
    /// Only the originator's process can see this representation.
    NSItemProviderRepresentationVisibilityOwnProcess = 3,                           // Ony the originator's process can see this representation
} API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));


// The default behavior is to copy files.
/// Data-access specifications that declare how to handle items.
typedef NS_OPTIONS(NSInteger, NSItemProviderFileOptions) {
    /// Allow the file to be opened in place.
    NSItemProviderFileOptionOpenInPlace = 1,
} API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));


/// A protocol that allows a class to export its data to a variety of binary representations.
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
@protocol NSItemProviderWriting <NSObject>

/// An array of type identifiers that the class can provide data for.
@property (class, NS_NONATOMIC_IOSONLY, readonly, copy) NSArray<NSString *> *writableTypeIdentifiersForItemProvider;

@optional

/// An array of type identifiers that this particular instance can provide data for.
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSArray<NSString *> *writableTypeIdentifiersForItemProvider;

/// Returns the visibility specification for the representation of the given type identifier.
+ (NSItemProviderRepresentationVisibility)itemProviderVisibilityForRepresentationWithTypeIdentifier:(NSString *)typeIdentifier;

/// Returns the visibility specification for the representation of the given type identifier for this instance.
- (NSItemProviderRepresentationVisibility)itemProviderVisibilityForRepresentationWithTypeIdentifier:(NSString *)typeIdentifier;

@required

/// Loads the data representation for the given type identifier.
- (nullable NSProgress *)loadDataWithTypeIdentifier:(NSString *)typeIdentifier // One of writableTypeIdentifiersForItemProvider
                   forItemProviderCompletionHandler:(void (NS_SWIFT_SENDABLE ^)(NSData * _Nullable data, NSError * _Nullable error))completionHandler;

@end


/// A protocol that allows a class to be constructed from a variety of binary representations.
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
@protocol NSItemProviderReading <NSObject>

/// An array of type identifiers that the class can read.
@property (class, NS_NONATOMIC_IOSONLY, readonly, copy) NSArray<NSString *> *readableTypeIdentifiersForItemProvider;

/// Creates a new instance of the class from the given data and type identifier.
+ (nullable instancetype)objectWithItemProviderData:(NSData *)data
                                     typeIdentifier:(NSString *)typeIdentifier
                                              error:(NSError **)outError;

@end


/// A block that receives the item provider's data.
///
/// Use this block to receive data from a call to the `loadItemForTypeIdentifier:options:completionHandler:` method. This block takes the following parameters:
///
/// - `item`: The item to be loaded. When specifying your block, set the type of this parameter to the specific data type you want. For example, when requesting text data, you might set the type to `NSString` or `NSAttributedString`. The item provider attempts to coerce the data to the class you specify.
/// - `error`: A pointer to an error object for receiving information about any problems that occurred when loading the data.
typedef void (NS_SWIFT_SENDABLE ^NSItemProviderCompletionHandler)(__nullable __kindof id <NSSecureCoding> item, NSError * __null_unspecified error);
/// A block that loads the item provider's data and coerces it to the specified type.
///
/// Use this block when registering a type-specific coercion handler with the `registerItemForTypeIdentifier:loadHandler:` method. The parameters for this block are as follows:
///
/// - `completionHandler`: The completion handler to call with the resulting data. For information about this block, see `NSItemProviderCompletionHandler`.
/// - `expectedValueClass`: The expected class of the item being loaded. Convert the item provider's data to this type and pass the resulting object as the first parameter of the `completionHandler` block.
/// - `options`: A dictionary with options for how to provide the requested item. For example, the dictionary may contain the pixel dimensions of a requested image.
///
/// When a client calls the `loadItemForTypeIdentifier:options:completionHandler:` method and requests the appropriate type, the item provider executes your block. In your implementation, create an object of the expected type and execute the block in the `completionHandler` parameter, passing the newly created object as the first parameter of that block. If there is an error, pass `nil` for the object and provide an appropriate `NSError` object explaining what happened.
typedef void (NS_SWIFT_SENDABLE ^NSItemProviderLoadHandler)(__null_unspecified NSItemProviderCompletionHandler completionHandler, __null_unspecified Class expectedValueClass, NSDictionary * __null_unspecified options);


/// An item provider for conveying data or a file between processes during drag-and-drop or copy-and-paste activities, or from a host app to an app extension.
///
/// Starting in iOS 11, item providers play a central role in drag and drop, and in copy and paste. They continue to play a role with app extensions.
///
/// The system uses an internal queue when calling the completion blocks for the `NSItemProvider` class. When using an item provider with drag and drop, ensure that UI updates take place on the main queue as follows:
///
/// ```swift
/// DispatchQueue.main.async {
/// // Work that impacts the user interface.
/// }
/// ```
///
///
///
///
/// ### App extension support
///
/// An app extension typically encounters item providers when examining the ``NSExtensionItem/attachments`` property of an ``NSExtensionItem`` object. During that examination, the extension can use the ``hasItemConformingToTypeIdentifier(_:)`` method to look for data that it recognizes. Item providers use <doc://com.apple.documentation/documentation/uniformtypeidentifiers> values to identify the data they contain. After finding a type of data that your extension can use, it calls the ``loadItem(forTypeIdentifier:options:completionHandler:)`` method to load the actual data, which is delivered to the provided completion handler.
///
/// You can create item providers to vend data to another process. An extension that modifies an original data item can create a new `NSItemProvider` object to send back to the host app. When creating data items, you specify your data object and the type of that object. You can optionally use the ``previewImageHandler`` property to generate a preview image for your data.
///
/// A single item provider may use custom blocks to provide its data in many different formats. When configuring an item provider, use the ``registerItem(forTypeIdentifier:loadHandler:)`` method to register your blocks and the formats each one supports. When a client requests data in a particular format, the item provider executes the corresponding block, which is then responsible for coercing the data to the appropriate type and returning it to the client.
API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
@interface NSItemProvider : NSObject <NSCopying>

#pragma mark - Binary interface


#pragma mark Provider


/// Creates an empty item provider to which you can later register a data or file representation.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

// Register higher-fidelity types first, followed by progressively lower-fidelity ones. This ordering helps consumers get the best representation they can handle.

/// Registers a data-backed representation for an item, specifying item visibility and a load handler.
///
/// Register higher-fidelity types first, followed by progressively lower-fidelity ones.
/// This ordering helps consumers get the best representation they can handle.
- (void)registerDataRepresentationForTypeIdentifier:(NSString *)typeIdentifier
                                         visibility:(NSItemProviderRepresentationVisibility)visibility
                                        loadHandler:(NSProgress * _Nullable (NS_SWIFT_SENDABLE ^)(void (NS_SWIFT_SENDABLE ^completionHandler)(NSData * _Nullable data, NSError * _Nullable error)))loadHandler API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// Registers a file-backed representation for an item, specifying file options, item visibility, and a load handler.
///
/// If a destination app must access the represented file using a file coordinator, set the `coordinated` parameter
/// in the load handler block to `YES`.
///
/// To offer a representation backed by a file provider, return an `NSURL` object that points to your app's file
/// provider's container. The file provider extension is then invoked to retrieve the file when requested.
///
/// To offer a representation backed by a file to open in place, set the `fileOptions` parameter to
/// `NSItemProviderFileOptionOpenInPlace`; in addition, return an `NSURL` object that points to your app's
/// file provider's container. Open-in-place support requires that the file provider is visible in the Files app.
///
/// If `NSItemProviderFileOptionOpenInPlace` is not provided, the file will be copied before the load handler returns.
- (void)registerFileRepresentationForTypeIdentifier:(NSString *)typeIdentifier
                                        fileOptions:(NSItemProviderFileOptions)fileOptions
                                         visibility:(NSItemProviderRepresentationVisibility)visibility
                                        loadHandler:(NSProgress * _Nullable (NS_SWIFT_SENDABLE ^)(void (NS_SWIFT_SENDABLE ^completionHandler)(NSURL * _Nullable url, BOOL coordinated, NSError * _Nullable error)))loadHandler API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));


#pragma mark Consumer


/// The array of type identifiers for the item provider, in the same order they were registered.
@property (copy, readonly, atomic) NSArray<NSString *> *registeredTypeIdentifiers;

/// Returns an array with a subset of type identifiers for the item provider, according to the specified file options,
/// in the same order they were registered.
///
/// To access the array of all registered UTIs, pass the value `0` in the `fileOptions` parameter.
///
/// - Parameter fileOptions: The file options to filter by.
/// - Returns: An array of type identifier strings.
- (NSArray<NSString *> *)registeredTypeIdentifiersWithFileOptions:(NSItemProviderFileOptions)fileOptions API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// Returns a Boolean value indicating whether an item provider contains a data representation conforming to
/// a specified universal type identifier, with a file options value of zero.
///
/// - Parameter typeIdentifier: A string that represents the desired UTI.
/// - Returns: `YES` if the item provider has at least one item that conforms to the supplied type identifier.
- (BOOL)hasItemConformingToTypeIdentifier:(NSString *)typeIdentifier;

/// Returns a Boolean value indicating whether an item provider contains a data representation conforming to
/// a specified universal type identifier and to specified open-in-place behavior.
///
/// To check all registered UTIs for type conformance, pass the value `0` in the `fileOptions` parameter.
- (BOOL)hasRepresentationConformingToTypeIdentifier:(NSString *)typeIdentifier
                                        fileOptions:(NSItemProviderFileOptions)fileOptions API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// Asynchronously copies the provided, typed data into an `NSData` object, returning a progress object.
///
/// If the source app provides a folder URL, the `NSData` object contains a zip archive with the folder
/// as its top-level entry.
- (NSProgress *)loadDataRepresentationForTypeIdentifier:(NSString *)typeIdentifier
                                      completionHandler:(void(NS_SWIFT_SENDABLE ^)(NSData * _Nullable data, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// Asynchronously writes a copy of the provided, typed data to a temporary file, returning a progress object.
///
/// This method writes a copy of the file's data to a temporary file, which the system deletes when the
/// completion handler returns. Your program should copy or move the file within the completion handler.
- (NSProgress *)loadFileRepresentationForTypeIdentifier:(NSString *)typeIdentifier
                                      completionHandler:(void(NS_SWIFT_SENDABLE ^)(NSURL * _Nullable url, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// Asynchronously opens a file in place, if possible, returning a progress object.
///
/// The system sets the `isInPlace` parameter to `YES` if the system successfully opened the file in place,
/// or `NO` if it made a local copy. In either case, you must access the returned URL using an `NSFileCoordinator`.
///
/// If the system created a local copy of a file, it will be automatically deleted after your file coordinator
/// relinquishes its read access to the file.
- (NSProgress *)loadInPlaceFileRepresentationForTypeIdentifier:(NSString *)typeIdentifier
                                             completionHandler:(void (NS_SWIFT_SENDABLE ^)(NSURL * _Nullable url, BOOL isInPlace, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));


#pragma mark Metadata


/// The suggested name for the item.
@property (atomic, copy, nullable) NSString *suggestedName API_AVAILABLE(macos(10.14), ios(11.0)) API_UNAVAILABLE(watchos, tvos);


#pragma mark - NSItemProviderReading and Writing interface


/// Creates a new item provider, employing a specified object's type identifiers to specify the data representations eligible for the provider to load.
///
/// - Parameters:
///   - object: An object containing the data you want to provide.
- (instancetype)initWithObject:(id<NSItemProviderWriting>)object API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// Adds representations of a specified object to an item provider, based on the object's implementation of
/// the `NSItemProviderWriting` protocol, adhering to a visibility specification.
///
/// If a representation for a given UTI is already registered, it is preserved (duplicate representations are ignored).
- (void)registerObject:(id<NSItemProviderWriting>)object visibility:(NSItemProviderRepresentationVisibility)visibility API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// Lazily adds representations of a specified object class to an item provider, based on the object's implementation
/// of the `NSItemProviderWriting` protocol, adhering to a visibility specification.
- (void)registerObjectOfClass:(Class<NSItemProviderWriting>)aClass
                   visibility:(NSItemProviderRepresentationVisibility)visibility
                  loadHandler:(NSProgress * _Nullable (NS_SWIFT_SENDABLE ^)(void (NS_SWIFT_SENDABLE ^completionHandler)(__kindof id<NSItemProviderWriting> _Nullable object, NSError * _Nullable error)))loadHandler API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// Returns a Boolean value indicating whether an item provider can load objects of a specified class.
///
/// - Parameter aClass: The object class for comparison.
/// - Returns: `YES` if the item provider can load objects of the class.
- (BOOL)canLoadObjectOfClass:(Class<NSItemProviderReading>)aClass API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// Asynchronously loads an object of a specified class to an item provider, returning a progress object.
- (NSProgress *)loadObjectOfClass:(Class<NSItemProviderReading>)aClass
                completionHandler:(void (NS_SWIFT_SENDABLE ^)(__kindof id<NSItemProviderReading> _Nullable object, NSError * _Nullable error))completionHandler API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));


#pragma mark - Coercing interface

// These methods allow you to assign NSSecureCoding-compliant objects to certain UTIs, and retrieve either the original object, or a coerced variant
// based on the following rules.
//
// If the object is retrieved using loadItemForTypeIdentifier:options:completionHandler, and the completion block signature contains a paramater of
// the same class as the initial object (or a superclass), the original object is returned.
//
// If the completion block signature contains a parameter that is not the same class as `item`, some coercion may occur:
//    Original class       Requested class          Coercion action
//    -------------------  -----------------------  -------------------
//    NSURL                NSData                   The contents of the URL is read and returned as NSData
//    NSData               NSImage/UIImage          An NSImage (macOS) or UIImage (iOS) is constructed from the data
//    NSURL                UIImage                  A UIImage is constructed from the file at the URL (iOS)
//    NSImage              NSData                   A TIFF representation of the image is returned
//
// When providing or consuming data using this interface, a file may be opened in-place depending on the NSExtension context in which this object is used.
//
// If the item is retrieved using the binary interface described above, the original object will be retrieved and coerced to NSData.
//
// Items registered using the binary interface will appear as NSData with respect to the coercing interface.


#pragma mark Provider


/// Creates an item provider with an object, according to the item provider type coercion policy.
///
/// Use this method to initialize an item provider for objects in your app. The item provider registers your object
/// with the specified type. Subsequent requests for that same type return the specified `item`.
///
/// - Parameters:
///   - item: An object containing the data you want to provide. You may specify `nil` for this parameter and register items and types later.
///   - typeIdentifier: A string that represents the UTI of the item. If `item` is not `nil`, this parameter must not be `nil`.
/// - Returns: An item provider for the specified item.
- (instancetype)initWithItem:(nullable id<NSSecureCoding>)item typeIdentifier:(nullable NSString *)typeIdentifier NS_DESIGNATED_INITIALIZER API_DEPRECATED("Use initWithObject: instead.", macos(10.10,27.0), ios(8.0,27.0), watchos(2.0,27.0), tvos(9.0,27.0), visionos(1.0,27.0));

/// Provides data-backed content from an existing file.
///
/// The system uses the URL's filename extension to select an appropriate universal type identifier. If the system can't
/// determine a specific universal type identifier based on the filename extension, it assigns the `public.data`
/// universal type identifier for the file.
///
/// - Parameters:
///   - fileURL: The URL of the file to use for the item provider's data. The item provider uses the filename extension to determine the universal type identifier for the associated data.
/// - Returns: An item provider for the specified file, or `nil` if an error occurs.
- (nullable instancetype)initWithContentsOfURL:(null_unspecified NSURL *)fileURL;

/// Lazily registers an item, according to the item provider type coercion policy.
///
/// Use this method to register blocks that can take the item provider's file or data object and convert it to
/// a specific data format. Your `loadHandler` block is executed when a client passes the same `typeIdentifier`
/// string to the `loadItemForTypeIdentifier:options:completionHandler:` method.
///
/// @deprecated Use `registerObjectOfClass:visibility:loadHandler:` instead.
///
/// - Parameters:
///   - typeIdentifier: A string that represents the desired UTI.
///   - loadHandler: A block capable of returning the data item as the specified type.
- (void)registerItemForTypeIdentifier:(NSString *)typeIdentifier loadHandler:(NSItemProviderLoadHandler)loadHandler API_DEPRECATED("Use registerObjectOfClass:visibility:loadHandler: instead.", macos(10.10,27.0), ios(8.0,27.0), watchos(2.0,27.0), tvos(9.0,27.0), visionos(1.0,27.0));


#pragma mark Consumer


// Loads the best matching item for a type identifier. The returned object depends on the class specified for the completion handler's `item` parameter.
// See the table above for coercion rules.
- (void)loadItemForTypeIdentifier:(NSString *)typeIdentifier options:(nullable NSDictionary *)options completionHandler:(nullable NSItemProviderCompletionHandler)completionHandler API_DEPRECATED("Use loadObjectOfClass:completionHandler: instead.", macos(10.10,27.0), ios(8.0,27.0), watchos(2.0,27.0), tvos(9.0,27.0), visionos(1.0,27.0));

@end


// Common keys for the item provider options dictionary.
/// A key provided to the options dictionary to indicate a preferred image size.
///
/// The value is an `NSValue` of `CGSize` or `NSSize`, specifying image size in pixels.
FOUNDATION_EXTERN NSString * const NSItemProviderPreferredImageSizeKey API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));


// Some uses of NSItemProvider support the use of optional preview images.
@interface NSItemProvider(NSPreviewSupport)

/// The custom preview image handler block for the item provider.
///
/// In your image handler block, return an ``NSURL`` object that specifies a file, or return an ``NSData`` object.
@property (nullable, copy, atomic) NSItemProviderLoadHandler previewImageHandler API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// Loads the preview image for the item that the item provider represents.
///
/// To handle image preview yourself, provide a completion handler block that returns an `NSData` or `NSURL` object,
/// or an instance of a platform-specific image class (`UIImage` or `NSImage`).
///
/// This method supports implicit type coercion for the item parameter of the completion block.
///
/// - Parameters:
///   - options: A dictionary of keys and values that provide information about the item, such as the size of an image.
///   - completionHandler: A completion handler block to execute with the results.
- (void)loadPreviewImageWithOptions:(null_unspecified NSDictionary *)options completionHandler:(null_unspecified NSItemProviderCompletionHandler)completionHandler API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

@end


// Keys used in property list items received from or sent to JavaScript code

/// A key whose value is an item of type `kUTTypePropertyList`. The item contains an `NSDictionary` that contains the object returned by the JavaScript code to its completion function.
FOUNDATION_EXTERN NSString * _Null_unspecified const NSExtensionJavaScriptPreprocessingResultsKey API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// A key whose value is an item of type `kUTTypePropertyList`. The item contains an `NSDictionary` that contains the arguments to be passed to a JavaScript finalize method.
FOUNDATION_EXTERN NSString * _Null_unspecified const NSExtensionJavaScriptFinalizeArgumentKey API_AVAILABLE(ios(8.0), watchos(2.0), tvos(9.0)) API_UNAVAILABLE(macos);


#pragma mark - Errors


/// The error domain associated with the item provider.
FOUNDATION_EXTERN NSString * const NSItemProviderErrorDomain API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

/// The error codes that describe problems with consuming data from an item provider.
typedef NS_ENUM(NSInteger, NSItemProviderErrorCode) {
    /// An unknown error occurred.
    NSItemProviderUnknownError                                      = -1,
    /// The item is unavailable.
    NSItemProviderItemUnavailableError                              = -1000,
    /// The item had an unexpected value class.
    NSItemProviderUnexpectedValueClassError                         = -1100,
    /// The coercion of the item to the requested type was unavailable.
    NSItemProviderUnavailableCoercionError API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0)) = -1200
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

NS_HEADER_AUDIT_END(nullability, sendability)


#else // __OBJC2__


@protocol NSItemProviderReading <NSObject>
@end

@protocol NSItemProviderWriting <NSObject>
@end


#endif
