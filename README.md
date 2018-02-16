Magic Audio: A C++ DirectSound audio renderer for Windows. 

This code was originally intended to integrate with the open source Wild Magic 3D Game Engine authored by David Eberly of Geometric Tools. For convenience, modified versions of WildMagic's Vector3, Tuple and SmartPointer classes have been incorporated in this codebase to make it standalone with regard to the Wild Magic source.

This code was originally written in 2002, but (with a few modifications) still builds and runs fine.

Build Environment: MSVC 2017. Solutions for samples/tools will build any dependent libraries.

Projects:

Common: Library of utility shared code

AudioRenderer: Library providing abstract audio rendering interface and classes that are idependent of the specific, undelying renderer implementation.

DxAudioRenderer: A DirecSound implementation of the AudioRenderer interface.

WavToMaf: File conversion utility that converts WAV files to the renderer's internal MAF (Magic Audio File) format.

AudioFXDesigner: An MFC sample app that allows the user to apply and tweak a range of DirectSound audio effects to a sound, and save the salient parameters for each applied effect to a text file. A sample audio file is provided in the AudioFXDesigner\SampleAudio folder.

PositionalAudioDemo: A basic Win32/OpenGL app that demonstrates the use of the audio renderer's 3D positional audio system. This demo makes use of the freeglut binary distribution, which has been bundled with this repo for convenience.