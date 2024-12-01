@_default:
    just --list

alias c := configure
configure:
    cmake -S . -B build

alias b := build
build:
    cmake --build build
    @just _add-shortcut-debug

alias br := build-release
build-release:
    cmake --build build --config=Release
    @just _add-shortcut-release

@_add-shortcut-debug:
    pwsh -Command ' \
      $ShortcutPath = "$(pwd)/Run_DEBUG.lnk"; \
      $TargetPath = "$(pwd)/build/Debug/raekan.exe"; \
      $WshShell = New-Object -ComObject WScript.Shell; \
      $Shortcut = $WshShell.CreateShortcut($ShortcutPath); \
      $Shortcut.TargetPath = $TargetPath; \
      $Shortcut.WorkingDirectory = "$(pwd)"; \
      $Shortcut.Save(); \
    '
@_add-shortcut-release:
    pwsh -Command ' \
      $ShortcutPath = "$(pwd)/Run_RELEASE.lnk"; \
      $TargetPath = "$(pwd)/build/Release/raekan.exe"; \
      $WshShell = New-Object -ComObject WScript.Shell; \
      $Shortcut = $WshShell.CreateShortcut($ShortcutPath); \
      $Shortcut.TargetPath = $TargetPath; \
      $Shortcut.WorkingDirectory = "$(pwd)"; \
      $Shortcut.Save(); \
    '
