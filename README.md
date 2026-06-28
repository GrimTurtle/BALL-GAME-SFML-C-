# C++ SFML Workspace Setup

This workspace is configured for MSYS2 UCRT64 + SFML with VS Code.

## Required tools
- MSYS2 installed at `C:\msys64`
- VS Code with the C/C++ extension installed
- Environment variable:
  - `MSYS2_UCRT64=C:\msys64\ucrt64`

## Install SFML
Open an MSYS2 UCRT64 shell and run:

```powershell
pacman -Syu
pacman -S mingw-w64-ucrt-x86_64-sfml
```

## Build and run
Use VS Code build task:
- `Ctrl+Shift+B`

Then run or debug with:
- `F5`

## What the workspace config does
- `.vscode/tasks.json` builds the active `.cpp` file with `g++.exe`
- `.vscode/c_cpp_properties.json` adds SFML header paths for IntelliSense
- `.vscode/launch.json` starts the debugger with MSYS2 `gdb.exe`

## Notes
- Make sure `MSYS2_UCRT64` is set in Windows system environment variables.
- If SFML apps fail at runtime, copy the DLLs from `C:\msys64\ucrt64\bin` into the output folder or add that path to `PATH`.
- Use this same workspace for other C++ files; the task and debugger are reusable.
