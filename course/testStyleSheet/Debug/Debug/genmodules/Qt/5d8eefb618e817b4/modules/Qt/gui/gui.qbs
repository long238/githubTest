import qbs.FileInfo
import qbs.ModUtils
import qbs.Utilities
import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "Gui"

    property string uicName: "uic"

    FileTagger {
        patterns: ["*.ui"]
        fileTags: ["ui"]
    }

    Rule {
        inputs: ["ui"]

        Artifact {
            filePath: FileInfo.joinPaths(input.moduleProperty("Qt.core", "generatedHeadersDir"),
                                         'ui_' + input.completeBaseName + '.h')
            fileTags: ["hpp"]
        }

        prepare: {
            var cmd = new Command(ModUtils.moduleProperty(product, "binPath") + '/'
                                  + ModUtils.moduleProperty(product, "uicName"),
                                  [input.filePath, '-o', output.filePath])
            cmd.description = 'uic ' + input.fileName;
            cmd.highlight = 'codegen';
            return cmd;
        }
    }

    property string defaultQpaPlugin: "qwindows"
    architectures: ["x86_64"]
    targetPlatform: "windows"
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
    libNameForLinkerDebug: "Qt5Guid.lib"
    libNameForLinkerRelease: "Qt5Gui.lib"
    libFilePathDebug: "D:/QT/5.14.1/msvc2017_64/lib/Qt5Guid.lib"
    libFilePathRelease: "D:/QT/5.14.1/msvc2017_64/lib/Qt5Gui.lib"
    pluginTypes: ["platforms","platforms/darwin","xcbglintegrations","platformthemes","platforminputcontexts","generic","iconengines","imageformats","egldeviceintegrations"]

    cpp.entryPoint: qbs.targetOS.containsAny(["ios", "tvos"])
                      && Utilities.versionCompare(version, "5.6.0") >= 0
                  ? "_qt_main_wrapper"
                  : undefined

    cpp.defines: ["QT_GUI_LIB"]
    cpp.includePaths: ["D:/QT/5.14.1/msvc2017_64/include","D:/QT/5.14.1/msvc2017_64/include/QtGui","D:/QT/5.14.1/msvc2017_64/include/QtANGLE"]
    cpp.libraryPaths: []

    Properties {
        condition: Qt.core.staticBuild && qbs.targetOS.contains("ios")
        cpp.frameworks: base.concat(["UIKit", "QuartzCore", "CoreText", "CoreGraphics",
                                     "Foundation", "CoreFoundation", "AudioToolbox"])
    }
    cpp.frameworks: base
    Group {
        files: [Qt["gui"].libFilePath]
        filesAreTargets: true
        fileTags: ["dynamiclibrary_import"]
    }
}

