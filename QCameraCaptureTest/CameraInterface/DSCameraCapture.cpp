#include "DSCameraCapture.h"
#include <strmif.h>
#include <uuids.h>
#include <control.h>
#pragma  comment(lib, "Strmiids.lib")

DSCameraCapture::DSCameraCapture() : CameraInterface()
{

}

DSCameraCapture::~DSCameraCapture()
{

}

void DSCameraCapture::GetAvailableCaptureDevices(std::list<std::string>& listDevices)
{
	ICreateDevEnum* pDevEnum = nullptr;
	IEnumMoniker* pEnum = nullptr;
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, nullptr, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, reinterpret_cast<void**>(&pDevEnum));
	if (SUCCEEDED(hr))
	{
		hr = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnum, 0);
	}
	if (!pEnum)
	{
		return;
	}
	IMoniker* pMoniker = nullptr;
	while (S_OK == pEnum->Next(1, &pMoniker, nullptr))
	{
		IPropertyBag* pPropBag;
		if (FAILED(pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void**)(&pPropBag))))
		{
			pMoniker->Release();
			continue;
		}

		VARIANT varName;
		VariantInit(&varName);
		hr = pPropBag->Read(L"Description", &varName, 0);
		if (FAILED(hr))
		{
			hr = pPropBag->Read(L"FriendlyName", &varName, 0); 
		}
		if (SUCCEEDED(hr))
		{
			char displayName[128];
			WideCharToMultiByte(CP_ACP, 0, varName.bstrVal, -1, displayName, 128, "", nullptr);
			listDevices.push_back(displayName);
			VariantClear(&varName);
		}
		pPropBag->Release();
		pMoniker->Release();
	}
}

void DSCameraCapture::CameraCaptureStart(int nIndex, std::function<void(const std::vector<unsigned char>&, int, int)> funcPresent)
{
	/*
	IGraphBuilder* m_pGraphBuilder = nullptr;
	ICaptureGraphBuilder2* m_pCaptureBuilder = nullptr;

	HRESULT hr = CoCreateInstance(CLSID_FilterGraph, nullptr, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&m_pGraphBuilder);
	hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, nullptr, CLSCTX_INPROC, IID_ICaptureGraphBuilder2, (void**)m_pCaptureBuilder);
	m_pCaptureBuilder->SetFiltergraph(m_pGraphBuilder);
	IMediaControl* m_pMediaControl = nullptr;
	hr = m_pGraphBuilder->QueryInterface(IID_IMediaControl, (void**)&m_pMediaControl);

	CComPtr<ICreateDevEnum> pCreateDevEnum;
	CoCreateInstance(CLSID_SystemDeviceEnum, nullptr, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, (void**)&pCreateDevEnum);
	*/

}

void DSCameraCapture::CameraCaptureSettings(const CameraSettings& settings)
{

}

void DSCameraCapture::CameraCaptureRestart()
{
	
}

void DSCameraCapture::CameraCaptureStop()
{
	
}

bool DSCameraCapture::GetCapture(std::vector<unsigned char>& vData, int& nWidth, int& nHeight)
{
	return true;
}
