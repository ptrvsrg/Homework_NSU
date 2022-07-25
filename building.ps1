$HOME_DIR = (Get-Location).path
$EXIT_STATUS = 0

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

    if ($IsWindows) 
    {
        $CMAKE_LOG = (cmake --build build)

        foreach ($str in ($CMAKE_LOG | Select-Object -Skip 3 -First 3))
        {
            Write-Host -ForegroundColor Green $str
        }

        if ($CMAKE_LOG | Select-String -Pattern "warning", "error")
        {
            $EXIT_STATUS = 1
            foreach ($str in ($CMAKE_LOG | Select-Object -Skip 6))
            {
                Write-Host -ForegroundColor Red $str
            }
            
            Write-Host -ForegroundColor Red Build failed
        }
        else
        {
            foreach ($str in ($CMAKE_LOG | Select-Object -Skip 6))
            {
                Write-Host -ForegroundColor Green $str
            }

            Write-Host -ForegroundColor Green Build completed    
        }
    }

    if ($IsLinux)
    {
        $CMAKE_LOG = (cmake --build build)

        foreach ($str in ($CMAKE_LOG | Select-Object -First 2))
        {
            Write-Host -ForegroundColor Green $str
        }

        if ($CMAKE_LOG | Select-String -Pattern "warning", "error")
        {
            $EXIT_STATUS = 1
            foreach ($str in ($CMAKE_LOG | Select-Object -Skip 2))
            {
                Write-Host -ForegroundColor Red $str
            }
            
            Write-Host -ForegroundColor Red Build failed
        }
        else
        {
            foreach ($str in ($CMAKE_LOG | Select-Object -Skip 2))
            {
                Write-Host -ForegroundColor Green $str
            }

            Write-Host -ForegroundColor Green Build completed    
        }
    }

    Write-Host ""
    Set-Location $HOME_DIR
}

exit $EXIT_STATUS