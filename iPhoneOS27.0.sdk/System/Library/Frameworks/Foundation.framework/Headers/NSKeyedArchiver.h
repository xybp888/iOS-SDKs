/*	NSKeyedArchiver.h
	Copyright (c) 2001-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSCoder.h>
#import <Foundation/NSPropertyList.h>
#import <Foundation/NSException.h>
#if TARGET_OS_OSX
#import <Foundation/NSGeometry.h>
#endif


@class NSArray<ObjectType>, NSMutableData, NSData, NSString;
@protocol NSKeyedArchiverDelegate, NSKeyedUnarchiverDelegate;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Name of an exception that occurs when there is a problem during archive creation.
FOUNDATION_EXPORT NSExceptionName const NSInvalidArchiveOperationException;
/// Name of an exception that occurs when there is a problem during unarchive.
FOUNDATION_EXPORT NSExceptionName const NSInvalidUnarchiveOperationException;
/// The key used for the root object in the hierarchy of encoded objects.
///
/// Archives created using ``NSKeyedArchiver/archivedData(withRootObject:requiringSecureCoding:)`` use this key for the root object. The ``NSKeyedUnarchiver`` class method ``NSKeyedUnarchiver/unarchivedObject(ofClass:from:)`` will look for this root key as well. You can also use it as the key for the root object in your own archives.
FOUNDATION_EXPORT NSString * const NSKeyedArchiveRootObjectKey API_AVAILABLE(macos(10.9), ios(7.0), watchos(2.0), tvos(9.0));

/// An encoder that stores an object's data to an archive referenced by keys.
///
/// ``NSKeyedArchiver``, a concrete subclass of ``NSCoder``, provides a way to encode objects (and scalar values) into an architecture-independent format suitable for storage in a file. When you archive a set of objects, the archiver writes the class information and instance variables for each object to the archive. The companion class ``NSKeyedUnarchiver`` decodes the data in an archive and creates a set of objects equivalent to the original set.
///
/// A keyed archive differs from a non-keyed archive in that all the objects and values encoded into the archive have names, or keys. When decoding a non-keyed archive, the decoder must decode values in the same order the original encoder used. When decoding a keyed archive, the decoder requests values by name, meaning it can decode values out of sequence or not at all. Keyed archives, therefore, provide better support for forward and backward compatibility.
///
/// The keys given to encoded values must be unique only within the scope of the currently-encoding object. A keyed archive is hierarchical, so the keys used by object A to encode its instance variables don't conflict with the keys used by object B. This is true even if A and B are instances of the same class. Within a single object, however, the keys used by a subclass can conflict with keys used in its superclasses.
///
/// An ``NSArchiver`` object can write the archive data to a file or to a mutable-data object (an instance of ``NSMutableData``) that you provide.
@interface NSKeyedArchiver : NSCoder

/**
 Initializes the receiver for encoding an archive, optionally disabling secure coding.

 If \c NSSecureCoding cannot be used, \c requiresSecureCoding may be turned off here; for improved security, however, \c requiresSecureCoding should be left enabled whenever possible. \c requiresSecureCoding ensures that all encoded objects conform to \c NSSecureCoding, preventing the possibility of encoding objects which cannot be decoded later.

 To produce archives whose structure matches those previously encoded using \c +archivedDataWithRootObject, encode the top-level object in your archive for the \c NSKeyedArchiveRootObjectKey.
 */
- (instancetype)initRequiringSecureCoding:(BOOL)requiresSecureCoding API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/**
 Returns an \c NSData object containing the encoded form of the object graph whose root object is given, optionally disabling secure coding.

 If \c NSSecureCoding cannot be used, \c requiresSecureCoding may be turned off here; for improved security, however, \c requiresSecureCoding should be left enabled whenever possible. \c requiresSecureCoding ensures that all encoded objects conform to \c NSSecureCoding, preventing the possibility of encoding objects which cannot be decoded later.

 If the object graph cannot be encoded, returns \c nil and sets the \c error out parameter.
 */
