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

#ifdef CAMERA_INTERFACE_LIB
#define CAMERA_INTERFACE_EXPORT	_declspec(dllexport)
#else
#define CAMERA_INTERFACE_EXPORT	_declspec(dllimport)
#endif

#include <vector>
#include <list>
#include <string>
#include <memory>
#include <functional>

class CameraSettings
{
public:
	CameraSettings(int nRate, int nWidth, int nHeight) : nCaptureRate(nRate),
		nCaptureWidth(nWidth), nCaptureHeight(nHeight) {}

	int			nCaptureWidth;
	int			nCaptureHeight;
	int			nCaptureRate;
};

class CAMERA_INTERFACE_EXPORT CameraInterface
{
public:
	CameraInterface() {}
	virtual ~CameraInterface() {}
	//获取采集设备列表
	virtual void GetAvailableCaptureDevices(std::list<std::string>& listDevices) = 0;
	//开启摄像头采集，指定设备序列号，可选的推送回调，如果实现支持推送采集数据
	virtual void CameraCaptureStart(int nIndex = 0, std::function<void(const std::vector<unsigned char>&, int, int)> funcPresent = nullptr) = 0;
	//设置采集配置参数，默认以25帧分辨率640*480采集
	virtual void CameraCaptureSettings(const CameraSettings& settings) = 0;
	//重启摄像头采集
	virtual void CameraCaptureRestart() = 0;
	//关闭摄像头采集
	virtual void CameraCaptureStop() = 0;
	//获取当前采集帧
	virtual bool GetCapture(std::vector<unsigned char>& vData, int& nWidth, int& nHeight) = 0;
};

CAMERA_INTERFACE_EXPORT std::shared_ptr<CameraInterface> CreateCameraInterface(int nType);

#endif //_CAMERA_INTERFACE_H__

