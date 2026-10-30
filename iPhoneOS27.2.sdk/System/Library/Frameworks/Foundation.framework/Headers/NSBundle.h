/*	NSBundle.h
	Copyright (c) 1994-2019, Apple Inc.  All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSSet.h>
#import <Foundation/NSProgress.h>
#import <Foundation/NSNotification.h>

@class NSString, NSURL, NSError, NSUUID, NSLock, NSNumber;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/* Because NSBundle caches allocated instances, subclasses should be prepared
   to receive an already initialized object back from [super initWithPath:] */

/// A representation of the code and resources stored in a bundle directory on disk.
///
/// Apple uses bundles to represent apps, frameworks, plug-ins, and many other specific types of content. Bundles organize their contained resources into well-defined subdirectories, and bundle structures vary depending on the platform and the type of the bundle. By using a bundle object, you can access a bundle's resources without knowing the structure of the bundle. The bundle object provides a single interface for locating items, taking into account the bundle structure, user preferences, available localizations, and other relevant factors.
///
/// Any executable can use a bundle object to locate resources, either inside an app's bundle or in a known bundle located elsewhere. You don't use a bundle object to locate files in a container directory or in other parts of the file system.
///
/// The general pattern for using a bundle object is as follows:
///
/// 1. Create a bundle object for the intended bundle directory.
/// 2. Use the methods of the bundle object to locate or load the needed resource.
/// 3. Use other system APIs to interact with the resource.
///
///
/// Some types of frequently used resources can be located and opened without a bundle. For example, when loading images, you store images in asset catalogs and load them using the <doc://com.apple.documentation/documentation/uikit/uiimage/init(named:)> methods of <doc://com.apple.documentation/documentation/uikit/uiimage> or <doc://com.apple.documentation/documentation/appkit/nsimage>. Similarly, for string resources, you use ``NSLocalizedString`` to load individual strings instead of loading the entire `.strings` file yourself.
///
/// > Note: Unlike some other Foundation classes with corresponding Core Foundation names (such as ``NSString`` and <doc://com.apple.documentation/documentation/corefoundation/cfstring>), ``Bundle`` objects cannot be cast to <doc://com.apple.documentation/documentation/corefoundation/cfbundle> references. If you need functionality provided by <doc://com.apple.documentation/documentation/corefoundation/cfbundle>, you can still create a <doc://com.apple.documentation/documentation/corefoundation/cfbundle> and use the <doc://com.apple.documentation/documentation/corefoundation/cfbundle> API. See [Toll-Free Bridging](https://developer.apple.com/library/archive/documentation/General/Conceptual/CocoaEncyclopedia/Toll-FreeBridgin/Toll-FreeBridgin.html#//apple_ref/doc/uid/TP40010810-CH2) for more information.
///
/// ### Finding and Opening a Bundle
///
/// Before you can locate a resource, you must first specify which bundle contains it. The ``Bundle`` class has many constructors, but the one you use most often is ``main``. The main bundle represents the bundle directory that contains the currently executing code. So for an app, the main bundle object gives you access to the resources that shipped with your app.
///
/// If your app interacts directly with plug-ins, frameworks, or other bundled content, you can use other methods of this class to create appropriate bundle objects. You can always create bundle objects from a known URL or path, but other methods make it easier to access bundles your app is already using. For example, if you link to a framework, you can use the ``init(for:)`` method to locate the framework bundle based on a class defined in that framework.
///
/// @TabNavigator {
/// @Tab("Swift") {
/// ```swift
/// // Get the app's main bundle
/// let mainBundle = Bundle.main
///
/// // Get the bundle containing the specified private class.
/// let myBundle = Bundle(for: NSClassFromString("MyPrivateClass")!)
/// ```
/// }
/// @Tab("Objective-C") {
/// ```objc
/// // Get the app's main bundle
/// NSBundle *main = [NSBundle mainBundle];
///
/// // Get the bundle containing the specified private class.
/// NSBundle *myBundle = [NSBundle bundleForClass:[MyPrivateClass class]];
/// ```
/// }
/// }
///
/// In Swift, use the ``bundle()`` macro to insert a bundle instance appropriate to the current execution context, whether an app, app extension, framework, or Swift package.
///
/// ### Locating Resources in a Bundle
///
/// You use ``Bundle`` objects to obtain the location of specific resources inside the bundle. When looking for resources, you provide the name of the resource and its type at a minimum. For resources in a specific subdirectory, you can also specify that directory. After locating the resource, the bundle routines return a path string or URL that you can use to open the file.
///
/// Locating a single resource in a bundle
///
/// ```objc
/// NSBundle *main = [NSBundle mainBundle];
/// NSString *resourcePath = [main pathForResource:@"Seagull" ofType:@"jpg"];
/// ```
///
///
///
///
/// Bundle objects follow a specific search pattern when looking for resources on disk. Global resources—that is, resources not in a language-specific `.lproj` directory—are returned first, followed by region- and language-specific resources. This search pattern means that the bundle looks for resources in the following order:
///
/// 1. Global (nonlocalized) resources
/// 2. Region-specific localized resources (based on the user's region preferences)
/// 3. Language-specific localized resources (based on the user's language preferences)
/// 4. Development language resources (as specified by the [CFBundleDevelopmentRegion](https://developer.apple.com/library/archive/documentation/General/Reference/InfoPlistKeyReference/Articles/CoreFoundationKeys.html#//apple_ref/doc/uid/20001431-130430) key in the bundle's Info.plist file)
///
///
/// Because global resources take precedence over language-specific resources, you should never include both a global and localized version of a given resource in your app. When a global version of a resource exists, language-specific versions are never returned. The reason for this precedence is performance. If localized resources were searched first, the bundle object might waste time searching for a nonexistent localized resource before returning the global resource.
///
/// > Important:
/// > Bundle objects always consider case when searching for resource files, even on file systems that support case-insensitive filenames. Always make sure that you specify filenames with case sensitivity in mind.
///
/// When locating resource files, the bundle object automatically considers many standard filename modifiers when determining which file to return. Resources may be tagged for a specific device (`~iphone`, `~ipad`) or for a specific screen resolution (`@2x`, `@3x`). Do not include these modifiers when specifying the name of the resource you want. The bundle object selects the file that is most appropriate for the underlying device. For more information, see [App Icons on iPhone, iPad and Apple Watch](https://developer.apple.com/library/archive/qa/qa1686/_index.html#//apple_ref/doc/uid/DTS40009882).
///
/// ### Understanding Bundle Structures
///
/// Bundle structures vary depending on the target platform and the type of bundle you are building. The ``Bundle`` class hides this underlying structure in most (but not all) cases. Many of the methods you use to load resources from a bundle automatically locate the appropriate starting directory and look for resources in known places. You can also use the methods and properties of this class to get the location of known bundle directories and to retrieve resources specifically from those directories.
///
/// For information about the bundle structure of iOS and macOS apps, see [Bundle Programming Guide](https://developer.apple.com/library/archive/documentation/CoreFoundation/Conceptual/CFBundles/Introduction/Introduction.html#//apple_ref/doc/uid/10000123i). For information about the structure of framework bundles, see [Framework Programming Guide](https://developer.apple.com/library/archive/documentation/MacOSX/Conceptual/BPFrameworks/Frameworks.html#//apple_ref/doc/uid/10000183i). For information about the structure of macOS plug-ins, see [Code Loading Programming Topics](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/LoadingCode/LoadingCode.html#//apple_ref/doc/uid/10000052i).
NS_SWIFT_SENDABLE
@interface NSBundle : NSObject

