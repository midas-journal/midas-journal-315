/*=========================================================================

  Project:   dijkstra
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkWeightMetricCalculator.h
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
#ifndef __itkWeightMetricCalculator_h
#define __itkWeightMetricCalculator_h

#include "itkObject.h"
#include "itkObjectFactory.h"
#include "itkShapedNeighborhoodIterator.h"






namespace itk
{


template <class TInputImageType>            
class ITK_EXPORT WeightMetricCalculator : public Object 
{
public:
  /** Standard class typedefs. */
  typedef WeightMetricCalculator Self;
  typedef Object  Superclass;
  typedef SmartPointer<Self>   Pointer;
  typedef SmartPointer<const Self>  ConstPointer;
  typedef ShapedNeighborhoodIterator< TInputImageType > itkShapedNeighborhoodIteratorType;
  

  /** Run-time type information (and related methods). */
  itkTypeMacro(WeightMetricCalculator, Object);

  /** Type definition for the input image. */
  typedef TInputImageType  ImageType;

  /** Pointer type for the image. */
  typedef typename TInputImageType::Pointer  ImagePointer;
  
  /** Const Pointer type for the image. */
  typedef typename TInputImageType::ConstPointer ImageConstPointer;

  /** Type definition for the input image pixel type. */
  typedef typename TInputImageType::PixelType PixelType;

   
  /** Type definition for the input image index type. */
  typedef const typename TInputImageType::IndexType IndexType;
  typedef typename ShapedNeighborhoodIterator< TInputImageType >::Iterator itkShapedNeighborhoodIteratorforIteratorType;
 
  /** Set the input image. */
  itkSetConstObjectMacro(Image,ImageType);

  virtual double GetEdgeWeight (const itkShapedNeighborhoodIteratorType &it1,const itkShapedNeighborhoodIteratorforIteratorType &it2) = 0;
  virtual void Initialize () = 0;
  WeightMetricCalculator();
  


protected:
  
  virtual ~WeightMetricCalculator() {};
  void PrintSelf(std::ostream& os, Indent indent) const;
  ImageConstPointer    m_Image;
private:
  
  WeightMetricCalculator(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented
  
  
 
};

} // end namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#include "itkWeightMetricCalculator.txx"
#endif

#endif /* __itkLabels2EdgesImageCalculator_h */
