/*
 * Copyright (c) 2015, 2018 Apple Inc.
 * All rights reserved.
 */

#ifndef __NE_INDIRECT__
#error "Please import the NetworkExtension module instead of this file directly."
#endif

#import <NetworkExtension/NETunnelNetworkSettings.h>

NS_ASSUME_NONNULL_BEGIN

@class NEIPv4Settings;
@class NEIPv6Settings;

/// NEPacketTunnelNetworkSettings IP Family types
typedef NS_ENUM(NSInteger, NEPacketTunnelNetworkSettingsIPFamily) {
	/*! @const NEPacketTunnelNetworkSettingsIPFamilyNone None */
	NEPacketTunnelNetworkSettingsIPFamilyNone = 0,
	/*! @const NEPacketTunnelNetworkSettingsIPFamilyAny Any IP family, i.e. IPv4, IPv6 */
	NEPacketTunnelNetworkSettingsIPFamilyAny = 1,
	/*! @const NEPacketTunnelNetworkSettingsIPFamilyIPv4 IPv4 only */
	NEPacketTunnelNetworkSettingsIPFamilyIPv4 = 2,
	/*! @const NEPacketTunnelNetworkSettingsIPFamilyIPv6 IPv6 only. */
	NEPacketTunnelNetworkSettingsIPFamilyIPv6 = 3,
} NS_SWIFT_NAME(NEPacketTunnelNetworkSettings.IPFamily) API_UNAVAILABLE(macos, ios, tvos, watchos);

/*!
 * @file NEPacketTunnelNetworkSettings
 * @discussion This file declares the NEPacketTunnelNetworkSettings API. The NEPacketTunnelNetworkSettings API is used to specify IP network settings for VPN tunnels.
 *
 * This API is part of NetworkExtension.framework
 */

/*!
 * @interface NEPacketTunnelNetworkSettings
 * @discussion The NEPacketTunnelNetworkSettings class declares the programmatic interface for an object that contains IP network settings.
 *
 * NEPacketTunnelNetworkSettings is used by NEPacketTunnelProviders to communicate the desired IP network settings for the packet tunnel to the framework. The framework takes care of applying the contained settings to the system.
 *
 * Instances of this class are thread safe.
 */
API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface NEPacketTunnelNetworkSettings : NETunnelNetworkSettings

/*!
 * @property IPv4Settings
 * @discussion An NEIPv4Settings object that contains the desired tunnel IPv4 settings.
 */
@property (copy, nullable) NEIPv4Settings *IPv4Settings API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property IPv6Settings
 * @discussion An NEIPv6Settings object that contains the desired tunnel IPv6 settings.
 */
@property (copy, nullable) NEIPv6Settings *IPv6Settings API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property tunnelOverheadBytes
 * @discussion An NSNumber object containing the number of bytes of overhead appended to each outbound packet through the tunnel. The MTU for the TUN interface is computed by subtracting this value from the MTU of the primary physical interface.
 */
@property (copy, nullable) NSNumber *tunnelOverheadBytes API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property MTU
 * @discussion An NSNumber object containing the Maximum Transmission Unit (MTU) size in bytes to assign to the TUN interface. If this property is set, the tunnelOverheadBytes property is ignored.
 */
@property (copy, nullable) NSNumber *MTU API_AVAILABLE(macos(10.11), ios(9.0), tvos(17.0)) API_UNAVAILABLE(watchos);

