/*=========================================================================

  Project:   dijkstra
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkWeightGradAngleMetricCalculator.txx
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
#ifndef __itkWeightGradAngleMetricCalculator_txx
#define __itkWeightGradAngleMetricCalculator_txx

#include "itkWeightGradAngleMetricCalculator.h"

#include <cmath>


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace itk
{ 
    
/**
 * Constructor
 */
template<class TInputImageType>
WeightGradAngleMetricCalculator<TInputImageType>
::WeightGradAngleMetricCalculator()
{
 SetSigma (5.0); 
 
}

template <class TInputImageType>
void WeightGradAngleMetricCalculator<TInputImageType>::
SetStartIndex (const typename TInputImageType::IndexType &StartIndex)
{
	for (unsigned int i=0;i<TInputImageType::ImageDimension;++i)
	{
		m_StartIndex[i] = StartIndex[i];
	}
}

template <class TInputImageType>
void WeightGradAngleMetricCalculator<TInputImageType>::
SetEndIndex (const typename TInputImageType::IndexType &EndIndex)
{
	for (unsigned int i=0;i<TInputImageType::ImageDimension;++i)
	{
		m_EndIndex[i] = EndIndex[i];
	}

}


template<class TInputImageType>
double
WeightGradAngleMetricCalculator<TInputImageType>
::GetEdgeWeight (const typename Superclass::itkShapedNeighborhoodIteratorType &it1,const typename Superclass::itkShapedNeighborhoodIteratorforIteratorType &it2)
{
	
	typename Superclass::IndexType &index1=it1.GetIndex();
	unsigned int i = it2.GetNeighborhoodIndex();
	typename Superclass::PixelType a,b;
	a=it1.GetCenterPixel();
	b=it2.Get();
	double iDifference=(b-a)*(b-a);
	grad_radius.Fill(1);
	itkShapedNeighborhoodGradIteratorType grad_it1( grad_radius, m_GradImage, m_GradImage->GetRequestedRegion() );
	grad_it1.SetLocation(index1);
	GradPixelType a_grad=grad_it1.GetCenterPixel();
	GradPixelType b_grad=grad_it1.GetPixel (i);	
	double pSmoothness=fabs((acos((a_grad*b_grad)/(a_grad.GetNorm()*b_grad.GetNorm())) / M_PI))*10000;
	typename Superclass::PixelType startValue= this->m_Image->GetPixel(m_StartIndex);
	typename Superclass::PixelType endValue=this->m_Image->GetPixel(m_EndIndex);
	double sIDifference=((b-startValue)*(b-startValue))+((b-endValue)*(b-endValue));
	double weight=iDifference+pSmoothness+sIDifference;
	return weight;
}


template<class TInputImageType>
void WeightGradAngleMetricCalculator<TInputImageType>
::Initialize()
{
 GradientRecursivePointer grad = itkGradientRecursiveGaussianImageFilterType::New();
 grad_radius.Fill(1);
 grad->SetInput (this->m_Image);
 grad->SetSigma (m_Sigma);
 grad->Update(); 
 SetGradImage(grad->GetOutput());
}


 

} // end namespace itk

#endif
