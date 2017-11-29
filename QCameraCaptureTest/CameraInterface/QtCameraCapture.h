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

#include <QAbstractVideoSurface>

//子类VideoSurface来获取推送的采集数据
class CameraVideoSurface : public QAbstractVideoSurface
{
	Q_OBJECT
public:
	CameraVideoSurface(QObject* parent = Q_NULLPTR);
	~CameraVideoSurface();

	virtual QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;
	virtual bool present(const QVideoFrame &frame);

signals:
	void presentFrame(const QVideoFrame& frame);
};

#include "CameraInterface.h"
#include <QCameraViewfinderSettings>
#include <QReadWriteLock>

class QCamera;

class QtCameraCapture : public QObject, public CameraInterface
{
	Q_OBJECT
public:
	QtCameraCapture(QObject* object = 0);
	virtual ~QtCameraCapture();

	virtual void GetAvailableCaptureDevices(std::list<std::string>& listDevices);
	virtual void CameraCaptureStart(int nIndex = 0, std::function<void(const std::vector<unsigned char>&, int, int)> funcPresent = nullptr);
	virtual void CameraCaptureSettings(const CameraSettings& settings);
	virtual void CameraCaptureRestart();
	virtual void CameraCaptureStop();
	virtual bool GetCapture(std::vector<uchar>& vData, int& nWidth, int& nHeight);

signals:
	void presentFrame(const std::vector<uchar>&, int, int);

public slots:
	void onImagePresent(const QVideoFrame& frame);

private:
	QCamera*						m_pCamera;
	QCameraViewfinderSettings		m_cameraSettings;
	QVideoFrame						m_frameBuffer;	//推送采集的缓冲数据
	QReadWriteLock					m_lock;			//读写锁，支持共享读
};

#endif // _CAMERA_CAPTURE_H__