/*!
 * @property includeAllNetworks
 * @discussion If this property is set then all network traffic is routed through the tunnel, with some exclusions. Several of the exclusions
 * can be controlled with the excludeLocalNetworks, excludeCellularServices, excludeAPNs and excludeDeviceCommunication properties. See the documentation
 * for those properties. The set value of NEPacketTunnelNetworkSettingsIPFamily type indicates if includeAllNetworks should be applied to all traffic, IPv4 only
 * or IPv6 only.
 * The following traffic is always excluded from the tunnel:
 * - Traffic necessary for connecting and maintaining the device's network connection, such as DHCP.
 * - Traffic necessary for connecting to captive networks.
 * - Certain cellular services traffic that is not routable over the internet and is instead directly routed to the cellular network. See the
 *   excludeCellularServices property for more details.
 * - Network communication with a companion device such as a watchOS device.
 * The default value of this property is NEPacketTunnelNetworkSettingsIPFamilyNone, disabling includeAllNetworks.
 * The includeAllNetworks property in NEVPNProtocol class takes precedence if set.
 */
@property NEPacketTunnelNetworkSettingsIPFamily includeAllNetworks API_UNAVAILABLE(macos, ios, tvos, watchos);

/*!
 * @property excludeLocalNetworks
 * @discussion If this property is set, traffic destined for local networks will be excluded from the tunnel. The set value of
 * NEPacketTunnelNetworkSettingsIPFamily type indicates if excludeLocalNetworks should be applied to all traffic, IPv4 only
 * or IPv6 only. The default is NEPacketTunnelNetworkSettingsIPFamilyNone on macOS and NEPacketTunnelNetworkSettingsIPFamilyAny on iOS.
 * If either the includeAllNetworks or the enforceRoutes property in NEVPNProtocol class is set, then the excludeLocalNetworks property in NEVPNProtocol class takes precedence.
 */
@property NEPacketTunnelNetworkSettingsIPFamily excludeLocalNetworks API_UNAVAILABLE(macos, ios, tvos, watchos);

/*!
 * @property excludeCellularServices
 * @discussion If includeAllNetworks is set to YES and this property is set to YES, then internet-routable network traffic for cellular services
 * (VoLTE, Wi-Fi Calling, IMS, MMS, Visual Voicemail, etc.) is excluded from the tunnel. Note that some cellular carriers route cellular services traffic
 * directly to the carrier network, bypassing the internet. Such cellular services traffic is always excluded from the tunnel. The default value of this
 * property is YES.
 * If either the includeAllNetworks property in NEVPNProtocol class is set, then the excludeCellularServices property in NEVPNProtocol class takes precedence.

 */
@property BOOL excludeCellularServices API_UNAVAILABLE(macos, ios, tvos, watchos) __WATCHOS_PROHIBITED;

/*!
 * @property excludeAPNs
 * @discussion If includeAllNetworks is set to YES and this property is set to YES, then network traffic for the Apple Push Notification service (APNs)
 * is excluded from the tunnel. The default value of this property is YES.
 * If either the includeAllNetworks property in NEVPNProtocol class is set, then the excludeAPNs property in NEVPNProtocol class takes precedence.
 */
@property BOOL excludeAPNs API_UNAVAILABLE(macos, ios, tvos, watchos) __WATCHOS_PROHIBITED;

/*!
 * @property excludeDeviceCommunication
 * @discussion If includeAllNetworks is set to YES and this property is set to YES, then network traffic used for communicating with devices connected via USB or Wi-Fi is excluded
 * from the tunnel. For example, Xcode uses a network tunnel to communicate with connected development devices like iPhone, iPad and TV. The default value of this
 * property is YES.
 * If either the includeAllNetworks property in NEVPNProtocol class is set, then the excludeDeviceCommunication property in NEVPNProtocol class takes precedence.
 */
@property BOOL excludeDeviceCommunication API_UNAVAILABLE(macos, ios, tvos, watchos) __WATCHOS_PROHIBITED;

/*!
 * @property enforceRoutes
 * @discussion If YES, route rules for this tunnel will take precendence over any locally-defined routes. The default is NO.
 * The enforceRoutes property in NEVPNProtocol class takes precedence if set.
 */
@property BOOL enforceRoutes API_UNAVAILABLE(macos, ios, tvos, watchos);

@end

NS_ASSUME_NONNULL_END

