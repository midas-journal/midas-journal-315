#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkShortestPathImageFilter.h"
#include "itkWeightGradAngleMetricCalculator.h"
#include "itkWeightSimpleMetricCalculator.h"

#include <iostream>

using namespace std;
int main(int argc, char *argv[])
{
	//typedefs
	typedef signed short        PixelType;
	typedef unsigned char       OutputPixelType;
	const unsigned int          Dimension = 2;
	typedef itk::Image<PixelType, Dimension > ImageType;
	typedef itk::Image<OutputPixelType, Dimension > OutputImageType;
	typedef itk::ShortestPathImageFilter <ImageType, OutputImageType> itkShortestPathImageFilterType;
	typedef itk::WeightMetricCalculator<ImageType> MetricType;
	MetricType::Pointer metric;
	// Class itk::WeightSimpleMetricCalculator is derived from
	//itk::WeightMetricCalculator and defines a gradient based weighting
	//function
	typedef itk::WeightSimpleMetricCalculator<ImageType> SimpleMetricType;

	// Class itk::WeightGradAngleMetricCalculator is derived from
	//itk::WeightMetricCalculator and defines a hybrid weighting
	//function
	typedef itk::WeightGradAngleMetricCalculator<ImageType> HybridMetricType;
	
	typedef itk::ImageFileReader< ImageType > ReaderType;
	
	if(argc < 9)
	{
		cerr << "Usage:" << endl;
		cerr << "inputImage, outputImage, startSeedX startSeedY endSeedX endSeedY neighborsMode weightingMethod" << endl;
		return -1;
    }
	ReaderType::Pointer reader = ReaderType::New();
	reader->SetFileName(argv[1]);
	try
    {
		reader->Update();
    }
	catch( itk::ExceptionObject & excp )
    {
		std::cerr << "Problem encountered while reading ";
		std::cerr << " image file : " << argv[1] << std::endl;
		std::cerr << excp << std::endl;
		return EXIT_FAILURE;
    }
	
	// Define the start and end points
	ImageType::IndexType start, end;
	start[0] = atoi(argv[3]);
	start[1] = atoi(argv[4]);
	end[0]   = atoi(argv[5]);
	end[1]   = atoi(argv[6]);

	// Instantiating and initializing metric object
	if (atoi(argv[8])==0)
	{
		SimpleMetricType::Pointer metricDerived = SimpleMetricType::New();
		metricDerived->SetImage(reader->GetOutput());
		metricDerived->Initialize();
		metric=metricDerived;
	}
	else
	{
		HybridMetricType::Pointer metricDerived = HybridMetricType::New();
		metricDerived->SetImage(reader->GetOutput());
		metricDerived->Initialize();
		metricDerived->SetStartIndex(start);
		metricDerived->SetEndIndex(end);
		metricDerived->SetSigma(5.0);
		metric=metricDerived;
	}
	
	
	// Instantiating itk :: ShortestPathImageFilter object and assigning
	// the metric object
	itkShortestPathImageFilterType::Pointer dijkstra = itkShortestPathImageFilterType::New();

	// Set the metric instance for the path
	dijkstra->SetMetric(metric);
	dijkstra->SetInput (reader->GetOutput());
	dijkstra->SetStartIndex (start);
	dijkstra->SetEndIndex (end);
	
	// Define the neighboring mode
	if (atoi(argv[7])==1)
		dijkstra->SetModeToFullNeighbors();
	else
		dijkstra->SetModeToNonFullNeighbors();
	
	typedef itk::ImageFileWriter< OutputImageType > WriterType;
	WriterType::Pointer pathWriter = WriterType::New();
	pathWriter->SetFileName(argv[2]);
	pathWriter->SetInput (dijkstra->GetOutput());
	try
    {
		pathWriter->Update();
    }
	catch( itk::ExceptionObject & excp )
    {
		std::cerr << "Problem encountered while writing ";
		std::cerr << " image file : " << argv[2] << std::endl;
		std::cerr << excp << std::endl;
		return EXIT_FAILURE;
    }

  	return EXIT_SUCCESS;
}
