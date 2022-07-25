$HOME_DIR = (Get-Location).path
$EXIT_STATUS = 0
if ($IsWindows) { $CMAKE_LOG_PATH = "build\CMakeLog.txt" }
if ($IsLinux) { $CMAKE_LOG_PATH = "build/CMakeLog.txt" }

Write-Host ""

foreach ($MY_PATH in (((Get-ChildItem -Recurse 'CMakeLists.txt').FullName).replace('CMakeLists.txt', '')))
{
    Write-Host  -ForegroundColor White "Building $MY_PATH..."
    Set-Location $MY_PATH

    if (Test-Path "build")
    {
	    Remove-Item -Path build -Recurse
    }
	
    cmake -Bbuild > $null
    New-Item -Path $CMAKE_LOG_PATH > $null

    if ($IsWindows) 
    {
        cmake --build build > $CMAKE_LOG_PATH

        foreach ($str in (Get-Content -Path $CMAKE_LOG_PATH | Select-Object -Skip 3 -First 3))
        {
            Write-Host -ForegroundColor Green $str
        }

        if (Select-String -Path $CMAKE_LOG_PATH -Pattern "warning", "error")
        {
            $EXIT_STATUS = 1
            foreach ($str in (Get-Content -Path $CMAKE_LOG_PATH | Select-Object -Skip 6))
            {
                Write-Host -ForegroundColor Red $str
            }
            
            Write-Host -ForegroundColor Red Build failed
        }
        else
        {
            foreach ($str in (Get-Content -Path $CMAKE_LOG_PATH | Select-Object -Skip 6))
            {
                Write-Host -ForegroundColor Green $str
            }

            Write-Host -ForegroundColor Green Build completed    
        }
    }

    if ($IsLinux)
    {
        cmake --build build 2> $CMAKE_LOG_PATH

        if ((Get-Content -Path $CMAKE_LOG_PATH).length -eq 0)
        {
            Write-Host -ForegroundColor Green "Build completed"
        }
        else 
        {
            foreach ($str in (Get-Content -Path $CMAKE_LOG_PATH))
            {
                Write-Host -ForegroundColor Red $str
            }
            
            Write-Host -ForegroundColor Red "Build failed"
            $EXIT_STATUS = 1
        }
    }

    Write-Host ""
    Set-Location $HOME_DIR
}

exit $EXIT_STATUS