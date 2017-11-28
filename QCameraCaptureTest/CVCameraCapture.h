/********************************************************************
文件名  :    CVCameraCapture
作者    :    @hxl
创建时间:    2015/7/22 15:17
版本	:	 1.0
文件描述:    摄像头捕获处理,单独的线程处理传输采集数据之后的动作(openCV版本)
版权	:	 Copyright ©2015 四川启程科技发展有限公司
*********************************************************************/
#ifndef _CV_CAMERA_CAPTURE_H__
#define _CV_CAMERA_CAPTURE_H__

#include "CameraInterface.h"
#include "opencv2/opencv.hpp"
using namespace cv;

class CVCameraCapture : public CameraInterface
{
public:
	CVCameraCapture();
	virtual ~CVCameraCapture();

	//开始采集
	virtual void CameraCaptureStart(int nIndex = 0, void* hWnd = nullptr);
	//重启摄像头采集，以之前的参数
	virtual void CameraCaptureRestart();
	//停止采集
	virtual void CameraCaptureStop();
	virtual bool GetCapture(std::vector<uchar>& vData, int& nWidth, int& nHeight);
};

#endif // _CV_CAMERA_CAPTURE_H__