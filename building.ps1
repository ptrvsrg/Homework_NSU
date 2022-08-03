if ($args[0])
{
    $HOME_DIR = (Get-Location).path
    $MY_PATH = $args[0]

    Set-Location $MY_PATH
    if (-not (Test-Path "CMakeLists.txt"))
    {
        Write-Host -ForegroundColor Red "CMakeLists.txt not found"
        exit 1
    }

    Write-Host -ForegroundColor Green "Building $MY_PATH..." -NoNewline

    if (Test-Path "build")
    {
        Remove-Item -Path build -Recurse
    }

    cmake -Bbuild
    cmake --build build

    Write-Host ""
    Set-Location $HOME_DIR

    if (Test-Path "build/Debug/*") 
    {
        exit 0
    }
    else 
    {
        exit 1
    }
}
else
{
    cmake -Bbuild
    cmake --build build
    
    $DEBUG_DIR = ((Get-ChildItem -Path build -Recurse Debug).FullName)

    foreach ($path in $DEBUG_DIR) 
    {
        if (-not (Test-Path "$path/*")) 
        {
            exit 1
        }
    }
}