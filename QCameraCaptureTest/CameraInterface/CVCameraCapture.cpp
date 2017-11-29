#include "CVCameraCapture.h"

CVCameraCapture::CVCameraCapture() : CameraInterface()
{

}

CVCameraCapture::~CVCameraCapture()
{

}

void CVCameraCapture::GetAvailableCaptureDevices(std::list<std::string>& listDevices)
{

}

void CVCameraCapture::CameraCaptureStart(int nIndex, std::function<void(const std::vector<unsigned char>&, int, int)> funcPresent)
{
	m_capture.open(nIndex);
	m_capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	m_capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
}

void CVCameraCapture::CameraCaptureSettings(const CameraSettings& settings)
{

}

void CVCameraCapture::CameraCaptureRestart()
{
}

void CVCameraCapture::CameraCaptureStop()
{
	m_capture.release();
}

bool CVCameraCapture::GetCapture(std::vector<uchar>& vData, int& nWidth, int& nHeight)
{
	static Mat matFrame;
	m_capture >> matFrame;
	if (matFrame.empty())
	{
		return false;
	}
	cvtColor(matFrame, matFrame, CV_RGB2BGR);
	vData.resize(matFrame.cols * matFrame.rows * 3);
	memcpy(&vData[0], matFrame.data, vData.size());
	nWidth = matFrame.cols;
	nHeight = matFrame.rows;
	return true;
}