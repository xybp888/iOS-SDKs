//
//  HKTypeIdentifiers
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKDefines.h>
#import <objc/NSObjCRuntime.h>

NS_ASSUME_NONNULL_BEGIN

/*--------------------------------*/
/*   HKQuantityType Identifiers   */
/*--------------------------------*/

typedef NSString * HKQuantityTypeIdentifier NS_STRING_ENUM;

// Body Measurements
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBodyMassIndex HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);             // Scalar(Count),               Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBodyFatPercentage HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);         // Scalar(Percent, 0.0 - 1.0),  Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierHeight HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);                    // Length,                      Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBodyMass HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);                  // Mass,                        Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierLeanBodyMass HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);              // Mass,                        Discrete

// Fitness
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierStepCount HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);                 // Scalar(Count),               Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDistanceWalkingRunning HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);    // Length,                      Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDistanceCycling HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);           // Length,                      Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDistanceWheelchair HK_AVAILABLE_IOS_WATCHOS(10_0, 3_0);       // Length,               Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBasalEnergyBurned HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);         // Energy,                      Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierActiveEnergyBurned HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);        // Energy,                      Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierFlightsClimbed HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);            // Scalar(Count),               Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierNikeFuel HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);                  // Scalar(Count),               Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierAppleExerciseTime HK_AVAILABLE_IOS_WATCHOS(9_3, 2_2);         // Time                         Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierPushCount HK_AVAILABLE_IOS_WATCHOS(10_0, 3_0);                // Scalar(Count),               Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDistanceSwimming HK_AVAILABLE_IOS_WATCHOS(10_0, 3_0);         // Length,                      Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierSwimmingStrokeCount HK_AVAILABLE_IOS_WATCHOS(10_0, 3_0);      // Scalar(Count),               Cumulative

// Vitals
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierHeartRate HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);                 // Scalar(Count)/Time,          Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBodyTemperature HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);           // Temperature,                 Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBasalBodyTemperature HK_AVAILABLE_IOS_WATCHOS(9_0, 2_0);                   // Basal Body Temperature,      Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBloodPressureSystolic HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);     // Pressure,                    Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBloodPressureDiastolic HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);    // Pressure,                    Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierRespiratoryRate HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);           // Scalar(Count)/Time,          Discrete

// Results
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierOxygenSaturation HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);          // Scalar (Percent, 0.0 - 1.0,  Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierPeripheralPerfusionIndex HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);  // Scalar(Percent, 0.0 - 1.0),  Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBloodGlucose HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);              // Mass/Volume,                 Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierNumberOfTimesFallen HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);       // Scalar(Count),               Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierElectrodermalActivity HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);     // Conductance,                 Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierInhalerUsage HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);              // Scalar(Count),               Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierBloodAlcoholContent HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);       // Scalar(Percent, 0.0 - 1.0),  Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierForcedVitalCapacity HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);       // Volume,                      Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierForcedExpiratoryVolume1 HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);   // Volume,                      Discrete
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierPeakExpiratoryFlowRate HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);    // Volume/Time,                 Discrete

// Nutrition
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryFatTotal HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);           // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryFatPolyunsaturated HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0); // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryFatMonounsaturated HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0); // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryFatSaturated HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);       // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryCholesterol HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);        // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietarySodium HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);             // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryCarbohydrates HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);      // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryFiber HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);              // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietarySugar HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);              // Mass,   Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryEnergyConsumed HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);     // Energy, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryProtein HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);            // Mass,   Cumulative

HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminA HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);           // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminB6 HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);          // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminB12 HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);         // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminC HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);           // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminD HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);           // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminE HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);           // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryVitaminK HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);           // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryCalcium HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);            // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryIron HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);               // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryThiamin HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);            // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryRiboflavin HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);         // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryNiacin HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);             // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryFolate HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);             // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryBiotin HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);             // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryPantothenicAcid HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);    // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryPhosphorus HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);         // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryIodine HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);             // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryMagnesium HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);          // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryZinc HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);               // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietarySelenium HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);           // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryCopper HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);             // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryManganese HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);          // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryChromium HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);           // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryMolybdenum HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);         // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryChloride HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);           // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryPotassium HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);          // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryCaffeine HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);           // Mass, Cumulative
HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierDietaryWater HK_AVAILABLE_IOS_WATCHOS(9_0, 2_0);              // Volume, Cumulative

