# RotatoExpress

A tool to rotate your playspace, allowing you to create Mixed Reality recording where the camera apears to orbit around the player.

## License

Distributed under the terms of the MIT License agreement. Copyright (C) 2019-2023 LIV Inc. 

[Upstream repository](https://github.com/LIV/RotatoExpress)

## How it works

Upon startup, this program caches the current playspace transform from OpenVR. The UI allows you to specify a rotation speed, and to offset the center. The rotation is locked by default, you will need to uncheck that

## Safety

This program *maniuplate* the Chaperone safety system of SteamVR in real time. It also add movement visible in the headset that do not match the real position of the headset. This needs to be used with care.

## Build instructions

You need to checkout this repository with submodules

```bash
git clone https://github.com/LIV/RotatoExpress
cd RotatoExpress
git submodule update --init --recursive
```

This program uses the CMake build system

```bash
mkdir build
cd build 
cmake .. #You may want to specify the Visual Studio 17 2022 generator in 64bit using the -G -A arguments.
```

The build folder contains a Visual Studio solution you can open. You can also do the above using CMake-gui

