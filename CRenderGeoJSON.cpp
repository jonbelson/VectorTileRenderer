// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

// CRenderGeoJSON.cpp : implementation file
//

#include "pch.h"
#include "VectorTileRenderer.h"
#include "afxdialogex.h"
#include "CRenderGeoJSON.h"

#include <filesystem>

import core.d2drendertarget;
import core.logger;
import formats.geojson.parser;
import formats.geojson.renderer;
import geo.projector;


class CRenderGeoJSONViewModel
{
	CString m_sPROJDataDir;
	CString m_sGeoJSONFile;

public:
	enum struct Status
	{
		Ok,
		GeoJSONFileInvalid,
		CouldNotAccessFile,
		NoSuchDirectory,
		UnknownError
	};

	CRenderGeoJSONViewModel() {}

	Status SetGeoJSONFile(const CString& sGeoJSONFile)
	{
		m_sGeoJSONFile = sGeoJSONFile;

		return Status::Ok;
	}

	Status SetPROJDataDir(const CString& sPROJDataDir)
	{
		CStringA utf8 { CW2A(sPROJDataDir, CP_UTF8) };

		//std::error_code ec {};
		if (!std::filesystem::is_directory(std::string(utf8)))
		{
			return Status::NoSuchDirectory;
		}

		m_sPROJDataDir = sPROJDataDir;

		return Status::Ok;
	}

	Status RenderGeoJSON(const CString& sFileName)
	{
		using namespace geojson;

		CStringA utf8GeoJSONFile { CW2A(m_sGeoJSONFile, CP_UTF8) };

		auto geojson = parser::ParseFromFile((LPCSTR) utf8GeoJSONFile);
		if (!geojson)
		{
			switch (geojson.error())
			{
				case parser::Status::ResourceNotFound:
					return Status::CouldNotAccessFile;
				case parser::Status::InvalidJson:
					return Status::GeoJSONFileInvalid;
			}

			return Status::UnknownError;
		}

		UINT dpi = ::GetDpiForWindow(::GetDesktopWindow());

		float dpiScale = dpi/96.0f;

		constexpr int Size = 2000;
		auto renderTarget = new core::rendertarget::D2DRenderTarget(static_cast<int>(dpiScale*Size), static_cast<int>(dpiScale*Size));
		renderTarget->PushScale(dpiScale);

		renderTarget->SetLineColor(core::rendertarget::Color("red"));
		renderTarget->SetLineWidth(2.0f);
		renderTarget->SetFillColor(core::rendertarget::Color("green"));

		CStringA utf8PROJDataDir { CW2A(m_sPROJDataDir, CP_UTF8) };
		geo::projector::Projector::SetSearchPath(std::string(utf8PROJDataDir));

		auto projector = geo::projector::Projector::Create(geo::projector::CRS::WGS84, geo::projector::CRS::WebMercator);
		if (!projector)
		{
			core::logger::Error("Failed to create projector.\n");
			return Status::UnknownError;
		}

		double ppm = Size/4000000.0;// Size/40000.0;
		geo::projector::Coord origin = { -7.5572, 49.7668 };
		geo::projector::MapContext mapContext { .targetCrs = geo::projector::CRS::WebMercator, .pixelsToMetres = ppm, .origin = origin, .projector = *projector.value() };

		renderer::RenderContext renderContext{ .renderTarget = *renderTarget };

		renderer::Renderer renderer;
		renderer.Render(renderContext, mapContext, *geojson.value());

		CStringA utf8Filename { CW2A(sFileName, CP_UTF8) };
		renderTarget->Save((LPCSTR)utf8Filename);


		return Status::Ok;
	}

};

// CRenderGeoJSON dialog

IMPLEMENT_DYNAMIC(CRenderGeoJSON, CDialogEx)

CRenderGeoJSON::CRenderGeoJSON(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RENDER_GEOJSON_DIALOG, pParent)
{
	m_pViewModel = std::make_unique<CRenderGeoJSONViewModel>();
}

CRenderGeoJSON::~CRenderGeoJSON()
{
}

void CRenderGeoJSON::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MFCEDITBROWSE_GEOJSON, m_sGeoJSONFile);
	DDX_Text(pDX, IDC_MFCEDITBROWSE_PROJ_DATA, m_sPROJDataDir);
}


BEGIN_MESSAGE_MAP(CRenderGeoJSON, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_RENDER, &CRenderGeoJSON::OnBnClickedButtonRender)
END_MESSAGE_MAP()


// CRenderGeoJSON message handlers

void CRenderGeoJSON::OnBnClickedButtonRender()
{
	if (!UpdateData())
	{
		return;
	}

	PWSTR path {};
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Documents, 0, nullptr, &path)))
	{
		CString sFileName { path };
		sFileName.AppendFormat(L"\\GeoJSON.png");

		CoTaskMemFree(path);

		auto status = m_pViewModel->SetGeoJSONFile(m_sGeoJSONFile);
		if (status == CRenderGeoJSONViewModel::Status::Ok)
		{
			status = m_pViewModel->SetPROJDataDir(m_sPROJDataDir);
			if (status == CRenderGeoJSONViewModel::Status::Ok)
			{
				m_pViewModel->RenderGeoJSON(sFileName);
			}
		}
	}

}
