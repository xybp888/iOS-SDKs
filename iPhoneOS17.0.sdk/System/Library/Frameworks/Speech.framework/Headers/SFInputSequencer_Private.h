//
//  SFInputSequencer_Private.h
//  Speech
//
//  Created by Festus Ojo on 1/10/23.
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

@class SpeechAnalyzerClientInputSequencerInternal;

@interface _SFInputSequencer : NSObject
-(instancetype _Nonnull)init;
-(void)addAudio:(AVAudioPCMBuffer *_Nonnull)audioBuffer;
-(void)finishAudio;

@property (nonatomic, readonly, strong, nonnull) SpeechAnalyzerClientInputSequencerInternal *underlyingObject;
@end