/* Methods for creating or retrieving bundle instances. */

/// Returns the bundle object that contains the current executable.
///
/// The main bundle lets you access the resources in the same directory as the currently running executable. For a running app or code running in a framework, the main bundle offers access to the app's bundle directory.
///
/// This method may return a valid bundle object even for unbundled apps. It may also return `nil` if the bundle object could not be created, so always check the return value.
@property (class, readonly, strong) NSBundle *mainBundle;

/// Creates and returns an `NSBundle` object that corresponds to the specified directory.
///
/// @param path The path to a directory. This must be a full pathname for a directory; if it contains any symbolic links, they must be resolvable.
/// @return An `NSBundle` object that corresponds to @c path. Returns @c nil if @c path does not exist or the user doesn't have access to it.
+ (nullable instancetype)bundleWithPath:(NSString *)path;

/// Returns an `NSBundle` object initialized to correspond to the specified directory.
///
/// This method initializes and returns a new instance only if there is no existing bundle associated with @c fullPath,
/// otherwise it deallocates @c self and returns the existing object.
///
/// @param path The path to a directory. This must be a full pathname for a directory; if it contains any symbolic links, they must be resolvable.
/// @return An `NSBundle` object initialized to correspond to @c fullPath, or @c nil if @c fullPath doesn't exist or the user doesn't have access to it.
- (nullable instancetype)initWithPath:(NSString *)path NS_DESIGNATED_INITIALIZER;

/// Creates and returns an `NSBundle` object that corresponds to the specified file URL.
///
/// @param url The file URL to a directory. This must be a full URL for a directory; if it contains any symbolic links, they must be resolvable.
/// @return An `NSBundle` object that corresponds to @c url. Returns @c nil if @c url does not exist or the user doesn't have access to it.
+ (nullable instancetype)bundleWithURL:(NSURL *)url API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns an `NSBundle` object initialized to correspond to the specified file URL.
///
/// This method initializes and returns a new instance only if there is no existing bundle associated with @c url,
/// otherwise it deallocates @c self and returns the existing object.
///
/// @param url The file URL to a directory. This must be a full URL for a directory; if it contains any symbolic links, they must be resolvable.
/// @return An `NSBundle` object initialized to correspond to @c url, or @c nil if @c url doesn't exist or the user doesn't have access to it.
- (nullable instancetype)initWithURL:(NSURL *)url API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns the `NSBundle` object with which the specified class is associated.
///
/// @param aClass A class.
/// @return The `NSBundle` object that dynamically loaded @c aClass (a loadable bundle), the `NSBundle` object for the framework in which @c aClass is defined, or the main bundle object if @c aClass was not dynamically loaded or is not defined in a framework.
+ (NSBundle *)bundleForClass:(Class)aClass;

/// Returns the `NSBundle` instance that has the specified bundle identifier.
///
/// This method is typically used by frameworks and plug-ins to locate their own bundle at runtime. It may be somewhat more
/// efficient than trying to locate the bundle using @c bundleForClass:. However, if the initial lookup fails, this method
/// uses potentially time-consuming heuristics to attempt to locate the bundle.
///
/// @param identifier The identifier for an existing `NSBundle` instance.
/// @return The previously allocated `NSBundle` object with the bundle identifier @c identifier, or @c nil if the requested bundle is not found.
+ (nullable NSBundle *)bundleWithIdentifier:(NSString *)identifier;

/// An array of all the application's non-framework bundles.
///
/// The returned array includes the main bundle and all bundles that have been dynamically created but doesn't contain any bundles that represent frameworks.
@property (class, readonly, copy) NSArray<NSBundle *> *allBundles;

/// An array of all of the application's bundles that represent frameworks.
///
/// The returned array includes frameworks that are linked into an application when the application is built and bundles for frameworks that have been dynamically created. Only frameworks with one or more Objective-C classes in them are included.
@property (class, readonly, copy) NSArray<NSBundle *> *allFrameworks;

/* Methods for loading and unloading bundles. */

/// Dynamically loads the bundle's executable code into a running program, if the code has not already been loaded.
///
/// You can use this method to load the code associated with a dynamically loaded bundle, such as a plug-in or framework.
/// You don't need to load a bundle's executable code to search the bundle's resources.
/// @return @c YES if the method successfully loads the bundle's code or if the code has already been loaded, otherwise @c NO.
- (BOOL)load;

/// The load status of a bundle.
///
/// @c YES if the bundle's code is currently loaded, otherwise @c NO.
@property (readonly, getter=isLoaded) BOOL loaded;

/// Unloads the code associated with the receiver.
///
/// This method attempts to unload a bundle's executable code using the underlying dynamic loader (typically @c dyld).
/// You may use this method to unload plug-in and framework bundles when you no longer need the code they contain.
/// It is the responsibility of the caller to ensure that no in-memory objects or data structures refer to the code being unloaded.
/// @return @c YES if the bundle was successfully unloaded or was not already loaded; otherwise, @c NO if the bundle could not be unloaded.
- (BOOL)unload;

/// Returns a Boolean value indicating whether the bundle's executable code could be loaded successfully.
///
/// This method does not actually load the bundle's executable code. Instead, it performs several checks to see if the code
/// could be loaded and with one exception returns the same errors that would occur during an actual load operation.
/// @param error On output, this variable may contain an error object indicating why the bundle's executable could not be loaded.
/// @return @c YES if the bundle's executable code could be loaded successfully or is already loaded; otherwise, @c NO.
- (BOOL)preflightAndReturnError:(NSError **)error API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Loads the bundle's executable code and returns any errors.
///
/// If this method returns @c NO and you pass a value for the @c error parameter, a suitable error object is returned.
/// Potential errors include @c NSFileNoSuchFileError, @c NSExecutableNotLoadableError,
/// @c NSExecutableArchitectureMismatchError, @c NSExecutableRuntimeMismatchError,
/// @c NSExecutableLoadError, and @c NSExecutableLinkError.
/// @param error On output, this variable may contain an error object indicating why the bundle's executable could not be loaded.
/// @return @c YES if the bundle's executable code was loaded successfully or was already loaded; otherwise, @c NO.
- (BOOL)loadAndReturnError:(NSError **)error API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/* Methods for locating various components of a bundle. */

