import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "Quick3DRender"
    Depends { name: "Qt"; submodules: ["quick3dutils-private","quick3drender"]}

    architectures: ["x86_64"]
    targetPlatform: "windows"
    hasLibrary: false
    staticLibsDebug: []
    staticLibsRelease: []
    dynamicLibsDebug: []
    dynamicLibsRelease: []
    linkerFlagsDebug: []
    linkerFlagsRelease: []
    frameworksDebug: []
    frameworksRelease: []
    frameworkPathsDebug: []
    frameworkPathsRelease: []
    libNameForLinkerDebug: undefined
    libNameForLinkerRelease: undefined
    libFilePathDebug: undefined
    libFilePathRelease: undefined
    pluginTypes: []
    moduleConfig: []
    cpp.defines: []
    cpp.includePaths: ["D:/QT/5.14.1/msvc2017_64/include/QtQuick3DRender/5.14.1","D:/QT/5.14.1/msvc2017_64/include/QtQuick3DRender/5.14.1/QtQuick3DRender"]
    cpp.libraryPaths: []
    
}
