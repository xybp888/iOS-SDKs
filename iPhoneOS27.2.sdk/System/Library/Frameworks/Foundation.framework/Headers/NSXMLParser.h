/*	NSXMLParser.h
        Copyright (c) 2003-2019, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSError.h>

@class NSData, NSDictionary<KeyType, ObjectType>, NSError, NSString, NSURL, NSInputStream, NSSet<ObjectType>;
@protocol NSXMLParserDelegate;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Defines the external entity resolving policy used by an `NSXMLParser` instance.
API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0))
typedef NS_ENUM(NSUInteger, NSXMLParserExternalEntityResolvingPolicy) {
    /// The parser should never resolve external entities.
    NSXMLParserResolveExternalEntitiesNever = 0, // default
    /// The parser resolves external entities but does not load them over the network.
    NSXMLParserResolveExternalEntitiesNoNetwork,
    /// The parser resolves external entities only from the same origin as the original URL. Only applies to `NSXMLParser` instances initialized with `-initWithContentsOfURL:`.
    NSXMLParserResolveExternalEntitiesSameOriginOnly,
    /// The parser always resolves external entities.
    NSXMLParserResolveExternalEntitiesAlways
};

/// An event driven parser of XML documents (including DTD declarations).
///
/// An ``XMLParser`` notifies its delegate about the items (elements, attributes, CDATA blocks, comments, and so on) that it encounters as it processes an XML document. It does not itself do anything with those parsed items except report them. It also reports parsing errors. For convenience, an ``XMLParser`` object in the following descriptions is sometimes referred to as a parser object. Unless used in a callback, the ``XMLParser`` is a thread-safe class as long as any given instance is only used in one thread.
///
/// > Note:
/// > Namespace support was implemented in ``XMLParser`` starting in macOS 10.4. Namespace-related methods of ``XMLParser`` prior to this version have no effect.
@interface NSXMLParser : NSObject
/// Initializes a parser with the XML content referenced by the given URL.
///
/// - Parameter url: An `NSURL` object specifying a URL. The URL must be fully qualified and refer to a scheme that is supported by the `NSURL` class.
/// - Returns: An initialized `NSXMLParser` object or `nil` if an error occurs.
- (nullable instancetype)initWithContentsOfURL:(NSURL *)url;
/// Initializes a parser with the XML contents encapsulated in a given data object.
///
/// This method is the designated initializer.
///
/// - Parameter data: An `NSData` object containing XML markup.
/// - Returns: An initialized `NSXMLParser` object or `nil` if an error occurs.
- (instancetype)initWithData:(NSData *)data NS_DESIGNATED_INITIALIZER;
/// Initializes a parser with the XML contents from the specified stream and parses it.
///
/// - Parameter stream: The input stream. The content is incrementally loaded from the specified stream and parsed. The `NSXMLParser` will open the stream, and synchronously read from it without scheduling it.
/// - Returns: An initialized `NSXMLParser` object or `nil` if an error occurs.
- (instancetype)initWithStream:(NSInputStream *)stream API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));

/// A delegate object that receives messages about the parsing process.
///
/// For methods to be implemented by the delegate, see `NSXMLParserDelegate`.
@property (nullable, assign) id <NSXMLParserDelegate> delegate;

/// A Boolean value that determines whether the parser reports the namespaces and qualified names of elements.
///
/// `YES` if the parser reports namespace and qualified name, `NO` otherwise.
///
/// The parser reports element names with the delegate methods `-parser:didStartElement:namespaceURI:qualifiedName:attributes:` and `-parser:didEndElement:namespaceURI:qualifiedName:`.
@property BOOL shouldProcessNamespaces;
/// A Boolean value that determines whether the parser reports the prefixes indicating the scope of namespace declarations.
///
/// `YES` if the parser reports the scope of namespace declarations, `NO` otherwise. The default value is `NO`.
///
/// The parser reports prefixes with the delegate methods `-parser:didStartMappingPrefix:toURI:` and `-parser:didEndMappingPrefix:`.
@property BOOL shouldReportNamespacePrefixes;

/// The external entity resolving policy for the parser.
///
/// Defaults to `NSXMLParserResolveExternalEntitiesNever`.
@property NSXMLParserExternalEntityResolvingPolicy externalEntityResolvingPolicy API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));

/// The set of external entity URLs that the parser is allowed to load.
@property (nullable, copy) NSSet<NSURL *> *allowedExternalEntityURLs API_AVAILABLE(macos(10.9), ios(8.0), watchos(2.0), tvos(9.0));

/// Starts the event-driven parsing operation.
///
/// - Returns: `YES` if the parsing operation succeeds; `NO` if an error occurs or if the parsing operation aborts.
- (BOOL)parse;
/// Stops the parser object.
///
/// If you invoke this method, the delegate, if it implements `-parser:parseErrorOccurred:`, is informed of the cancelled parsing operation.
- (void)abortParsing;

/// An `NSError` object from which you can obtain information about a parsing error.
///
/// You may access this property after a parsing operation abnormally terminates to determine the cause of error.
@property (nullable, readonly, copy) NSError *parserError;

/// A Boolean value that determines whether the parser reports declarations of external entities.
///
/// `YES` if the parser reports declarations of external entities, `NO` otherwise. The default value is `NO`. If you set this property to `YES`, you may cause other I/O operations, either network-based or disk-based, to load the external DTD.
///
/// Toggles between disabling external entities entirely, and the current setting of the `externalEntityResolvingPolicy`.
/// The `externalEntityResolvingPolicy` property should be used instead of this, unless targeting 10.9/7.0 or earlier.
@property BOOL shouldResolveExternalEntities;

@end

// Once a parse has begun, the delegate may be interested in certain parser state. These methods will only return meaningful information during parsing, or after an error has occurred.
@interface NSXMLParser (NSXMLParserLocatorAdditions)
/// The public identifier of the external entity referenced in the XML document.
///
/// You may access this property once a parsing operation has begun or after an error occurs.
@property (nullable, readonly, copy) NSString *publicID;
/// The system identifier of the external entity referenced in the XML document.
///
/// You may access this property once a parsing operation has begun or after an error occurs.
@property (nullable, readonly, copy) NSString *systemID;
/// The line number of the XML document being processed by the parser.
///
/// You may access this property once a parsing operation has begun or after an error occurs.
@property (readonly) NSInteger lineNumber;
/// The column number of the XML document being processed by the parser.
///
/// The column refers to the nesting level of the XML elements in the document. You may access this property once a parsing operation has begun or after an error occurs.
@property (readonly) NSInteger columnNumber;

@end

/*

 For the discussion of event methods, assume the following XML:

 <?xml version="1.0" encoding="UTF-8"?>
 <?xml-stylesheet type='text/css' href='cvslog.css'?>
 <!DOCTYPE cvslog SYSTEM "cvslog.dtd">
 <cvslog xmlns="http://xml.apple.com/cvslog">
   <radar:radar xmlns:radar="http://xml.apple.com/radar">
     <radar:bugID>2920186</radar:bugID>
     <radar:title>API/NSXMLParser: there ought to be an NSXMLParser</radar:title>
   </radar:radar>
 </cvslog>

 */

