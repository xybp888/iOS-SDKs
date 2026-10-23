//
//  HKWorkoutActivityType.h
//  HealthKit
//
//  Copyright © 2014-2026 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <HealthKit/HKDefines.h>



NS_ASSUME_NONNULL_BEGIN

/**
 @enum          HKWorkoutActivityType
 @abstract      Represents a particular type of workout or exercise

 @constant      HKWorkoutActivityTypeBoxing                         See also HKWorkoutActivityTypeKickboxing.
 @constant      HKWorkoutActivityTypeCrossTraining                  Any mix of cardio and/or strength training. See also
                                                                    HKWorkoutActivityTypeCoreTraining and
                                                                    HKWorkoutActivityTypeFlexibility.
 @constant      HKWorkoutActivityTypeDance                          This enum remains available to access older data.
 @constant      HKWorkoutActivityTypeDanceInspiredTraining          This enum remains available to access older data.
 @constant      HKWorkoutActivityTypeEquestrianSports               Polo, Horse Racing, Horse Riding, etc.
 @constant      HKWorkoutActivityTypeFunctionalStrengthTraining     Primarily free weights and/or body weight and/or
                                                                    accessories
 @constant      HKWorkoutActivityTypeHockey                         Ice Hockey, Field Hockey, etc.
 @constant      HKWorkoutActivityTypeMindAndBody                    Qigong, meditation, etc.
 @constant      HKWorkoutActivityTypeMixedMetabolicCardioTraining   This enum remains available to access older data.
 @constant      HKWorkoutActivityTypePaddleSports                   Canoeing, Kayaking, Outrigger, Stand Up Paddle
                                                                    Board, etc.
 @constant      HKWorkoutActivityTypePlay                           Dodge Ball, Hopscotch, Tetherball, Jungle Gym, etc.
 @constant      HKWorkoutActivityTypePreparationAndRecovery         Therapeutic activities like foam rolling, self
                                                                    massage and flexibility moves.
 @constant      HKWorkoutActivityTypeSkatingSports                  Ice Skating, Speed Skating, Inline Skating,
                                                                    Skateboarding, etc.
 @constant      HKWorkoutActivityTypeSnowSports                     Sledding, Snowmobiling, Building a Snowman, etc. See
                                                                    also HKWorkoutActivityTypeCrossCountrySkiing,
                                                                    HKWorkoutActivityTypeSnowboarding, and
                                                                    HKWorkoutActivityTypeDownhillSkiing.
 @constant      HKWorkoutActivityTypeStairClimbing                  See also HKWorkoutActivityTypeStairs and
                                                                    HKWorkoutActivityTypeStepTraining.
 @constant      HKWorkoutActivityTypeSurfingSports                  Traditional Surfing, Kite Surfing, Wind Surfing,
                                                                    etc.
 @constant      HKWorkoutActivityTypeTrackAndField                  Shot Put, Javelin, Pole Vaulting, etc.
 @constant      HKWorkoutActivityTypeTraditionalStrengthTraining    Primarily machines and/or free weights
 @constant      HKWorkoutActivityTypeWaterSports                    Water Skiing, Wake Boarding, etc.
 @constant      HKWorkoutActivityTypeBarre                          HKWorkoutActivityTypeDanceInspiredTraining
 @constant      HKWorkoutActivityTypePilates                        HKWorkoutActivityTypeDanceInspiredTraining
 @constant      HKWorkoutActivityTypeMixedCardio                    HKWorkoutActivityTypeMixedMetabolicCardioTraining
 @constant      HKWorkoutActivityTypeSocialDance                    Dances done in social settings like swing, salsa and
                                                                    folk dances from different world regions.
 @constant      HKWorkoutActivityTypeCooldown                       Low intensity stretching and mobility exercises
                                                                    following a more vigorous workout type
 */
