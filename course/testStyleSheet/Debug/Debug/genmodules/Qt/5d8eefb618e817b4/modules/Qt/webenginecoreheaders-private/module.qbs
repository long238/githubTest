import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "WebEngineCore"
    Depends { name: "Qt"; submodules: []}

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
    cpp.defines: ["QT_WEBENGINECOREHEADERS_LIB"]
    cpp.includePaths: ["D:/QT/5.14.1/msvc2017_64/include","D:/QT/5.14.1/msvc2017_64/include/QtWebEngineCore","D:/QT/5.14.1/msvc2017_64/include/QtWebEngineCore/5.14.1","D:/QT/5.14.1/msvc2017_64/include/QtWebEngineCore/5.14.1/QtWebEngineCore"]
    cpp.libraryPaths: []
    
}