/// The full URL of the receiver's bundle directory.
@property (readonly, copy) NSURL *bundleURL API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// The file URL of the bundle's subdirectory containing resource files.
///
/// This property contains the appropriate path for modern application and framework bundles. This property may not contain a path for non-standard bundle formats or for some older bundle formats.
@property (nullable, readonly, copy) NSURL *resourceURL API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// The file URL of the receiver's executable file.
@property (nullable, readonly, copy) NSURL *executableURL API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns the file URL of the executable with the specified name in the receiver's bundle.
///
/// This method returns the appropriate path for modern application and framework bundles.
/// This method may not return a URL for non-standard bundle formats or for some older bundle formats.
/// @param executableName The name of an executable file.
/// @return The file URL of the executable in the receiver's bundle.
- (nullable NSURL *)URLForAuxiliaryExecutable:(NSString *)executableName API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// The file URL of the bundle's subdirectory containing private frameworks.
///
/// This property contains the appropriate path for modern application and framework bundles. This property may not be a URL for non-standard bundle formats or for some older bundle formats.
@property (nullable, readonly, copy) NSURL *privateFrameworksURL API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// The file URL of the receiver's subdirectory containing shared frameworks.
///
/// This property contains the appropriate path for modern application and framework bundles. This property may not contain a URL for non-standard bundle formats or for some older bundle formats.
@property (nullable, readonly, copy) NSURL *sharedFrameworksURL API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// The file URL of the bundle's subdirectory containing shared support files.
///
/// This property contains the appropriate path for modern application and framework bundles. This property may not contain a path for non-standard bundle formats or for some older bundle formats.
@property (nullable, readonly, copy) NSURL *sharedSupportURL API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// The file URL of the receiver's subdirectory containing plug-ins.
///
/// This is the appropriate path for modern application and framework bundles. This may not be a URL for non-standard bundle formats or for some older bundle formats.
@property (nullable, readonly, copy) NSURL *builtInPlugInsURL API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

#if defined(__swift__) // Deprecated for Swift only
/// The file URL for the bundle's App Store receipt.
///
/// Use this app bundle property to locate the app receipt if it's present; this property is @c nil if the receipt isn't present.
/// In the rare case a receipt is invalid or missing in an app that a user downloads from the App Store,
/// use @c SKReceiptRefreshRequest to request a new receipt.
@property (nullable, readonly, copy) NSURL *appStoreReceiptURL API_DEPRECATED("Use AppTransaction.shared and Transaction.all from StoreKit.framework instead", macosx(10.7,15.0), ios(7.0,18.0), watchos(2.0,11.0), tvos(9.0,18.0));
#else
/// The file URL for the bundle's App Store receipt.
///
/// Use this app bundle property to locate the app receipt if it's present; this property is @c nil if the receipt isn't present.
/// In the rare case a receipt is invalid or missing in an app that a user downloads from the App Store,
/// use @c SKReceiptRefreshRequest to request a new receipt.
@property (nullable, readonly, copy) NSURL *appStoreReceiptURL API_AVAILABLE(macos(10.7), ios(7.0), watchos(2.0), tvos(9.0));
#endif

/// The full pathname of the receiver's bundle directory.
@property (readonly, copy) NSString *bundlePath;

/// The full pathname of the bundle's subdirectory containing resources.
@property (nullable, readonly, copy) NSString *resourcePath;

/// The full pathname of the receiver's executable file.
@property (nullable, readonly, copy) NSString *executablePath;

/// Returns the full pathname of the executable with the specified name in the receiver's bundle.
///
/// This method returns the appropriate path for modern application and framework bundles.
/// This method may not return a path for non-standard bundle formats or for some older bundle formats.
/// @param executableName The name of an executable file.
/// @return The full pathname of the executable in the receiver's bundle.
- (nullable NSString *)pathForAuxiliaryExecutable:(NSString *)executableName;

/// The full pathname of the bundle's subdirectory containing private frameworks.
///
/// This property contains the appropriate path for modern application and framework bundles. This property may not contain a path for non-standard bundle formats or for some older bundle formats.
@property (nullable, readonly, copy) NSString *privateFrameworksPath;

/// The full pathname of the bundle's subdirectory containing shared frameworks.
///
/// This property contains the appropriate path for modern application and framework bundles. This property may not contain a path for non-standard bundle formats or for some older bundle formats.
@property (nullable, readonly, copy) NSString *sharedFrameworksPath;

/// The full pathname of the bundle's subdirectory containing shared support files.
///
/// This property contains the appropriate path for modern application and framework bundles. This property may not contain a path for non-standard bundle formats or for some older bundle formats.
@property (nullable, readonly, copy) NSString *sharedSupportPath;

/// The full pathname of the receiver's subdirectory containing plug-ins.
///
/// This is the appropriate path for modern application and framework bundles. This may not be a path for non-standard bundle formats or for some older bundle formats.
@property (nullable, readonly, copy) NSString *builtInPlugInsPath;

/* Methods for locating bundle resources.  Instance methods locate resources in the bundle indicated by the receiver; class methods take an argument pointing to a bundle on disk.  In the class methods, bundleURL is a URL pointing to the location of a bundle on disk, and may not be nil; bundlePath is the path equivalent of bundleURL, an absolute path pointing to the location of a bundle on disk.  By contrast, subpath is a relative path to a subdirectory inside the relevant global or localized resource directory, and should be nil if the resource file in question is not in a subdirectory.  Where appropriate, localizationName is the name of a .lproj directory in the bundle, minus the .lproj extension; passing nil for localizationName retrieves only global resources, whereas using a method without this argument retrieves both global and localized resources (using the standard localization search algorithm).  */

