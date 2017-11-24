#include "QtCameraCapture.h"

#include <QCamera>
#include <QCameraInfo>
#include <QCameraImageCapture>
#include <QLabel>
#include <QImage>

CameraVideoSurface::CameraVideoSurface(QObject* parent /*= Q_NULLPTR*/)
{

}

CameraVideoSurface::~CameraVideoSurface()
{

}

QList<QVideoFrame::PixelFormat> CameraVideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
	return QList<QVideoFrame::PixelFormat>() << QVideoFrame::Format_RGB24 << QVideoFrame::Format_RGB32;
}

bool CameraVideoSurface::present(const QVideoFrame &frame)
{
	if (!frame.isValid())
	{
		return false;
	}
	Q_UNUSED(frame);
	QVideoFrame f(frame);
	f.map(QAbstractVideoBuffer::ReadOnly);
 	//处理
	emit captureFrame(QImage(f.bits(), f.width(), f.height(), 
		QVideoFrame::imageFormatFromPixelFormat(f.pixelFormat())));
	f.unmap();
	return true;
}

QtCameraCapture::QtCameraCapture(QObject* object /*= 0*/) : QObject(object), CameraInterface()
{

}

QtCameraCapture::~QtCameraCapture()
{

}

void QtCameraCapture::CameraCaptureStart(int nIndex, void* hWnd)
{
	QCameraViewfinderSettings cameraSettings;
	cameraSettings.setResolution(640, 480);
	m_pCamera = new QCamera(QCameraInfo::availableCameras().at(0));
	m_pCamera->setViewfinderSettings(cameraSettings);
 	CameraVideoSurface* pVideoSurface = new CameraVideoSurface();
	m_pCamera->setViewfinder(pVideoSurface);
	connect(pVideoSurface, &CameraVideoSurface::captureFrame, this, &QtCameraCapture::onImageCaptured);
	m_label = new QLabel;
	m_label->resize(640, 480);
	m_label->show();
	//m_pCamera->setCaptureMode(QCamera::CaptureStillImage);
	//启动采集
	m_pCamera->start();
}

void QtCameraCapture::CameraCaptureRestart()
{

}

void QtCameraCapture::CameraCaptureStop()
{

}

void QtCameraCapture::onImageCaptured(const QImage& image)
{
	QImage im = image.copy();
	m_label->setPixmap(QPixmap::fromImage(im));
}
