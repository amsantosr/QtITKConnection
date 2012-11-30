#include <itkImageFileReader.h>
#include <itkCastImageFilter.h>
#include "imagelayer.h"

ImageLayer *ImageLayer::imageLayerInstance = 0;

ImageLayer::ImageLayer()
{
    m_width = 0;
    m_height = 0;
}

ImageLayer::FloatImageType::Pointer ImageLayer::floatGrayImagePointer(int index)
{
    typedef itk::CastImageFilter<GrayImageType, FloatImageType> CastFloatFilterType;
    CastFloatFilterType::Pointer castFilter = CastFloatFilterType::New();
    castFilter->SetInput(grayImageVector[index]);
    castFilter->Update();
    FloatImageType::Pointer castFilterOutput = castFilter->GetOutput();
    return castFilterOutput;
}

void ImageLayer::setGrayImage(int index, GrayImageType::Pointer grayImagePointer)
{
    Q_ASSERT(0 <= index && index < grayImageVector.size());
    grayImageVector[index] = grayImagePointer;
    emit grayImageChanged(index);
}

void ImageLayer::setRgbImage(int index, RGBImageType::Pointer rgbImagePointer)
{
    Q_ASSERT(0 <= index && index < rgbImageVector.size());
    rgbImageVector[index] = rgbImagePointer;
    emit rgbImageChanged(index);
}

void ImageLayer::openGrayImage(const char *filename)
{
    typedef itk::ImageFileReader<GrayImageType> ImageFileReaderFilterType;
    ImageFileReaderFilterType::Pointer imageReader = ImageFileReaderFilterType::New();

    imageReader->SetFileName(filename);
    imageReader->Update();
    GrayImageType::Pointer sourceImage = imageReader->GetOutput();
    resizeImageVector(1);
    setGrayImage(0, sourceImage);
    m_width = sourceImage->GetBufferedRegion().GetSize()[0];
    m_height = sourceImage->GetBufferedRegion().GetSize()[1];

    emit grayImageChanged(0);
}

void ImageLayer::resizeImageVector(int size)
{
    grayImageVector.resize(size);
    emit imageVectorSizeChanged(size);
}

ImageLayer *ImageLayer::instance()
{
    if (imageLayerInstance == 0)
        imageLayerInstance = new ImageLayer;
    return imageLayerInstance;
}