/// Creates and returns a file URL for the resource with the specified name and extension in the specified bundle.
///
/// @param name The name of the resource file. If @c nil, the method returns the first resource file it finds that matches the remaining criteria.
/// @param ext The filename extension of the file to locate. If an empty string or @c nil, the extension is assumed not to exist.
/// @param subpath The name of the bundle subdirectory to search.
/// @param bundleURL The file URL of the bundle to search.
/// @return The file URL for the resource file or @c nil if the file could not be located.
+ (nullable NSURL *)URLForResource:(nullable NSString *)name withExtension:(nullable NSString *)ext subdirectory:(nullable NSString *)subpath inBundleWithURL:(NSURL *)bundleURL API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns an array containing the file URLs for all bundle resources having the specified filename extension, residing in the specified resource subdirectory, within the specified bundle.
///
/// @param ext The filename extension of the files to locate. If an empty string or @c nil, all files in @c subpath are returned.
/// @param subpath The name of the bundle subdirectory to search.
/// @param bundleURL The file URL of the bundle to search.
/// @return An array of file URLs for the resource files matching the criteria or an empty array if no files could be located.
+ (nullable NSArray<NSURL *> *)URLsForResourcesWithExtension:(nullable NSString *)ext subdirectory:(nullable NSString *)subpath inBundleWithURL:(NSURL *)bundleURL API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns the file URL for the resource identified by the specified name and file extension.
///
/// @param name The name of the resource file. If @c nil, the method returns the first resource file it finds with the specified extension.
/// @param ext The extension of the resource file. If an empty string or @c nil, the extension is assumed not to exist.
/// @return The file URL for the resource file or @c nil if the file could not be located.
- (nullable NSURL *)URLForResource:(nullable NSString *)name withExtension:(nullable NSString *)ext API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns the file URL for the resource file identified by the specified name and extension and residing in a given bundle directory.
///
/// @param name The name of a resource file. If @c nil, the method returns the first resource file it finds with the specified extension.
/// @param ext The filename extension of the file to locate. If an empty string or @c nil, the extension is assumed not to exist.
/// @param subpath The name of the bundle subdirectory to search.
/// @return The file URL for the resource file or @c nil if the file could not be located.
- (nullable NSURL *)URLForResource:(nullable NSString *)name withExtension:(nullable NSString *)ext subdirectory:(nullable NSString *)subpath API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns the file URL for the resource identified by the specified name and file extension, located in the specified bundle subdirectory, and limited to global resources and those associated with the specified localization.
///
/// @param name The name of the resource file. If @c nil, the method returns the first resource file it finds that matches the remaining criteria.
/// @param ext The filename extension of the file to locate. If an empty string or @c nil, the extension is assumed not to exist.
/// @param subpath The name of the bundle subdirectory to search.
/// @param localizationName The language ID for the localization. This parameter should correspond to the name of one of the bundle's language-specific resource directories without the @c .lproj extension.
/// @return The file URL for the resource file or @c nil if the file could not be located.
- (nullable NSURL *)URLForResource:(nullable NSString *)name withExtension:(nullable NSString *)ext subdirectory:(nullable NSString *)subpath localization:(nullable NSString *)localizationName API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns an array of file URLs for all resources identified by the specified file extension and located in the specified bundle subdirectory.
///
/// @param ext The filename extension of the files to locate. If an empty string or @c nil, all files in @c subpath are returned.
/// @param subpath The name of the bundle subdirectory.
/// @return An array of file URLs for the resource files or @c nil if no files could be located.
- (nullable NSArray<NSURL *> *)URLsForResourcesWithExtension:(nullable NSString *)ext subdirectory:(nullable NSString *)subpath API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns an array containing the file URLs for all bundle resources having the specified filename extension, residing in the specified resource subdirectory, and limited to global resources and those associated with the specified localization.
///
/// @param ext The filename extension of the files to locate. If an empty string or @c nil, all files in @c subpath are returned.
/// @param subpath The name of the bundle subdirectory to search.
/// @param localizationName The language ID for the localization. This parameter should correspond to the name of one of the bundle's language-specific resource directories without the @c .lproj extension.
/// @return An array containing the file URLs for all bundle resources matching the specified criteria. Returns an empty array if no matching resource files are found.
- (nullable NSArray<NSURL *> *)URLsForResourcesWithExtension:(nullable NSString *)ext subdirectory:(nullable NSString *)subpath localization:(nullable NSString *)localizationName API_AVAILABLE(macos(10.6), ios(4.0), watchos(2.0), tvos(9.0));

/// Returns the full pathname for the resource file identified by the specified name and extension and residing in a given bundle directory.
///
/// @param name The name of a resource file contained in the directory specified by @c bundlePath. If @c nil, the method returns the first resource file it finds with the specified extension.
/// @param ext The filename extension of the file to locate. If an empty string or @c nil, the extension is assumed not to exist.
/// @param bundlePath The path of a top-level bundle directory. This must be a valid path.
/// @return The full pathname for the resource file or @c nil if the file could not be located.
+ (nullable NSString *)pathForResource:(nullable NSString *)name ofType:(nullable NSString *)ext inDirectory:(NSString *)bundlePath;

/// Returns an array containing the pathnames for all bundle resources having the specified extension and residing in the bundle directory at the specified path.
///
/// @param ext The filename extension of the files to locate. If an empty string or @c nil, all files in @c bundlePath are returned.
/// @param bundlePath The top-level directory of a bundle. This must represent a valid path.
/// @return An array containing the full pathnames for all bundle resources with the specified extension. Returns an empty array if no matching resource files are found.
+ (NSArray<NSString *> *)pathsForResourcesOfType:(nullable NSString *)ext inDirectory:(NSString *)bundlePath;

/// Returns the full pathname for the resource identified by the specified name and file extension.
///
/// The method first looks for a matching resource file in the non-localized resource directory of the specified bundle.
/// If a matching resource file is not found, it then looks in the top level of an available language-specific @c .lproj folder.
/// @param name The name of the resource file. If @c nil, the method returns the first resource file it finds with the specified extension.
/// @param ext The filename extension of the file to locate. If an empty string or @c nil, the extension is assumed not to exist.
/// @return The full pathname for the resource file, or @c nil if the file could not be located.
- (nullable NSString *)pathForResource:(nullable NSString *)name ofType:(nullable NSString *)ext;

/// Returns the full pathname for the resource identified by the specified name and file extension and located in the specified bundle subdirectory.
///
/// @param name The name of the resource file. If @c nil, the method returns the first resource file it finds that matches the remaining criteria.
/// @param ext The filename extension of the files to locate. If an empty string or @c nil, all files in @c subpath and its subdirectories are returned.
/// @param subpath The name of the bundle subdirectory.
/// @return The full pathname for the resource file, or @c nil if the file could not be located.
- (nullable NSString *)pathForResource:(nullable NSString *)name ofType:(nullable NSString *)ext inDirectory:(nullable NSString *)subpath;

