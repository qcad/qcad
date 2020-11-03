QCAD - The Open Source 2D CAD
=============================

QCAD is a 2D CAD solution for Windows, macOS and Linux. Its core is developed in C++, based on the Qt tool kit.
QCAD can be extended through a C++ plugin interface as well as through its very powerful and complete scripting 
interface (ECMAScript/JavaScript).

History
-------
QCAD started as version 1 in October 1999 and has since evolved through version 2 (September 2003) 
and the current version 3 (from July 2012).

License
-------
The QCAD 3 source code is released under the GPLv3 open source license. Script add-ons and C++ plugins 
are released under their respective licenses.

Compilation
-----------
Detailed compilation instructions for Windows, macOS and Linux can be found on our web site at:

http://www.qcad.org/en/component/content/article/78-qcad/111-qcad-compilation-from-sources

Window
-------

- Clone

```
git clone https://github.com/wblong/qcad.git
```

- 编译qcad
```
cd c:\Users\me\qcad\qcad
c:\Qt\Qt5.10.1\5.10.1\msvc2017_64\bin\qmake -r CONFIG+=ractivated 
"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"
nmake release //vs2017 命令行工具运行
```
- 编译Qt Scripts 插件
```
cd c:\Users\me\qcd\qcd\src\3rdparty\qt-labs-qtscriptgenerator-5.10.1
c:\Qt\Qt5.10.1\5.10.1\msvc2017_64\bin\qmake -r CONFIG+=ractivated 
nmake release //vs2017 命令行工具运行
```
- 运行

```
release\qcad.exe
```

Extensions Help
-------

[help](./help/help.md)
