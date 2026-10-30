/*    NLContextualEmbedding.h
      Copyright (c) 2022-2023, Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <NaturalLanguage/NLEmbedding.h>
#import <NaturalLanguage/NLLanguage.h>
#import <NaturalLanguage/NLScript.h>
#import <NaturalLanguage/NLTokenizer.h>

NS_ASSUME_NONNULL_BEGIN

@class NLContextualEmbeddingResult;

/// A model that computes sequences of embedding vectors for natural language utterances.
///
/// `NLContextualEmbedding` provides a dense vector representation of natural language utterances
/// using models trained with contextualized language understanding. Unlike static word embeddings provided
///  by `NLEmbedding`, contextual embeddings dynamically adjust based on surrounding words, enabling
/// deeper language comprehension.
///
/// If you are building text classification or word tagging models, you can use
/// `NLContextualEmbedding` with <doc://com.apple.documentation/documentation/createml>
/// by selecting <doc://com.apple.documentation/documentation/createml/mltextclassifier/featureextractortype/bertembedding> as the feature extraction component in your model. For more information on how to create your own text
/// classification model refer to <doc://com.apple.documentation/documentation/createml/creating-a-text-classifier-model>.
///
/// > Note: For semantic similarity tasks, consider using ``NLEmbedding``. To learn more on how to
/// implement semantic similarity, refer to <doc://com.apple.documentation/documentation/naturallanguage/finding-similarities-between-pieces-of-text>.
///
/// Before configuring your contextual embedding:
///
/// - Select a model that's appropriate for your target language when initializing the embedding.
/// - Call ``NLContextualEmbedding/requestAssets(completionHandler:)`` before computing the embedding to confirm assets are available.
///
/// Some models support multiple languages; for example, you can use the same object to compute
/// embeddings for both English and Spanish. However, this isn't always the case — languages like
/// English and Chinese may require separate models. For more information about supported
/// languages, refer to ``languages``.
NS_CLASS_AVAILABLE(14_0, 17_0)
@interface NLContextualEmbedding : NSObject

- (instancetype)init NS_UNAVAILABLE;

/// Creates a contextual embedding from a model identifier.
/// - Parameter modelIdentifier: A string that uniquely identifies the embedding model.
///
/// If you train a custom model with the contextual embedding as the feature layer, keep track of this
/// identifier and use it when loading the custom model in your app.
+ (nullable instancetype)contextualEmbeddingWithModelIdentifier:(NSString *)modelIdentifier;

/// This class defines properties that you can filter or search for contextual embeddings.
///
/// The keys within this class provide filtering criteria that you can specify within your model. For example, you
/// can use a defined key like ``NLContextualEmbeddingKey/scripts`` and search for models
/// that use a specfic script like `Latin`.
typedef NSString *NLContextualEmbeddingKey NS_TYPED_EXTENSIBLE_ENUM;

/// A key that identifies the supported languages in a contextual embedding.
FOUNDATION_EXPORT NLContextualEmbeddingKey const NLContextualEmbeddingKeyLanguages;
/// A key that identifies the writing system that the language uses in a contextual embedding.
FOUNDATION_EXPORT NLContextualEmbeddingKey const NLContextualEmbeddingKeyScripts;
/// A key that identifies the version number the contextual embedding uses.
FOUNDATION_EXPORT NLContextualEmbeddingKey const NLContextualEmbeddingKeyRevision;


/// Returns contextual embedding models that match the specified language, script, or revision criteria.
+ (NSArray<NLContextualEmbedding *> *)contextualEmbeddingsForValues:(NSDictionary<NLContextualEmbeddingKey, id> *)valuesDictionary;

/// Creates a contextual embedding from a language.
/// - Parameter language: The language the framework uses to find the most recent embedding
/// suitable for the value you specify.
///
/// The language the framework uses to find the most recent embedding suitable for the value you specify.
+ (nullable NLContextualEmbedding *)contextualEmbeddingWithLanguage:(NLLanguage)language;

/// Creates a contextual embedding from a script.
/// - Parameter script: The writing system the framework uses to find the most suitable system
///  embedding for the value you specify; for example, Chinese or Latin.
+ (nullable NLContextualEmbedding *)contextualEmbeddingWithScript:(NLScript)script;

/// A string that uniquely identifies the embedding model.
///
/// Use the same model identifier that you developed and tested your app with to maintain consistent results.
@property (readonly, copy) NSString *modelIdentifier;

/// The languages that the contextual embedding supports.
///
/// Starting in iOS 17 and macOS 14, the framework supports 27 languages across three models:
/// - Latin — including Croatian, Czech, Danish, Dutch, English, Finnish, French, German, Hungarian,
///   Indonesian, Italian, Norwegian, Polish, Portuguese, Romanian, Slovak, Swedish, Spanish, Turkish, and
///   Vietnamese
/// - Cyrillic — including Bulgarian, Kazakh, Russian, and Ukrainian
/// - Chinese, Japanese, and Korean
///
/// In iOS 18 and macOS 15, the framework expands language support to include three additional models:
///
/// - Arabic
/// - Indic — including Bangla, Gujarati, Hindi, Kannada, Malayalam, Marathi, Punjabi, Tamil, Telugu, and Urdu
/// - Thai
///
@property (readonly, copy) NSArray <NLLanguage> *languages;
/// The writing systems that the language uses.
///
/// The current scripts that are supported by `NLContextualEmbedding` include:
/// - Arabic
/// - Cyrillic
/// - Chinese, Japanese, and Korean
/// - Indic
/// - Latin
/// - Thai
///
/// For the specific languages that each script supports, refer to ``languages``.
@property (readonly, copy) NSArray <NLScript> *scripts;
/// The version number the contextual embedding uses.
///
/// Ensure your app uses the same model revision you used during development and testing to maintain consistent results.
@property (readonly) NSUInteger revision;

/// The dimensionality of the embedding vectors generated by the model.
@property (readonly) NSUInteger dimension;

/// The maximum number of tokens in sequence for which the embedding generates vectors.
///
/// > Note: The model operates on subword tokens rather than whole words. Each token may represent a single character, part of a word, or (less commonly) an entire word. Most words are split into multiple tokens, especially rare or complex terms. As a result, the number of tokens in a sequence is often greater than the number of words.
///
/// Inputs longer than the token limit will be truncated, and only the first `maximumSequenceLength`
/// tokens will be processed to generate embeddings.
///
/// `NLContextualEmbedding` works best with text snippets at the sentence or paragraph level.
/// The model truncates text that exceeds this maximum length and only processes the truncated portion of the input.
///
@property (readonly) NSUInteger maximumSequenceLength;

/// The instance method that loads the embedding model.
///
/// - Returns: A Boolean value that indicates whether the load succeeds.
/// When you create a contextual embedding, the framework doesn't load the model until you need it. Use
/// ``NLContextualEmbedding/load()`` and ``NLContextualEmbedding/unload()`` to
/// control when to load and unload the model. The first time load can be expensive, make sure you load the
/// model before you need to use it.
///
/// The method fails if the necessary assets aren't on device for the model you specify. Use
/// ``NLContextualEmbedding/hasAvailableAssets`` and
/// ``NLContextualEmbedding/requestAssets(completionHandler:)`` to manage the
/// assets.
- (BOOL)loadWithError:(NSError **)error;
/// The instance method that unloads the embedding model.
- (void)unload;

/// Applies an embedding to a string and obtains the resulting embedding vectors.
/// - Parameters:
///   - string: The string to apply an embedding to.
///   - language: The language of the string.
///   - error: On output, a pointer to an error object that describes why the method failed, or nil if no
///   error occurred. If you are not interested in the error information, pass nil for this parameter.
/// - Returns: An embedding result. On failure, this method returns nil.
///
- (nullable NLContextualEmbeddingResult *)embeddingResultForString:(NSString *)string language:(nullable NLLanguage)language error:(NSError **)error;

/// The availability of the contextual embedding model assets.
///
/// The framework downloads models over-the-air, so check asset availability and download them if needed.
///
/// ```swift
/// if !embeddingModel.hasAvailableAssets {
///     let downloadResult = try await embeddingModel.requestAssets()
///     guard downloadResult == .available else {
///        print("Assets are not available locally and failed to be downloaded. Check your network connection and try again later.")
///        return
///    }
/// }
/// ```
///
typedef NS_ENUM(NSInteger, NLContextualEmbeddingAssetsResult) {
   /// A result that indicates that the assets are present on-device.
   NLContextualEmbeddingAssetsResultAvailable,
   /// A result that indicates that the assets aren't present on-device.
   NLContextualEmbeddingAssetsResultNotAvailable,
   /// A result that indicates the framework encounters an error.
   NLContextualEmbeddingAssetsResultError
} NS_SWIFT_NAME(NLContextualEmbedding.AssetsResult);

/// A Boolean value that indicates whether assets are available on-device.
@property (readonly) BOOL hasAvailableAssets;
/// Requests embedding model assets and downloads them if available.
///
/// - Parameter completionHandler: A closure that notifies your app when the asset request completes.
///
/// ## Asynchronous alternative
///
/// You can call this method from synchronous code using a completion handler, as shown on this page, or you can call it as an asynchronous method that has the following declaration:
///
/// ```swift
/// func requestAssets() async throws -> NLContextualEmbedding.AssetsResult
/// ```
///
/// For information about concurrency and asynchronous code in Swift, see <doc://com.apple.documentation/documentation/swift/calling-objective-c-apis-asynchronously>.
///
/// ## Discussion
///
/// You use a contextual embedding after loading the necessary assets onto the device. Use ``NLContextualEmbedding/hasAvailableAssets`` to determine whether assets are available.
/// This method returns immediately if the framework knows the state of the assets or if an error occurs.
- (void)requestEmbeddingAssetsWithCompletionHandler:(void (^)(NLContextualEmbeddingAssetsResult result, NSError * _Nullable error))completionHandler;

@end

/// An object that represents the embedding vector result from applying a contextual embedding to a string.
///
/// This object returns embeddings at the subword level, meaning a single word may generate multiple vectors, especially for rare or complex terms. If you need
/// to work with whole-word embeddings or create single representations for entire
/// text inputs, pool or combine subword vectors.
NS_CLASS_AVAILABLE(14_0, 17_0)
@interface NLContextualEmbeddingResult : NSObject

- (instancetype)init NS_UNAVAILABLE;

/// A copy of the input string used to generate the embedding vectors.
@property (readonly, copy) NSString *string;
/// The language that the framework identified or used when processing the input string.
@property (readonly, copy) NLLanguage language;

/// The number of embedding vectors the request generates.
@property (readonly) NSUInteger sequenceLength;

/// Iterates over the embedding vectors corresponding to the subword tokens within the specified range of the input string.
/// - Parameters:
///   - range: The range in the string to enumerate.
///   - block: A block that contains each token's embedding vector and its corresponding character range in the string.
///
/// Use this method to access the individual (subword) token embeddings. You can apply pooling or combination techniques to aggregate these subword vectors into a single representation for a word, phrase, or entire input.
///
/// Common pooling techniques include:
/// * Mean pooling to take the average of subword vectors.
/// * Max pooling for finding the element-wise maximum across tokens.
/// * Use the embeddings of the first or last subword tokens to represent the entire input.
- (void)enumerateTokenVectorsInRange:(NSRange)range usingBlock:(void (NS_NOESCAPE ^)(NSArray <NSNumber *> *tokenVector, NSRange tokenRange, BOOL *stop))block NS_REFINED_FOR_SWIFT;

/// Returns a token vector at the specified character index.
/// - Parameters:
///   - characterIndex: The index to get the token vector at.
///   - tokenRange: The character range of the token in the input string.
- (nullable NSArray <NSNumber *> *)tokenVectorAtIndex:(NSUInteger)characterIndex tokenRange:(nullable NSRangePointer)tokenRange NS_REFINED_FOR_SWIFT;

@end

NS_ASSUME_NONNULL_END
