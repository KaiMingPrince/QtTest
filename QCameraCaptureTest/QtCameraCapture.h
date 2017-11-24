/********************************************************************
文件名  :    QtCameraCapture
作者    :    @hxl
创建时间:    2015/7/22 15:17
版本	:	 1.0
文件描述:    摄像头捕获处理,单独的线程处理传输采集数据之后的动作(Qt版本)
版权	:	 Copyright ©2015 四川启程科技发展有限公司
*********************************************************************/
#ifndef _QT_CAMERA_CAPTURE_H__
#define _QT_CAMERA_CAPTURE_H__

#include "CameraInterface.h"
#include <QAbstractVideoSurface>

class CameraVideoSurface : public QAbstractVideoSurface
{
	Q_OBJECT
public:
	CameraVideoSurface(QObject* parent = Q_NULLPTR);
	~CameraVideoSurface();

	virtual QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;
	virtual bool present(const QVideoFrame &frame);

signals:
	void captureFrame(const QImage& image);
};

class QCamera;
class QCameraImageCapture;
class QLabel;

class QtCameraCapture : public QObject, public CameraInterface
{
	Q_OBJECT
public:
	QtCameraCapture(QObject* object = 0);
	virtual ~QtCameraCapture();

	//开始采集
	virtual void CameraCaptureStart(int nIndex = 0, void* hWnd = nullptr);
	//重启摄像头采集，以之前的参数
	virtual void CameraCaptureRestart();
	//停止采集
	virtual void CameraCaptureStop();

public slots:
	void onImageCaptured(const QImage& image);

private:
	QCamera*						m_pCamera;
	QLabel*							m_label;
};

#endif // _CAMERA_CAPTURE_H__