// The parser's delegate is informed of events through the methods in the NSXMLParserDelegateEventAdditions category.
/// The interface an XML parser uses to inform its delegate about the content of the parsed document.
@protocol NSXMLParserDelegate <NSObject>
@optional

// Document handling methods
/// Sent by the parser object to the delegate when it begins parsing a document.
///
/// - Parameter parser: A parser object.
- (void)parserDidStartDocument:(NSXMLParser *)parser;
/// Sent by the parser object to the delegate when it has successfully completed parsing.
///
/// - Parameter parser: A parser object.
- (void)parserDidEndDocument:(NSXMLParser *)parser;

// DTD handling methods for various declarations.
/// Sent by a parser object to its delegate when it encounters a notation declaration.
///
/// - Parameters:
///   - parser: An `NSXMLParser` object parsing XML.
///   - name: A string that is the name of the notation.
///   - publicID: A string specifying the public ID associated with the notation `name`.
///   - systemID: A string specifying the system ID associated with the notation `name`.
- (void)parser:(NSXMLParser *)parser foundNotationDeclarationWithName:(NSString *)name publicID:(nullable NSString *)publicID systemID:(nullable NSString *)systemID;

/// Sent by a parser object to its delegate when it encounters an unparsed entity declaration.
///
/// - Parameters:
///   - parser: An `NSXMLParser` object parsing XML.
///   - name: A string that is the name of the unparsed entity in the declaration.
///   - publicID: A string specifying the public ID associated with the entity `name`.
///   - systemID: A string specifying the system ID associated with the entity `name`.
///   - notationName: A string specifying a notation of the declaration of entity `name`.
- (void)parser:(NSXMLParser *)parser foundUnparsedEntityDeclarationWithName:(NSString *)name publicID:(nullable NSString *)publicID systemID:(nullable NSString *)systemID notationName:(nullable NSString *)notationName;

