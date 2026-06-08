; -- 64Bit.iss --
; Demonstrates installation of a program built for the x64 (a.k.a. AMD64)
; architecture.
; To successfully run this installation and the program it installs,
; you must have a "x64" edition of Windows or Windows 11 on Arm.

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING .ISS SCRIPT FILES!


[Languages]
Name: "spanish"; MessagesFile: "compiler:Languages\Spanish.isl"


[Setup]
AppName=Interfaz TIVA PC
AppVersion=1.1
WizardStyle=modern dynamic includetitlebar windows11
DefaultDirName={autopf}\GUILLESOFT\LoadMonitor
DefaultGroupName=Load Monitor
;UninstallDisplayIcon={app}\MyProg.exe Windows will select on its own
Compression=zip
SolidCompression=yes
OutputBaseFilename=Load Monitor Installer
OutputDir=D:\TFG\QT\installer
; "ArchitecturesAllowed=x64compatible" specifies that Setup cannot run
; on anything but x64 and Windows 11 on Arm.
ArchitecturesAllowed=x64compatible
; "ArchitecturesInstallIn64BitMode=x64compatible" requests that the
; install be done in "64-bit mode" on x64 or Windows 11 on Arm,
; meaning it should use the native 64-bit Program Files directory and
; the 64-bit view of the registry.
ArchitecturesInstallIn64BitMode=x64compatible
SetupIconFile=D:\TFG\QT\Designer.ico

[Files]
Source: "release\*"; DestDir: "{app}\bin";
Source : "release\generic\*"; DestDir: "{app}\bin\generic";
Source : "release\iconengines\*"; DestDir: "{app}\bin\iconengines";
Source : "release\imageformats\*"; DestDir: "{app}\bin\imageformats";
Source : "release\networkinformation\*"; DestDir: "{app}\bin\networkinformation";
Source : "release\platforms\*"; DestDir: "{app}\bin\platforms";
Source : "release\styles\*"; DestDir: "{app}\bin\styles";
Source : "release\tls\*"; DestDir: "{app}\bin\tls";
Source : "release\translations\*"; DestDir: "{app}\bin\translations";
Source : "Designer.ico"; DestDir:{app};

[Tasks]
Name: "desktopicon"; Description: "Crear un acceso directo en el escritorio";GroupDescription:"Acciones opcionales:"; 

[Icons]
Name: "{group}\Load Monitor"; Filename: "{app}\bin\LoadMonitor.exe"; IconFilename:"{app}\Designer.ico"
Name: "{commondesktop}\Load Monitor"; Filename: "{app}\bin\LoadMonitor.exe"; IconFilename:"{app}\Designer.ico"; Tasks:desktopicon