+ (nullable NSData *)archivedDataWithRootObject:(id)object requiringSecureCoding:(BOOL)requiresSecureCoding error:(NSError **)error API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// Initialize the archiver with empty data, ready for writing.
- (instancetype)init API_DEPRECATED("Use -initRequiringSecureCoding: instead", macosx(10.12,10.14), ios(10.0,12.0), watchos(3.0,5.0), tvos(10.0,12.0));
/// Initializes an archiver to encode data into a given a mutable-data object.
///
/// @DeprecationSummary {
///     Use ``NSKeyedArchiver/initRequiringSecureCoding:`` instead.
/// }
///
/// When you finish encoding data, you must invoke ``finishEncoding`` at which point `data` is filled. The format of the receiver is `NSPropertyListBinaryFormat_v1_0`.
- (instancetype)initForWritingWithMutableData:(NSMutableData *)data API_DEPRECATED("Use -initRequiringSecureCoding: instead", macosx(10.2,10.14), ios(2.0,12.0), watchos(2.0,5.0), tvos(9.0,12.0));

/// Returns a data object that contains the encoded form of the object graph formed by the given root object.
///
/// @DeprecationSummary {
///     Use ``NSKeyedArchiver/archivedDataWithRootObject:requiringSecureCoding:error:`` instead.
/// }
///
/// The format of the archive is `NSPropertyListBinaryFormat_v1_0`.
+ (NSData *)archivedDataWithRootObject:(id)rootObject API_DEPRECATED("Use +archivedDataWithRootObject:requiringSecureCoding:error: instead", macosx(10.2,10.14), ios(2.0,12.0), watchos(2.0,5.0), tvos(9.0,12.0));
#if !0
/// Archives an object graph rooted at a given object to a file at a given path.
///
/// @DeprecationSummary {
///     Use ``NSKeyedArchiver/archivedDataWithRootObject:requiringSecureCoding:error:`` and `-writeToURL:options:error:` instead.
/// }
///
/// This method archives the graph formed by the root object to a data object, then atomically writes it to the given path. The format of the archive is `NSPropertyListBinaryFormat_v1_0`.
+ (BOOL)archiveRootObject:(id)rootObject toFile:(NSString *)path API_DEPRECATED("Use +archivedDataWithRootObject:requiringSecureCoding:error: and -writeToURL:options:error: instead", macosx(10.2,10.14), ios(2.0,12.0), watchos(2.0,5.0), tvos(9.0,12.0));
#endif

/// The archiver's delegate.
@property (nullable, assign) id <NSKeyedArchiverDelegate> delegate;

/// The format in which the receiver encodes its data.
///
/// The available formats are XML and binary.
@property NSPropertyListFormat outputFormat;

/// If encoding has not yet finished, then invoking this property will call finishEncoding and return the data. If you initialized the keyed archiver with a specific mutable data instance, then it will be returned from this property after finishEncoding is called.
@property (readonly, strong) NSData *encodedData API_AVAILABLE(macosx(10.12), ios(10.0), watchos(3.0), tvos(10.0));

/// Instructs the receiver to construct the final data stream.
///
/// No more values can be encoded after this method is called. You must call this method when finished.
- (void)finishEncoding;

/// Sets a global translation mapping to encode instances of a given class with the provided name, rather than their real name.
///
/// When encoding, an archiver consults its own translation map before using the class' translation map.
+ (void)setClassName:(nullable NSString *)codedName forClass:(Class)cls;
/// Sets a mapping for this archiver to encode instances of a given class with the provided name, rather than their real name.
///
/// When encoding, the receiver's translation map overrides any translation that may also be present in the class's map.
- (void)setClassName:(nullable NSString *)codedName forClass:(Class)cls;

/// Returns the class name with which the archiver class encodes instances of a given class.
///
/// Returns `nil` if `NSKeyedArchiver` does not have a translation mapping for `cls`.
+ (nullable NSString *)classNameForClass:(Class)cls;
/// Returns the class name with which this archiver encodes instances of a given class.
///
/// Returns `nil` if the receiver does not have a translation mapping for `cls`. The class's separate translation map is not searched.
- (nullable NSString *)classNameForClass:(Class)cls;

