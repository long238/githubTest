import '../QtModule.qbs' as QtModule

QtModule {
    qtModuleName: "Bootstrap"
    Depends { name: "Qt"; submodules: []}

    architectures: ["x86_64"]
    targetPlatform: "windows"
    hasLibrary: true
    staticLibsDebug: []
    staticLibsRelease: ["user32.lib","ole32.lib","advapi32.lib","shell32.lib","netapi32.lib","C:/Utils/postgresql/pgsql/lib/zlib.lib"]
    dynamicLibsDebug: []
    dynamicLibsRelease: []
    linkerFlagsDebug: []
    linkerFlagsRelease: []
    frameworksDebug: []
    frameworksRelease: []
    frameworkPathsDebug: []
    frameworkPathsRelease: []
    libNameForLinkerDebug: "Qt5Bootstrapd.lib"
    libNameForLinkerRelease: "Qt5Bootstrap.lib"
    libFilePathDebug: undefined
    libFilePathRelease: "D:/QT/5.14.1/msvc2017_64/lib/Qt5Bootstrap.lib"
    pluginTypes: []
    moduleConfig: ["lex","yacc","depend_includepath","testcase_targets","import_qpa_plugin","windows","qt_build_extra","file_copies","qmake_use","qt","warn_on","release","link_prl","flat","debug_and_release","precompile_header","autogen_precompile_source","embed_manifest_dll","embed_manifest_exe","release","no_plugin_manifest","win32","msvc","copy_dir_files","sse2","aesni","sse3","ssse3","sse4_1","sse4_2","avx","avx2","avx512f","avx512bw","avx512cd","avx512dq","avx512er","avx512ifma","avx512pf","avx512vbmi","avx512vl","compile_examples","f16c","force_debug_info","largefile","precompile_header","rdrnd","shani","x86SimdAlways","prefix_build","force_independent","utf8_source","create_prl","link_prl","prepare_docs","qt_docs_targets","no_private_qt_headers_warning","QTDIR_build","qt_example_installs","exceptions_off","testcase_exceptions","warning_clean","release","ReleaseBuild","Release","build_pass","c++11","minimal_syncqt","internal_module","force_bootstrap","gc_binaries","no_core_dep","static","relative_qt_rpath","git_build","target_qt","c++11","strict_c++","c++14","c++1z","need_fwd_pri","qt_install_module","create_cmake","skip_target_version_ext","release","ReleaseBuild","Release","build_pass","have_target","staticlib","exclusive_builds","debug_info","no_autoqmake","thread"]
    cpp.defines: ["QT_BOOTSTRAP_LIB","QT_VERSION_STR=\\\"\\\\\\\"5.14.1\\\\\\\"\\\"","QT_VERSION_MAJOR=5","QT_VERSION_MINOR=14","QT_VERSION_PATCH=1","QT_BOOTSTRAPPED","QT_NO_CAST_TO_ASCII"]
    cpp.includePaths: ["D:/QT/5.14.1/msvc2017_64/include","D:/QT/5.14.1/msvc2017_64/include/QtCore","D:/QT/5.14.1/msvc2017_64/include/QtCore/5.14.1","D:/QT/5.14.1/msvc2017_64/include/QtCore/5.14.1/QtCore","D:/QT/5.14.1/msvc2017_64/include/QtXml","D:/QT/5.14.1/msvc2017_64/include/QtXml/5.14.1","D:/QT/5.14.1/msvc2017_64/include/QtXml/5.14.1/QtXml"]
    cpp.libraryPaths: ["C:/openssl/lib","C:/Utils/my_sql/mysql-5.7.25-winx64/lib","C:/Utils/postgresql/pgsql/lib"]
    isStaticLibrary: true
Group {
        files: [Qt["bootstrap-private"].libFilePath]
        filesAreTargets: true
        fileTags: ["staticlibrary"]
    }
}
