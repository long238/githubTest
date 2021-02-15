import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "Quick3DRuntimeRender"
    Depends { name: "Qt"; submodules: ["quick3drender-private","quick3dassetimport-private","quick3druntimerender"]}

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
    cpp.includePaths: ["D:/QT/5.14.1/msvc2017_64/include/QtQuick3DRuntimeRender/5.14.1","D:/QT/5.14.1/msvc2017_64/include/QtQuick3DRuntimeRender/5.14.1/QtQuick3DRuntimeRender"]
    cpp.libraryPaths: []
    
}
