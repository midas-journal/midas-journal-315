/*=========================================================================

  Project:   dijkstra
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkSimpleWeightMetricCalculator.h
  Language:  C++
  Date:      26/1/2009
  Version:   1.0
  Authors:   Lior Weizman & Moti Freiman

  Portions of this code are covered under the ITK and VTK copyright.
  See VTKCopyright.txt or http://www.kitware.com/VTKCopyright.htm for details.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkWeightSimpleMetricCalculator_h
#define __itkWeightSimpleMetricCalculator_h

#include "itkObject.h"
#include "itkObjectFactory.h"
#include "itkShapedNeighborhoodIterator.h"
#include "itkWeightMetricCalculator.h"





namespace itk
{

/** 
 */
template <class TInputImageType>            
class ITK_EXPORT WeightSimpleMetricCalculator : public WeightMetricCalculator<TInputImageType>
{
public:
  /** Standard class typedefs. */
  typedef WeightSimpleMetricCalculator Self;
  typedef WeightMetricCalculator  <TInputImageType> Superclass;
  typedef SmartPointer<Self>   Pointer;
  typedef SmartPointer<const Self>  ConstPointer;
    /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(WeightSimpleMetricCalculator, Object);


  virtual double GetEdgeWeight (const typename Superclass::itkShapedNeighborhoodIteratorType &it1,const typename Superclass::itkShapedNeighborhoodIteratorforIteratorType &it2);
  virtual void Initialize ();
//  WeightSimpleMetricCalculator();
  
 WeightSimpleMetricCalculator();
  


protected:
  
  virtual ~WeightSimpleMetricCalculator() {};

  


private:

  
  
 
};

} // end namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#include "itkWeightSimpleMetricCalculator.txx"
#endif

#endif /* __itkLabels2EdgesImageCalculator_h */
