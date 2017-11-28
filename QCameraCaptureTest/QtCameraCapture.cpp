#include "QtCameraCapture.h"

#include <QCamera>
#include <QCameraInfo>
#include <QImage>

CameraVideoSurface::CameraVideoSurface(QObject* parent)
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
	QVideoFrame cloneFrame(frame);
	cloneFrame.map(QAbstractVideoBuffer::ReadOnly);
	emit presentFrame(QImage(cloneFrame.bits(), cloneFrame.width(), cloneFrame.height(),
		QVideoFrame::imageFormatFromPixelFormat(cloneFrame.pixelFormat())));
	cloneFrame.unmap();
	return true;
}

QtCameraCapture::QtCameraCapture(QObject* object) : QObject(object), CameraInterface()
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
	m_pCamera->setCaptureMode(QCamera::CaptureStillImage);

	connect(pVideoSurface, &CameraVideoSurface::presentFrame, this, &QtCameraCapture::onImagePresent);

	//Æô¶¯²É¼¯
	m_pCamera->start();
}

void QtCameraCapture::CameraCaptureRestart()
{
	m_pCamera->stop();
	m_pCamera->start();
}

void QtCameraCapture::CameraCaptureStop()
{
	m_pCamera->stop();
}

bool QtCameraCapture::GetCapture(std::vector<uchar>& vData, int& nWidth, int& nHeight)
{
	QReadLocker locker(&m_lock);
	int nByteCount = m_imageBuffer.byteCount();
	if (0 == nByteCount)
	{
		return false;
	}
	vData.resize(nByteCount);
	memcpy(&vData[0], m_imageBuffer.constBits(), nByteCount);
	nWidth = m_imageBuffer.width();
	nHeight = m_imageBuffer.height();
	return true;
}

void QtCameraCapture::onImagePresent(const QImage& image)
{
	static QMatrix matrix(1, 0, 0, -1, 0, 0);
	QWriteLocker locker(&m_lock);
	m_imageBuffer = image.transformed(matrix);
}