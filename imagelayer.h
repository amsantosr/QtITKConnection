#ifndef IMAGELAYER_H
#define IMAGELAYER_H

#include <itkImage.h>
#include <itkRGBPixel.h>
#include <QObject>
#include <QVector>

class ImageLayer : public QObject
{
    Q_OBJECT

public:
    typedef itk::Image<unsigned char, 2> GrayImageType;
    typedef itk::Image<float, 2> FloatImageType;
    typedef itk::RGBPixel<unsigned char> RGBPixelType;
    typedef itk::Image<RGBPixelType, 2> RGBImageType;

    ImageLayer();
    void openGrayImage(const char *filename);
    void openRgbImage(const char *filename);
    unsigned char *grayImageData(int index);
    unsigned char *rgbImageData(int index);
    GrayImageType::Pointer grayImagePointer(int index);
    RGBImageType::Pointer rgbImagePointer(int index);
    FloatImageType::Pointer floatGrayImagePointer(int index);
    int width() const;
    int height() const;
    int grayBytesPerLine() const;
    void resizeImageVector(int size);
    void setGrayImage(int index, GrayImageType::Pointer grayImagePointer);
    void setRgbImage(int index, RGBImageType::Pointer rgbImagePointer);
    static ImageLayer *instance();

signals:
    void imageVectorSizeChanged(int newSize);
    void grayImageChanged(int index);
    void rgbImageChanged(int index);

private:
    static ImageLayer *imageLayerInstance;

private:
    int m_width;
    int m_height;

private:
    QVector<GrayImageType::Pointer> grayImageVector;
    QVector<RGBImageType::Pointer> rgbImageVector;
};

inline int ImageLayer::width() const
{
    return m_width;
}

inline int ImageLayer::height() const
{
    return m_height;
}

inline int ImageLayer::grayBytesPerLine() const
{
    return m_width;
}

inline ImageLayer::GrayImageType::Pointer ImageLayer::grayImagePointer(int index)
{
    Q_ASSERT(0 <= index && index < grayImageVector.size());
    return grayImageVector[index];
}

inline ImageLayer::RGBImageType::Pointer ImageLayer::rgbImagePointer(int index)
{
    Q_ASSERT(0 <= index && index < rgbImageVector.size());
    return rgbImageVector[index];
}

inline unsigned char *ImageLayer::grayImageData(int index)
{
    Q_ASSERT(0 <= index && index < grayImageVector.size());
    return grayImageVector[index]->GetBufferPointer();
}

inline unsigned char *ImageLayer::rgbImageData(int index)
{
    Q_ASSERT(0 <= index && index < rgbImageVector.size());
    return reinterpret_cast<unsigned char*>(rgbImageVector[index]->GetBufferPointer());
}

#endif // IMAGELAYER_H
