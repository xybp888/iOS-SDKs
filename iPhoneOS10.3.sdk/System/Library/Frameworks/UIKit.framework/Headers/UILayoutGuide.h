//
//  UILayoutGuide.h
//  UIKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>

@class NSLayoutXAxisAnchor, NSLayoutYAxisAnchor, NSLayoutDimension;

NS_ASSUME_NONNULL_BEGIN
@class UIView;
/* UILayoutGuides will not show up in the view hierarchy, but may be used as items in
 an NSLayoutConstraint and represent a rectangle in the layout engine.
 
 Create a UILayoutGuide with -init, and add to a view with -[UIView addLayoutGuide:]
 before using it in a constraint.
 */
NS_CLASS_AVAILABLE_IOS(9_0)
@interface UILayoutGuide : NSObject <NSCoding>

/* The frame of the UILayoutGuide in its owningView's coordinate system.
 Valid by the time the owningView receives -layoutSubviews.
 */
@property(nonatomic,readonly) CGRect layoutFrame;

/* The guide must be added to a view with -[UIView addLayoutGuide:] before being used in a constraint.
 Do not use this property directly to change the owningView of a layout guide. Instead, use 
 -[UIView addLayoutGuide:] and -[UIView removeLayoutGuide:], which will use this property to 
 change the owningView.
 */
@property(nonatomic,weak,nullable) UIView *owningView;

/* For ease of debugging.
 'UI' prefix is reserved for UIKit-created layout guides.
 */
@property(nonatomic,copy) NSString *identifier;


/* Constraint creation conveniences. See NSLayoutAnchor.h for details.
 */
@property(readonly, strong) NSLayoutXAxisAnchor *leadingAnchor;
@property(readonly, strong) NSLayoutXAxisAnchor *trailingAnchor;
@property(readonly, strong) NSLayoutXAxisAnchor *leftAnchor;
@property(readonly, strong) NSLayoutXAxisAnchor *rightAnchor;
@property(readonly, strong) NSLayoutYAxisAnchor *topAnchor;
@property(readonly, strong) NSLayoutYAxisAnchor *bottomAnchor;
@property(readonly, strong) NSLayoutDimension *widthAnchor;
@property(readonly, strong) NSLayoutDimension *heightAnchor;
@property(readonly, strong) NSLayoutXAxisAnchor *centerXAnchor;
@property(readonly, strong) NSLayoutYAxisAnchor *centerYAnchor;

@end
NS_ASSUME_NONNULL_END
