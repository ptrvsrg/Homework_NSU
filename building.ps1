if ($args[0])
{
    $MY_PATH = $args[0]
}
else 
{
    $MY_PATH = "."
}

if (-not (Test-Path "$MY_PATH/CMakeLists.txt"))
{
    Write-Host -ForegroundColor Red "$MY_PATH/CMakeLists.txt not found"
    exit 1
}

if (Test-Path "$MY_PATH/build")
{
    Remove-Item -Path "$MY_PATH/build" -Recurse
}

cmake -B $MY_PATH/build -S $MY_PATH
cmake --build $MY_PATH/build

if (cmake --build $MY_PATH/build | Select-String -Pattern "error", "warning") 
{
    exit 1
}