/// Returns the full pathname for the resource identified by the specified name and file extension, located in the specified bundle subdirectory, and limited to global resources and those associated with the specified localization.
///
/// @param name The name of the resource file. If @c nil, the method returns the first resource file it finds that matches the remaining criteria.
/// @param ext The filename extension of the files to locate. If an empty string or @c nil, the extension is assumed not to exist.
/// @param subpath The name of the bundle subdirectory to search.
/// @param localizationName The language ID for the localization. This parameter should correspond to the name of one of the bundle's language-specific resource directories without the @c .lproj extension.
/// @return The full pathname for the resource file or @c nil if the file could not be located.
- (nullable NSString *)pathForResource:(nullable NSString *)name ofType:(nullable NSString *)ext inDirectory:(nullable NSString *)subpath forLocalization:(nullable NSString *)localizationName;

/// Returns an array containing the pathnames for all bundle resources having the specified filename extension and residing in the resource subdirectory.
///
/// @param ext The filename extension of the files to locate. If an empty string or @c nil, all files in @c subpath are returned.
/// @param subpath The name of the bundle subdirectory to search.
/// @return An array containing the full pathnames for all bundle resources matching the specified criteria. Returns an empty array if no matching resource files are found.
- (NSArray<NSString *> *)pathsForResourcesOfType:(nullable NSString *)ext inDirectory:(nullable NSString *)subpath;

/// Returns an array containing the file for all bundle resources having the specified filename extension, residing in the specified resource subdirectory, and limited to global resources and those associated with the specified localization.
///
/// @param ext The filename extension of the files to locate. If an empty string or @c nil, all files in @c subpath are returned.
/// @param subpath The name of the bundle subdirectory to search.
/// @param localizationName The language ID for the localization. This parameter should correspond to the name of one of the bundle's language-specific resource directories without the @c .lproj extension.
/// @return An array containing the full pathnames for all bundle resources matching the specified criteria. Returns an empty array if no matching resource files are found.
- (NSArray<NSString *> *)pathsForResourcesOfType:(nullable NSString *)ext inDirectory:(nullable NSString *)subpath forLocalization:(nullable NSString *)localizationName;

/* Methods for retrieving localized strings. */

/// Returns a localized version of the string designated by the specified key and residing in the specified table.
///
/// @param key The key for a string in the table identified by @c tableName.
/// @param value The value to return if @c key is @c nil or if a localized string for @c key can't be found in the table.
/// @param tableName The receiver's string table to search. If @c nil or an empty string, the method attempts to use the table in @c Localizable.strings.
/// @return A localized version of the string designated by @c key in table @c tableName.
- (NSString *)localizedStringForKey:(NSString *)key value:(nullable NSString *)value table:(nullable NSString *)tableName NS_FORMAT_ARGUMENT(1);
#if !0
- (NSAttributedString *)localizedAttributedStringForKey:(NSString *)key value:(nullable NSString *)value table:(nullable NSString *)tableName NS_FORMAT_ARGUMENT(1) NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(12.0), ios(15.0), watchos(8.0), tvos(15.0));
#endif 

/// Look up a localized string given a list of available localizations.
/// - Parameters:
///   - key: The key for the localized string to retrieve.
///   - value: A default value to return if a localized string for ``key`` cannot be found.
///   - tableName: The name of the strings file to search. If `nil`, the method uses tables in `Localizable.strings`.
///   - localizations: An array of BCP 47 language codes corresponding to available localizations. Bundle compares the array against its available localizations, and uses the best result to retrieve the localized string. If empty, we treat it as no localization is available, and may return a fallback.
/// - Returns: A localized version of the string designated by ``key`` in table ``tableName``.
- (NSString *)localizedStringForKey:(NSString *)key value:(nullable NSString *)value table:(nullable NSString *)tableName localizations:(NSArray<NSString *>*)localizations NS_FORMAT_ARGUMENT(1) API_AVAILABLE(macos(15.4), ios(18.4), watchos(11.4), tvos(18.4), visionos(2.4)) NS_REFINED_FOR_SWIFT;

/* Methods for obtaining various information about a bundle. */

/// The receiver's bundle identifier.
///
/// The bundle identifier is defined by the @c CFBundleIdentifier key in the bundle's information property list.
@property (nullable, readonly, copy) NSString *bundleIdentifier;

/// A dictionary, constructed from the bundle's @c Info.plist file, that contains information about the receiver.
///
/// If the bundle does not contain an @c Info.plist file, this dictionary contains only private keys that are used internally by the @c NSBundle class.
/// Common keys for accessing the values of the dictionary are @c CFBundleIdentifier, @c NSMainNibFile, and @c NSPrincipalClass.
@property (nullable, readonly, copy) NSDictionary<NSString *, id> *infoDictionary;

/// A dictionary with the keys from the bundle's localized property list.
///
/// This property uses the preferred localization for the current user when determining which resources to include.
/// If the preferred localization is not available, this property chooses the most appropriate localization found in the bundle.
@property (nullable, readonly, copy) NSDictionary<NSString *, id> *localizedInfoDictionary;

/// Returns the value associated with the specified key in the receiver's information property list.
///
/// Use of this method is preferred over other access methods because it returns the localized value of a key when one is available.
/// @param key A key in the receiver's property list.
/// @return The value associated with @c key in the receiver's property list (@c Info.plist). The localized value of a key is returned when one is available.
- (nullable id)objectForInfoDictionaryKey:(NSString *)key;

/// Returns the @c Class object for the specified name.
///
/// If the bundle's executable code is not yet loaded, this method dynamically loads it into memory.
/// @param className The name of a class.
/// @return The @c Class object for @c className. Returns @c nil if @c className is not one of the classes associated with the receiver or if there is an error loading the executable code.
- (nullable Class)classNamed:(NSString *)className;

/// The bundle's principal class.
///
/// This property is set after ensuring that the code containing the definition of the class is dynamically loaded.
/// If the bundle encounters errors in loading or if it can't find the executable code file in the bundle directory, this property is @c nil.
/// The bundle obtains the principal class from the information dictionary using the key @c NSPrincipalClass. For non-loadable bundles
/// (applications and frameworks), if the principal class is not specified in the property list, this property is @c nil.
@property (nullable, readonly) Class principalClass;

/* Methods for dealing with localizations. */

/// An ordered list of preferred localizations contained in the bundle.
///
/// An array of @c NSString objects containing language IDs for localizations in the bundle.
/// The strings are ordered according to the user's language preferences and available localizations.
@property (readonly, copy) NSArray<NSString *> *preferredLocalizations;	// a subset of this bundle's localizations, re-ordered into the preferred order for this process's current execution environment; the main bundle's preferred localizations indicate the language (of text) the user is most likely seeing in the UI