/// Encodes a given object and associates it with a given key.
- (void)encodeObject:(nullable id)object forKey:(NSString *)key;
/// Encodes a reference to a given object and associates it with a key only if it has been unconditionally encoded elsewhere in the archive.
- (void)encodeConditionalObject:(nullable id)object forKey:(NSString *)key;
/// Encodes a given Boolean value and associates it with a key.
- (void)encodeBool:(BOOL)value forKey:(NSString *)key;
/// Encodes a given `int` value and associates it with a key.
- (void)encodeInt:(int)value forKey:(NSString *)key;
/// Encodes a given 32-bit integer value and associates it with a key.
- (void)encodeInt32:(int32_t)value forKey:(NSString *)key;
/// Encodes a given 64-bit integer value and associates it with a key.
- (void)encodeInt64:(int64_t)value forKey:(NSString *)key;
/// Encodes a given `float` value and associates it with a key.
- (void)encodeFloat:(float)value forKey:(NSString *)key;
/// Encodes a given `double` value and associates it with a key.
- (void)encodeDouble:(double)value forKey:(NSString *)key;
/// Encodes a given number of bytes from a given C array of bytes and associates them with a key.
- (void)encodeBytes:(nullable const uint8_t *)bytes length:(NSUInteger)length forKey:(NSString *)key;

/// Indicates whether the archiver requires all archived classes to resist object substitution attacks.
///
/// If you set the archiver to require secure coding, it throws an exception if you attempt to archive a class which doesn't conform to `NSSecureCoding`.
///
/// Note that the getter is on the superclass, `NSCoder`. See `NSCoder` for more information about secure coding. Enabling secure coding doesn't change the output format of the archive.
@property (readwrite) BOOL requiresSecureCoding API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));

@end

/// A decoder that restores data from an archive referenced by keys.
///
/// ``NSKeyedUnarchiver`` is a concrete subclass of ``NSCoder`` that defines methods for decoding a set of named objects (and scalar values) from a keyed archive. The ``NSKeyedArchiver`` class produces archives that this class can decode.
///
/// The archiver creates keyed archive as a hierarchy of objects. The archiver treats each object as a namespace into which it can encode other objects. This means that an unarchiver can only decode objects encoded within the immediate scope of their parent object. Objects encoded elsewhere in the hierarchy — whether higher than, lower than, or parallel to this particular object — aren't accessible. In this way, the keys used by a particular object to encode its instance variables need to be unique only within the scope of that object.
///
/// If you invoke one of the `decode`-prefixed methods of this class using a key that does not exist in the archive, the return value indicates failure. This value varies by decoded type. For example, if a key does not exist in an archive, ``decodeBool(forKey:)`` returns <doc://com.apple.documentation/documentation/swift/false>, ``decodeIntForKey:`` returns `0`, and ``decodeObject(forKey:)`` returns `nil`.
///
/// ``NSKeyedUnarchiver`` supports limited type coercion for numeric types. You can use any of the integer decode methods to decode a value encoded as any type of integer, whether a standard `Int` or an explicit 32-bit or 64-bit integer. Likewise, you can use the `Float`- or `Double`-returning decode methods to handle value encoded as a `Float` or `Double`. If an encoded value is too large to fit within the coerced type, the decoding method throws a ``NSExceptionName/rangeException``. Further, when trying to coerce a value to an incompatible type — for example decoding an `Int` as a `Float` — the decoding method throws an ``NSExceptionName/invalidUnarchiveOperationException``.
@interface NSKeyedUnarchiver : NSCoder

/**
 Initializes the receiver for decoding an archive previously encoded by \c NSKeyedUnarchiver.

 Enables \c requiresSecureCoding by default. If \c NSSecureCoding cannot be used, \c requiresSecureCoding may be turned off manually; for improved security, \c requiresSecureCoding should be left enabled whenever possible.

 Sets the unarchiver's \c decodingFailurePolicy to \c NSDecodingFailurePolicySetErrorAndReturn.

 Returns \c nil if the given data is not valid, and sets the \c error out parameter.
 */
