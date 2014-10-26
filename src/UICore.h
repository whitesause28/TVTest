#ifndef UI_CORE_H
#define UI_CORE_H


#include <vector>
#include "UISkin.h"


class CAppMain;
class CBasicDialog;

class CUICore
{
public:
	enum {
		POPUPMENU_DEFAULT = 0x0001U
	};

	enum MenuType {
		MENU_TUNERSELECT,
		MENU_RECORD,
		MENU_CAPTURE,
		MENU_BUFFERING,
		MENU_STREAMERROR,
		MENU_CLOCK,
		MENU_PROGRAMINFO
	};

	typedef CUISkin::PanAndScanInfo PanAndScanInfo;

	enum {
		PANANDSCAN_DEFAULT,
		PANANDSCAN_16x9,
		PANANDSCAN_LETTERBOX,
		PANANDSCAN_SUPERFRAME,
		PANANDSCAN_SIDECUT,
		PANANDSCAN_4x3,
		PANANDSCAN_32x9,
		PANANDSCAN_16x9_LEFT,
		PANANDSCAN_16x9_RIGHT,
		PANANDSCAN_CUSTOM
	};

	CUICore(CAppMain &App);
	~CUICore();
	bool SetSkin(CUISkin *pSkin);
	CUISkin *GetSkin() const { return m_pSkin; }
	HWND GetMainWindow() const;
	HWND GetDialogOwner() const;

	bool InitializeViewer(BYTE VideoStreamType=0);
	bool IsViewerInitializeError() const { return m_fViewerInitializeError; }
	bool FinalizeViewer();
	bool IsViewerEnabled() const;
	bool EnableViewer(bool fEnable);
	HWND GetViewerWindow() const;

	bool SetZoomRate(int Rate,int Factor=100);
	bool GetZoomRate(int *pRate,int *pFactor) const;
	int GetZoomPercentage() const;
	bool GetPanAndScan(PanAndScanInfo *pInfo) const;
	bool SetPanAndScan(const PanAndScanInfo &Info);

	int GetVolume() const;
	bool SetVolume(int Volume,bool fOSD=true);
	bool GetMute() const;
	bool SetMute(bool fMute);
	int GetStereoMode() const;
	bool SetStereoMode(int StereoMode);
	int GetAudioStream() const;
	int GetNumAudioStreams() const;
	bool SetAudioStream(int Stream);
	bool SwitchStereoMode();
	bool SwitchAudio();
	int FormatCurrentAudioText(LPTSTR pszText,int MaxLength) const;

	bool GetStandby() const { return m_fStandby; }
	bool SetStandby(bool fStandby);
	bool GetResident() const;
	bool SetResident(bool fResident);
	bool GetFullscreen() const { return m_fFullscreen; }
	bool SetFullscreen(bool fFullscreen);
	bool ToggleFullscreen();
	bool GetAlwaysOnTop() const { return m_fAlwaysOnTop; }
	bool SetAlwaysOnTop(bool fTop);
	bool PreventDisplaySave(bool fPrevent);

	void PopupMenu(const POINT *pPos=NULL,UINT Flags=0);
	void PopupSubMenu(int SubMenu,const POINT *pPos=NULL,UINT Flags=0);
	bool ShowSpecialMenu(MenuType Menu,const POINT *pPos=NULL,UINT Flags=0);
	void InitChannelMenu(HMENU hmenu);
	void InitTunerMenu(HMENU hmenu);
	bool ProcessTunerMenu(int Command);

	bool DoCommand(int Command);
	bool DoCommand(LPCTSTR pszCommand);
	bool DoCommandAsync(int Command);
	bool DoCommandAsync(LPCTSTR pszCommand);

	bool ConfirmChannelChange();
	bool ConfirmStopRecording();

	bool UpdateIcon();
	bool UpdateTitle();
	bool SetLogo(LPCTSTR pszFileName);

	bool RegisterModelessDialog(CBasicDialog *pDialog);
	bool UnregisterModelessDialog(CBasicDialog *pDialog);
	bool ProcessDialogMessage(MSG *pMessage);

private:
	CAppMain &m_App;
	CUISkin *m_pSkin;
	bool m_fStandby;
	bool m_fFullscreen;
	bool m_fAlwaysOnTop;

	HICON m_hicoLogoBig;
	HICON m_hicoLogoSmall;

	bool m_fViewerInitializeError;

	BOOL m_fScreenSaverActiveOriginal;
	/*
	BOOL m_fLowPowerActiveOriginal;
	BOOL m_fPowerOffActiveOriginal;
	*/

	std::vector<CBasicDialog*> m_ModelessDialogList;
};


#endif