HK_EXTERN HKQuantityTypeIdentifier const HKQuantityTypeIdentifierUVExposure HK_AVAILABLE_IOS_WATCHOS(9_0, 2_0);                // Scalar (Count), Discrete

/*--------------------------------*/
/*   HKCategoryType Identifiers   */
/*--------------------------------*/

typedef NSString * HKCategoryTypeIdentifier NS_STRING_ENUM;

HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierSleepAnalysis HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);             // HKCategoryValueSleepAnalysis
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierAppleStandHour HK_AVAILABLE_IOS_WATCHOS(9_0, 2_0);            // HKCategoryValueAppleStandHour
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierCervicalMucusQuality HK_AVAILABLE_IOS_WATCHOS(9_0, 2_0);      // HKCategoryValueCervicalMucusQuality
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierOvulationTestResult HK_AVAILABLE_IOS_WATCHOS(9_0, 2_0);       // HKCategoryValueOvulationTestResult
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierMenstrualFlow HK_AVAILABLE_IOS_WATCHOS(9_0, 2_0);             // HKCategoryValueMenstrualFlow
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierIntermenstrualBleeding HK_AVAILABLE_IOS_WATCHOS(9_0, 2_0);    // (Spotting) HKCategoryValue
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierSexualActivity HK_AVAILABLE_IOS_WATCHOS(9_0, 2_0);            // HKCategoryValue
HK_EXTERN HKCategoryTypeIdentifier const HKCategoryTypeIdentifierMindfulSession HK_AVAILABLE_IOS_WATCHOS(10_0, 3_0);           // HKCategoryValue

/*--------------------------------------*/
/*   HKCharacteristicType Identifiers   */
/*--------------------------------------*/

typedef NSString * HKCharacteristicTypeIdentifier NS_STRING_ENUM;

HK_EXTERN HKCharacteristicTypeIdentifier const HKCharacteristicTypeIdentifierBiologicalSex HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);          // HKBiologicalSexObject
HK_EXTERN HKCharacteristicTypeIdentifier const HKCharacteristicTypeIdentifierBloodType HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);              // HKBloodTypeObject
HK_EXTERN HKCharacteristicTypeIdentifier const HKCharacteristicTypeIdentifierDateOfBirth HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);            // NSDateComponents
HK_EXTERN HKCharacteristicTypeIdentifier const HKCharacteristicTypeIdentifierFitzpatrickSkinType HK_AVAILABLE_IOS_WATCHOS(9_0, 2_0);    // HKFitzpatrickSkinTypeObject
HK_EXTERN HKCharacteristicTypeIdentifier const HKCharacteristicTypeIdentifierWheelchairUse HK_AVAILABLE_IOS_WATCHOS(10_0, 3_0);         // HKWheelchairUseObject

/*-----------------------------------*/
/*   HKCorrelationType Identifiers   */
/*-----------------------------------*/

typedef NSString * HKCorrelationTypeIdentifier NS_STRING_ENUM;

HK_EXTERN HKCorrelationTypeIdentifier const HKCorrelationTypeIdentifierBloodPressure HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);
HK_EXTERN HKCorrelationTypeIdentifier const HKCorrelationTypeIdentifierFood HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);

/*--------------------------------*/
/*   HKDocumentType Identifiers   */
/*--------------------------------*/

typedef NSString * HKDocumentTypeIdentifier NS_STRING_ENUM;

HK_EXTERN HKDocumentTypeIdentifier const HKDocumentTypeIdentifierCDA HK_AVAILABLE_IOS_WATCHOS(10_0, 3_0);

/*------------------------------*/
/*   HKWorkoutType Identifier   */
/*------------------------------*/

HK_EXTERN NSString * const HKWorkoutTypeIdentifier HK_AVAILABLE_IOS_WATCHOS(8_0, 2_0);

NS_ASSUME_NONNULL_END