- (nullable instancetype)initForReadingFromData:(NSData *)data error:(NSError **)error API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/**
 Decodes the root object of the given class from the given archive, previously encoded by \c NSKeyedArchiver.

 Enables \c requiresSecureCoding and sets the \c decodingFailurePolicy to \c NSDecodingFailurePolicySetErrorAndReturn.

 Returns \c nil if the given data is not valid or cannot be decoded, and sets the \c error out parameter.

 @important Make sure you have adopted \c NSSecureCoding in the types you decode. If any call to a \c decode -prefixed method fails, the default \c decodingFailurePolicy sets the error rather than throwing an exception. In this case, the current and all subsequent decode calls return \c 0 or \c nil.
 */
+ (nullable id)unarchivedObjectOfClass:(Class)cls fromData:(NSData *)data error:(NSError **)error API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0)) NS_REFINED_FOR_SWIFT;

/**
 Decodes the \c NSArray root object from \c data which should be an \c NSArray<cls> containing the given non-collection class (no nested arrays or arrays of dictionaries, etc) from the given archive, previously encoded by \c NSKeyedArchiver.
 
 Enables \c requiresSecureCoding and sets the \c decodingFailurePolicy to \c NSDecodingFailurePolicySetErrorAndReturn.

 Returns \c nil if the given data is not valid or cannot be decoded, and sets the \c error out parameter.
 */
+ (nullable NSArray *)unarchivedArrayOfObjectsOfClass:(Class)cls fromData:(NSData *)data error:(NSError **)error API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) NS_REFINED_FOR_SWIFT;

/**
Decodes the \c NSDictionary root object from \c data which should be an \c NSDictionary<keyCls,objectCls>  with keys of type given in \c keyCls and objects of the given non-collection class \c objectCls (no nested dictionaries or other dictionaries contained in the dictionary, etc) from the given archive, previously encoded by \c NSKeyedArchiver.

Enables \c requiresSecureCoding and sets the \c decodingFailurePolicy to \c NSDecodingFailurePolicySetErrorAndReturn.

Returns \c nil if the given data is not valid or cannot be decoded, and sets the \c error out parameter.
*/
+ (nullable NSDictionary *)unarchivedDictionaryWithKeysOfClass:(Class)keyCls objectsOfClass:(Class)valueCls fromData:(NSData *)data error:(NSError **)error API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) NS_REFINED_FOR_SWIFT;

/**
 Decodes the root object of one of the given classes from the given archive, previously encoded by \c NSKeyedArchiver.

 Enables \c requiresSecureCoding and sets the \c decodingFailurePolicy to \c NSDecodingFailurePolicySetErrorAndReturn.

 Returns \c nil if the given data is not valid or cannot be decoded, and sets the \c error out parameter.

 @important Make sure you have adopted \c NSSecureCoding in the types you decode. If any call to a \c decode -prefixed method fails, the default \c decodingFailurePolicy sets the error rather than throwing an exception. In this case, the current and all subsequent decode calls return \c 0 or \c nil.
 */
+ (nullable id)unarchivedObjectOfClasses:(NSSet<Class> *)classes fromData:(NSData *)data error:(NSError **)error API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/**
Decodes the \c NSArray root object from \c data which should be an \c NSArray, containing the given non-collection classes in \c classes  (no nested arrays or arrays of dictionaries, etc) from the given archive, previously encoded by \c NSKeyedArchiver.

Enables \c requiresSecureCoding and sets the \c decodingFailurePolicy to \c NSDecodingFailurePolicySetErrorAndReturn.

Returns \c nil if the given data is not valid or cannot be decoded, and sets the \c error out parameter.
*/
+ (nullable NSArray *)unarchivedArrayOfObjectsOfClasses:(NSSet<Class> *)classes fromData:(NSData *)data error:(NSError **)error API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) NS_REFINED_FOR_SWIFT;