/// Sent by a parser object to its delegate when it encounters a declaration of an attribute that is associated with a specific element.
///
/// - Parameters:
///   - parser: An `NSXMLParser` object parsing XML.
///   - attributeName: A string that is the name of an attribute.
///   - elementName: A string that is the name of an element that has the attribute `attributeName`.
///   - type: A string, such as "ENTITY", "NOTATION", or "ID", that indicates the type of the attribute.
///   - defaultValue: A string that specifies the default value of the attribute.
- (void)parser:(NSXMLParser *)parser foundAttributeDeclarationWithName:(NSString *)attributeName forElement:(NSString *)elementName type:(nullable NSString *)type defaultValue:(nullable NSString *)defaultValue;

/// Sent by a parser object to its delegate when it encounters a declaration of an element with a given model.
///
/// - Parameters:
///   - parser: An `NSXMLParser` object parsing XML.
///   - elementName: A string that is the name of an element.
///   - model: A string that specifies a model for `elementName`.
- (void)parser:(NSXMLParser *)parser foundElementDeclarationWithName:(NSString *)elementName model:(NSString *)model;

/// Sent by a parser object to the delegate when it encounters an internal entity declaration.
///
/// - Parameters:
///   - parser: An `NSXMLParser` object parsing XML.
///   - name: A string that is the declared name of an internal entity.
///   - value: A string that is the value of entity `name`.
- (void)parser:(NSXMLParser *)parser foundInternalEntityDeclarationWithName:(NSString *)name value:(nullable NSString *)value;

/// Sent by a parser object to its delegate when it encounters an external entity declaration.
///
/// - Parameters:
///   - parser: An `NSXMLParser` object parsing XML.
///   - name: A string that is the name of an entity.
///   - publicID: A string that specifies the public ID associated with `entityName`.
///   - systemID: A string that specifies the system ID associated with `entityName`.
- (void)parser:(NSXMLParser *)parser foundExternalEntityDeclarationWithName:(NSString *)name publicID:(nullable NSString *)publicID systemID:(nullable NSString *)systemID;

