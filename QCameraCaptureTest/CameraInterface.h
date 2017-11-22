/********************************************************************
文件名  :    CameraInterface
作者    :    @hxl
创建时间:    2017/9/4 11:56
版本	:	 1.0
文件描述:    摄像头采集操作接口
版权	:	 Copyright ©2017 四川启程科技发展有限公司
*********************************************************************/
#ifndef _CAMERA_INTERFACE_H__
#define _CAMERA_INTERFACE_H__

class CameraInterface
{
public:
	CameraInterface() {}
	virtual ~CameraInterface() {}
	//采集数据后交给窗口显示
	virtual void CameraCaptureStart(int nIndex = 0, void* hWnd = nullptr) = 0;
	virtual void CameraCaptureRestart() = 0;
	virtual void CameraCaptureStop() = 0;
};

#endif //_CAMERA_INTERFACE_H__