/**
Decodes the \c NSDictionary root object from \c data which should be an \c NSDictionary, with keys of the types given in \c keyClasses and objects of the given non-collection classes in \c objectClasses (no nested dictionaries or other dictionaries contained in the dictionary, etc) from the given archive, previously encoded by \c NSKeyedArchiver.

Enables \c requiresSecureCoding and sets the \c decodingFailurePolicy to \c NSDecodingFailurePolicySetErrorAndReturn.

Returns \c nil if the given data is not valid or cannot be decoded, and sets the \c error out parameter.
*/
+ (nullable NSDictionary *)unarchivedDictionaryWithKeysOfClasses:(NSSet<Class> *)keyClasses objectsOfClasses:(NSSet<Class> *)valueClasses fromData:(NSData *)data error:(NSError **)error API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) NS_REFINED_FOR_SWIFT;

/// Initialize the unarchiver with empty state.
///
/// @DeprecationSummary {
///     Use ``NSKeyedUnarchiver/initForReadingFromData:error:`` instead.
/// }
- (instancetype)init API_DEPRECATED("Use -initForReadingFromData:error: instead", macosx(10.2,10.14), ios(2.0,12.0), watchos(2.0,5.0), tvos(9.0,12.0));
/// Initializes the receiver for decoding an archive previously encoded by `NSKeyedArchiver`.
///
/// @DeprecationSummary {
///     Use ``NSKeyedUnarchiver/initForReadingFromData:error:`` instead.
/// }
- (instancetype)initForReadingWithData:(NSData *)data API_DEPRECATED("Use -initForReadingFromData:error: instead", macosx(10.2,10.14), ios(2.0,12.0), watchos(2.0,5.0), tvos(9.0,12.0));

/// Decodes and returns the previously-archived object graph rooted in the given data.
///
/// @DeprecationSummary {
///     Use ``NSKeyedUnarchiver/unarchivedObjectOfClass:fromData:error:`` instead.
/// }
+ (nullable id)unarchiveObjectWithData:(NSData *)data API_DEPRECATED("Use +unarchivedObjectOfClass:fromData:error: instead", macosx(10.2,10.14), ios(2.0,12.0), watchos(2.0,5.0), tvos(9.0,12.0));
/// Decodes and returns the previously-archived object graph in the given data, returning an error if decoding fails.
///
/// This method throws an error if `data` does not contain valid keyed data.
///
/// @DeprecationSummary {
///     Use ``NSKeyedUnarchiver/unarchivedObjectOfClass:fromData:error:`` instead.
/// }
+ (nullable id)unarchiveTopLevelObjectWithData:(NSData *)data error:(NSError **)error API_DEPRECATED("Use +unarchivedObjectOfClass:fromData:error: instead", macosx(10.11,10.14), ios(2.0,12.0), watchos(2.0,5.0), tvos(9.0,12.0)) NS_SWIFT_UNAVAILABLE("Use 'unarchiveTopLevelObjectWithData(_:) throws' instead");
#if !0
/// Decodes and returns the previously-archived object graph from the file at the given path.
///
/// @DeprecationSummary {
///     Use ``NSKeyedUnarchiver/unarchivedObjectOfClass:fromData:error:`` instead.
/// }
+ (nullable id)unarchiveObjectWithFile:(NSString *)path API_DEPRECATED("Use +unarchivedObjectOfClass:fromData:error: instead", macosx(10.2,10.14), ios(2.0,12.0), watchos(2.0,5.0), tvos(9.0,12.0));
#endif

/// The unarchiver's delegate.
@property (nullable, assign) id <NSKeyedUnarchiverDelegate> delegate;

/// Tells the receiver that you are finished decoding objects.
///
/// Invoking this method allows the receiver to notify its delegate and to perform any final operations on the archive.
- (void)finishDecoding;

/// Sets a global translation mapping to decode objects encoded with a given class name as instances of a given class instead.
///
/// When decoding, the unarchiver first checks with its own translation map before using the class's map.
+ (void)setClass:(nullable Class)cls forClassName:(NSString *)codedName;
/// Sets a mapping for this unarchiver to decode objects encoded with a given class name as instances of a given class instead.
///
/// When decoding, the receiver's translation map overrides any translation that may also be present in the class's map.
- (void)setClass:(nullable Class)cls forClassName:(NSString *)codedName;