/// Sent by a parser object to its delegate when it encounters a start tag for a given element.
///
/// - Parameters:
///   - parser: A parser object.
///   - elementName: A string that is the name of an element (in its start tag).
///   - namespaceURI: If namespace processing is turned on, contains the URI for the current namespace as a string object.
///   - qName: If namespace processing is turned on, contains the qualified name for the current namespace as a string object.
///   - attributeDict: A dictionary that contains any attributes associated with the element. Keys are the names of attributes, and values are attribute values.
- (void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName namespaceURI:(nullable NSString *)namespaceURI qualifiedName:(nullable NSString *)qName attributes:(NSDictionary<NSString *, NSString *> *)attributeDict;

/// Sent by a parser object to its delegate when it encounters an end tag for a specific element.
///
/// - Parameters:
///   - parser: A parser object.
///   - elementName: A string that is the name of an element (in its end tag).
///   - namespaceURI: If namespace processing is turned on, contains the URI for the current namespace as a string object.
///   - qName: If namespace processing is turned on, contains the qualified name for the current namespace as a string object.
- (void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName namespaceURI:(nullable NSString *)namespaceURI qualifiedName:(nullable NSString *)qName;

/// Sent by a parser object to its delegate the first time it encounters a given namespace prefix, which is mapped to a URI.
///
/// The parser object sends this message only when namespace-prefix reporting is turned on through the `shouldReportNamespacePrefixes` property.
///
/// - Parameters:
///   - parser: A parser object.
///   - prefix: A string that is a namespace prefix.
///   - namespaceURI: A string that specifies a namespace URI.
- (void)parser:(NSXMLParser *)parser didStartMappingPrefix:(NSString *)prefix toURI:(NSString *)namespaceURI;

/// Sent by a parser object to its delegate when a given namespace prefix goes out of scope.
///
/// The parser sends this message only when namespace-prefix reporting is turned on through the `shouldReportNamespacePrefixes` property.
///
/// - Parameter parser: A parser object.
/// - Parameter prefix: A string that is a namespace prefix.
- (void)parser:(NSXMLParser *)parser didEndMappingPrefix:(NSString *)prefix;

/// Sent by a parser object to provide its delegate with a string representing all or part of the characters of the current element.
///
/// The parser object may send the delegate several `-parser:foundCharacters:` messages to report the characters of an element. Because `string` may be only part of the total character content for the current element, you should append it to the current accumulation of characters until the element changes.
///
/// - Parameters:
///   - parser: A parser object.
///   - string: A string representing the complete or partial textual content of the current element.
- (void)parser:(NSXMLParser *)parser foundCharacters:(NSString *)string;

/// Reported by a parser object to provide its delegate with a string representing all or part of the ignorable whitespace characters of the current element.
///
/// All the whitespace characters of the element (including carriage returns, tabs, and new-line characters) may not be provided through an individual invocation of this method. The parser may send the delegate several `-parser:foundIgnorableWhitespace:` messages to report the whitespace characters of an element. You should append the characters in each invocation to the current accumulation of characters.
///
/// - Parameters:
///   - parser: A parser object.
///   - whitespaceString: A string representing all or part of the ignorable whitespace characters of the current element.
- (void)parser:(NSXMLParser *)parser foundIgnorableWhitespace:(NSString *)whitespaceString;

/// Sent by a parser object to its delegate when it encounters a processing instruction.
///
/// - Parameters:
///   - parser: A parser object.
///   - target: A string representing the target of a processing instruction.
///   - data: A string representing the data for a processing instruction.
- (void)parser:(NSXMLParser *)parser foundProcessingInstructionWithTarget:(NSString *)target data:(nullable NSString *)data;

/// Sent by a parser object to its delegate when it encounters a comment in the XML.
///
/// - Parameters:
///   - parser: An `NSXMLParser` object parsing XML.
///   - comment: A string that is the content of a comment in the XML.
- (void)parser:(NSXMLParser *)parser foundComment:(NSString *)comment;

/// Sent by a parser object to its delegate when it encounters a CDATA block.
///
/// Through this method the parser object passes the contents of the block to its delegate in an `NSData` object. The CDATA block is character data that is ignored by the parser. The encoding of the character data is UTF-8. To convert the data object to a string object, use the `NSString` method `-initWithData:encoding:`.
///
/// - Parameters:
///   - parser: An `NSXMLParser` object parsing XML.
///   - CDATABlock: A data object containing a block of CDATA.
- (void)parser:(NSXMLParser *)parser foundCDATA:(NSData *)CDATABlock;

/// Sent by a parser object to its delegate when it encounters a given external entity with a specific system ID.
///
/// The delegate can resolve the external entity (for example, locating and reading an externally declared DTD) and provide the result to the parser object as an `NSData` object.
///
/// - Parameters:
///   - parser: A parser object.
///   - name: A string that specifies the external name of an entity.
///   - systemID: A string that specifies the system ID for the external entity.
/// - Returns: An `NSData` object that contains the resolution of the given external entity.
- (nullable NSData *)parser:(NSXMLParser *)parser resolveExternalEntityName:(NSString *)name systemID:(nullable NSString *)systemID;

/// Sent by a parser object to its delegate when it encounters a fatal error.
///
/// When this method is invoked, parsing is stopped. For further information about the error, you can query `parseError` or you can send the `parser` a `parserError` message. You can also send the parser `lineNumber` and `columnNumber` messages to further isolate where the error occurred. Typically you implement this method to display information about the error to the user.
///
/// - Parameters:
///   - parser: A parser object.
///   - parseError: An `NSError` object describing the parsing error that occurred.
- (void)parser:(NSXMLParser *)parser parseErrorOccurred:(NSError *)parseError;

/// Sent by a parser object to its delegate when it encounters a fatal validation error. `NSXMLParser` currently does not invoke this method and does not perform validation.
///
/// - Parameters:
///   - parser: A parser object.
///   - validationError: An `NSError` object describing the validation error that occurred.
- (void)parser:(NSXMLParser *)parser validationErrorOccurred:(NSError *)validationError;
@end

/// Indicates an error in XML parsing.
///
/// Used by `NSError`.
FOUNDATION_EXPORT NSErrorDomain const NSXMLParserErrorDomain	API_AVAILABLE(macos(10.3), ios(2.0), watchos(2.0), tvos(9.0));

/// The following error codes are defined by `NSXMLParser`. For error codes not listed here, see the `<libxml/xmlerror.h>` header file.
typedef NS_ENUM(NSInteger, NSXMLParserError) {
    /// The parser object encountered an internal error.
    NSXMLParserInternalError = 1,
    /// The parser object ran out of memory.
    NSXMLParserOutOfMemoryError = 2,
    /// The parser object is unable to start parsing.
    NSXMLParserDocumentStartError = 3,
    /// The document is empty.
    NSXMLParserEmptyDocumentError = 4,
    /// The document ended unexpectedly.
    NSXMLParserPrematureDocumentEndError = 5,
    /// Invalid hexadecimal character reference encountered.
    NSXMLParserInvalidHexCharacterRefError = 6,
    /// Invalid decimal character reference encountered.
    NSXMLParserInvalidDecimalCharacterRefError = 7,
    /// Invalid character reference encountered.
    NSXMLParserInvalidCharacterRefError = 8,
    /// Invalid character encountered.
    NSXMLParserInvalidCharacterError = 9,
    /// Target of character reference cannot be found.
    NSXMLParserCharacterRefAtEOFError = 10,
    /// Invalid character found in the prolog.
    NSXMLParserCharacterRefInPrologError = 11,
    /// Invalid character found in the epilog.
    NSXMLParserCharacterRefInEpilogError = 12,
    /// Invalid character encountered in the DTD.
    NSXMLParserCharacterRefInDTDError = 13,
    /// Target of entity reference is not found.
    NSXMLParserEntityRefAtEOFError = 14,
    /// Invalid entity reference found in the prolog.
    NSXMLParserEntityRefInPrologError = 15,
    /// Invalid entity reference found in the epilog.
    NSXMLParserEntityRefInEpilogError = 16,
    /// Invalid entity reference found in the DTD.
    NSXMLParserEntityRefInDTDError = 17,
    /// Target of parsed entity reference is not found.
    NSXMLParserParsedEntityRefAtEOFError = 18,
    /// Target of parsed entity reference is not found in prolog.
    NSXMLParserParsedEntityRefInPrologError = 19,
    /// Target of parsed entity reference is not found in epilog.
    NSXMLParserParsedEntityRefInEpilogError = 20,
    /// Target of parsed entity reference is not found in internal subset.
    NSXMLParserParsedEntityRefInInternalSubsetError = 21,
    /// Entity reference is without name.
    NSXMLParserEntityReferenceWithoutNameError = 22,
    /// Entity reference is missing semicolon.
    NSXMLParserEntityReferenceMissingSemiError = 23,
    /// Parsed entity reference is without an entity name.
    NSXMLParserParsedEntityRefNoNameError = 24,
    /// Parsed entity reference is missing semicolon.
    NSXMLParserParsedEntityRefMissingSemiError = 25,
    /// Entity is not declared.
    NSXMLParserUndeclaredEntityError = 26,
    /// Cannot parse entity.
    NSXMLParserUnparsedEntityError = 28,
    /// Cannot parse external entity.
    NSXMLParserEntityIsExternalError = 29,
    /// Entity is a parameter.
    NSXMLParserEntityIsParameterError = 30,
    /// Document encoding is unknown.
    NSXMLParserUnknownEncodingError = 31,
    /// Document encoding is not supported.
    NSXMLParserEncodingNotSupportedError = 32,
    /// String is not started.
    NSXMLParserStringNotStartedError = 33,
    /// String is not closed.
    NSXMLParserStringNotClosedError = 34,
    /// Invalid namespace declaration encountered.
    NSXMLParserNamespaceDeclarationError = 35,
    /// Entity is not started.
    NSXMLParserEntityNotStartedError = 36,
    /// Entity is not finished.
    NSXMLParserEntityNotFinishedError = 37,
    /// Angle bracket is used in attribute.
    NSXMLParserLessThanSymbolInAttributeError = 38,
    /// Attribute is not started.
    NSXMLParserAttributeNotStartedError = 39,
    /// Attribute is not finished.
    NSXMLParserAttributeNotFinishedError = 40,
    /// Attribute doesn't contain a value.
    NSXMLParserAttributeHasNoValueError = 41,
    /// Attribute is redefined.
    NSXMLParserAttributeRedefinedError = 42,
    /// Literal is not started.
    NSXMLParserLiteralNotStartedError = 43,
    /// Literal is not finished.
    NSXMLParserLiteralNotFinishedError = 44,
    /// Comment is not finished.
    NSXMLParserCommentNotFinishedError = 45,
    /// Processing instruction is not started.
    NSXMLParserProcessingInstructionNotStartedError = 46,
    /// Processing instruction is not finished.
    NSXMLParserProcessingInstructionNotFinishedError = 47,
    /// Notation is not started.
    NSXMLParserNotationNotStartedError = 48,
    /// Notation is not finished.
    NSXMLParserNotationNotFinishedError = 49,
    /// Attribute list is not started.
    NSXMLParserAttributeListNotStartedError = 50,
    /// Attribute list is not finished.
    NSXMLParserAttributeListNotFinishedError = 51,
    /// Mixed content declaration is not started.
    NSXMLParserMixedContentDeclNotStartedError = 52,
    /// Mixed content declaration is not finished.
    NSXMLParserMixedContentDeclNotFinishedError = 53,
    /// Element content declaration is not started.
    NSXMLParserElementContentDeclNotStartedError = 54,
    /// Element content declaration is not finished.
    NSXMLParserElementContentDeclNotFinishedError = 55,
    /// XML declaration is not started.
    NSXMLParserXMLDeclNotStartedError = 56,
    /// XML declaration is not finished.
    NSXMLParserXMLDeclNotFinishedError = 57,
    /// Conditional section is not started.
    NSXMLParserConditionalSectionNotStartedError = 58,
    /// Conditional section is not finished.
    NSXMLParserConditionalSectionNotFinishedError = 59,
    /// External subset is not finished.
    NSXMLParserExternalSubsetNotFinishedError = 60,
    /// Document type declaration is not finished.
    NSXMLParserDOCTYPEDeclNotFinishedError = 61,
    /// Misplaced CDATA end string.
    NSXMLParserMisplacedCDATAEndStringError = 62,
    /// CDATA block is not finished.
    NSXMLParserCDATANotFinishedError = 63,
    /// Misplaced XML declaration.
    NSXMLParserMisplacedXMLDeclarationError = 64,
    /// Space is required.
    NSXMLParserSpaceRequiredError = 65,
    /// Separator is required.
    NSXMLParserSeparatorRequiredError = 66,
    /// Name token is required.
    NSXMLParserNMTOKENRequiredError = 67,
    /// Name is required.
    NSXMLParserNAMERequiredError = 68,
    /// CDATA is required.
    NSXMLParserPCDATARequiredError = 69,
    /// URI is required.
    NSXMLParserURIRequiredError = 70,
    /// Public identifier is required.
    NSXMLParserPublicIdentifierRequiredError = 71,
    /// Left angle bracket is required.
    NSXMLParserLTRequiredError = 72,
    /// Right angle bracket is required.
    NSXMLParserGTRequiredError = 73,
    /// Left angle bracket slash is required.
    NSXMLParserLTSlashRequiredError = 74,
    /// Equal sign expected.
    NSXMLParserEqualExpectedError = 75,
    /// Tag name mismatch.
    NSXMLParserTagNameMismatchError = 76,
    /// Unfinished tag found.
    NSXMLParserUnfinishedTagError = 77,
    /// Standalone value found.
    NSXMLParserStandaloneValueError = 78,
    /// Invalid encoding name found.
    NSXMLParserInvalidEncodingNameError = 79,
    /// Comment contains double hyphen.
    NSXMLParserCommentContainsDoubleHyphenError = 80,
    /// Invalid encoding.
    NSXMLParserInvalidEncodingError = 81,
    /// External standalone entity.
    NSXMLParserExternalStandaloneEntityError = 82,
    /// Invalid conditional section.
    NSXMLParserInvalidConditionalSectionError = 83,
    /// Entity value is required.
    NSXMLParserEntityValueRequiredError = 84,
    /// Document is not well balanced.
    NSXMLParserNotWellBalancedError = 85,
    /// Error in content found.
    NSXMLParserExtraContentError = 86,
    /// Invalid character in entity found.
    NSXMLParserInvalidCharacterInEntityError = 87,
    /// Internal error in parsed entity reference found.
    NSXMLParserParsedEntityRefInInternalError = 88,
    /// Entity reference loop encountered.
    NSXMLParserEntityRefLoopError = 89,
    /// Entity boundary error.
    NSXMLParserEntityBoundaryError = 90,
    /// Invalid URI specified.
    NSXMLParserInvalidURIError = 91,
    /// URI fragment.
    NSXMLParserURIFragmentError = 92,
    /// Missing DTD.
    NSXMLParserNoDTDError = 94,
    /// Delegate aborted parse.
    NSXMLParserDelegateAbortedParseError = 512
};

NS_HEADER_AUDIT_END(nullability, sendability)