/// A list of all the localizations contained in the bundle.
///
/// An array of @c NSString objects containing language IDs for all the localizations contained in the bundle.
@property (readonly, copy) NSArray<NSString *> *localizations;		// list of language names this bundle appears to be localized to

/// The localization for the development language.
///
/// This property corresponds to the value in the @c CFBundleDevelopmentRegion key of the bundle's property list (@c Info.plist).
@property (nullable, readonly, copy) NSString *developmentLocalization;

/// Returns one or more localizations from the specified list that a bundle object would use to locate resources for the current user.
///
/// This method does not return all localizations in preference order but only those from which @c NSBundle would get
/// localized content, typically either a single non-region-specific localization or a region-specific localization
/// followed by a corresponding non-region-specific localization as a fallback.
/// @param localizationsArray An array of @c NSString objects, each of which specifies the language ID for a localization that the bundle supports.
/// @return An array of @c NSString objects containing the preferred localizations, ordered according to the user's language preferences.
+ (NSArray<NSString *> *)preferredLocalizationsFromArray:(NSArray<NSString *> *)localizationsArray;

/// Returns locale identifiers for which a bundle would provide localized content, given a specified list of candidates for a user's language preferences.
///
/// @param localizationsArray An array of identifiers, each corresponding to a localization that a bundle can support.
/// @param preferencesArray An array of BCP 47 language codes corresponding to a user's preferred languages. If @c nil, the method uses the current user's language preferences.
/// @return An array of locale identifiers, ordered according to user preference. If none of the user-preferred localizations are available, this method returns one of the values in @c localizationsArray.
+ (NSArray<NSString *> *)preferredLocalizationsFromArray:(NSArray<NSString *> *)localizationsArray forPreferences:(nullable NSArray<NSString *> *)preferencesArray;

/* Method for determining executable architectures. */
enum {
    /// The 32-bit Intel architecture.
    NSBundleExecutableArchitectureI386      = 0x00000007,
    /// The 32-bit PowerPC architecture.
    NSBundleExecutableArchitecturePPC       = 0x00000012,
    /// The 64-bit Intel architecture.
    NSBundleExecutableArchitectureX86_64    = 0x01000007,
    /// The 64-bit PowerPC architecture.
    NSBundleExecutableArchitecturePPC64     = 0x01000012,
    /// The 64-bit ARM architecture.
    NSBundleExecutableArchitectureARM64 API_AVAILABLE(macos(11.0), ios(14.0), watchos(7.0), tvos(14.0)) = 0x0100000c
};

/// An array of numbers indicating the architecture types supported by the bundle's executable.
///
/// An array of @c NSNumber objects, each of which contains an integer value corresponding to a supported processor
/// architecture. If the bundle does not contain a Mach-O executable, this is @c nil.
@property (nullable, readonly, copy) NSArray<NSNumber *> *executableArchitectures API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

@end

/// Returns a localized version of a string from the default table, which Xcode autogenerates when exporting localizations.
///
/// Use this macro to automatically generate the default `Localizable.strings` file from your code
/// when exporting localizations from Xcode or the `genstrings` utility. You can specify Unicode
/// characters in `key` using `\\Uxxxx`---see the `-u` option for the `genstrings` utility.
///
/// The initial value for `key` in the strings file is `key`. To avoid collisions between words or
/// phrases with multiple meanings, use a unique `key` for each use of the same phrase. Use the
/// ``NSLocalizedStringWithDefaultValue`` macro to specify another value for `key`.
///
/// As of OS X 10.11 and iOS 9, `NSBundle` is thread-safe. As such, you can safely call
/// `NSLocalizedString` from any execution context.
///
/// > Important: The values for `key` and `comment` must be string literal values. Xcode can read
/// > these values from source code to automatically create localization tables when exporting
/// > localizations, but it doesn't resolve string variables. If you want to use string variables,
/// > manually create a strings file and use ``NSBundle/localizedStringForKey:value:table:`` instead.
///
/// - Parameters:
///   - key: The key for a string in the default table.
///   - comment: The comment to place above the key-value pair in the strings file. This parameter
///     provides the translator with some context about the localized string's presentation to the user.
/// - Returns: The result of sending ``NSBundle/localizedStringForKey:value:table:`` to the main bundle,
///   passing the specified `key`.
#define NSLocalizedString(key, comment) \
	    [NSBundle.mainBundle localizedStringForKey:(key) value:@"" table:nil]
/// Returns a localized version of a string from the table that you specify, which Xcode autogenerates when exporting localizations.
///
/// Use this macro to automatically generate a strings file named `[tableName].strings` from your
/// code when exporting localizations from Xcode or the `genstrings` utility. You can specify
/// Unicode characters in `key` using `\\Uxxxx`---see the `-u` option for the `genstrings` utility.
///
/// The initial value for `key` in the strings file is `key`. To avoid collisions between words or
/// phrases with multiple meanings, use a unique `key` for each use of the same phrase. Use the
/// ``NSLocalizedStringWithDefaultValue`` macro to specify another value for `key`.
///
/// As of OS X 10.11 and iOS 9, `NSBundle` is thread-safe. As such, you can safely call
/// `NSLocalizedStringFromTable` from any execution context.
///
/// > Important: The values for `key`, `tbl`, and `comment` must be string literal values. Xcode
/// > can read these values from source code to automatically create localization tables when
/// > exporting localizations, but it doesn't resolve string variables. If you want to use string
/// > variables, manually create a strings file and use ``NSBundle/localizedStringForKey:value:table:``
/// > instead.
///
/// - Parameters:
///   - key: The key for a string in the specified table.
///   - tbl: The name of the table containing the key-value pairs. Also, the suffix for the strings
///     file (a file with the `.strings` extension) to store the localized string. The default table
///     in `Localizable.strings` is used when `tbl` is `nil` or an empty string.
///   - comment: The comment to place above the key-value pair in the strings file. This parameter
///     provides the translator with some context about the localized string's presentation to the user.
/// - Returns: The result of invoking ``NSBundle/localizedStringForKey:value:table:`` on the main bundle,
///   passing the specified `key` and `tbl`.
#define NSLocalizedStringFromTable(key, tbl, comment) \
	    [NSBundle.mainBundle localizedStringForKey:(key) value:@"" table:(tbl)]
