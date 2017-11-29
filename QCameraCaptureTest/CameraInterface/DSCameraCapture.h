/********************************************************************
文件名  :    DSCameraCapture
作者    :    @hxl
创建时间:    2015/7/22 15:17
版本	:	 1.0
文件描述:    摄像头捕获处理,单独的线程处理传输采集数据之后的动作(DirectShow版本)
版权	:	 Copyright ©2015 四川启程科技发展有限公司
*********************************************************************/
#ifndef _DS_CAMERA_CAPTURE_H__
#define _DS_CAMERA_CAPTURE_H__

#include "CameraInterface.h"

class DSCameraCapture : public CameraInterface
{
public:
	DSCameraCapture();
	virtual ~DSCameraCapture();

	virtual void GetAvailableCaptureDevices(std::list<std::string>& listDevices);
	virtual void CameraCaptureStart(int nIndex = 0, std::function<void(const std::vector<unsigned char>&, int, int)> funcPresent = nullptr);
	virtual void CameraCaptureSettings(const CameraSettings& settings);
	virtual void CameraCaptureRestart();
	virtual void CameraCaptureStop();
	virtual bool GetCapture(std::vector<unsigned char>& vData, int& nWidth, int& nHeight);

protected:
	bool ListCaptureDevices();
};

#endif // _DS_CAMERA_CAPTURE_H__