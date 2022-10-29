//
//  MPSGraphOptimizerOps.h
//  MetalPerformanceShadersGraph
//
//  Created on 2/4/20.
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#ifndef MPSGraphOptimizerOps_h
#define MPSGraphOptimizerOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

MPS_CLASS_AVAILABLE_STARTING(macos(11.0), ios(14.0), tvos(14.0))
@interface MPSGraph(MPSGraphOptimizerOps)

/*!
 *  @abstract      StochasticGradientDescent
 *  @discussion The StochasticGradientDescent performs a gradient descent
 *
 *              variable = variable - (learningRate * g)
 *
 *              where,
 *                g    is gradient of error wrt variable
 *
 */
-(MPSGraphTensor *) stochasticGradientDescentWithLearningRateTensor:(MPSGraphTensor *) learningRateTensor
                                                       valuesTensor:(MPSGraphTensor *) valuesTensor
                                                     gradientTensor:(MPSGraphTensor *) gradientTensor
                                                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( stochasticGradientDescent(learningRate:values:gradient:name:) );

-(MPSGraphOperation *) applyStochasticGradientDescentWithLearningRateTensor:(MPSGraphTensor *) learningRateTensor
                                                                   variable:(MPSGraphVariableOp *) variable
                                                             gradientTensor:(MPSGraphTensor *) gradientTensor
                                                                       name:(NSString * _Nullable) name
MPS_SWIFT_NAME( applyStochasticGradientDescent(learningRate:variable:gradient:name:) );

/*!
 *  @abstract      Adam
 *  @discussion    The adam update ops are added
 *
 *              current learning rate:
 *              lr[t] = learningRate * sqrt(1 - beta2^t) / (1 - beta1^t)
 *
 *              m[t]     = beta1 * m[t-1] + (1 - beta1) * g
 *              v[t]     = beta2 * v[t-1] + (1 - beta2) * (g ^ 2)
 *              maxVel[t] = max(maxVel[t-1],v[t])
 *              variable = variable - lr[t] * m[t] / (sqrt(maxVel) + epsilon)
 *  @return     if maximumVelocity is nil array of 3 tensors (update, newMomentum, newVelocity) else array of 4 tensors (update, newMomentum, newVelocity, newMaximumVelocity)
 */
-(NSArray<MPSGraphTensor *> *) adamWithLearningRateTensor:(MPSGraphTensor *) learningRateTensor
                                              beta1Tensor:(MPSGraphTensor *) beta1Tensor
                                              beta2Tensor:(MPSGraphTensor *) beta2Tensor
                                            epsilonTensor:(MPSGraphTensor *) epsilonTensor
                                         beta1PowerTensor:(MPSGraphTensor *) beta1PowerTensor
                                         beta2PowerTensor:(MPSGraphTensor *) beta2PowerTensor
                                             valuesTensor:(MPSGraphTensor *) valuesTensor
                                           momentumTensor:(MPSGraphTensor *) momentumTensor
                                           velocityTensor:(MPSGraphTensor *) velocityTensor
                                    maximumVelocityTensor:(MPSGraphTensor * _Nullable) maximumVelocityTensor
                                           gradientTensor:(MPSGraphTensor *) gradientTensor
                                                     name:(NSString * _Nullable) name
MPS_SWIFT_NAME( adam(learningRate:beta1:beta2:epsilon:beta1Power:beta2Power:values:momentum:velocity:maximumVelocity:gradient:name:) );


/*!
 *  @abstract      Adam
 *  @discussion    The adam update ops are added
 *
 *              m[t]     = beta1 * m[t-1] + (1 - beta1) * g
 *              v[t]     = beta2 * v[t-1] + (1 - beta2) * (g ^ 2)
 *              maxVel[t] = max(maxVel[t-1],v[t])
 *              variable = variable - lr[t] * m[t] / (sqrt(maxVel) + epsilon)
 *  @return     if maximumVelocity is nil array of 3 tensors (update, newMomentum, newVelocity) else array of 4 tensors (update, newMomentum, newVelocity, newMaximumVelocity)
 */
-(NSArray<MPSGraphTensor *> *) adamWithCurrentLearningRateTensor:(MPSGraphTensor *) currentLearningRateTensor
                                                     beta1Tensor:(MPSGraphTensor *) beta1Tensor
                                                     beta2Tensor:(MPSGraphTensor *) beta2Tensor
                                                   epsilonTensor:(MPSGraphTensor *) epsilonTensor
                                                    valuesTensor:(MPSGraphTensor *) valuesTensor
                                                  momentumTensor:(MPSGraphTensor *) momentumTensor
                                                  velocityTensor:(MPSGraphTensor *) velocityTensor
                                           maximumVelocityTensor:(MPSGraphTensor * _Nullable) maximumVelocityTensor
                                                  gradientTensor:(MPSGraphTensor *) gradientTensor
                                                            name:(NSString * _Nullable) name
MPS_SWIFT_NAME( adam(currentLearningRate:beta1:beta2:epsilon:values:momentum:velocity:maximumVelocity:gradient:name:) );

@end

NS_ASSUME_NONNULL_END


#endif /* MPSGraphOptimizerOps_h */
