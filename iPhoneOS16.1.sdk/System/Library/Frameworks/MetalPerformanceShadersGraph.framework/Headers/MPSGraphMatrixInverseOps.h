//
//  MPSGraphInverseOps.h
//  MPSGraph
//
//  Created on 8/2/22.
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#ifndef MPSGraphInverseOps_h
#define MPSGraphInverseOps_h

#import <MetalPerformanceShadersGraph/MPSGraph.h>

NS_ASSUME_NONNULL_BEGIN

@interface MPSGraph(MPSGraphMatrixInverseOps)

/*!
 *  @abstract   Create  Matrix inverse op and return the result tensor
 *  @discussion Find the inverse of a square matrix by calling LU decomposition and solver
 *              The op computes inverse for all batches If the input tensor has more than
 *              2 dimensions. Results are undefined for ill conditioned matrices.
 *
 *  @param      inputTensor          input tensor to inverse op
 *  @param      name                          name for the operation
 *
 *  @return     A valid MPSGraphTensor object.
 */
-(MPSGraphTensor *) inverseOfTensor:(MPSGraphTensor *) inputTensor
                               name:(NSString * _Nullable) name
MPS_SWIFT_NAME( inverse(input:name:) )
MPS_CLASS_AVAILABLE_STARTING(macos(13.0), ios(16.1), tvos(16.1));

@end


NS_ASSUME_NONNULL_END


#endif /* MPSGraphInverseOps_h */
