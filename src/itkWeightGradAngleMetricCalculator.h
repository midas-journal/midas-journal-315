/*=========================================================================

  Project:   dijkstra
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkWeightGradAngleMetricCalculator.h
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
#ifndef __itkWeightGradAngleMetricCalculator_h
#define __itkWeightGradAngleMetricCalculator_h

#include "itkObject.h"
#include "itkObjectFactory.h"
#include "itkShapedNeighborhoodIterator.h"
#include "itkWeightMetricCalculator.h"
#include "itkGradientRecursiveGaussianImageFilter.h"




namespace itk
{

/** 
 */
template <class TInputImageType>            
class ITK_EXPORT WeightGradAngleMetricCalculator : public WeightMetricCalculator<TInputImageType>
{
public:
  /** Standard class typedefs. */
  typedef WeightGradAngleMetricCalculator Self;
  typedef WeightMetricCalculator<TInputImageType>  Superclass;
  typedef SmartPointer<Self>   Pointer;
  typedef SmartPointer<const Self>  ConstPointer;
  typedef itk::GradientRecursiveGaussianImageFilter <TInputImageType> itkGradientRecursiveGaussianImageFilterType;
  typedef typename itkGradientRecursiveGaussianImageFilterType::OutputImageType GradImageType;
  typedef const typename itkGradientRecursiveGaussianImageFilterType::OutputPixelType GradPixelType;
  typedef typename GradImageType::ConstPointer GradientImageConstPointer;
  typedef itk::ShapedNeighborhoodIterator< GradImageType> itkShapedNeighborhoodGradIteratorType;
  typedef typename itkShapedNeighborhoodGradIteratorType::Iterator itkShapedNeighborhoodGradIteratorforIteratorType;
  typedef typename itkShapedNeighborhoodGradIteratorType::RadiusType RadiusType;
  typedef typename itkGradientRecursiveGaussianImageFilterType::Pointer GradientRecursivePointer;

    /** Method for creation through the object factory. */

  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(WeightGradientMetricCalculator, Object);


  virtual double GetEdgeWeight (const  typename Superclass::itkShapedNeighborhoodIteratorType &it1, const typename Superclass::itkShapedNeighborhoodIteratorforIteratorType &it2);
  virtual void Initialize ();

  
 WeightGradAngleMetricCalculator();
  
  itkSetMacro (Sigma, double);	
  itkGetMacro (Sigma, double);
 void SetStartIndex (const typename TInputImageType::IndexType & StartIndex);
  void SetEndIndex(const typename TInputImageType::IndexType & EndIndex);
  


protected:
  
  virtual ~WeightGradAngleMetricCalculator() {};

  


private:
 RadiusType grad_radius;
 itkSetConstObjectMacro(GradImage,GradImageType);
 double m_Sigma;
 GradientImageConstPointer    m_GradImage;
 typename TInputImageType::IndexType  m_StartIndex, m_EndIndex;
};

} // end namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#include "itkWeightGradAngleMetricCalculator.txx"
#endif

#endif /* __itkLabels2EdgesImageCalculator_h */
