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

API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
NS_SWIFT_NAME(CPMapPanel.Delegate)
@protocol CPMapPanelDelegate <NSObject>
@optional
- (void)panelDidShow:(CPMapPanel *)panel;
- (void)panelDidHide:(CPMapPanel *)panel;
@end

API_AVAILABLE(ios(27.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPMapPanel : CPPanel

/**
 Initializes a new overlay page.

 @param title An optional title for the page.
 @param sections An array of @c CPPanelListSection objects describing the content of the page.
 @param buttonConfiguration An optional button configuration for the page.
 @return A new @c CPPanelList instance
 */
- (instancetype)initWithTitle:(nullable NSString *)title
                     sections:(NSArray<CPMapPanelSection *> *)sections
          buttonConfiguration:(nullable CPMapPanelButtonConfiguration *)buttonConfiguration;

/**
 The title of the page.
 */
@property (nonatomic, copy, readonly, nullable) NSString *title;

/**
 The sections contained in this page.
 */
@property (nonatomic, copy, readwrite) NSArray<CPMapPanelSection *> *sections;

/**
 The button configuration for this page.
 */
@property (nonatomic, strong, readonly, nullable) CPMapPanelButtonConfiguration *buttonConfiguration;

/**
 The @c CPMapPanelDelegate.
 */
@property (nonatomic, weak, nullable) id<CPMapPanelDelegate> delegate;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
