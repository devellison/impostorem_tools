RequestExecutionLevel Admin
Unicode True

!define PRODUCT_NAME "Impostorem Tools"
!define PRODUCT_VERSION "1.1.1.0"
!define PRODUCT_PUBLISHER "Impostorem"
!define PRODUCT_WEB_SITE "https://www.impostorem.com"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

!include "LogicLib.nsh"
!include "MUI.nsh"

!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "..\LICENSE"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY

Var FLINSTALL
Var ZGEV_DIR
!define MUI_DIRECTORYPAGE_VARIABLE $ZGEV_DIR
!insertmacro MUI_PAGE_DIRECTORY

!insertmacro MUI_PAGE_INSTFILES
!define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\README.pdf"
!insertmacro MUI_PAGE_FINISH
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_LANGUAGE "English"

; MUI end ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "..\bin\ImpostoremTools_${PRODUCT_VERSION}_Win64_Setup.exe"
InstallDir "$COMMONFILES64\VST3\Impostorem"
ShowInstDetails show
ShowUnInstDetails show

Function .onInit
  ReadRegStr $FLINSTALL HKLM "SOFTWARE\Image-Line\Shared\Paths" "Image-Line"
  
  ${If} $FLINSTALL == ""
	StrCpy $FLINSTALL $INSTDIR
  ${EndIf}

  StrCpy $ZGEV_DIR "$FLINSTALL\FL Studio 20\Plugins\Fruity\Effects\ZGameEditor Visualizer\Effects"
FunctionEnd

Section "VST Plugins" SEC01
  SetOutPath $INSTDIR
  SetOverwrite ifnewer
  File "..\bin\x64\Release\BeatDelay.vst3"
  File "..\bin\x64\Release\MIDIMuck.vst3"
  File "..\README.md"
  File "..\doc\pdf\README.pdf"
  File "..\LICENSE"

  SetOutPath "$INSTDIR\images"
  File "..\doc\images\VST_Compatible_Logo_Steinberg_with_TM_negative.png"
SectionEnd

Section "ZGEV Effects" SEC02
  SetOutPath "$ZGEV_DIR\Midi"
  File "..\externals\pianoshooter\PianoShooter.zgeproj"

  SetOutPath "$ZGEV_DIR\Text"
  File "..\externals\lyrictext\LyricText.zgeproj"
SectionEnd

Section -AdditionalIcons
  SetOutPath $INSTDIR
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateDirectory "$SMPROGRAMS\Impostorem"
  CreateShortCut "$SMPROGRAMS\Impostorem\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\Impostorem\Uninstall.lnk" "$INSTDIR\uninstall.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninstall.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninstall.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "ZGEV_DIR" "$ZGEV_DIR"
SectionEnd

; Section descriptions
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC01} "VST Plugins"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC02} "ZGameEditor Visualizer Effects"
!insertmacro MUI_FUNCTION_DESCRIPTION_END


Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) was successfully removed from your computer."
FunctionEnd

Function un.onInit
  ReadRegStr $ZGEV_DIR ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "ZGEV_DIR"
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove $(^Name) and all of its components?" IDYES +2
  Abort
FunctionEnd

Section Uninstall
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninstall.exe"
  Delete "$INSTDIR\images\VST_Compatible_Logo_Steinberg_with_TM_negative.png"
  RMDir "$INSTDIR\images"
  Delete "$INSTDIR\README.md"
  Delete "$INSTDIR\README.pdf"
  Delete "$INSTDIR\LICENSE"
  Delete "$INSTDIR\BeatDelay.vst3"
  Delete "$INSTDIR\MIDIMuck.vst3"
  Delete "$ZGEV_DIR\Midi\Pianoshooter.zgeproj"
  Delete "$ZGEV_DIR\Text\LyricText.zgeproj"

  Delete "$SMPROGRAMS\Impostorem\Uninstall.lnk"
  Delete "$SMPROGRAMS\Impostorem\Website.lnk"

  RMDir "$SMPROGRAMS\Impostorem"
  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  SetAutoClose true
SectionEnd
