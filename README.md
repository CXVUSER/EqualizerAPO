# EqualizerAPO 1.3

1. Added support apo chaining(run another vendor apo's proprietary sound drivers 'realtek,creative,dolby')
2. Added partial(not ui) support for VST3

Apochaining syntax:
  APO: <GUID_to_apo_vendor_library> UI <GUID_to_apo_ui_vendor_library>

VST3: Dll <path_to_dll> Data <settings_for_plugin>

# Equalizer APO compilation 
Compilation prerequisites
1. The following software has been successfully used to compile Equalizer APO.

2. Visual Studio Community 2019. Unfortunately, downloads of non-current versions of Visual Studio are only possible with an MSDN or (free) Dev Essentials membership.

3. libsndfile. There are installers for the 64 and 32 bit version, so no need to compile from source. Has to be installed to C:\Program Files\libsndfile and C:\Program Files (x86)\libsndfile, respectively.

4. FFTW. The prebuilt 64/32 bit archives have to be extracted to C:\Program Files\fftw3 and C:\Program Files (x86)\fftw3, respectively. As mentioned on the linked page, the import libraries have to be created using the lib program of Visual Studio.

5. muParserX 3.0.1. Unfortunately, there are no prebuilt files, so compilation from source is needed. Please note that the version has to be 3.0.1 as an important feature was removed in 3.0.2 (semicolon). As version 3.0.1 is no longer available, it is now attached to this page including prebuilt static library files for MSVC2013. The zip file has to be extracted to C:\Program Files.

6. TCLAP. As this is a template library, only the source is needed, which will be compiled into the application. The downloaded tar.gz file has to be extracted to C:\Program Files. This library only used in the Benchmark application.

7. Qt 5. The 32 and 64 bit versions for MSVC2019 should be installed to C:\Qt. Qt Creator is used instead of Visual Studio as IDE. The prebuilt versions can be used for development although Equalizer APO ships with custom-built variants with reduced dependencies. Currently only needed to build the Configuration Editor.

8. NSIS. Needed to create the installer. Additionaly, the plugins NSISpcre and AccessControl are needed.
