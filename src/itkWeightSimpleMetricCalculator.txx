/*=========================================================================

  Project:   dijkstra
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkSimpleWeightMetricCalculator.txx
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
#ifndef __itkWeightSimpleMetricCalculator_txx
#define __itkWeightSimpleMetricCalculator_txx

#include "itkWeightSimpleMetricCalculator.h"


namespace itk
{ 
    
/**
 * Constructor
 */
template<class TInputImageType>
WeightSimpleMetricCalculator<TInputImageType>
::WeightSimpleMetricCalculator()
{
  
 
}



template<class TInputImageType>
double
WeightSimpleMetricCalculator<TInputImageType>
::GetEdgeWeight (const typename Superclass::itkShapedNeighborhoodIteratorType &it1,const typename Superclass::itkShapedNeighborhoodIteratorforIteratorType &it2)
{

	double a,b;
	a=it1.GetCenterPixel();
	b=it2.Get();
	return (b-a)*(b-a);
	

}


template<class TInputImageType>
void WeightSimpleMetricCalculator<TInputImageType>
::Initialize()
{
  
 
}


 

} // end namespace itk

#endif
