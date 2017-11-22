#include "QtCameraCapture.h"

#include <QCamera>
#include <QCameraInfo>

CameraVideoSurface::CameraVideoSurface(QObject* parent /*= Q_NULLPTR*/)
{

}

CameraVideoSurface::~CameraVideoSurface()
{

}

QList<QVideoFrame::PixelFormat> CameraVideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
	return QList<QVideoFrame::PixelFormat>() << QVideoFrame::Format_RGB24;
}

bool CameraVideoSurface::present(const QVideoFrame &frame)
{
	Q_UNUSED(frame);
	frame.map(QAbstractVideoBuffer::ReadOnly);
	//处理
	frame.unmap();
	return true;
}

void QtCameraCapture::CameraCaptureStart(int nIndex, void* hWnd)
{
	QCameraViewfinderSettings cameraSettings;
	cameraSettings.setResolution(640, 480);
	QCamera* pCamera = new QCamera(nIndex);
	pCamera->setViewfinderSettings(cameraSettings);
	CameraVideoSurface* pVideoSurface = new CameraVideoSurface()
	pCamera->setViewfinder(pVideoSurface);

	//启动采集
	pCamera->start();
}

void QtCameraCapture::CameraCaptureRestart()
{

}

void QtCameraCapture::CameraCaptureStop()
{

}


