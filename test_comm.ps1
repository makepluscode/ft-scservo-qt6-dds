# test_comm.ps1 - DDS Communication Verification Script (Improved)

$ErrorActionPreference = "Stop"
$ProjectRoot = $PSScriptRoot
$BuildDir = "$ProjectRoot\build\Release"

# RTI DDS & Qt6 Env
$NDDSHOME = "C:\Program Files\rti_connext_dds-7.5.0"
$Qt6Path = "C:\Qt\6.10.2\msvc2022_64"

$env:PATH = "$NDDSHOME\lib\x64Win64VS2017;$Qt6Path\bin;$env:PATH"

# RTI 라이선스 파일 설정
$env:RTI_LICENSE_FILE = "$NDDSHOME\rti_license.dat"

# 중요: NDDS_QOS_PROFILES 환경변수 제거 (자동 로드 중복 방지)
if (Test-Path env:NDDS_QOS_PROFILES) { Remove-Item env:NDDS_QOS_PROFILES }

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "  DDS Communication Test (Retry)" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan

# Clean previous logs
if (Test-Path "$ProjectRoot\daemon_log.txt") { Remove-Item "$ProjectRoot\daemon_log.txt" -Force -ErrorAction SilentlyContinue }

# 1. Start Daemon in Background
Write-Host "[1/3] Starting ServoDaemon..." -ForegroundColor Yellow
$DaemonLog = "$ProjectRoot\daemon_log.txt"
$DaemonProcess = Start-Process -FilePath "$BuildDir\ServoDaemon.exe" -PassThru -NoNewWindow -RedirectStandardOutput $DaemonLog -WorkingDirectory $ProjectRoot

# Wait for Daemon to init
Start-Sleep -Seconds 3

# 2. Run GUI in Test Mode
Write-Host "[2/3] Running ServoGUI in Test Mode..." -ForegroundColor Yellow
try {
    $PInfo = New-Object System.Diagnostics.ProcessStartInfo
    $PInfo.FileName = "$BuildDir\ServoGUI.exe"
    $PInfo.Arguments = "--test"
    $PInfo.RedirectStandardOutput = $true
    $PInfo.UseShellExecute = $false
    $PInfo.WorkingDirectory = $ProjectRoot
    
    $P = [System.Diagnostics.Process]::Start($PInfo)
    $Output = $P.StandardOutput.ReadToEnd()
    $P.WaitForExit()
    
    # Write-Host "$Output" -ForegroundColor Gray
    
    # 더 확실한 문자열 매칭
    if ($Output -match "TEST_SUCCESS" -or $Output.Contains("TEST_SUCCESS")) {
        Write-Host ""
        Write-Host "✅ TEST PASSED: Communication Verified!" -ForegroundColor Green
    }
    else {
        Write-Host ""
        Write-Host "❌ TEST FAILED: 'TEST_SUCCESS' not found." -ForegroundColor Red
        
        Write-Host "--- GUI Output (Last 10 lines) ---" -ForegroundColor Gray
        $Output -split "`n" | Select-Object -Last 10 | ForEach-Object { Write-Host $_ }

        if (Test-Path $DaemonLog) {
            Write-Host "--- Daemon Log ---" -ForegroundColor Gray
            Get-Content $DaemonLog | Write-Host -ForegroundColor Gray
        }
    }

}
catch {
    Write-Host "❌ TEST FAILED: Exception occurred." -ForegroundColor Red
    Write-Host $_
}
finally {
    # 3. Cleanup
    Write-Host "[3/3] Stopping Daemon..." -ForegroundColor Yellow
    Stop-Process -Id $DaemonProcess.Id -Force -ErrorAction SilentlyContinue
    
    # 프로세스 종료 대기
    Start-Sleep -Seconds 1
    
    if (Test-Path $DaemonLog) { 
        Remove-Item $DaemonLog -Force -ErrorAction SilentlyContinue 
    }
}
