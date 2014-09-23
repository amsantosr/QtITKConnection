PROJECT(QtITKConnection)

set(CMAKE_AUTOMOC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

IF(COMMAND CMAKE_POLICY)
	CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND CMAKE_POLICY)

FIND_PACKAGE(ITK REQUIRED)
IF (ITK_FOUND)
	INCLUDE(${USE_ITK_FILE})
ELSE(ITK_FOUND)
	MESSAGE(FATAL_ERROR "Cannot build this application without ITK. Please set ITK_DIR")
ENDIF(ITK_FOUND)

FIND_PACKAGE(Qt5Widgets REQUIRED)



INCLUDE_DIRECTORIES(
	${Qt5Widgets_INCLUDES}
	${QtITKConnection_BINARY_DIR}
	${QtITKConnection_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR} #this is where ui_ImageViewerUI.h is generated
	${CMAKE_CURRENT_SOURCE_DIR}
)

add_definitions(${Qt5Widgets_DEFINITIONS})

set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

SET(QtITKConnection_SRCS
	binarythresholdfilterdialog.cpp
	cannyedgedetectionfilterdialog.cpp
	confidenceconnectedsegmentationdialog.cpp
	connectedthresholdsegmentationdialog.cpp
	customgraphicsscene.cpp
	customscrollarea.cpp
	derivativeimagefilterdialog.cpp
	fastmarchingsegmentationdialog.cpp
	gradientanisotropicfilterdialog.cpp
	gradientmagnituderecursivegaussianfilterdialog.cpp
	imagelayer.cpp
	isolatedconnectedsegmentationdialog.cpp
	main.cpp
	mainwindow.cpp
	neighborhoodconnectedsegmentationdialog.cpp
	otsuthresholdsegmentationdialog.cpp
	rescaleintensityfilterdialog.cpp
	sigmoidfilterdialog.cpp
	thresholdfilterdialog.cpp
	watershedsegmentationdialog.cpp)
SET(QtITKConnection_HDRS
	binarythresholdfilterdialog.h
	cannyedgedetectionfilterdialog.h
	confidenceconnectedsegmentationdialog.h
	connectedthresholdsegmentationdialog.h
	customgraphicsscene.h
	customscrollarea.h
	derivativeimagefilterdialog.h
	fastmarchingsegmentationdialog.h
	gradientanisotropicfilterdialog.h
	gradientmagnituderecursivegaussianfilterdialog.h
	imagelayer.h
	isolatedconnectedsegmentationdialog.h
	mainwindow.h
	neighborhoodconnectedsegmentationdialog.h
	otsuthresholdsegmentationdialog.h
	rescaleintensityfilterdialog.h
	sigmoidfilterdialog.h
	thresholdfilterdialog.h
	watershedsegmentationdialog.h)
SET(QtITKConnection_UI
	binarythresholdfilterdialog.ui
	cannyedgedetectionfilterdialog.ui
	confidenceconnectedsegmentationdialog.ui
	connectedthresholdsegmentationdialog.ui
	derivativeimagefilterdialog.ui
	fastmarchingsegmentationdialog.ui
	gradientanisotropicfilterdialog.ui
	gradientmagnituderecursivegaussianfilterdialog.ui
	isolatedconnectedsegmentationdialog.ui
	mainwindow.ui
	neighborhoodconnectedsegmentationdialog.ui
	otsuthresholdsegmentationdialog.ui
	rescaleintensityfilterdialog.ui
	sigmoidfilterdialog.ui
	thresholdfilterdialog.ui
	watershedsegmentationdialog.ui)

QT5_WRAP_UI(QtITKConnection_UIS_H
        binarythresholdfilterdialog.ui
        cannyedgedetectionfilterdialog.ui
        confidenceconnectedsegmentationdialog.ui
        connectedthresholdsegmentationdialog.ui
        derivativeimagefilterdialog.ui
        fastmarchingsegmentationdialog.ui
        gradientanisotropicfilterdialog.ui
        gradientmagnituderecursivegaussianfilterdialog.ui
        isolatedconnectedsegmentationdialog.ui
        mainwindow.ui
        neighborhoodconnectedsegmentationdialog.ui
        otsuthresholdsegmentationdialog.ui
        rescaleintensityfilterdialog.ui
        sigmoidfilterdialog.ui
        thresholdfilterdialog.ui
        watershedsegmentationdialog.ui)

ADD_EXECUTABLE(QtITKConnection ${QtITKConnection_SRCS} ${QtITKConnection_UIS_H} ${QtITKConnection_MOC_CPP})

QT5_USE_MODULES(QtITKConnection Widgets)

TARGET_LINK_LIBRARIES(QtITKConnection ${ITK_LIBRARIES} ${Qt5Widgets_LIBRARIES})

