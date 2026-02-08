# build.ps1 - FT SCServo Qt6 DDS 빌드 스크립트 수정본 (ppDisable 추가)

param(
    [switch]$Clean,
    [switch]$Generate
)

$ErrorActionPreference = "Stop"

# 경로 설정
$ProjectRoot = $PSScriptRoot
$BuildDir = "$ProjectRoot\build"
$GenDir = "$ProjectRoot\gen"

# RTI DDS 환경 설정
$NDDSHOME = "C:\Program Files\rti_connext_dds-7.5.0"
$RTIDDSGEN = "$NDDSHOME\bin\rtiddsgen.bat"

# Qt6 경로
$Qt6Path = "C:\Qt\6.10.2\msvc2022_64"
$env:PATH = "$Qt6Path\bin;$env:PATH"
$env:CMAKE_PREFIX_PATH = $Qt6Path

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "  FT SCServo Qt6 DDS Build Script" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# 1. Clean
if ($Clean) {
    Write-Host "[1/4] Cleaning build directory..." -ForegroundColor Yellow
    if (Test-Path $BuildDir) { Remove-Item -Recurse -Force $BuildDir }
    if (Test-Path $GenDir) { Remove-Item -Recurse -Force $GenDir }
}

# 2. IDL 코드 생성
if ($Generate -or !(Test-Path "$GenDir\scservo.hpp")) {
    Write-Host "[2/4] Generating DDS code from IDL..." -ForegroundColor Yellow
    if (!(Test-Path $GenDir)) { New-Item -ItemType Directory -Force -Path $GenDir | Out-Null }
    
    Push-Location $GenDir
    try {
        # -ppDisable 옵션 추가
        & $RTIDDSGEN -language C++11 -d . "$ProjectRoot\scservo.idl" -replace -ppDisable
        if ($LASTEXITCODE -ne 0) { throw "rtiddsgen failed" }
        Write-Host "      Generated DDS code" -ForegroundColor Green
    }
    finally { Pop-Location }
}

# 3. CMake 구성
Write-Host "[3/4] Configuring CMake..." -ForegroundColor Yellow
if (!(Test-Path $BuildDir)) { New-Item -ItemType Directory -Force -Path $BuildDir | Out-Null }

Push-Location $BuildDir
try {
    # Qt 경로 명시적으로 전달
    cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_PREFIX_PATH="$Qt6Path"
    if ($LASTEXITCODE -ne 0) { throw "CMake configuration failed" }
}
finally { Pop-Location }

# 4. 빌드
Write-Host "[4/4] Building..." -ForegroundColor Yellow
Push-Location $BuildDir
try {
    cmake --build . --config Release --parallel
    if ($LASTEXITCODE -ne 0) { throw "Build failed" }
    Write-Host "      Build completed successfully!" -ForegroundColor Green
}
finally { Pop-Location }
