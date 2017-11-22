#include "CameraCapture.h"
#include "afxwin.h"

#include "opencv2/opencv.hpp"
using namespace cv;

const int g_nFrameWidth = 640;
const int g_nFrameHeight = 480;

CameraCapture::CameraCapture(QObject* object) 
	: QThread(object),
	  CameraInterface(),
	  m_nDeviceIndex(-1),
	  m_nInterval(40), 
	  m_ulCaptureTick(0),
	  m_bTerminate(false)
{
}

CameraCapture::~CameraCapture()
{
}

void CameraCapture::CameraCaptureStart(int nIndex, std::function<void(unsigned char*, unsigned char*, int, int)> funcSendData)
{
	m_nDeviceIndex = nIndex;
	connect(this, &CameraCapture::captureData, funcSendData);
	CameraCaptureRestart();
}

void CameraCapture::CameraCaptureStart(int nIndex, void* hWnd)
{
	//这个实现暂时不做
}

void CameraCapture::CameraCaptureRestart()
{
	m_bTerminate = false;
	start();
}

void CameraCapture::CameraCaptureStop()
{
	m_bTerminate = true;
	wait(m_nInterval);
	printf("Camera Capture Thread is stoped at %s!\n", __TIME__);
}

void CameraCapture::run()
{
	VideoCapture capture;
	if (capture.open(m_nDeviceIndex))
	{
		capture.set(CV_CAP_PROP_FRAME_WIDTH, g_nFrameWidth);
		capture.set(CV_CAP_PROP_FRAME_HEIGHT, g_nFrameHeight);

		Mat matFrame;
		Mat matYUV(g_nFrameHeight + g_nFrameHeight / 2, g_nFrameWidth, CV_8UC1, Scalar(0));
		m_ulCaptureTick = GetTickCount();
		int nCount = 0;
		while (1)
		{
			capture >> matFrame;
			if (matFrame.empty())
			{
				printf("opencv cannot capture frame\n");
				QThread::msleep(m_nInterval);
				continue;
			}

			//如果强制采集的尺寸不符合设置标准，只能在这里做一次resize转换
			if ((g_nFrameWidth != matFrame.cols) || (g_nFrameHeight != matFrame.rows))
			{
				Mat matResize(g_nFrameHeight, g_nFrameWidth, CV_8UC3, Scalar(0));
				resize(matFrame, matResize, Size(g_nFrameWidth, g_nFrameHeight));
				matFrame.create(g_nFrameHeight, g_nFrameWidth, CV_8UC3);
				matResize.copyTo(matFrame);
			}

			cvtColor(matFrame, matFrame, CV_RGB2BGR);
			cvtColor(matFrame, matYUV, CV_RGB2YUV_I420);

			emit captureData(matFrame.data, matYUV.data, g_nFrameWidth, g_nFrameHeight);

			long nElapsed = GetTickCount() - m_ulCaptureTick;
			if (nElapsed < m_nInterval)
			{
				QThread::msleep(m_nInterval - nElapsed);
			}
			m_ulCaptureTick = GetTickCount();

			if (m_bTerminate)
			{
				break;
			}
		}
		capture.release();
	}
}