/// Returns a localized version of a string from the table and bundle that you specify, which Xcode autogenerates when exporting localizations.
///
/// Use this macro to automatically generate a strings file named `[tableName].strings` located in
/// `bundle` from your code when exporting localizations from Xcode or the `genstrings` utility.
/// You can specify Unicode characters in `key` using `\\Uxxxx`---see the `-u` option for the
/// `genstrings` utility.
///
/// The initial value for `key` in the strings file is `key`. To avoid collisions between words or
/// phrases with multiple meanings, use a unique `key` for each use of the same phrase. Use the
/// ``NSLocalizedStringWithDefaultValue`` macro to specify another value for `key`.
///
/// As of OS X 10.11 and iOS 9, `NSBundle` is thread-safe. As such, you can safely call
/// `NSLocalizedStringFromTableInBundle` from any execution context.
///
/// > Important: The values for `key`, `tbl`, and `comment` must be string literal values. Xcode
/// > can read these values from source code to automatically create localization tables when
/// > exporting localizations, but it doesn't resolve string variables. If you want to use string
/// > variables, manually create a strings file and use ``NSBundle/localizedStringForKey:value:table:``
/// > instead.
///
/// - Parameters:
///   - key: The key for a string in the specified table.
///   - tbl: The name of the table containing the key-value pairs. Also, the suffix for the strings
///     file (a file with the `.strings` extension) to store the localized string. The default table
///     in `Localizable.strings` is used when `tbl` is `nil` or an empty string.
///   - bundle: The bundle containing the table's strings file.
///   - comment: The comment to place above the key-value pair in the strings file. This parameter
///     provides the translator with some context about the localized string's presentation to the user.
/// - Returns: The result of sending ``NSBundle/localizedStringForKey:value:table:`` to `bundle`,
///   passing the specified `key` and `tbl`.
#define NSLocalizedStringFromTableInBundle(key, tbl, bundle, comment) \
	    [bundle localizedStringForKey:(key) value:@"" table:(tbl)]
/// Returns a localized version of a string identified by a key in the table that you specify, which Xcode autogenerates when exporting localizations.
///
/// Use this macro to automatically generate a strings file named `[tableName].strings` located in
/// `bundle` from your code when exporting localizations from Xcode or the `genstrings` utility.
/// The initial value for `key` in the strings file is `val`. You can specify Unicode characters in
/// `key` using `\\Uxxxx`---see the `-u` option for the `genstrings` utility.
///
/// As of OS X 10.11 and iOS 9, `NSBundle` is thread-safe. As such, you can safely call
/// `NSLocalizedStringWithDefaultValue` from any execution context.
///
/// > Important: The values for `key`, `tbl`, `val`, and `comment` must be string literal values.
/// > Xcode can read these values from source code to automatically create localization tables when
/// > exporting localizations, but it doesn't resolve string variables. If you want to use string
/// > variables, manually create a strings file and use ``NSBundle/localizedStringForKey:value:table:``
/// > instead.
///
/// - Parameters:
///   - key: The key for a string in the specified table.
///   - tbl: The name of the table containing the key-value pairs. Also, the suffix for the strings
///     file (a file with the `.strings` extension) to store the localized string. The default table
///     in `Localizable.strings` is used when `tbl` is `nil` or an empty string.
///   - bundle: The bundle containing the table's strings file.
///   - val: The localized string for the development locale. For other locales, return this value
///     if `key` is `nil` or if a localized string for `key` isn't found in the table.
///   - comment: The comment to place above the key-value pair in the strings file. This parameter
///     provides the translator with some context about the localized string's presentation to the user.
/// - Returns: The result of sending ``NSBundle/localizedStringForKey:value:table:`` to `bundle`,
///   passing the specified `key`, `val`, and `tbl`.
#define NSLocalizedStringWithDefaultValue(key, tbl, bundle, val, comment) \
	    [bundle localizedStringForKey:(key) value:(val) table:(tbl)]

#define NSLocalizedAttributedString(key, comment) \
	    [NSBundle.mainBundle localizedAttributedStringForKey:(key) value:@"" table:nil]
#define NSLocalizedAttributedStringFromTable(key, tbl, comment) \
	    [NSBundle.mainBundle localizedAttributedStringForKey:(key) value:@"" table:(tbl)]
#define NSLocalizedAttributedStringFromTableInBundle(key, tbl, bundle, comment) \
	    [bundle localizedAttributedStringForKey:(key) value:@"" table:(tbl)]
#define NSLocalizedAttributedStringWithDefaultValue(key, tbl, bundle, val, comment) \
	    [bundle localizedAttributedStringForKey:(key) value:(val) table:(tbl)]

@interface NSString (NSBundleExtensionMethods)

/// Returns a string variation suitable for the specified presentation width.
///
/// You can use this method to provide adaptive strings for the user's device -- that is, text that avoids truncation and maximizes available space. For example, an app running on an iPad Pro in Landscape orientation might welcome a user with the message "Greetings and Salutations!", whereas the same app running on an iPhone SE in Portrait orientation might instead show an abbreviated welcome message, like "Hello!".
///
/// > Note: Don't call this method when setting user-visible text for standard UIKit controls, such as `UILabel`. UIKit provides built-in support for adaptive strings, and automatically selects the string width variant appropriate for the current screen size.
///
/// Call this method on a string with one or more width variations. You define width variations for a localized string in a Stringsdict file using the `NSStringVariableWidthRuleType` key, and then retrieve a string with variations using `NSLocalizedString`.
///
/// This method selects a variation for a specified width according to the following behavior:
///
/// - If no variations exist for the string, the original string is returned.
/// - If a variation exists for the specified width, that string is returned.
/// - If no variation is found with a width less than the specified value, the variation with the smallest width is returned.
/// - Otherwise, the variation with the next smallest width value is returned.
///
/// - Parameter width: The desired width of the string variation.
/// - Returns: A string variation, or the original string if no variations exist for the specified width.
- (NSString *)variantFittingPresentationWidth:(NSInteger)width API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

@end

/// A notification that lets observers know when classes are dynamically loaded.
///
/// The notification object is the @c NSBundle instance that dynamically loads classes. The @c userInfo dictionary contains an @c NSLoadedClasses key.
FOUNDATION_EXPORT NSNotificationName const NSBundleDidLoadNotification;
/// Generates a log of the class names loaded by the runtime.
FOUNDATION_EXPORT NSString * const NSLoadedClasses;	// notification key


#if !0

/*
 The NSBundleResourceRequest class is used to interact with the on demand resource loading system.
 
 The purpose of the system is to allow an application to download certain resources on demand, when they are required. This also means that the system can purge a resource from disk when it is no longer required, which will save disk space. This class describes which resources are required, makes the request and reports progress, allows the app to specify how long during its execution that they are required.
 
 Resources are downloaded into the application container, and are made available via the standard NSBundle resource lookup API.
 
 The request object itself is lightweight. You may create as many as you need, for example to request the same set of tags in different components of your application.
*/

