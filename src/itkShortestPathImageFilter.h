/*=========================================================================

  Project:   dijkstra
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkShortestPathImageFilter.h
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
#ifndef __itkShortestPathImageFilter_h_
#define __itkShortestPathImageFilter_h_


#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#ifdef __BORLANDC__
#define ITK_LEAN_AND_MEAN
#endif


#include "itkImageToImageFilter.h"
#include "itkWeightMetricCalculator.h"


namespace itk {

template <class TInputImageType, class TOutputImageType>
class ITK_EXPORT ShortestPathImageFilter :
    public ImageToImageFilter<TInputImageType, TOutputImageType>
{
public:

  typedef ShortestPathImageFilter			       Self;
  typedef ImageToImageFilter<TInputImageType,TOutputImageType> Superclass;
  typedef SmartPointer<Self>                                   Pointer;
  typedef SmartPointer<const Self>                             ConstPointer;
  
  	
  /**  Type of the metric. */
  typedef WeightMetricCalculator< TInputImageType >       MetricType;
  typedef typename MetricType::Pointer                MetricPointer;
  
  
  itkNewMacro(Self);

  /** Run-time type information */
  itkTypeMacro(ShortestPathImageFilter, ImageToImageFilter);

  /** Display */
  void PrintSelf( std::ostream& os, Indent indent ) const;


  typedef typename TInputImageType::PixelType PixelType;
 
  

  void SetStartIndex (const typename TInputImageType::IndexType & StartIndex);
  void SetEndIndex(const typename TInputImageType::IndexType & EndIndex);
  


  itkSetMacro (FullNeighborsMode, int);
  itkGetMacro (FullNeighborsMode, int);

  /** Set/Get the Metric. */
  itkSetObjectMacro( Metric, MetricType );
  itkGetObjectMacro( Metric, MetricType );
  void SetModeToFullNeighbors ();
  void SetModeToNonFullNeighbors ();



 



protected:

  ShortestPathImageFilter ();



  void GenerateData();

  
private:

  ShortestPathImageFilter(Self&);   // intentionally not implemented
  void operator=(const Self&);          // intentionally not implemented
  const static int BACKGROUND = 0;
  const static int FOREGROUND = 1;
  int m_FullNeighborsMode;
  MetricPointer m_Metric;
  typename TInputImageType::IndexType m_StartIndex, m_EndIndex;  //compelet set/get functions
  
  int computeNodeNum (const typename TInputImageType::SizeType &size,
		      const typename TInputImageType::IndexType &index);
  const static int EUCLID_SHORT = 0;
  const static int NON_EUCLID_SHORT = 1;
  const static int NON_FULL_NEIGHBORS = 0;
  const static int FULL_NEIGHBORS = 1;
};

} // end of namespace itk


#ifndef ITK_MANUAL_INSTANTIATION
#include "itkShortestPathImageFilter.txx"
#endif

#undef ITK_LEAN_AND_MEAN

#endif
