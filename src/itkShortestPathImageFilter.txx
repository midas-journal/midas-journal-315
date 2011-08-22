/*=========================================================================

  Project:   dijkstra
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkShortestPathImageFilter.txx
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

=========================================================================*///boost includes
#include <climits>
#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

#include <vector>
#include <cmath>

#include "itkImageRegionConstIteratorWithIndex.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkCastImageFilter.h"
#include "itkConstNeighborhoodIterator.h"
#include "itkShapedNeighborhoodIterator.h"

using namespace boost;


namespace itk 
{


template <class TInputImageType, class TOutputImageType>
int ShortestPathImageFilter<TInputImageType, TOutputImageType>::
computeNodeNum (const typename TInputImageType::SizeType &size,
		const typename TInputImageType::IndexType &index)
{
	int temp_val;
	int res=0;
	int dim=TInputImageType::ImageDimension;
	for (int k=0; k<dim;++k)
 	{
		temp_val=1;
		for (int l=0;l<k;++l)
		{
			temp_val=temp_val*size[l];
		}
		temp_val=temp_val*index[k];
		res=res+temp_val;
	}
	return res;
}
			
				 


template <class TInputImageType, class TOutputImageType>
void ShortestPathImageFilter<TInputImageType, TOutputImageType>
::SetModeToFullNeighbors ()
{

	m_FullNeighborsMode = ShortestPathImageFilter<TInputImageType, TOutputImageType>::FULL_NEIGHBORS;
}

template <class TInputImageType, class TOutputImageType>
void ShortestPathImageFilter<TInputImageType, TOutputImageType>
::SetModeToNonFullNeighbors ()
{

	m_FullNeighborsMode = ShortestPathImageFilter<TInputImageType, TOutputImageType>::NON_FULL_NEIGHBORS;
}


template <class TInputImageType, class TOutputImageType>
ShortestPathImageFilter<TInputImageType, TOutputImageType>
::ShortestPathImageFilter() :
m_FullNeighborsMode(ShortestPathImageFilter<TInputImageType, TOutputImageType>::NON_FULL_NEIGHBORS)
{

  

} 
template <class TInputImageType, class TOutputImageType>
void ShortestPathImageFilter<TInputImageType, TOutputImageType>::
SetStartIndex (const typename TInputImageType::IndexType &StartIndex)
{
	for (unsigned int i=0;i<TInputImageType::ImageDimension;++i)
	{
		m_StartIndex[i] = StartIndex[i];
	}
}

template <class TInputImageType, class TOutputImageType>
void ShortestPathImageFilter<TInputImageType, TOutputImageType>::
SetEndIndex (const typename TInputImageType::IndexType &EndIndex)
{
	for (unsigned int i=0;i<TInputImageType::ImageDimension;++i)
	{
		m_EndIndex[i] = EndIndex[i];
	}

}



template <class TInputImageType, class TOutputImageType>
void
ShortestPathImageFilter<TInputImageType, TOutputImageType>::
GenerateData()
{
	
	const int dim=TInputImageType::ImageDimension;
	
	//check for n-d
	const typename TInputImageType::SizeType &size = this->GetInput()->GetRequestedRegion().GetSize();
	int nodesNum=1;
	for (int i=0;i<dim;++i)
	{
		nodesNum=nodesNum*size[i];		
	}
	
	int edgesNum;
        if (m_FullNeighborsMode == ShortestPathImageFilter<TInputImageType, TOutputImageType>::FULL_NEIGHBORS) 
        {
		edgesNum = nodesNum*((int) pow((double) 3.0,dim));
        }
	else
        {
		edgesNum = nodesNum*(2*dim);
	}

	
	// boost code
	typedef adjacency_list < vecS, vecS, undirectedS, no_property, property < edge_weight_t, double > > graph_t;
	typedef graph_traits < graph_t >::vertex_descriptor vertex_descriptor;
	typedef graph_traits < graph_t >::edge_descriptor edge_descriptor;
	typedef std::pair<int, int> Edge;

	
	graph_t g(nodesNum);
	std::vector <Edge> edgeVec (edgesNum);

	property_map<graph_t, edge_weight_t>::type weightmap = get (edge_weight, g);

	typedef itk::ShapedNeighborhoodIterator< TInputImageType > itkShapedNeighborhoodIteratorType;
	typename itkShapedNeighborhoodIteratorType::RadiusType radius;
	radius.Fill(1);
	itkShapedNeighborhoodIteratorType it( radius, this->GetInput(), this->GetInput()->GetRequestedRegion() );
	
	
	
	//build graph
	int curNodeNum,toNodeNum;
	int startNodeNum=computeNodeNum(size,m_StartIndex);
	int endNodeNum=computeNodeNum(size,m_EndIndex);
	
	
	typename TInputImageType::PixelType dstValue;
	double sum_s = 0, s_sum = 0, std_val = 0;
	
	it.GoToBegin();
	unsigned int centerIndex = it.GetCenterNeighborhoodIndex();
	typename ShapedNeighborhoodIterator<TInputImageType>::OffsetType offset;
		
	if (m_FullNeighborsMode == ShortestPathImageFilter<TInputImageType, TOutputImageType>::FULL_NEIGHBORS)
	{
		for (unsigned int d=0; d < 2*centerIndex + 1; d++)
		{
			offset = it.GetOffset(d);
			it.ActivateOffset(offset);
		}
	}
	else
	{		
		for (int d=0; d<dim; d++)
		{
			offset = it.GetOffset(centerIndex+(int)pow((double)3.0,d));
			it.ActivateOffset(offset);
			offset = it.GetOffset(centerIndex-(int)pow((double)3.0,d));
			it.ActivateOffset(offset);
		}		
	}				
					
	for (it.GoToBegin(); !it.IsAtEnd(); ++it)
	{
		
		const typename TInputImageType::IndexType &index = it.GetIndex ();
		curNodeNum=computeNodeNum(size,index);
		
		
		
		
		sum_s = 0, s_sum = 0, std_val = 0;
		
		it.DeactivateOffset(it.GetOffset(centerIndex));
		 
		typename ShapedNeighborhoodIterator<TInputImageType>::Iterator org_local_it;
		for( org_local_it = it.Begin(); !org_local_it.IsAtEnd(); ++org_local_it)
		{
			unsigned int i = org_local_it.GetNeighborhoodIndex();
			bool IsInBounds;
			dstValue=it.GetPixel( i, IsInBounds );
			typename TInputImageType::IndexType idx_i = it.GetIndex( i );
			if( !IsInBounds || index == idx_i )
			{
				continue;
			}
			toNodeNum=computeNodeNum(size,idx_i);
			
			edge_descriptor e; bool inserted;                    
			tie(e, inserted) = add_edge(curNodeNum, toNodeNum, g);
			weightmap[e]=m_Metric->GetEdgeWeight(it,org_local_it);
		}
	}

	
	
	
	std::vector<vertex_descriptor> p(num_vertices(g));
	std::vector<int> d(num_vertices(g));
	vertex_descriptor s = vertex(startNodeNum, g);
	typename property_map<graph_t, vertex_index_t>::type indexmap = get(vertex_index, g);
	

	

	dijkstra_shortest_paths(g, s, &p[0], &d[0], weightmap, indexmap, 
                                std::less<int>(), closed_plus<int>(), 
                        	(std::numeric_limits<int>::max)(), 0,
                        	default_dijkstra_visitor());

	
	
	
	


	//prepare and update res Image
	typedef itk::CastImageFilter <TInputImageType,TOutputImageType> itkCastImageFilterType;
	typename itkCastImageFilterType::Pointer caster = itkCastImageFilterType::New();
	caster->SetInput (this->GetInput());
	caster->Update();


	typename TOutputImageType::Pointer outputImage = caster->GetOutput();

	typedef itk::ImageRegionIteratorWithIndex< TOutputImageType > itkImageRegionIteratorWithIndexType;
	itkImageRegionIteratorWithIndexType resIt (outputImage, outputImage->GetRequestedRegion());

	for (resIt.GoToBegin(); !resIt.IsAtEnd(); ++resIt)
	{
		resIt.Value() = BACKGROUND;
	}


	
	vertex_descriptor c = vertex(endNodeNum, g);
	typename TOutputImageType::IndexType curIndex;
	for (unsigned int i=0;i<TOutputImageType::ImageDimension;++i)
	{
		curIndex [i] = m_EndIndex[i];
	}
	resIt.SetIndex (curIndex);
	resIt.Value() = FOREGROUND;
	while (indexmap [c] != indexmap[s])
	{
		int tmp_c = indexmap[c];
		int temp_val;
		for (int k=dim-1;k>=0;--k)
		{
			temp_val=1;
			for (int l=0;l<k;++l)
			{
				temp_val=temp_val*size[l];
			}
			curIndex[k]=tmp_c/temp_val;
			tmp_c=tmp_c-curIndex[k]*temp_val;
		}
		
		resIt.SetIndex (curIndex);
		resIt.Value() = FOREGROUND;
                c  = vertex(indexmap[p[c]], g);
		//compute parent index
		
	}

	resIt.SetIndex (m_StartIndex);
	resIt.Value() = FOREGROUND;
	
	//update res image
	
	


	this->GraftOutput( outputImage );
} //Generate Data



template <class TInputImageType, class TOutputImageType>
void
ShortestPathImageFilter<TInputImageType, TOutputImageType>::
PrintSelf( std::ostream& os, Indent indent ) const
{
  Superclass::PrintSelf(os,indent);

  
 
}

} /* end namespace itk */
