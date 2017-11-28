#include "CameraCapture.h"
#include "QtCameraCapture.h"
#include <QLabel>

const int g_nFrameWidth = 640;
const int g_nFrameHeight = 480;

CameraCapture::CameraCapture(QObject* object) 
	: QThread(object),
	  m_nDeviceIndex(0),
	  m_nInterval(40), 
	  m_ulCaptureTick(0),
	  m_bTerminate(false)	  
{
	m_labelShow = new QLabel;
	m_labelShow->resize(g_nFrameWidth, g_nFrameHeight);
	m_labelShow->show();
	m_pCameraCapture = new QtCameraCapture;
	m_pCameraCapture->CameraCaptureStart(0, (void*)(m_labelShow->winId()));
}

CameraCapture::~CameraCapture()
{
	terminate();
	wait();
}

void CameraCapture::run()
{
	std::vector<uchar> vRgbData;
	int nWidth = 0, nHeight = 0;
	while (1)
	{
		if (m_pCameraCapture->GetCapture(vRgbData, nWidth, nHeight))
		{
			QMetaObject::invokeMethod(m_labelShow, "setPixmap", Qt::AutoConnection, Q_ARG(QPixmap, QPixmap::fromImage(QImage(&vRgbData[0], nWidth, nHeight, QImage::Format_RGB32))));
		}
		QThread::msleep(60);
	}
}