#-------------------------------------------------------------------
# This file is part of the CMake build system for CAVE_ENGINE
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

############################################################
# CaveEngine core library
############################################################

# define header and source files for the library
file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Public/*.h")
# list(APPEND HEADER_FILES
#     ${PROJECT_BINARY_DIR}/include/OgreBuildSettings.h
#     ${PROJECT_BINARY_DIR}/include/OgreComponents.h
#     ${PROJECT_BINARY_DIR}/include/OgreExports.h
#     ${CMAKE_CURRENT_SOURCE_DIR}/include/Ogre.i)

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Private/*.cpp")

# # Remove optional header files
# list(REMOVE_ITEM HEADER_FILES
#     "${CMAKE_CURRENT_SOURCE_DIR}/include/OgreDDSCodec.h"
#     "${CMAKE_CURRENT_SOURCE_DIR}/include/OgrePVRTCCodec.h"
#     "${CMAKE_CURRENT_SOURCE_DIR}/include/OgreETCCodec.h"
#     "${CMAKE_CURRENT_SOURCE_DIR}/include/OgreZip.h"
# )

# # Remove optional source files
# list(REMOVE_ITEM SOURCE_FILES
#     "${CMAKE_CURRENT_SOURCE_DIR}/src/OgreFileSystemLayerNoOp.cpp"
#     "${CMAKE_CURRENT_SOURCE_DIR}/src/OgreDDSCodec.cpp"
#     "${CMAKE_CURRENT_SOURCE_DIR}/src/OgrePVRTCCodec.cpp"
#     "${CMAKE_CURRENT_SOURCE_DIR}/src/OgreETCCodec.cpp"
#     "${CMAKE_CURRENT_SOURCE_DIR}/src/OgreZip.cpp"
#     "${CMAKE_CURRENT_SOURCE_DIR}/src/OgreSearchOps.cpp"
# )

file(GLOB ASSERTION_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Public/Assertion/*.h")
file(GLOB CONTAINERS_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Public/Containers/*.h")
file(GLOB CURVE_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Public/Curve/*.h")
file(GLOB DEBUG_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Public/Debug/*.h")
file(GLOB ENGINE_CONFIG_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Public/EngineConfig/*.h")
file(GLOB FILE_IO_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Public/FileIo/*.h")
file(GLOB LOCALIZATION_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Public/Input/*.h")
file(GLOB MATH_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Public/Math/*.h")
file(GLOB MEMORY_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Public/Memory/*.h")
file(GLOB MODULE_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Public/Module/*.h")
file(GLOB PARSER_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Public/Parser/*.h")
file(GLOB PROFILING_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Public/Profiling/*.h")
file(GLOB RANDOM_NUMBER_GENERATOR_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Public/RandomNumberGenerator/*.h")
file(GLOB STRING_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Public/String/*.h")
file(GLOB TEMPLATE_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Public/Template/*.h")
file(GLOB THREAD_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Public/Thread/*.h")
file(GLOB TIMER_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Public/Timer/*.h")
file(GLOB UNIT_TEST_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Public/UnitTest/*.h")
file(GLOB UTIL_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Public/Utils/*.h")

file(GLOB ASSERTION_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Private/Assertion/*.cpp")
file(GLOB CONTAINERS_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Private/Containers/*.cpp")
file(GLOB CURVE_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Private/Curve/*.cpp")
file(GLOB DEBUG_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Private/Debug/*.cpp")
file(GLOB ENGINE_CONFIG_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Private/EngineConfig/*.cpp")
file(GLOB FILE_IO_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Private/FileIo/*.cpp")
file(GLOB LOCALIZATION_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Private/Localization/*.cpp")
file(GLOB MATH_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Private/Math/*.cpp")
file(GLOB MEMORY_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Private/Memory/*.cpp")
file(GLOB MODULE_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Private/Module/*.cpp")
file(GLOB PARSER_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Private/Parser/*.cpp")
file(GLOB PROFILING_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Private/Profiling/*.cpp")
file(GLOB RANDOM_NUMBER_GENERATOR_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Private/RandomNumberGenerator/*.cpp")
file(GLOB STRING_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Private/String/*.cpp")
file(GLOB TEMPLATE_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Private/Template/*.cpp")
file(GLOB THREAD_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Private/Thread/*.cpp")
file(GLOB TIMER_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Private/Timer/*.cpp")
file(GLOB UNIT_TEST_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Private/UnitTest/*.cpp")

# # Add platform specific files
# if (EMSCRIPTEN)
#   set(PLATFORM_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/OgreFileSystemLayerNoOp.cpp")
# elseif (WIN32)
#   file(GLOB PLATFORM_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/WIN32/*.cpp")
# elseif (APPLE)
#   if (APPLE_IOS)
#     include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/iOS")
#     file(GLOB PLATFORM_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/iOS/*.cpp"
#       "${CMAKE_CURRENT_SOURCE_DIR}/src/iOS/*.mm")

#     set(PLATFORM_LIBS "")
#   else ()
#     include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/OSX")
#     file(GLOB PLATFORM_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/OSX/*.cpp"
#       "${CMAKE_CURRENT_SOURCE_DIR}/src/OSX/*.mm")
#     set(PLATFORM_LIBS "-framework CoreFoundation -framework Foundation")
#   endif ()
# elseif(ANDROID)
#   # required by OgrePlatformInformation.cpp
#   include_directories(${ANDROID_NDK}/sources/android/cpufeatures)

#   file(GLOB PLATFORM_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/Android/*.cpp")
#   # Remove optional platform source files
#   list(REMOVE_ITEM PLATFORM_SOURCE_FILES
#     "${CMAKE_CURRENT_SOURCE_DIR}/src/Android/OgreAPKZipArchive.cpp"
#   )
# elseif (UNIX)
#   file(GLOB PLATFORM_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/GLX/*.cpp")

#   set(PLATFORM_LIBS pthread)
# endif()

# if(NOT WIN32)
#     list(APPEND PLATFORM_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/OgreSearchOps.cpp")
# endif()

# # Configure threading files
# file(GLOB THREAD_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/Threading/*.h")
# include_directories("include/Threading" "src/")

# if (OGRE_THREAD_PROVIDER EQUAL 0)
# 	list(APPEND THREAD_HEADER_FILES
# 		include/Threading/OgreThreadDefinesNone.h
# 		include/Threading/OgreDefaultWorkQueueStandard.h
# 	)
# 	set(THREAD_SOURCE_FILES
# 		src/Threading/OgreDefaultWorkQueueStandard.cpp
# 	)
# elseif (OGRE_THREAD_PROVIDER EQUAL 1)
#   include_directories(${Boost_INCLUDE_DIRS})
#   link_directories(${Boost_LIBRARY_DIRS})

# 	list(APPEND THREAD_HEADER_FILES
# 		include/Threading/OgreThreadDefinesBoost.h
# 		include/Threading/OgreThreadHeadersBoost.h
# 		include/Threading/OgreDefaultWorkQueueStandard.h
# 	)
# 	set(THREAD_SOURCE_FILES
# 		src/Threading/OgreDefaultWorkQueueStandard.cpp
# 	)
# elseif (OGRE_THREAD_PROVIDER EQUAL 2)
# 	list(APPEND THREAD_HEADER_FILES
# 		include/Threading/OgreThreadDefinesPoco.h
# 		include/Threading/OgreThreadHeadersPoco.h
# 		include/Threading/OgreDefaultWorkQueueStandard.h
# 	)
# 	set(THREAD_SOURCE_FILES
# 		src/Threading/OgreDefaultWorkQueueStandard.cpp
# 	)
# elseif (OGRE_THREAD_PROVIDER EQUAL 3)
# 	list(APPEND THREAD_HEADER_FILES
# 		include/Threading/OgreThreadDefinesTBB.h
# 		include/Threading/OgreThreadHeadersTBB.h
# 		include/Threading/OgreDefaultWorkQueueTBB.h
# 	)
# 	set(THREAD_SOURCE_FILES
# 		src/Threading/OgreDefaultWorkQueueTBB.cpp
# 	)
# elseif (OGRE_THREAD_PROVIDER EQUAL 4)
# 	list(APPEND THREAD_HEADER_FILES
# 		include/Threading/OgreThreadDefinesSTD.h
# 		include/Threading/OgreThreadHeadersSTD.h
# 		include/Threading/OgreDefaultWorkQueueStandard.h
# 	)
# 	list(APPEND THREAD_SOURCE_FILES
# 		src/Threading/OgreDefaultWorkQueueStandard.cpp
# 	)
# endif ()

# list(APPEND HEADER_FILES ${THREAD_HEADER_FILES})

# set(LIBRARIES)

# if (OGRE_CONFIG_THREADS)
#   list(APPEND LIBRARIES ${OGRE_THREAD_LIBRARIES})
# endif ()

# if (OGRE_CONFIG_ENABLE_DDS)
#   list(APPEND HEADER_FILES include/OgreDDSCodec.h)
#   list(APPEND SOURCE_FILES src/OgreDDSCodec.cpp)
# endif ()

# if (OGRE_CONFIG_ENABLE_PVRTC)
#   list(APPEND HEADER_FILES include/OgrePVRTCCodec.h)
#   list(APPEND SOURCE_FILES src/OgrePVRTCCodec.cpp)
# endif ()

# if (OGRE_CONFIG_ENABLE_ETC)
#   list(APPEND HEADER_FILES include/OgreETCCodec.h)
#   list(APPEND SOURCE_FILES src/OgreETCCodec.cpp)
# endif ()

# if (OGRE_CONFIG_ENABLE_ASTC)
#   list(APPEND HEADER_FILES include/OgreASTCCodec.h)
#   list(APPEND SOURCE_FILES src/OgreASTCCodec.cpp)
# endif ()

# if (OGRE_CONFIG_ENABLE_ZIP)
#   include_directories("${ZZip_INCLUDE_DIRS}")
#   list(APPEND HEADER_FILES include/OgreZip.h)
#   list(APPEND SOURCE_FILES src/OgreZip.cpp)

#   if(ANDROID)
#     ADD_DEFINITIONS(-DZZIP_OMIT_CONFIG_H)
#     list(APPEND PLATFORM_SOURCE_FILES src/Android/OgreAPKZipArchive.cpp)
#   endif()

#   list(APPEND LIBRARIES "${ZZip_LIBRARIES}")
#   list(APPEND LIBRARIES ZLIB::ZLIB)
# endif ()

# if(OGRE_CONFIG_FILESYSTEM_UNICODE)
#   set_source_files_properties(src/OgreFileSystem.cpp
#     PROPERTIES COMPILE_DEFINITIONS _OGRE_FILESYSTEM_ARCHIVE_UNICODE)
#   set_source_files_properties(src/OgreZip.cpp
#     PROPERTIES COMPILE_DEFINITIONS _OGRE_FILESYSTEM_ARCHIVE_UNICODE)
# endif()

# if(OGRE_PROFILING_REMOTERY_PATH)
#   list(APPEND SOURCE_FILES ${OGRE_PROFILING_REMOTERY_PATH}/Remotery.c)
#   set_source_files_properties(${OGRE_PROFILING_REMOTERY_PATH}/Remotery.c PROPERTIES LANGUAGE CXX)
#   set_source_files_properties(src/OgreProfiler.cpp PROPERTIES COMPILE_DEFINITIONS USE_REMOTERY)
# endif()

# set (TARGET_LINK_FLAGS "")

# setup OgreMain target

# get_native_precompiled_header(OgreMain)
add_library(Core SHARED ${HEADER_FILES} ${SOURCE_FILES} 
						${CONTAINERS_HEADER_FILES} ${CONTAINERS_SOURCE_FILES} 
						${TEMPLATE_HEADER_FILES} ${TEMPLATE_SOURCE_FILES}
						${DEBUG_HEADER_FILES} ${DEBUG_SOURCE_FILES} 
						${MEMORY_HEADER_FILES} ${MEMORY_SOURCE_FILES} 
						${STRING_HEADER_FILES} ${STRING_SOURCE_FILES} 
						${UTIL_HEADER_FILES})

if(MSVC)
	target_compile_options(Core PRIVATE /W4 /WX)
else()
	target_compile_options(Core PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
# add_library(Core ${CAVE_ENGINE_LIB_TYPE} ${HEADER_FILES} ${SOURCE_FILES} ${ASSERTION_HEADER_FILES} ${ASSERTION_SOURCE_FILES} ${CONTAINERS_HEADER_FILES} ${CONTAINER_SOURCE_FILES} ${CURVE_HEADER_FILES} ${CURVE_SOURCE_FILES} ${DEBUG_HEADER_FILES} ${DEBUG_SOURCE_FILES})
# add_library(Core ${CAVE_ENGINE_LIB_TYPE} ${OgreMain_pch} ${HEADER_FILES} ${SOURCE_FILES} ${PLATFORM_HEADERS} ${PLATFORM_SOURCE_FILES} ${THREAD_HEADER_FILES} ${THREAD_SOURCE_FILES})

# if (WINDOWS_STORE OR WINDOWS_PHONE)
# 	set_target_properties(OgreMain PROPERTIES VS_WINRT_COMPONENT "true")
# endif ()

# generate_export_header(OgreMain 
#     EXPORT_MACRO_NAME _OgreExport
#     NO_EXPORT_MACRO_NAME _OgrePrivate
#     DEPRECATED_MACRO_NAME OGRE_DEPRECATED
#     EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/OgreExports.h)

target_precompile_headers(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Public/CorePch.h)

link_libraries(${tictor-BINARY_DIR})
target_include_directories(Core PUBLIC ${PROJECT_SOURCE_DIR}/CaveEngine/ThirdParty/tictoc)
target_link_libraries(Core PUBLIC tictoc)

# target_include_directories(Core PUBLIC 
#   "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Public>" 
#   "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>"
#   $<INSTALL_INTERFACE:include/CAVE_ENGINE>
#   PRIVATE "${CAVE_ENGINE_PROFILING_REMOTERY_PATH}")
target_include_directories(Core PUBLIC 
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Public>" 
  "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>"
  $<INSTALL_INTERFACE:include/CAVE_ENGINE>)
# target_include_directories(OgreMain PUBLIC 
#   "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>" 
#   "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>"
#   $<INSTALL_INTERFACE:include/OGRE>
#   PRIVATE "${OGRE_PROFILING_REMOTERY_PATH}")

# # In visual studio 2010 - 64 bit we get this error: "LINK : fatal error LNK1210: exceeded internal ILK size limit; link with /INCREMENTAL:NO"
# if(WIN32 AND MSVC10 AND CMAKE_CL_64)
#   set_target_properties(OgreMain PROPERTIES 
#                         VERSION ${OGRE_SOVERSION}
#                         LINK_FLAGS "/INCREMENTAL:NO"
#                       )
# else()
#   set_target_properties(OgreMain PROPERTIES VERSION ${OGRE_SOVERSION} SOVERSION ${OGRE_SOVERSION})
# endif()

# if (APPLE)
#   if (APPLE_IOS)
#     set_target_properties(OgreMain PROPERTIES INSTALL_NAME_DIR "OGRE")
#   else()
#     if(OGRE_BUILD_LIBS_AS_FRAMEWORKS)
#       set(OGRE_OSX_BUILD_CONFIGURATION "$ENV{PLATFORM_NAME}/$ENV{CONFIGURATION}")
#       add_custom_command(TARGET OgreMain POST_BUILD
#           COMMAND mkdir ARGS -p ${PROJECT_BINARY_DIR}/lib/${OGRE_OSX_BUILD_CONFIGURATION}/Ogre.framework/Headers/Threading
#           COMMAND ditto
#           ${PROJECT_SOURCE_DIR}/OgreMain/include/Threading/*.h ${PROJECT_BINARY_DIR}/lib/${OGRE_OSX_BUILD_CONFIGURATION}/Ogre.framework/Headers/Threading
#           COMMAND cd ${PROJECT_BINARY_DIR}/lib/${OGRE_OSX_BUILD_CONFIGURATION}/Ogre.framework/Headers
#           )

#       foreach(HEADER_PATH ${THREAD_HEADER_FILES})
#           get_filename_component(HEADER_FILE ${HEADER_PATH} NAME)
#           set(FWK_HEADER_PATH ${PROJECT_BINARY_DIR}/lib/${OGRE_OSX_BUILD_CONFIGURATION}/Ogre.framework/Headers/${HEADER_FILE})
#           add_custom_command(TARGET OgreMain POST_BUILD
#               COMMAND rm -f ${FWK_HEADER_PATH}
#               )
#       endforeach()
#     endif()

#     ogre_config_framework(OgreMain)
#   endif ()

#   if(OGRE_BUILD_LIBS_AS_FRAMEWORKS)
#     # Framework is called 'Ogre'
#     set_target_properties(OgreMain PROPERTIES	OUTPUT_NAME Ogre)
#   endif()
# endif ()
# target_link_libraries(OgreMain PUBLIC ${PLATFORM_LIBS} PRIVATE ${LIBRARIES} ${CMAKE_DL_LIBS})

# # specify a precompiled header to use
# add_native_precompiled_header(OgreMain "${CMAKE_CURRENT_SOURCE_DIR}/src/OgreStableHeaders.h")

# install Engine
# cave_engine_config_lib(Engine TRUE)
# install(FILES ${HEADER_FILES}
#   DESTINATION include/OGRE
# )
# install(FILES ${PLATFORM_HEADERS}
#   DESTINATION include/OGRE/${PLATFORM_HEADER_INSTALL}
# )
# install(FILES ${THREAD_HEADER_FILES}
# 	DESTINATION include/OGRE/Threading
# )