$HOME_DIR = (Get-Location).path
$EXIT_STATUS = 0

foreach ($MY_PATH in (((Get-ChildItem -Recurse 'CMakeLists.txt').FullName).replace('\CMakeLists.txt', '')))
{
    Write-Host  -ForegroundColor White "Building $MY_PATH\..."
    Set-Location $MY_PATH
	Remove-Item -Path build -Recurse 2> $null
	cmake -Bbuild > $null
    New-Item -Path "build\CMakeLog.txt" > $null
	cmake --build build --config Release > "build\CMakeLog.txt"

    foreach ($str in (Get-Content -Path "build\CMakeLog.txt" | Select-Object -Skip 3 -First 3))
    {
        Write-Host -ForegroundColor DarkGreen $str
    }

    if (Select-String -Path "build\CMakeLog.txt" -Pattern "warning", "error")
    {
        $EXIT_STATUS = 1
        foreach ($str in (Get-Content -Path "build\CMakeLog.txt" | Select-Object -Skip 6))
        {
            Write-Host -ForegroundColor DarkRed $str
        }
        
        Write-Host -ForegroundColor Red Build failed
    }
    else
    {
        foreach ($str in (Get-Content -Path "build\CMakeLog.txt" | Select-Object -Skip 6))
        {
            Write-Host -ForegroundColor DarkGreen $str
        }

        Write-Host -ForegroundColor Green Build completed    
    }

    Write-Host ""
	Remove-Item -Path build -Recurse 2> $null
    Set-Location $HOME_DIR
}

exit $EXIT_STATUS