/// Returns the class from which the unarchiver class instantiates an encoded object with a given class name.
///
/// Returns `nil` if `NSKeyedUnarchiver` does not have a translation mapping for `codedName`.
+ (nullable Class)classForClassName:(NSString *)codedName;
/// Returns the class from which this unarchiver instantiates an encoded object with a given class name.
///
/// Returns `nil` if the receiver does not have a translation mapping for `codedName`. The class's separate translation map is not searched.
- (nullable Class)classForClassName:(NSString *)codedName;

/// Returns a Boolean value that indicates whether the archive contains a value for a given key within the current decoding scope.
- (BOOL)containsValueForKey:(NSString *)key;

/// Decodes and returns a previously-encoded object that was associated with the string key.
- (nullable id)decodeObjectForKey:(NSString *)key;
/// Decodes and returns a boolean value that was previously encoded and associated with the string key.
- (BOOL)decodeBoolForKey:(NSString *)key;
/// Decodes and returns an int value that was previously encoded and associated with the string key.
///
/// If the encoded integer does not fit into the default integer size, the method raises an `NSRangeException`.
- (int)decodeIntForKey:(NSString *)key;
/// Decodes and returns a 32-bit integer value that was previously encoded and associated with the string key.
- (int32_t)decodeInt32ForKey:(NSString *)key;
/// Decodes and returns a 64-bit integer value that was previously encoded and associated with the string key.
- (int64_t)decodeInt64ForKey:(NSString *)key;
/// Decodes and returns a float value that was previously encoded and associated with the string key.
- (float)decodeFloatForKey:(NSString *)key;
/// Decodes and returns a double value that was previously encoded and associated with the string key.
- (double)decodeDoubleForKey:(NSString *)key;
/// Decodes a buffer of data that was previously encoded with `encodeBytes:length:forKey:` and associated with the string key.
///
/// The buffer's length is returned by reference in `lengthp`. The returned bytes are immutable, and they go away with the unarchiver, not the containing autorelease pool.
- (nullable const uint8_t *)decodeBytesForKey:(NSString *)key returnedLength:(nullable NSUInteger *)lengthp NS_RETURNS_INNER_POINTER;

/// Indicates whether the unarchiver requires all unarchived classes to resist object substitution attacks.
///
/// When enabled, unarchiving a disallowed class throws an exception. Once enabled, attempting to set `requiresSecureCoding` to `NO` will throw an exception. This is to prevent classes from selectively turning secure coding off. This is designed to be set once at the top level and remain on. Note that the getter is on the superclass, `NSCoder`. See `NSCoder` for more information about secure coding.
@property (readwrite) BOOL requiresSecureCoding API_AVAILABLE(macos(10.8), ios(6.0), watchos(2.0), tvos(9.0));

/// The action to take when the unarchiver encounters decode failures.
@property (readwrite) NSDecodingFailurePolicy decodingFailurePolicy API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

@end

/// The optional methods implemented by the delegate of a keyed archiver.
@protocol NSKeyedArchiverDelegate <NSObject>
@optional

/// Informs the delegate that the object is about to be encoded.
///
/// The delegate either returns this object or can return a different object to be encoded instead. The delegate can also fiddle with the coder state. If the delegate returns `nil`, `nil` is encoded. This method is called after the original object may have replaced itself with `replacementObjectForKeyedArchiver:`. This method is not called for an object once a replacement mapping has been set up for that object (either explicitly, or because the object has previously been encoded). This is also not called when `nil` is about to be encoded. This method is called whether or not the object is being encoded conditionally.
- (nullable id)archiver:(NSKeyedArchiver *)archiver willEncodeObject:(id)object;

/// Informs the delegate that the given object has been encoded.
///
/// The delegate might restore some state it had fiddled previously, or use this to keep track of the objects which are encoded. The object may be `nil`. Not called for conditional objects until they are really encoded (if ever).
- (void)archiver:(NSKeyedArchiver *)archiver didEncodeObject:(nullable id)object;

