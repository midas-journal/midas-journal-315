cmake_minimum_required(VERSION 2.6)


PROJECT (dijkstra)


INCLUDE(${CMAKE_SOURCE_DIR}/IJMacros.txt)

ENABLE_TESTING()

INCLUDE(Dart)

SET(PROJECT_HOME ${CMAKE_SOURCE_DIR})

SET(RESULTS_PATH ${CMAKE_SOURCE_DIR}/Results)
SET(DATA_PATH ${CMAKE_SOURCE_DIR}/Data)

SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_ADDITIONAL_VERSIONS "1.36.0" "1.37.0")  
SET(Boost_USE_MULTITHREAD OFF)
FIND_PACKAGE( Boost 1.34.0)

IF(Boost_FOUND)

   INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

ELSE(Boost_FOUND)

  MESSAGE(FATAL_ERROR

          "Cannot build applications without Boost.  Please set

 BOOST_INCLUDEDIR.")

ENDIF(Boost_FOUND)




FIND_PACKAGE(ITK)

IF(ITK_FOUND)

   INCLUDE(${ITK_USE_FILE})

ELSE(ITK_FOUND)

   MESSAGE(FATAL_ERROR

           "Cannot build InsightApplications without ITK.  Please set

ITK_DIR.")

ENDIF(ITK_FOUND)



SET(Required_Packages

ITK

)

FOREACH(Package ${Required_Packages})
  
	LOADPACKAGE(${Package})

ENDFOREACH(Package)

SET (ITK_LIBS

     ITKBasicFilters

     ITKAlgorithms

     ITKCommon

     ITKIO

     ITKNumerics

     ITKNrrdIO

     itkpng

     itktiff

     itkgdcm

     itkjpeg8

     itkjpeg12

     itkjpeg16

     ITKMetaIO

     itkzlib

     ITKDICOMParser

     ITKEXPAT

     itkvnl_inst

     itkvnl_algo

     itkvnl

     itkvcl

     itksys

)





#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_HOME}/bin)





SET( DIJKSTRA_2D_SRCS
  src/itkShortestPathImageFilter.h

  src/itkShortestPathImageFilter.txx

  src/itkWeightGradAngleMetricCalculator.h
  src/itkWeightGradAngleMetricCalculator.txx
  src/itkWeightMetricCalculator.h
  src/itkWeightMetricCalculator.txx
  src/itkWeightSimpleMetricCalculator.h
  src/itkWeightSimpleMetricCalculator.txx
  src/itkDijkstraFilterTest2D.cpp




  
)



SET( DIJKSTRA_3D_SRCS


  src/itkShortestPathImageFilter.h

  src/itkShortestPathImageFilter.txx

  src/itkWeightGradAngleMetricCalculator.h
  src/itkWeightGradAngleMetricCalculator.txx
  src/itkWeightMetricCalculator.h
  src/itkWeightMetricCalculator.txx
  src/itkWeightSimpleMetricCalculator.h
  src/itkWeightSimpleMetricCalculator.txx




  src/itkDijkstraFilterTest3D.cpp


)
SET( DIJKSTRA_2D_LIB
     itkDijkstraFilterTest2D
     ${ITK_LIBS}




)

SET( DIJKSTRA_3D_LIB

    itkDijkstraFilterTest3D
    ${ITK_LIBS}




)

SET (IMAGE_COMPARE_LIB
	ImageCompare
	${ITK_LIBS}


)
ADD_EXECUTABLE(itkDijkstraFilterTest2D ${DIJKSTRA_2D_SRCS} )

TARGET_LINK_LIBRARIES( ${DIJKSTRA_2D_LIB})

ADD_EXECUTABLE(itkDijkstraFilterTest3D ${DIJKSTRA_3D_SRCS} )

TARGET_LINK_LIBRARIES( ${DIJKSTRA_3D_LIB})

ADD_EXECUTABLE(ImageCompare src/ImageCompare.cxx) 
TARGET_LINK_LIBRARIES( ${IMAGE_COMPARE_LIB})

ADD_TEST(Test2D_simple_full itkDijkstraFilterTest2D ${DATA_PATH}/test_2D.vtk ${RESULTS_PATH}/test_2D_result_simple_metric_full_neighbors.vtk 21 76 52 12 1 0)

ADD_TEST(Test2D_hybrid_full itkDijkstraFilterTest2D ${DATA_PATH}/test_2D.vtk ${RESULTS_PATH}/test_2D_result_hybrid_metric_full_neighbors.vtk 21 76 52 12 1 1)

ADD_TEST(Test2D_hybrid_non_full itkDijkstraFilterTest2D ${DATA_PATH}/test_2D.vtk ${RESULTS_PATH}/test_2D_result_hybrid_metric_non_full_neighbors.vtk 21 76 52 12 0 1)

ADD_TEST(Test3D_simple_non_full itkDijkstraFilterTest3D ${DATA_PATH}/test_3D.vtk ${RESULTS_PATH}/test_3D_result_simple_metric_non_full_neighbors.vtk 12 12 5 9 38 45 0 0)
ADD_TEST(Test3D_hybrid_full itkDijkstraFilterTest3D ${DATA_PATH}/test_3D.vtk ${RESULTS_PATH}/test_3D_result_hybrid_metric_full_neighbors.vtk 12 12 5 9 38 45 1 1)

ADD_TEST(Test3D_hybrid_non_full itkDijkstraFilterTest3D ${DATA_PATH}/test_3D.vtk ${RESULTS_PATH}/test_3D_result_hybrid_metric_non_full_neighbors.vtk 12 12 5 9 38 45 0 1)


ADD_TEST(CompareImage_2D_simple_full ImageCompare ${DATA_PATH}/test_2D_result_simple_metric_full_neighbors.vtk ${RESULTS_PATH}/test_2D_result_simple_metric_full_neighbors.vtk)
ADD_TEST(CompareImage_2D_hybrid_full ImageCompare ${DATA_PATH}/test_2D_result_hybrid_metric_full_neighbors.vtk ${RESULTS_PATH}/test_2D_result_hybrid_metric_full_neighbors.vtk)
ADD_TEST(CompareImage_2D_hybrid_non_full ImageCompare ${DATA_PATH}/test_2D_result_hybrid_metric_non_full_neighbors.vtk ${RESULTS_PATH}/test_2D_result_hybrid_metric_non_full_neighbors.vtk)
ADD_TEST(CompareImage_3D_simple_non_full ImageCompare ${DATA_PATH}/test_3D_result_simple_metric_non_full_neighbors.vtk ${RESULTS_PATH}/test_3D_result_simple_metric_non_full_neighbors.vtk)
ADD_TEST(CompareImage_3D_hybrid_full ImageCompare ${DATA_PATH}/test_3D_result_hybrid_metric_full_neighbors.vtk ${RESULTS_PATH}/test_3D_result_hybrid_metric_full_neighbors.vtk)
ADD_TEST(CompareImage_3D_hybrid_non_full ImageCompare ${DATA_PATH}/test_3D_result_hybrid_metric_non_full_neighbors.vtk ${RESULTS_PATH}/test_3D_result_hybrid_metric_non_full_neighbors.vtk)
