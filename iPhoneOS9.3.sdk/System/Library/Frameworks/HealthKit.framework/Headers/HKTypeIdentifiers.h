//
//  HKTypeIdentifiers
//  HealthKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*--------------------------------*/
/*   HKQuantityType Identifiers   */
/*--------------------------------*/

// Body Measurements
HK_EXTERN NSString * const HKQuantityTypeIdentifierBodyMassIndex NS_AVAILABLE_IOS(8_0);             // Scalar(Count),               Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierBodyFatPercentage NS_AVAILABLE_IOS(8_0);         // Scalar(Percent, 0.0 - 1.0),  Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierHeight NS_AVAILABLE_IOS(8_0);                    // Length,                      Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierBodyMass NS_AVAILABLE_IOS(8_0);                  // Mass,                        Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierLeanBodyMass NS_AVAILABLE_IOS(8_0);              // Mass,                        Discrete

// Fitness
HK_EXTERN NSString * const HKQuantityTypeIdentifierStepCount NS_AVAILABLE_IOS(8_0);                 // Scalar(Count),               Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDistanceWalkingRunning NS_AVAILABLE_IOS(8_0);    // Length,                      Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDistanceCycling NS_AVAILABLE_IOS(8_0);           // Length,                      Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierBasalEnergyBurned NS_AVAILABLE_IOS(8_0);         // Energy,                      Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierActiveEnergyBurned NS_AVAILABLE_IOS(8_0);        // Energy,                      Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierFlightsClimbed NS_AVAILABLE_IOS(8_0);            // Scalar(Count),               Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierNikeFuel NS_AVAILABLE_IOS(8_0);                  // Scalar(Count),               Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierAppleExerciseTime HK_AVAILABLE_IOS_WATCHOS(9_3, 2_2);    // Time                         Cumulative

// Vitals
HK_EXTERN NSString * const HKQuantityTypeIdentifierHeartRate NS_AVAILABLE_IOS(8_0);                 // Scalar(Count)/Time,          Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierBodyTemperature NS_AVAILABLE_IOS(8_0);           // Temperature,                 Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierBasalBodyTemperature NS_AVAILABLE_IOS(9_0);      // Basal Body Temperature,      Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierBloodPressureSystolic NS_AVAILABLE_IOS(8_0);     // Pressure,                    Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierBloodPressureDiastolic NS_AVAILABLE_IOS(8_0);    // Pressure,                    Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierRespiratoryRate NS_AVAILABLE_IOS(8_0);           // Scalar(Count)/Time,          Discrete

// Results
HK_EXTERN NSString * const HKQuantityTypeIdentifierOxygenSaturation NS_AVAILABLE_IOS(8_0);          // Scalar (Percent, 0.0 - 1.0,  Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierPeripheralPerfusionIndex NS_AVAILABLE_IOS(8_0);  // Scalar(Percent, 0.0 - 1.0),  Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierBloodGlucose NS_AVAILABLE_IOS(8_0);              // Mass/Volume,                 Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierNumberOfTimesFallen NS_AVAILABLE_IOS(8_0);       // Scalar(Count),               Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierElectrodermalActivity NS_AVAILABLE_IOS(8_0);     // Conductance,                 Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierInhalerUsage NS_AVAILABLE_IOS(8_0);              // Scalar(Count),               Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierBloodAlcoholContent NS_AVAILABLE_IOS(8_0);       // Scalar(Percent, 0.0 - 1.0),  Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierForcedVitalCapacity NS_AVAILABLE_IOS(8_0);       // Volume,                      Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierForcedExpiratoryVolume1 NS_AVAILABLE_IOS(8_0);   // Volume,                      Discrete
HK_EXTERN NSString * const HKQuantityTypeIdentifierPeakExpiratoryFlowRate NS_AVAILABLE_IOS(8_0);    // Volume/Time,                 Discrete

// Nutrition
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryFatTotal NS_AVAILABLE_IOS(8_0);           // Mass,   Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryFatPolyunsaturated NS_AVAILABLE_IOS(8_0); // Mass,   Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryFatMonounsaturated NS_AVAILABLE_IOS(8_0); // Mass,   Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryFatSaturated NS_AVAILABLE_IOS(8_0);       // Mass,   Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryCholesterol NS_AVAILABLE_IOS(8_0);        // Mass,   Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietarySodium NS_AVAILABLE_IOS(8_0);             // Mass,   Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryCarbohydrates NS_AVAILABLE_IOS(8_0);      // Mass,   Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryFiber NS_AVAILABLE_IOS(8_0);              // Mass,   Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietarySugar NS_AVAILABLE_IOS(8_0);              // Mass,   Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryEnergyConsumed NS_AVAILABLE_IOS(8_0);     // Energy, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryProtein NS_AVAILABLE_IOS(8_0);            // Mass,   Cumulative

HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryVitaminA NS_AVAILABLE_IOS(8_0);           // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryVitaminB6 NS_AVAILABLE_IOS(8_0);          // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryVitaminB12 NS_AVAILABLE_IOS(8_0);         // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryVitaminC NS_AVAILABLE_IOS(8_0);           // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryVitaminD NS_AVAILABLE_IOS(8_0);           // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryVitaminE NS_AVAILABLE_IOS(8_0);           // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryVitaminK NS_AVAILABLE_IOS(8_0);           // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryCalcium NS_AVAILABLE_IOS(8_0);            // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryIron NS_AVAILABLE_IOS(8_0);               // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryThiamin NS_AVAILABLE_IOS(8_0);            // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryRiboflavin NS_AVAILABLE_IOS(8_0);         // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryNiacin NS_AVAILABLE_IOS(8_0);             // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryFolate NS_AVAILABLE_IOS(8_0);             // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryBiotin NS_AVAILABLE_IOS(8_0);             // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryPantothenicAcid NS_AVAILABLE_IOS(8_0);    // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryPhosphorus NS_AVAILABLE_IOS(8_0);         // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryIodine NS_AVAILABLE_IOS(8_0);             // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryMagnesium NS_AVAILABLE_IOS(8_0);          // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryZinc NS_AVAILABLE_IOS(8_0);               // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietarySelenium NS_AVAILABLE_IOS(8_0);           // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryCopper NS_AVAILABLE_IOS(8_0);             // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryManganese NS_AVAILABLE_IOS(8_0);          // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryChromium NS_AVAILABLE_IOS(8_0);           // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryMolybdenum NS_AVAILABLE_IOS(8_0);         // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryChloride NS_AVAILABLE_IOS(8_0);           // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryPotassium NS_AVAILABLE_IOS(8_0);          // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryCaffeine NS_AVAILABLE_IOS(8_0);           // Mass, Cumulative
HK_EXTERN NSString * const HKQuantityTypeIdentifierDietaryWater NS_AVAILABLE_IOS(9_0);              // Volume, Cumulative

HK_EXTERN NSString * const HKQuantityTypeIdentifierUVExposure NS_AVAILABLE_IOS(9_0);                // Scalar (Count), Discrete

/*--------------------------------*/
/*   HKCategoryType Identifiers   */
/*--------------------------------*/

HK_EXTERN NSString * const HKCategoryTypeIdentifierSleepAnalysis NS_AVAILABLE_IOS(8_0);             // HKCategoryValueSleepAnalysis
HK_EXTERN NSString * const HKCategoryTypeIdentifierAppleStandHour NS_AVAILABLE_IOS(9_0);            // HKCategoryValueAppleStandHour
HK_EXTERN NSString * const HKCategoryTypeIdentifierCervicalMucusQuality NS_AVAILABLE_IOS(9_0);      // HKCategoryValueCervicalMucusQuality
HK_EXTERN NSString * const HKCategoryTypeIdentifierOvulationTestResult NS_AVAILABLE_IOS(9_0);       // HKCategoryValueOvulationTestResult
HK_EXTERN NSString * const HKCategoryTypeIdentifierMenstrualFlow NS_AVAILABLE_IOS(9_0);             // HKCategoryValueMenstrualFlow
HK_EXTERN NSString * const HKCategoryTypeIdentifierIntermenstrualBleeding NS_AVAILABLE_IOS(9_0);    // (Spotting) HKCategoryValue
HK_EXTERN NSString * const HKCategoryTypeIdentifierSexualActivity NS_AVAILABLE_IOS(9_0);            // HKCategoryValue


/*--------------------------------------*/
/*   HKCharacteristicType Identifiers   */
/*--------------------------------------*/

HK_EXTERN NSString * const HKCharacteristicTypeIdentifierBiologicalSex NS_AVAILABLE_IOS(8_0); // NSNumber (HKCharacteristicBiologicalSex)
HK_EXTERN NSString * const HKCharacteristicTypeIdentifierBloodType NS_AVAILABLE_IOS(8_0);     // NSNumber (HKCharacteristicBloodType)
HK_EXTERN NSString * const HKCharacteristicTypeIdentifierDateOfBirth NS_AVAILABLE_IOS(8_0);   // NSDate
HK_EXTERN NSString * const HKCharacteristicTypeIdentifierFitzpatrickSkinType NS_AVAILABLE_IOS(9_0); // HKFitzpatrickSkinType

/*-----------------------------------*/
/*   HKCorrelationType Identifiers   */
/*-----------------------------------*/

HK_EXTERN NSString * const HKCorrelationTypeIdentifierBloodPressure NS_AVAILABLE_IOS(8_0);
HK_EXTERN NSString * const HKCorrelationTypeIdentifierFood NS_AVAILABLE_IOS(8_0);

/*------------------------------*/
/*   HKWorkoutType Identifier   */
/*------------------------------*/

HK_EXTERN NSString * const HKWorkoutTypeIdentifier NS_AVAILABLE_IOS(8_0);

NS_ASSUME_NONNULL_END
