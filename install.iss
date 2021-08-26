#define MyAppName "XAPKDetector"
#define MyAppVersion "0.02"
#define MyAppPublisher "NTInfo"
#define MyAppURL "ntinfo.biz"
#define MyAppExeName "xapkd.exe"

[Setup]
AppId={{4D856E80-2DE7-4DBC-857E-61614D75F028}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={userpf}\{#MyAppName}
DefaultGroupName={#MyAppName}
OutputDir=release
OutputBaseFilename=install
Compression=lzma
SolidCompression=yes
LicenseFile=LICENSE
PrivilegesRequired=lowest

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; 

[Files]
Source: "release\xapkdetector\*"; DestDir: "{app}\"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\Uninstall"; Filename: "{app}\unins000.exe"
Name: "{userdesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[InstallDelete]
Type: filesandordirs; Name: {app}\*;

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall

