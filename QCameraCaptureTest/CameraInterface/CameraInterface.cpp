#include "CameraInterface.h"
#include "QtCameraCapture.h"
#include "CVCameraCapture.h"

std::shared_ptr<CameraInterface> CreateCameraInterface(int nType)
{
	switch (nType)
	{
	case 0:
		return std::make_shared<QtCameraCapture>();
	case 1:
		return std::make_shared<CVCameraCapture>();
	default:
		break;
	}
}