/// Informs the delegate that the new object is being substituted for the old object.
///
/// This is also called when the delegate itself is doing or has done the substitution. The delegate may use this method if it is keeping track of the encoded or decoded objects.
- (void)archiver:(NSKeyedArchiver *)archiver willReplaceObject:(nullable id)object withObject:(nullable id)newObject;

/// Notifies the delegate that encoding is about to finish.
- (void)archiverWillFinish:(NSKeyedArchiver *)archiver;

/// Notifies the delegate that encoding has finished.
- (void)archiverDidFinish:(NSKeyedArchiver *)archiver;

@end

/// The optional methods implemented by the delegate of a keyed unarchiver.
@protocol NSKeyedUnarchiverDelegate <NSObject>
@optional

/// Informs the delegate that the named class is not available during decoding.
///
/// The delegate may, for example, load some code to introduce the class to the runtime and return it, or substitute a different class object. If the delegate returns `nil`, unarchiving aborts with an exception. The first class name string in the array is the class of the encoded object, the second is the immediate superclass, and so on.
- (nullable Class)unarchiver:(NSKeyedUnarchiver *)unarchiver cannotDecodeObjectOfClassName:(NSString *)name originalClasses:(NSArray<NSString *> *)classNames;

/// Informs the delegate that the object has been decoded.
///
/// The delegate either returns this object or can return a different object to replace the decoded one. The object may be `nil`. If the delegate returns `nil`, the decoded value will be unchanged (that is, the original object will be decoded). The delegate may use this to keep track of the decoded objects.
- (nullable id)unarchiver:(NSKeyedUnarchiver *)unarchiver didDecodeObject:(nullable id) NS_RELEASES_ARGUMENT object NS_RETURNS_RETAINED;

/// Informs the delegate that the new object is being substituted for the old object.
///
/// This is also called when the delegate itself is doing or has done the substitution. The delegate may use this method if it is keeping track of the encoded or decoded objects.
- (void)unarchiver:(NSKeyedUnarchiver *)unarchiver willReplaceObject:(id)object withObject:(id)newObject;

/// Notifies the delegate that decoding is about to finish.
- (void)unarchiverWillFinish:(NSKeyedUnarchiver *)unarchiver;

/// Notifies the delegate that decoding has finished.
- (void)unarchiverDidFinish:(NSKeyedUnarchiver *)unarchiver;

@end

@interface NSObject (NSKeyedArchiverObjectSubstitution)

@property (nullable, readonly) Class classForKeyedArchiver;
	// Implemented by classes to substitute a new class for instances during
	// encoding.  The object will be encoded as if it were a member of the
	// returned class.  The results of this method are overridden by the archiver
        // class and instance name<->class encoding tables.  If nil is returned,
        // the result of this method is ignored.  This method returns the result of
	// [self classForArchiver] by default, NOT -classForCoder as might be
	// expected.  This is a concession to source compatibility.

- (nullable id)replacementObjectForKeyedArchiver:(NSKeyedArchiver *)archiver;
	// Implemented by classes to substitute new instances for the receiving
	// instance during encoding.  The returned object will be encoded instead
	// of the receiver (if different).  This method is called only if no
	// replacement mapping for the object has been set up in the archiver yet
        // (for example, due to a previous call of replacementObjectForKeyedArchiver:
        // to that object).  This method returns the result of
	// [self replacementObjectForArchiver:nil] by default, NOT
	// -replacementObjectForCoder: as might be expected.  This is a concession
	// to source compatibility.


+ (NSArray<NSString *> *)classFallbacksForKeyedArchiver;


@end

@interface NSObject (NSKeyedUnarchiverObjectSubstitution)

+ (Class)classForKeyedUnarchiver;
	// Implemented by classes to substitute a new class during decoding.
        // Objects of the class will be decoded as members of the returned
        // class.  This method overrides the results of the unarchiver's class and
        // instance name<->class encoding tables.  Returns self by default.

@end

NS_HEADER_AUDIT_END(nullability, sendability)
