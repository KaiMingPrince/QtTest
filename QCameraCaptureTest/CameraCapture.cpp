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
	m_pCameraCapture = new QtCameraCapture;
	m_pCameraCapture->CameraCaptureStart();
}

CameraCapture::~CameraCapture()
{
}

void CameraCapture::run()
{
	while (1)
	{
		QThread::msleep(60);
	}
}
