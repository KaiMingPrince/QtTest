/********************************************************************
文件名  :    CameraCapture
作者    :    @hxl
创建时间:    2015/7/22 15:17
版本	:	 1.0
文件描述:    摄像头捕获处理,单独的线程处理传输采集数据之后的动作
版权	:	 Copyright ©2015 四川启程科技发展有限公司
*********************************************************************/
#ifndef _CAMERA_CAPTURE_H__
#define _CAMERA_CAPTURE_H__

#include <QThread>
#include "CameraInterface.h"

class QLabel;

class CameraCapture : public QThread
{
	Q_OBJECT
public:
	CameraCapture(QObject* object = 0);
	virtual ~CameraCapture();

protected:
	virtual void run();

private:	
	int								m_nInterval;					//摄像头采集数据的间隔(由下层传递的帧率控制)
	unsigned long					m_ulCaptureTick;				//采集数据的时间戳
	bool							m_bTerminate;
	int								m_nDeviceIndex;					//要开启的设备序列号
	QLabel*							m_labelShow;					//

};

#endif // _CAMERA_CAPTURE_H__