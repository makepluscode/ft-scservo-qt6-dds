# run.ps1 - FT SCServo Qt6 DDS 실행 스크립트 수정본

param(
    [ValidateSet("daemon", "gui", "both")]
    [string]$Mode = "both"
)

$ErrorActionPreference = "Stop"

# 경로 설정
$ProjectRoot = $PSScriptRoot
$BuildDir = "$ProjectRoot\build\Release"
$QoSFile = "$ProjectRoot\USER_QOS_PROFILES.xml" # 원본 위치 사용

# RTI DDS 런타임 PATH & QoS
$NDDSHOME = "C:\Program Files\rti_connext_dds-7.5.0"
$env:PATH = "$NDDSHOME\lib\x64Win64VS2017;$env:PATH"
# 중복 로드 에러 방지를 위해 환경변수 비움 (로컬 파일 자동 감지 활용)
$env:NDDS_QOS_PROFILES = "" 

# Qt6 런타임 PATH
$Qt6Path = "C:\Qt\6.10.2\msvc2022_64"
$env:PATH = "$Qt6Path\bin;$env:PATH"

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "  FT SCServo Qt6 DDS Runner" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "Qt6 Path:  $Qt6Path" -ForegroundColor Gray
Write-Host "NDDS Home: $NDDSHOME" -ForegroundColor Gray
Write-Host ""

# 실행 파일 확인
$DaemonExe = "$BuildDir\ServoDaemon.exe"
$GuiExe = "$BuildDir\ServoGUI.exe"

if (!(Test-Path $DaemonExe) -or !(Test-Path $GuiExe)) {
    Write-Host "Error: Executables not found. Run build.ps1 first." -ForegroundColor Red
    exit 1
}

switch ($Mode) {
    "daemon" {
        Write-Host "Starting ServoDaemon..." -ForegroundColor Yellow
        Push-Location $BuildDir
        & $DaemonExe
        Pop-Location
    }
    "gui" {
        Write-Host "Starting ServoGUI..." -ForegroundColor Yellow
        Push-Location $BuildDir
        & $GuiExe
        Pop-Location
    }
    "both" {
        Write-Host "Starting both applications..." -ForegroundColor Yellow
        Write-Host ""
        
        Write-Host "[1] Launching ServoDaemon in new terminal..." -ForegroundColor Gray
        Start-Process powershell -ArgumentList "-NoExit", "-Command", @"
            cd '$BuildDir'
            `$env:PATH = '$NDDSHOME\lib\x64Win64VS2017;'+`$env:PATH
            `$env:NDDS_QOS_PROFILES = ''
            .\ServoDaemon.exe
"@
        
        Start-Sleep -Seconds 1
        
        Write-Host "[2] Launching ServoGUI..." -ForegroundColor Gray
        Push-Location $BuildDir
        & $GuiExe
        Pop-Location
    }
}
