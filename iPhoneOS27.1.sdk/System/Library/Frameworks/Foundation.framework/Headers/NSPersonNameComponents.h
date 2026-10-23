/*	NSPersonNameComponents.h
	Copyright (c) 2015-2019, Apple Inc. All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSString.h>
#import <Foundation/NSDictionary.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object that manages the separate parts of a person's name to allow locale-aware formatting.
///
/// You can use this type in Swift when you need reference semantics or other Foundation-specific behavior.
///
/// An `NSPersonNameComponents` object encapsulates the components of a person's name in an extendable, object-oriented manner. It is used to specify a person's name by providing the components comprising a full name: given name, middle name, family name, prefix, suffix, nickname, and phonetic representation.
///
/// `NSPersonNameComponents` objects can be used by an instance of ``PersonNameComponentsFormatter`` to create string representations suitable for display in the current locale.
///
/// > Important:
/// > The Swift overlay to the Foundation framework provides the ``PersonNameComponents`` structure, which bridges to the ``NSPersonNameComponents`` class. For more information about value types, see <doc://com.apple.documentation/documentation/swift/working-with-foundation-types>.
///
/// ### Working with Names
///
/// It is important to understand that names are disjoint from a person's identity. An individual may, at any time, have zero, one, or many names. Names cannot be used as a determination of a person's identity, because two names may correspond to the same individual, and two people may have the same name. Nor can names be used as a determination of a person's relation to others, because an individual may have a different family name than their relatives, and two individuals may have the same family name, but not be related.
///
/// Many locales and cultures have rules about what kinds of names are allowed and how they are structured. An `NSPersonNameComponents` object does not impose any restrictions about which combinations of properties may have values or what those values may be.
///
/// > Note:
/// > `NSPersonNameComponents` represents only the components of a name. To represent contact information, such as postal addresses or phone numbers, in addition to a personal name, use <doc://com.apple.documentation/documentation/contacts/cncontact> or <doc://com.apple.documentation/documentation/contacts/cnmutablecontact> instead.
///
/// ### Name Components
///
/// An `NSPersonNameComponents` object encodes the following components of a personal name, which are described in detail below.
///
/// - Given Name (``givenName``)
/// - Middle Name (``middleName``)
/// - Family Name (``familyName``)
/// - Prefix (``namePrefix``)
/// - Suffix (``nameSuffix``)
/// - Nickname (``nickname``)
/// - Phonetic Representation (``phoneticRepresentation``)
///
/// #### Given Name
///
/// A given name is bestowed upon an individual to differentiate them from other members of a group that share a family name. In some locales, this is also known as a "first name" or "forename."
///
/// ##### Multiple Given Names
///
/// Names may consist of multiple given names. For example, the Spanish name "María Rosalía Rita de Castro" consists of the given names "María," "Rosalía," and "Rita."
///
/// When modeling a name containing multiple given names with an `NSPersonNameComponents` object, concatenate them using a locale-appropriate delimiter and set the result as the `givenName` property value. If one of the given names is more commonly used in informal settings, such as "Rosalía" for "Rosalía de Castro," you can set that as the `nickname` property value.
///
/// #### Middle Name
///
/// A middle name is a secondary given name bestowed upon an individual to differentiate them from others that have the same given name.
///
/// ##### Multiple Middle Names and Middle Initials
///
/// Names can consist of one or more middle names in addition to a given name and/or family name. A middle name may appear only in certain styles, depending on the user localization preferences.
///
/// A middle name may consist only of an initial, such as the American name "Salmon P. Chase." When modeling a name containing a middle initial, set the initial and locale-appropriate punctuation as the `middleName` property value. Although many English-speaking locales commonly abbreviate middle names with middle initials, don't attempt to abbreviate a provided middle name yourself.
///
/// Sometimes, a middle name is preferred to a given name for common use. In that case, set the `middleName` property value as the nickname property value instead.
///
/// When modeling a name containing multiple middle names with an `NSPersonNameComponents` object, concatenate them using a locale-appropriate delimiter and set the result as the `middleName` property value.
///
/// #### Family Name
///
/// A family name is a name bestowed upon an individual to denote membership in a group or family.
///
/// ##### Prepositional Particles
///
/// Some family names consist of a prepositional phrase to denote nobility or regional ancestry, such as the Dutch name "Joost van den Vondel," which contains the prepositional phrase "van den." When modeling a name containing such a family name with an `NSPersonNameComponents` object, include any prepositional particles as part of the `familyName` property value.
///
/// ##### Composite Names
///
/// Some family names consist of matronymic, patronymic, or other ancestral names. For example, the Chilean name "Manuel Xavier Rodríguez Erdoíza" consists of the paternal name "Rodríguez" and the maternal name "Erdoíza." The usage and order of composite name components vary across different locales and cultures.
///
/// When modeling a name containing multiple family names with an `NSPersonNameComponents` object, use the entire composite family name as the `familyName` property value.
///
/// ##### Generational Name
///
/// It is traditional in some locales, particularly in China, for relatives born in the same generation to have a common generational name. For example, the Chinese name "郑秋媛 (Zheng Qiuyuan)" consists of the family name "郑 (Zheng)" and the given name "秋媛 (Qiuyuan)." The generational name "秋 (Qiu)" might be shared between the names of siblings or cousins, for instance, "郑秋德 (Zheng Qiude)." When modeling a name consisting of a generational name with `NSPersonNameComponents`, you should use the combined generational and given name values as the `givenName` property value.
///
/// Some names incorporate generational suffixes, such as "Jr.," "Sr.," or a roman numeral (I, II, III, IV, etc.) to distinguish between family members that have the same name. For example, the Samoan name "Malietoa Tanumafili II" contains the generational suffix "II" to denote the second generation. When modeling a name consisting of a generational suffix with `NSPersonNameComponents`, use it as the `nameSuffix` property value.
///
/// ##### Mononyms
///
/// Some individuals are commonly, legally, and/or historically identified by a single name. For example, the Lithuanian names "Vydūnas," "Žemaitė," and "Maironis." When modeling a mononymous name with `NSPersonNameComponents`, set the name as the `familyName` property value.
///
/// #### Prefix and Suffix
///
/// A name prefix is the portion of a name's full form of address that precedes the name itself. A name suffix is the portion of a name's full form of address that follows the name itself. Depending on the locale and individual, both may include any number of titles, honorifics, distinctions, or other information.
///
/// ##### Honorifics and Distinctions
///
/// Names can incorporate honorifics to convey respect when addressing an individual. Depending on the locale, honorifics may be incorporated into a name prefix or suffix, which is usually applied to a full name or family name only. For example, the American name "Mr. Sherman" contains the honorific "Mr." as a prefix, whereas the Japanese name "夏目さん (Natsume-san)" contains the honorific "san (さん)" as a suffix. Unlike most other aspects of names, honorifics are often localized to their corresponding equivalent for another language. For example, an American person might address a Japanese person as "Mr. Natsume," and a Japanese person might address an American person as "シャーマンさん (Sherman-san)."
///
/// A person that holds an academic degree, accreditation, decoration, or honor may convey that distinction through a name prefix or suffix, which can sometimes take the place of a conventional honorific. For example, the name "James Watt, FRS, FRSE" contains the postnominal letters "FRS" and "FRSE" to convey membership to learned societies. When modeling postnominal letters with `NSPersonNameComponents`, concatenate them using a locale-appropriate delimiter and set the result as the `nameSuffix` property value.
///
/// Users often prefer to be addressed informally when using an app, so the use of honorifics in names is not always appropriate. For this reason, honorifics and other distinctions typically appear in names only when a formatter specifies the most explicit style. When such formalities are appropriate, you should be aware of the particular conventions for addressing individuals in the target locale.
///
/// #### Phonetic Representation
///
/// It is sometimes beneficial to provide phonetic representations to aid in the pronunciation of names that are foreign or unfamiliar. For example, the Malay name "يوسف بن اسحاق" in Jawi script may be transliterated into Latin script as "Yusof bin Ishak" for English-speaking locales, where Latin script is commonly used. Depending on the locale and on the way the name is to be displayed to the user, it may be appropriate to provide an appropriate transliteration. This may be provided by the user or computed using the <doc://com.apple.documentation/documentation/corefoundation/cfstringtransform(_:_:_:_:)> function, except for names in certain nonphonetic scripts.
///
/// A phonetic representation may also be used to specify the pronunciation of a name in idiographic script with multiple pronunciations. For example, the character "藤" in the Japanese name "近藤 藤子 (Kondō Fujiko)" is pronounced "dō" in the family name and "fuji" in the given name, which can be clarified by providing the furigana "こんどう ふじこ" as a phonetic representation for a Japanese locale.
///
/// A phonetic representation may also be appropriate for names in a script appropriate for, but unfamiliar to, a given locale. For example, for the French name "Claude Debussy" the phonetic representation "clawed deb-you-see" as a pronunciation aid to an American English-speaking locale. Use of this kind of phonetic representation is discouraged for most user contexts.
///
/// ##### Aliases
///
/// Individuals may have one or more valid names, or aliases. This may be the result of adopting a new name in conjunction with a life event, such as marriage. For example, the name "Marie Curie" could have the corresponding alias "Maria Salomea Skłodowska."
///
/// Because each alias represents a separate name, an individual with one or more aliases would be modeled by a corresponding of number of `NSPersonNameComponents` objects, each representing a single alias.
API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0))
@interface NSPersonNameComponents : NSObject <NSCopying, NSSecureCoding>{
@private
    id _private;
}

/* The below examples all assume the full name Dr. Johnathan Maple Appleseed Esq., nickname "Johnny" */

/// Pre-nominal letters denoting title, salutation, or honorific, e.g. Dr., Mr.
@property (copy, nullable) NSString *namePrefix;

/// Name bestowed upon an individual by one's parents, e.g. Johnathan.
@property (copy, nullable) NSString *givenName;

/// Secondary given name chosen to differentiate those with the same first name, e.g. Maple.
@property (copy, nullable) NSString *middleName;

/// Name passed from one generation to another to indicate lineage, e.g. Appleseed.
@property (copy, nullable) NSString *familyName;

/// Post-nominal letters denoting degree, accreditation, or other honor, e.g. Esq., Jr., Ph.D.
@property (copy, nullable) NSString *nameSuffix;

/// Name substituted for the purposes of familiarity, e.g. "Johnny".
@property (copy, nullable) NSString *nickname;

/// The phonetic representation of the name components.
///
/// Each element of the phonetic representation should correspond to an element of the original `NSPersonNameComponents` instance. The phonetic representation of the phonetic representation object itself will be ignored. `nil` by default; must be instantiated.
@property (copy, nullable) NSPersonNameComponents *phoneticRepresentation;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
