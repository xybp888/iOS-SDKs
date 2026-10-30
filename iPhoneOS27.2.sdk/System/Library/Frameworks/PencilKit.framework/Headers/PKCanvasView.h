//
//  PKCanvasView.h
//  PencilKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <PencilKit/PKToolPicker.h>


NS_ASSUME_NONNULL_BEGIN

@class PKDrawing, PKTool, PKCanvasView;

/// The optional methods a delegate receives from editing-related changes to the canvas view.
API_AVAILABLE(ios(13.0))
NS_SWIFT_UI_ACTOR
@protocol PKCanvasViewDelegate<NSObject, UIScrollViewDelegate>
@optional
/// Tells the delegate that the drawing on the canvas changes.
///
/// This may be called some time after the `canvasViewDidEndUsingTool:` delegate method.
/// For example, when using Apple Pencil, pressure data is delayed from touch data — a person
/// can stop drawing (`canvasViewDidEndUsingTool:` is called) while the canvas view still waits
/// for final pressure values. The drawing updates, and this method is called, only after those
/// final values arrive.
///
/// It's also possible that this method isn't called if the drawing interaction is cancelled.
///
/// @param canvasView The canvas view that changed.
- (void)canvasViewDrawingDidChange:(PKCanvasView *)canvasView;

/// Tells the delegate that the canvas finishes rendering all visible content.
///
/// This method lets you know when the canvas view finishes rendering all of the currently
/// visible content. Use it to delay showing the canvas view until all content is visible.
///
/// This is called every time the canvas view transitions from partially rendered to fully rendered,
/// including after setting the drawing, and after zooming or scrolling.
///
/// @param canvasView The canvas view that finished rendering.
- (void)canvasViewDidFinishRendering:(PKCanvasView *)canvasView;

/// Tells the delegate that a person begins using a tool such as selecting, drawing, or erasing.
///
/// Moving the ruler does not trigger this method.
///
/// @param canvasView The canvas view the person started interacting with.
- (void)canvasViewDidBeginUsingTool:(PKCanvasView *)canvasView  NS_SWIFT_NAME(canvasViewDidBeginUsingTool(_:));

/// Tells the delegate that a person stops using a tool.
///
/// @param canvasView The canvas view the person stopped interacting with.
- (void)canvasViewDidEndUsingTool:(PKCanvasView *)canvasView NS_SWIFT_NAME(canvasViewDidEndUsingTool(_:));

/// Tells the delegate that the selection changes.
///
/// @param canvasView The canvas view that the selection changed on.
- (void)canvasViewSelectionDidChange:(PKCanvasView *)canvasView;
@end


/// A policy that controls which input types can draw on the canvas.
typedef NS_ENUM(NSUInteger, PKCanvasViewDrawingPolicy) {
    /// The default input policy for the canvas view.
    ///
    /// When a tool picker is visible, this policy respects `UIPencilInteraction.prefersPencilOnlyDrawing`.
    /// When no tool picker is visible, only Apple Pencil touches draw.
    PKCanvasViewDrawingPolicyDefault,
    /// A policy that allows any input type to draw on the canvas.
    PKCanvasViewDrawingPolicyAnyInput,
    /// A policy that allows only Apple Pencil to draw on the canvas.
    PKCanvasViewDrawingPolicyPencilOnly
};


/// A view that lets people draw interactively and displays drawing content.
///
/// Use the `drawing` property to get and set the displayed `PKDrawing`.
API_AVAILABLE(ios(13.0))
@interface PKCanvasView : UIScrollView <PKToolPickerObserver>

/// The delegate for drawing operations.
@property (nonatomic, weak, nullable) id<PKCanvasViewDelegate> delegate;

/// The drawing shown on this view.
@property (nonatomic, copy) PKDrawing *drawing;

/// The tool a person uses to interact with the canvas.
///
/// Defaults to `[[PKInkingTool alloc] initWithType:PKInkTypePen color:UIColor.blackColor]`.
@property (nonatomic, copy) PKTool *tool NS_REFINED_FOR_SWIFT;

/// A Boolean value that indicates whether the ruler is active on the canvas.
@property (nonatomic, getter=isRulerActive) BOOL rulerActive;

/// The gesture recognizer that handles drawing input on the canvas.
@property (nonatomic, readonly) UIGestureRecognizer *drawingGestureRecognizer;

/// A Boolean value that indicates whether drawing input is enabled on the canvas.
///
/// Defaults to `true`. When the canvas observes a `PKToolPicker`, selecting a `PKToolPickerItem`
/// without an associated `PKTool` sets this value to `false` automatically.
@property (nonatomic, assign, getter=isDrawingEnabled) BOOL drawingEnabled API_AVAILABLE(ios(18.0), visionos(2.0));

@property (nonatomic) BOOL allowsFingerDrawing API_DEPRECATED("Use 'drawingPolicy' property.", ios(13_0, 14_0));

/// The policy that determines which input types can draw on the canvas.
///
/// Defaults to `PKCanvasViewDrawingPolicyDefault`.
@property (nonatomic, assign) PKCanvasViewDrawingPolicy drawingPolicy API_AVAILABLE(ios(14.0));

/// The maximum PencilKit content version the canvas supports.
///
/// Setting this to less than `.latest` limits the edits that can be made so they are compatible
/// with the specified version. If you set this property, also set it on any `PKToolPicker` used.
/// Defaults to `.latest`.
@property (nonatomic, assign) PKContentVersion maximumSupportedContentVersion API_AVAILABLE(ios(17.0));

/// The identifiers of the strokes selected on the canvas.
@property (nonatomic, copy) NSSet<NSUUID *> *selectedStrokeIDs API_AVAILABLE(ios(27.0), visionos(27.0)) NS_SWIFT_NAME(selection);

@end

NS_ASSUME_NONNULL_END
