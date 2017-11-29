#include "QtCameraCapture.h"

#include <QCamera>
#include <QCameraInfo>

CameraVideoSurface::CameraVideoSurface(QObject* parent) : QAbstractVideoSurface(parent)
{

}

CameraVideoSurface::~CameraVideoSurface()
{

}

QList<QVideoFrame::PixelFormat> CameraVideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
	return QList<QVideoFrame::PixelFormat>() << QVideoFrame::Format_RGB32;
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
	emit presentFrame(cloneFrame);
	cloneFrame.unmap();
	return true;
}

QtCameraCapture::QtCameraCapture(QObject* object) : QObject(object), CameraInterface()
{
	CameraCaptureSettings(CameraSettings(0, 640, 480));
}

QtCameraCapture::~QtCameraCapture()
{

}

void QtCameraCapture::GetAvailableCaptureDevices(std::list<std::string>& listDevices)
{
	for (auto cameraInfo : QCameraInfo::availableCameras())
	{
		listDevices.push_back(cameraInfo.description().toStdString());
	}
}

void QtCameraCapture::CameraCaptureStart(int nIndex, std::function<void(const std::vector<unsigned char>&, int, int)> funcPresent)
{
	m_pCamera = new QCamera(QCameraInfo::availableCameras().at(0));
	m_pCamera->setViewfinderSettings(m_cameraSettings);
 	CameraVideoSurface* pVideoSurface = new CameraVideoSurface(this);
	m_pCamera->setViewfinder(pVideoSurface);
	m_pCamera->setCaptureMode(QCamera::CaptureStillImage);

	connect(pVideoSurface, &CameraVideoSurface::presentFrame, this, &QtCameraCapture::onImagePresent);
	if (funcPresent)
	{
		qRegisterMetaType<std::vector<uchar> >("std::vector<uchar>");
		connect(this, &QtCameraCapture::presentFrame, funcPresent);
	}
	
	//Æô¶¯²É¼¯
	m_pCamera->start();
}

void QtCameraCapture::CameraCaptureSettings(const CameraSettings& settings)
{
	m_cameraSettings.setResolution(settings.nCaptureWidth, settings.nCaptureHeight);
// 	m_cameraSettings.setMinimumFrameRate(settings.nCaptureRate);
// 	m_cameraSettings.setMaximumFrameRate(settings.nCaptureRate);
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
	m_frameBuffer.map(QAbstractVideoBuffer::ReadOnly);
	int nByteCount = m_frameBuffer.width()*m_frameBuffer.height()*4;
	if (0 == nByteCount)
	{
		return false;
	}
	vData.resize(nByteCount);
	memcpy(&vData[0], m_frameBuffer.bits(), nByteCount);
	nWidth = m_frameBuffer.width();
	nHeight = m_frameBuffer.height();
	m_frameBuffer.unmap();
	return true;
}

void QtCameraCapture::onImagePresent(const QVideoFrame& frame)
{
	//static QMatrix matrix(1, 0, 0, -1, 0, 0);
	{
		QWriteLocker locker(&m_lock);
		m_frameBuffer = frame;
	}

	static std::vector<uchar> vData;
	int nWidth = 0, nHeight = 0;
	GetCapture(vData, nWidth, nHeight);
	emit presentFrame(vData, nWidth, nHeight);
}