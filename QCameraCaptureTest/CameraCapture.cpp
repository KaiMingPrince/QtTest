#include "CameraCapture.h"
#include "CameraInterface\CameraInterface.h"
#pragma  comment (lib, "CameraInterface.lib")
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
	m_pCameraCapture = CreateCameraInterface(0);
	std::list<std::string> listDevices;
	m_pCameraCapture->GetAvailableCaptureDevices(listDevices);
	m_pCameraCapture->CameraCaptureStart(0, std::bind(&CameraCapture::Show, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

CameraCapture::~CameraCapture()
{
	terminate();
	wait();
}

void CameraCapture::Show(const std::vector<uchar>& vData, int nWidth, int nHeight)
{
	QMetaObject::invokeMethod(m_labelShow, "setPixmap", Qt::AutoConnection, Q_ARG(QPixmap, QPixmap::fromImage(QImage(&vData[0], nWidth, nHeight, QImage::Format_RGB32))));
}

void CameraCapture::run()
{
	std::vector<uchar> vRgbData;
	int nWidth = 0, nHeight = 0;
	while (1)
	{
		if (m_pCameraCapture->GetCapture(vRgbData, nWidth, nHeight))
		{
			QMetaObject::invokeMethod(m_labelShow, "setPixmap", Qt::AutoConnection, Q_ARG(QPixmap, QPixmap::fromImage(QImage(&vRgbData[0], nWidth, nHeight, QImage::Format_RGB888))));
		}
		QThread::msleep(60);
	}
}