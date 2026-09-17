/*	
    NSURLProtectionSpace.h
    Copyright (c) 2003-2019, Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Foundation/NSObject.h>
#import <Security/Security.h>

@class NSString;
@class NSArray<ObjectType>;
@class NSData;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// The protocol for HTTP.
FOUNDATION_EXPORT NSString * const NSURLProtectionSpaceHTTP API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// The protocol for HTTPS.
FOUNDATION_EXPORT NSString * const NSURLProtectionSpaceHTTPS API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// The protocol for FTP.
FOUNDATION_EXPORT NSString * const NSURLProtectionSpaceFTP API_DEPRECATED("FTP is deprecated and only supported in the classic loading mode", macos(10.5,15.4), ios(2.0,18.4), watchos(2.0,11.4), tvos(9.0,18.4), visionos(1.0,2.4));

/// The proxy type for HTTP proxies.
FOUNDATION_EXPORT NSString * const NSURLProtectionSpaceHTTPProxy API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/// The proxy type for HTTPS proxies.
FOUNDATION_EXPORT NSString * const NSURLProtectionSpaceHTTPSProxy API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/// The proxy type for FTP proxies.
FOUNDATION_EXPORT NSString * const NSURLProtectionSpaceFTPProxy API_DEPRECATED("FTP is deprecated and only supported in the classic loading mode", macos(10.2,15.4), ios(2.0,18.4), watchos(2.0,11.4), tvos(9.0,18.4), visionos(1.0,2.4));

/// The proxy type for SOCKS proxies.
FOUNDATION_EXPORT NSString * const NSURLProtectionSpaceSOCKSProxy API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/// The default authentication method for a protocol.
FOUNDATION_EXPORT NSString * const NSURLAuthenticationMethodDefault API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/// HTTP basic authentication. Equivalent to ``NSURLAuthenticationMethodDefault`` for HTTP.
FOUNDATION_EXPORT NSString * const NSURLAuthenticationMethodHTTPBasic API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/// HTTP digest authentication.
FOUNDATION_EXPORT NSString * const NSURLAuthenticationMethodHTTPDigest API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/// HTML form authentication. Applies to any protocol.
FOUNDATION_EXPORT NSString * const NSURLAuthenticationMethodHTMLForm API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0));

/// NTLM authentication.
FOUNDATION_EXPORT NSString * const NSURLAuthenticationMethodNTLM API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// Negotiate authentication.
FOUNDATION_EXPORT NSString * const NSURLAuthenticationMethodNegotiate API_AVAILABLE(macos(10.5), ios(2.0), watchos(2.0), tvos(9.0));

/// SSL client certificate. Applies to any protocol.
FOUNDATION_EXPORT NSString * const NSURLAuthenticationMethodClientCertificate API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));

/// `SecTrustRef` validation required. Applies to any protocol.
FOUNDATION_EXPORT NSString * const NSURLAuthenticationMethodServerTrust API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));

@class NSURLProtectionSpaceInternal;

/// A server or an area on a server, commonly referred to as a realm, that requires authentication.
///
/// A protection space defines a series of matching constraints that determine which credential should be provided. For example, if a request provides your delegate with a ``URLAuthenticationChallenge`` object that requests a client username and password, your app should provide the correct username and password for the particular host, port, protocol, and realm, as specified in the challenge's protection space.
///
/// > Note:
/// > This class has no designated initializer; its `init` method always returns `nil`. You must initialize this class by calling one of the initialization methods described in Creating a protection space.
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(10.2), ios(2.0), watchos(2.0), tvos(9.0))
@interface NSURLProtectionSpace : NSObject <NSSecureCoding, NSCopying>
{
@private
    NSURLProtectionSpaceInternal *_internal;
}

/// Creates a protection space object from the given host, port, protocol, realm, and authentication method.
///
/// - Parameters:
///   - host: The host name for the protection space object.
///   - port: The port for the protection space object. If `port` is `0`, the default port for the specified protocol is used, for example, port 80 for HTTP. Note that servers can, and do, treat these values differently.
///   - protocol: The protocol for the protection space object. The value of `protocol` is equivalent to the scheme for a URL in the protection space, for example, `"http"`, `"https"`, `"ftp"`, etc.
///   - realm: A string indicating a protocol-specific subdivision of the host. `realm` may be `nil` if there is no specified realm or if the protocol doesn't support realms.
///   - authenticationMethod: The type of authentication to use. `authenticationMethod` should be set to one of the authentication method constants or `nil` to use the default.
/// - Returns: A new protection space object, initialized with the given host, port, protocol, realm, and authentication method.
- (instancetype)initWithHost:(NSString *)host port:(NSInteger)port protocol:(nullable NSString *)protocol realm:(nullable NSString *)realm authenticationMethod:(nullable NSString *)authenticationMethod;

/// Creates a protection space object representing a proxy server.
///
/// - Parameters:
///   - host: The host of the proxy server for the protection space object.
///   - port: The port for the protection space object. If `port` is `0`, the default port for the specified proxy type is used, for example, port 80 for HTTP. Note that servers can, and do, treat these values differently.
///   - type: The type of proxy server.
///   - realm: A string indicating a protocol-specific subdivision of the host. `realm` may be `nil` if there is no specified realm or if the protocol doesn't support realms.
///   - authenticationMethod: The type of authentication to use. `authenticationMethod` should be set to one of the authentication method constants or `nil` to use the default.
/// - Returns: A new protection space object, with the given host, port, proxy type, realm, and authentication method.
- (instancetype)initWithProxyHost:(NSString *)host port:(NSInteger)port type:(nullable NSString *)type realm:(nullable NSString *)realm  authenticationMethod:(nullable NSString *)authenticationMethod;

/// The receiver's authentication realm.
///
/// This value is `nil` if no realm has been set. A realm is generally only specified for HTTP and HTTPS authentication.
@property (nullable, readonly, copy) NSString *realm;

/// A Boolean value that indicates whether the credentials for the protection space can be sent securely.
@property (readonly) BOOL receivesCredentialSecurely;

/// A Boolean value that indicates whether this authenticating protection space is a proxy server.
@property (readonly) BOOL isProxy;

/// The receiver's host.
@property (readonly, copy) NSString *host;

/// The receiver's port.
@property (readonly) NSInteger port;

/// The receiver's proxy type.
///
/// This value is `nil` if the receiver does not represent a proxy protection space.
@property (nullable, readonly, copy) NSString *proxyType;

/// The receiver's protocol.
///
/// This value is `nil` if the receiver represents a proxy protection space.
@property (nullable, readonly, copy) NSString *protocol;

/// The authentication method used by the receiver.
@property (readonly, copy) NSString *authenticationMethod;

@end

/// This category supplies additional information for use when a client certificate is required by the server in order to complete authentication.
@interface NSURLProtectionSpace(NSClientCertificateSpace)

/// The acceptable certificate-issuing authorities for client certificate authentication.
///
/// Issuers are identified by their distinguished name and returned as DER encoded data.
/// This value is `nil` if the authentication method is not `NSURLAuthenticationMethodClientCertificate`.
@property (nullable, readonly, copy) NSArray<NSData *> *distinguishedNames API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));

@end

/// This category supplies additional information for use by the client to evaluate whether to trust a given server during a security handshake.
@interface NSURLProtectionSpace(NSServerTrustValidationSpace)

/// A representation of the server's SSL transaction state.
///
/// This value is `nil` if the authentication method is not `NSURLAuthenticationMethodServerTrust`.
@property (nullable, readonly) SecTrustRef serverTrust API_AVAILABLE(macos(10.6), ios(3.0), watchos(2.0), tvos(9.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
