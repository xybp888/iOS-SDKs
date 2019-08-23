//
//  CNContactViewController.h
//  ContactsUI
//
//  Copyright (c) 2015 Apple, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Contacts/Contacts.h>

NS_ASSUME_NONNULL_BEGIN

@protocol CNContactViewControllerDelegate;


/*!
 * @abstract The CNContactViewController is used to display a contact.
 * @discussion This class can display a new contact, unknown contact or existing contact. You must use one of the designated initializers.
 */
NS_CLASS_AVAILABLE_IOS(9_0)
@interface CNContactViewController : UIViewController

/*!
 * @abstract Descriptor for all keys that must be fetched on your contact before setting it on the view controller.
 * @discussion Pass this descriptor to the keysToFetch of the CNContactFetchRequest if you want to display the contact in a CNContactViewController.
 */
+ (id<CNKeyDescriptor>)descriptorForRequiredKeys;

/*!
 * @abstract Designated initializers.
 * @discussion These initializers customize the behavior and appearance of CNContactViewController.
 * @note All keys of the given contact must be fetched 
 */
+ (instancetype)viewControllerForContact:(CNContact *)contact;
+ (instancetype)viewControllerForUnknownContact:(CNContact *)contact;
+ (instancetype)viewControllerForNewContact:(nullable CNContact *)contact;

/*!
 * @abstract The contact being displayed.
 */
@property (nonatomic, strong, readonly) CNContact *contact;

/*!
 * @abstract The CNContact property keys to display.
 * @discussion If not set all properties are displayed.
 * @note All properties are visible when editing the contact.
 */
@property (nonatomic, copy, nullable) NSArray *displayedPropertyKeys;

/*!
 * @abstract The delegate to be notified.
 */
@property (nonatomic, weak, nullable) id <CNContactViewControllerDelegate> delegate;

/*!
 * @abstract The CNContactStore where the contact was fetched from or will be saved to.
 * @discussion If not set adding the contact to the user's contacts is disabled.
 */
@property (nonatomic, strong, nullable) CNContactStore *contactStore;

/*!
 * @abstract A CNGroup where the new contact will be assigned membership.
 * @discussion If not set the contact is added only to the default CNContainer with no group membership.
 * @note When set to a group not in the default container, the container property must also be set to the container of parentGroup.
 */
@property (nonatomic, strong, nullable) CNGroup *parentGroup;

/*!
 * @abstract A CNContainer where the new contact will be created.
 * @discussion If not set the contact is added to the default container.
 */
@property (nonatomic, strong, nullable) CNContainer *parentContainer;

/*!
 * @abstract The name to use if the contact has no display name.
 */
@property (nonatomic, copy, nullable) NSString *alternateName;

/*!
 * @abstract The message to display under the name.
 */
@property (nonatomic, copy, nullable) NSString *message;

/*!
 * @abstract Customization of the card.
 */
@property (nonatomic, assign) BOOL allowsEditing; // YES by default
@property (nonatomic, assign) BOOL allowsActions; // YES by default
@property (nonatomic, assign) BOOL shouldShowLinkedContacts; // NO by default

/*!
 * @abstract Highlight a property.
 * @discussion Indicates whether to highlight a certain property value for the contact.
 * If a single value property key is specified, identifier will be ignored.
 */
- (void)highlightPropertyWithKey:(NSString *)key identifier:(nullable NSString *)identifier;

@end


NS_AVAILABLE_IOS(9_0)
@protocol CNContactViewControllerDelegate <NSObject>
@optional

/*!
 * @abstract Called when the user selects a single property.
 * @discussion Return NO if you do not want anything to be done or if you are handling the actions yourself.
 * Return YES if you want the default action performed for the property otherwise return NO.
 */
- (BOOL)contactViewController:(CNContactViewController *)viewController shouldPerformDefaultActionForContactProperty:(CNContactProperty *)property;

/*!
 * @abstract Called when the view has completed.
 * @discussion If creating a new contact, the new contact added to the contacts list will be passed.
 * If adding to an existing contact, the existing contact will be passed.
 * @note It is up to the delegate to dismiss the view controller.
 */
- (void)contactViewController:(CNContactViewController *)viewController didCompleteWithContact:(nullable CNContact *)contact;

@end

NS_ASSUME_NONNULL_END
