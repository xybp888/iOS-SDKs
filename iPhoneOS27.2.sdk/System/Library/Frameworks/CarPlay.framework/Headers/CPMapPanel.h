//
//  CPMapPanel.h
//  CarPlay
//
//  Created by Rico Bowman on 4/20/26.
//  Copyright © 2026 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CarPlay/CPMapPanelSection.h>
#import <CarPlay/CPPanel.h>
#import <CarPlay/CPMapPanelButtonConfiguration.h>

@class CPMapPanel;

NS_ASSUME_NONNULL_BEGIN

/**
 The interface you use to respond to the appearance and disappearance of the panel.

 If you need to know when the system shows or hides the map panel, implement this protocol in a custom object and
 assign it to the ``CPMapPanel/delegate`` property of your ``CPMapPanel`` object. The system calls the methods
 of your object after it shows or hides the panel.
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
NS_SWIFT_NAME(CPMapPanel.Delegate)
@protocol CPMapPanelDelegate <NSObject>
@optional
/**
 Tells the delegate that the system displayed the specified map panel.

 - Parameters:
     - panel: The panel that appeared in your map interface.

 Shortly after a panel appears in your CarPlay interface, the system calls this method to give you a chance to respond. Use this
 method to perform any additional tasks that require the panel to be visible. The system calls this method on your app’s main
 thread after any animations to display the panel.
 */
- (void)panelDidShow:(CPMapPanel *)panel;

/**
 Tells the delegate that the system hid the specified map panel.

 - Parameters:
     - panel: The panel that disappeared from your map interface.

 Shortly after the system removes a map panel from your CarPlay interface, the system calls this method to give you a chance
 to respond. Use this method to perform any cleanup tasks associated with the panel’s disappearance. The system calls this method
 on your app’s main thread.
 */
- (void)panelDidHide:(CPMapPanel *)panel;
@end

/**
 An overlay for a custom map interface that shows navigation-related instructions or information over a portion of the map.

 When you want to display information on top of your custom map interface, create a ``CPMapPanel`` object and fill it with the
 information to display. For example, you might use this panel to display a list of waypoints, nearby points of interest, route information,
 or other content. When you show this panel from a ``CPMapTemplate`` object, CarPlay layers the panel on top of your custom map,
 covering only a portion of it. Map panels support a navigation-style interface structure, allowing you to create a hierarchical
 structure for navigating your panel content. To add a new level of hierarchy, _push_ a new panel using the map template methods. To remove
 a panel, _pop_ it off the top of the navigation stack using the map template methods.

 Create an instance of this panel when you want to add navigation-related details to your map interface. The panel displays content you
 provide using the ``CPMapPanelSection`` and ``CPMapPanelButtonConfiguration`` types. When you’re ready to display
 the panel over your map, call the ``CPMapTemplate/showPanel(_:completion:)`` or ``CPMapTemplate/pushPanel(_:completion:)``
 method of your ``CPMapTemplate`` object. If your panel’s ``CPPanel/showsCloseButton`` property is `true`, the driver
 can dismiss the panel at any time; otherwise, hide or dismiss the panel programmatically using your map template’s
 ``CPMapTemplate/hidePanel(completion:)`` or ``CPMapTemplate/popPanel(completion:)`` method.

 To monitor the appearance and disappearance of the panel, assign a delegate object to your map panel. The delegate object adopts the
 ``CPMapPanel/Delegate`` protocol and receives callbacks when your panel’s visibility changes. If you change the configured
 sections or their contents after you display the panel, CarPlay updates your interface accordingly.
 */
API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPMapPanel : CPPanel

/**
 Creates and configures a new map panel for display over your navigation app’s map template.

 - Parameters:
     - title: The title of the map panel. This title appears at the top of the panel display. The panel stores a copy of the string you provide.
     - sections: The information to display in the panel. Use this parameter to specify route options, charging stations, or other relevant content. If the number of items in this array exceeds the value in the ``CPPanel/maximumPanelItemsCount`` property, the map panel ignores any array items past the maximum. The system stores a copy of the array you provide.
     - buttonConfiguration: Optional buttons and travel estimate data to display at the bottom of the panel. Specify `nil` if you don’t want to include any buttons in the panel.
 - Returns: A new map panel instance.
*/
- (instancetype)initWithTitle:(nullable NSString *)title
                     sections:(NSArray<CPMapPanelSection *> *)sections
          buttonConfiguration:(nullable CPMapPanelButtonConfiguration *)buttonConfiguration;

/**
 The title to display at the top of the panel.
*/
@property (nonatomic, copy, readonly, nullable) NSString *title;

/**
 The sections of content to display in the panel.

 You specify this information initially when you create the panel, but can also update the list of sections by assigning a new value
 to this property. When assigning a new value to this property, the panel discards the previous data and stores a copy of the
 new sections you provide.

 If the panel isn’t tall enough to display all of the sections at the same time, it places them in a scrollable interface.
 */
@property (nonatomic, copy, readwrite) NSArray<CPMapPanelSection *> *sections;

/**
 The button information and travel estimates to display in the panel.

 You specify this information initially when you create the panel, but can also update it by assigning a new value to
 this property. The property stores the buttons and other map-related information to display in the panel.

 The system pins the information in this type to the bottom of the map panel, keeping it visible at all times.
 */
@property (nonatomic, strong, readonly, nullable) CPMapPanelButtonConfiguration *buttonConfiguration;

/**
 The app-specific object that the system notifies when it hides and shows the panel.

 Specify a custom object that adopts the ``CPMapPanel/Delegate`` protocol if you want to know when the map panel appears
 or disappears from your CarPlay interface. The system maintains a weak reference to the object you provide, so keep a reference
 to the object in your own code.
 */
@property (nonatomic, weak, nullable) id<CPMapPanelDelegate> delegate;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