typedef NS_ENUM(NSUInteger, HKWorkoutActivityType) {
    HKWorkoutActivityTypeAmericanFootball = 1,
    HKWorkoutActivityTypeArchery = 2,
    HKWorkoutActivityTypeAustralianFootball = 3,
    HKWorkoutActivityTypeBadminton = 4,
    HKWorkoutActivityTypeBaseball = 5,
    HKWorkoutActivityTypeBasketball = 6,
    HKWorkoutActivityTypeBowling = 7,
    HKWorkoutActivityTypeBoxing = 8,
    HKWorkoutActivityTypeClimbing = 9,
    HKWorkoutActivityTypeCricket = 10,
    HKWorkoutActivityTypeCrossTraining = 11,
    HKWorkoutActivityTypeCurling = 12,
    HKWorkoutActivityTypeCycling = 13,
    HKWorkoutActivityTypeDance API_DEPRECATED_WITH_REPLACEMENT("Use HKWorkoutActivityTypeSocialDance or HKWorkoutActivityTypeCardioDance", ios(8.0, 14.0), watchos(2.0, 7.0)) = 14,
    HKWorkoutActivityTypeDanceInspiredTraining API_DEPRECATED_WITH_REPLACEMENT("Use HKWorkoutActivityTypeSocialDance, HKWorkoutActivityTypeCardioDance, HKWorkoutActivityTypeBarre or HKWorkoutActivityTypePilates", ios(8.0, 10.0), watchos(2.0, 3.0)) = 15,
    HKWorkoutActivityTypeElliptical = 16,
    HKWorkoutActivityTypeEquestrianSports = 17,
    HKWorkoutActivityTypeFencing = 18,
    HKWorkoutActivityTypeFishing = 19,
    HKWorkoutActivityTypeFunctionalStrengthTraining = 20,
    HKWorkoutActivityTypeGolf = 21,
    HKWorkoutActivityTypeGymnastics = 22,
    HKWorkoutActivityTypeHandball = 23,
    HKWorkoutActivityTypeHiking = 24,
    HKWorkoutActivityTypeHockey = 25,
    HKWorkoutActivityTypeHunting = 26,
    HKWorkoutActivityTypeLacrosse = 27,
    HKWorkoutActivityTypeMartialArts = 28,
    HKWorkoutActivityTypeMindAndBody = 29,
    HKWorkoutActivityTypeMixedMetabolicCardioTraining API_DEPRECATED_WITH_REPLACEMENT("Use HKWorkoutActivityTypeMixedCardio or HKWorkoutActivityTypeHighIntensityIntervalTraining", ios(8.0, 11.0), watchos(2.0, 4.0)) = 30,
    HKWorkoutActivityTypePaddleSports = 31,
    HKWorkoutActivityTypePlay = 32,
    HKWorkoutActivityTypePreparationAndRecovery = 33,
    HKWorkoutActivityTypeRacquetball = 34,
    HKWorkoutActivityTypeRowing = 35,
    HKWorkoutActivityTypeRugby = 36,
    HKWorkoutActivityTypeRunning = 37,
    HKWorkoutActivityTypeSailing = 38,
    HKWorkoutActivityTypeSkatingSports = 39,
    HKWorkoutActivityTypeSnowSports = 40,
    HKWorkoutActivityTypeSoccer = 41,
    HKWorkoutActivityTypeSoftball = 42,
    HKWorkoutActivityTypeSquash = 43,
    HKWorkoutActivityTypeStairClimbing = 44,
    HKWorkoutActivityTypeSurfingSports = 45,
    HKWorkoutActivityTypeSwimming = 46,
    HKWorkoutActivityTypeTableTennis = 47,
    HKWorkoutActivityTypeTennis = 48,
    HKWorkoutActivityTypeTrackAndField = 49,
    HKWorkoutActivityTypeTraditionalStrengthTraining = 50,
    HKWorkoutActivityTypeVolleyball = 51,
    HKWorkoutActivityTypeWalking = 52,
    HKWorkoutActivityTypeWaterFitness = 53,
    HKWorkoutActivityTypeWaterPolo = 54,
    HKWorkoutActivityTypeWaterSports = 55,
    HKWorkoutActivityTypeWrestling = 56,
    HKWorkoutActivityTypeYoga = 57,
    HKWorkoutActivityTypeBarre API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0)) = 58,
    HKWorkoutActivityTypeCoreTraining API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0)) = 59,
    HKWorkoutActivityTypeCrossCountrySkiing API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0)) = 60,
    HKWorkoutActivityTypeDownhillSkiing API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0)) = 61,
    HKWorkoutActivityTypeFlexibility API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0)) = 62,
    HKWorkoutActivityTypeHighIntensityIntervalTraining API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0)) = 63,
    HKWorkoutActivityTypeJumpRope API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0)) = 64,
    HKWorkoutActivityTypeKickboxing API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0)) = 65,
    HKWorkoutActivityTypePilates API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0)) = 66,
    HKWorkoutActivityTypeSnowboarding API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0)) = 67,
    HKWorkoutActivityTypeStairs API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0)) = 68,
    HKWorkoutActivityTypeStepTraining API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0)) = 69,
    HKWorkoutActivityTypeWheelchairWalkPace API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0)) = 70,
    HKWorkoutActivityTypeWheelchairRunPace API_AVAILABLE(ios(10.0), watchos(3.0), macCatalyst(13.0), macos(13.0)) = 71,
    HKWorkoutActivityTypeTaiChi API_AVAILABLE(ios(11.0), watchos(4.0), macCatalyst(13.0), macos(13.0)) = 72,
    HKWorkoutActivityTypeMixedCardio API_AVAILABLE(ios(11.0), watchos(4.0), macCatalyst(13.0), macos(13.0)) = 73,
    HKWorkoutActivityTypeHandCycling API_AVAILABLE(ios(11.0), watchos(4.0), macCatalyst(13.0), macos(13.0)) = 74,
    HKWorkoutActivityTypeDiscSports API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0)) = 75,
    HKWorkoutActivityTypeFitnessGaming API_AVAILABLE(ios(13.0), watchos(6.0), macCatalyst(13.0), macos(13.0)) = 76,
    HKWorkoutActivityTypeCardioDance API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0)) = 77,
    HKWorkoutActivityTypeSocialDance API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0)) = 78,
    HKWorkoutActivityTypePickleball API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0)) = 79,
    HKWorkoutActivityTypeCooldown API_AVAILABLE(ios(14.0), watchos(7.0), macCatalyst(14.0), macos(13.0)) = 80,
    HKWorkoutActivityTypeSwimBikeRun API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0)) = 82,
    HKWorkoutActivityTypeTransition API_AVAILABLE(ios(16.0), watchos(9.0), macCatalyst(16.0), macos(13.0)) = 83,
    HKWorkoutActivityTypeUnderwaterDiving API_AVAILABLE(ios(17.0), watchos(10.0), macCatalyst(17.0), macos(14.0)) = 84,
    HKWorkoutActivityTypeRest API_UNAVAILABLE(ios, watchos, macCatalyst, macos) = 2998,
    HKWorkoutActivityTypeGroup API_UNAVAILABLE(ios, watchos, macCatalyst, macos) = 2999,
    HKWorkoutActivityTypeOther = 3000,
} API_AVAILABLE(ios(8.0), watchos(2.0), macCatalyst(13.0), macos(13.0));

NS_ASSUME_NONNULL_END
