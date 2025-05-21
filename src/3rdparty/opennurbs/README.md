# openNURBS

[![Discourse users](https://img.shields.io/discourse/https/discourse.mcneel.com/users.svg)](https://discourse.mcneel.com/c/opennurbs)

The openNURBS Initiative provides CAD, CAM, CAE, and computer graphics software developers the tools to accurately transfer 3D geometry between applications.

The openNURBS Toolkit consists of C++ source code for a library that will read and write openNURBS 3D model files (_.3dm_). More than 400 software development teams and applications, including [_Rhinoceros®_](https://rhino3d.com), exchange 3D models using the openNURBS file format. Additionally, the Toolkit provides NURBS evaluation tools and elementary geometric and 3D view manipulation tools as well as including source code for several example programs.

For more information, see ["What is openNURBS?"](https://developer.rhino3d.com/guides/opennurbs/what-is-opennurbs).

## Getting started

1. Clone this repository.
2. Open opennurbs_public.sln, select the platform and configuration, and rebuild all.
3. Create your C++ project that will use opennurbs.
4. In your project's stdafx.h, put the following lines:

    ```cpp
    // defining OPENNURBS_PUBLIC_INSTALL_DIR enables automatic linking using pragmas
    #define OPENNURBS_PUBLIC_INSTALL_DIR "<MY_INSTALLPATH>"
    // uncomment the next line if you want to use opennurbs as a DLL
    //#define OPENNURBS_IMPORTS
    #include "<MY_INSTALLPATH>/opennurbs_public.h"
    ```
    Replace `<MY_INSTALLPATH>` with the full path where you installed opennurbs using forward slashes as directory separators.

Please see ["Getting started"](https://developer.rhino3d.com/guides/opennurbs/getting-started/) for more information about openNURBS including supported compilers, build instructions, and a description of the examples.

There's also a collection of [example 3dm files](example_files/) available for testing.

## Questions?

For technical support, please head over to [Discourse](https://discourse.mcneel.com/category/opennurbs).