/// A resource manager you use to download content hosted on the App Store at the time your app needs it.
///
/// You identify on-demand resources during development by creating string identifiers known as tags and assigning one or more tags to each resource. An ``NSBundleResourceRequest`` object manages the resources marked by one or more tags.
///
/// You use the resource request to inform the system when the managed tags are needed and when you have finished accessing them. The resource request manages the downloading of any resources marked with the managed tags that are not already on the device and informs your app when the resources are ready for use.
///
/// > Note:
/// > This class ignores calls from Mac apps built with Mac Catalyst.
///
/// The system will not attempt to purge the resources marked with a tag from on-device storage as long as at least one ``NSBundleResourceRequest`` object is managing the tag. Apps can access resources after the completion handler of either ``beginAccessingResources(completionHandler:)`` or ``conditionallyBeginAccessingResources(completionHandler:)`` is called successfully. Management ends after a call to ``endAccessingResources()`` or after the resource request object is deallocated.
///
/// Other properties and methods let you track the progress of a download, change the priority of a download, and check whether the resources marked by a set of tags are already on the device. Methods in ``Bundle`` indicate to the system the relative importance of preserving a tag in memory after it is no longer in use. For more information, see ``Bundle/setPreservationPriority(_:forTags:)`` and ``Bundle/preservationPriority(forTag:)``.
///
/// > Important:
/// > An ``NSBundleResourceRequest`` object can only be used for one successful resource request.
API_DEPRECATED("Use Background Assets instead.", ios(9.0, 27.0), watchos(2.0, 27.0), tvos(9.0, 27.0)) API_UNAVAILABLE(macos)
@interface NSBundleResourceRequest : NSObject <NSProgressReporting>

- (instancetype)init NS_UNAVAILABLE;

/// Creates a resource request with the specified tags.
///
/// Resources are looked up in the main bundle.
- (instancetype)initWithTags:(NSSet<NSString *> *)tags;
/// Creates a resource request with the specified tags and bundle.
- (instancetype)initWithTags:(NSSet<NSString *> *)tags bundle:(NSBundle *)bundle NS_DESIGNATED_INITIALIZER;

/// A hint to the system about the relative priority of the resource request.
///
/// Values are limited to between `0` and `1`, with `1` being the highest priority. The default priority is `0.5`.
@property double loadingPriority;

/// The tags managed by this request.
@property (readonly, copy) NSSet<NSString *> *tags;

/// The bundle object that will hold the requested resources.
@property (readonly, strong) NSBundle *bundle;

/// Requests access to the resources and initiates download of content if necessary.
///
/// Resources will not be purged while in use. When you are finished with the resources, invoke `-endAccessingResources`. The completion block will be invoked on a non-main serial queue when the resources are available or an error has occurred.
- (void)beginAccessingResourcesWithCompletionHandler:(void (NS_SWIFT_SENDABLE ^)(NSError * _Nullable error))completionHandler;

/// Checks whether the resources are already available on disk without initiating a download.
///
/// The completion handler will be invoked with `YES` if the resources are available. If so, you must invoke `-endAccessingResources` when done. Otherwise, use `-beginAccessingResourcesWithCompletionHandler:` to initiate a download.
- (void)conditionallyBeginAccessingResourcesWithCompletionHandler:(void (NS_SWIFT_SENDABLE ^)(BOOL resourcesAvailable))completionHandler;

/// Informs the system that you are finished with the resources that were part of the tag set in this request.
- (void)endAccessingResources;

/// Progress for the request.
///
/// The progress object will be valid at initialization and begin updating after `-beginAccessingResourcesWithCompletionHandler:` is called.
@property (readonly, strong) NSProgress *progress;

@end

@interface NSBundle (NSBundleResourceRequestAdditions)

/* Set a preservation priority for tags that are included in this bundle for the On Demand Resources system. Preservation priorities may be between 0.0 and 1.0, with higher values being the last choice for purging by the system. The exact meaning of this value is up to your application as it only has meaning within the set of tags your application uses.
   
   The default value is 0.0.
 
   This method will throw an exception if the receiver bundle has no on demand resource tag information.
*/
/// A hint to the system of the relative order for purging tagged sets of resources in the bundle.
///
/// @param priority A number specifying the relative priority of preserving the resources. Possible values are between @c 0.0 and @c 1.0. The default is @c 0.0.
/// @param tags A set of tag names specifying resources stored in the bundle. Must not be @c nil.
- (void)setPreservationPriority:(double)priority forTags:(NSSet<NSString *> *)tags API_DEPRECATED("Use Background Assets instead.", ios(9.0, 27.0), watchos(2.0, 27.0), tvos(9.0, 27.0)) API_UNAVAILABLE(macos);

/// Returns the current preservation priority for the specified tag.
///
/// @param tag A string specifying the identifier for a group of related resources.
/// @return The preservation priority for the specified @c tag. Possible values are between @c 0.0 and @c 1.0.
- (double)preservationPriorityForTag:(NSString *)tag API_DEPRECATED("Use Background Assets instead.", ios(9.0, 27.0), watchos(2.0, 27.0), tvos(9.0, 27.0)) API_UNAVAILABLE(macos);

@end

/// Posted after the system detects that the amount of available disk space is getting low. The notification is posted to the default notification center.
///
/// After receiving this notification, the app should release any on-demand resources that are not required. Call `endAccessingResources()` to release the managed resources. If the app is in the background and the app does not free up enough space, it may be terminated.
///
/// > Note: This notification may not be the same as low disk space on the system, as applications can have a smaller quota.
FOUNDATION_EXPORT NSNotificationName const NSBundleResourceRequestLowDiskSpaceNotification API_DEPRECATED("Use Background Assets instead.", ios(9.0, 27.0), watchos(2.0, 27.0), tvos(9.0, 27.0)) API_UNAVAILABLE(macos);

/* Use this value for the loadingPriority property if the user is doing nothing but waiting on the result of this request. The system will dedicate the maximum amount of resources available to finishing this request as soon as possible.
 */
/// A priority that causes a resource request to load as soon as possible.
FOUNDATION_EXPORT double const NSBundleResourceRequestLoadingPriorityUrgent API_DEPRECATED("Use Background Assets instead.", ios(9.0, 27.0), watchos(2.0, 27.0), tvos(9.0, 27.0)) API_UNAVAILABLE(macos);

#endif 

NS_HEADER_AUDIT_END(nullability, sendability)
