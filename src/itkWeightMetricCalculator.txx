/*=========================================================================

  Project:   dijkstra
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkWeightMetricCalculator.txx
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
#ifndef __itkWeightMetricCalculator_txx
#define __itkWeightMetricCalculator_txx

#include "itkWeightMetricCalculator.h"


namespace itk
{ 
    
/**
 * Constructor
 */
template<class TInputImageType>
WeightMetricCalculator<TInputImageType>
::WeightMetricCalculator()
{
  
 
}







 
template<class TInputImageType>
void
WeightMetricCalculator<TInputImageType>
::PrintSelf( std::ostream& os, Indent indent ) const
{
  Superclass::PrintSelf(os,indent);

  
  
  
}

} // end namespace itk

#endif
