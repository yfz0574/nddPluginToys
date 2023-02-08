cmake_minimum_required(VERSION 3.25)
project(nddPluginToys CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${PROJECT_SOURCE_DIR}/ui)
			#set(CMAKE_VERBOSE_MAKEFILEON ON)
			#set(CMAKE_VERBOSE ON)
set(NDD_ROOT F:/myproj/notepad--)
# Add in Qt5
set (CMAKE_PREFIX_PATH "H:/develop/Qt/5.15.2/msvc2019_64")
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Network Concurrent) 
list(APPEND QTMODULES Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Concurrent Qt5::Network )	
				
# when cmake version is over 2.8.8, we may use the code below to replace setting CMAKE_CXX_FLAGS
#-----------------------------------
#if(Qt5_POSITION_INDEPENDENT_CODE)
#	set(CMAKE_POSITION_INDEPENDENT_CODE ON)
#endif()
#qt5_wrap_ui(ui_FILES ${CMAKE_SOURCE_DIR}/src/plugin/nddPluginToys/ui/qttoysclass.ui)  这句加上可能跟set(CMAKE_AUTOUIC ON)冲突了，导致项目加载失败
			#qt5_add_resources(qrc_FILES drawable.qrc)
	
######### LIB_OPENCC
set(OPENCC_BUILD_PATH F:/libsrc/OpenCC/build)
set(OPENCC_PATH F:/libsrc/OpenCC)

set(LIB_OPENCC_RELEASE  ${OPENCC_BUILD_PATH}/src/Release/opencc.dll )	
set(LIB_OPENCC_DEBUG    ${OPENCC_BUILD_PATH}/src/Debug/opencc.dll   )	
				#add_library(libopencc SHARED IMPORTED GLOBAL)
add_library(libopencc SHARED IMPORTED)

set_target_properties(libopencc PROPERTIES
  IMPORTED_LOCATION_RELEASE "${LIB_OPENCC_RELEASE}"
  IMPORTED_LOCATION_DEBUG "${LIB_OPENCC_DEBUG}"
  IMPORTED_IMPLIB_RELEASE "${OPENCC_BUILD_PATH}/src/Release/opencc.lib"
  IMPORTED_IMPLIB_DEBUG "${OPENCC_BUILD_PATH}/src/Debug/opencc.lib"
  IMPORTED_CONFIGURATIONS "RELEASE;DEBUG"
)
###### QSCINT
set(QSCINT_PATH F:/myproj/notepad--/src/qscint)
set(QSCINT_BUILD_PATH ${PROJECT_SOURCE_DIR}/lib/qscint)
set(LIB_QSCINT_RELEASE  ${QSCINT_BUILD_PATH}/Release/qmyedit_qt5.dll )	
set(LIB_QSCINT_DEBUG    ${QSCINT_BUILD_PATH}/Debug/qmyedit_qt5.dll   )	
				#add_library(qscint SHARED IMPORTED GLOBAL)
add_library(qscint SHARED IMPORTED)

set_target_properties(qscint PROPERTIES
  IMPORTED_LOCATION_RELEASE "${LIB_QSCINT_RELEASE}"
  IMPORTED_LOCATION_DEBUG "${LIB_QSCINT_DEBUG}"
  IMPORTED_IMPLIB_RELEASE "${QSCINT_BUILD_PATH}/Release/qmyedit_qt5.lib"
  IMPORTED_IMPLIB_DEBUG "${QSCINT_BUILD_PATH}/Debug/qmyedit_qt5.lib"
  IMPORTED_CONFIGURATIONS "RELEASE;DEBUG"
)

				# file(GLOB UI_SRC ${CMAKE_SOURCE_DIR}/src/*.ui)

				#aux_source_directory(${CMAKE_SOURCE_DIR}/src/plugin/nddPluginToys SRC)
###### 		
	
aux_source_directory(${PROJECT_SOURCE_DIR}/src TOYS_SRC)
add_library(${PROJECT_NAME} SHARED ${TOYS_SRC} ${ui_FILES})
				#target_include_directories(${PROJECT_NAME} ${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} )


				#message("PROJECT_NAME:${PROJECT_NAME}")
				
				#target_compile_definitions(${PROJECT_NAME} PUBLIC )
#用到make生成的opencc_config.h,应该是从opencc_config.h.in生成而
target_include_directories(${PROJECT_NAME} PUBLIC 
	${NDD_ROOT}/src
	${PROJECT_SOURCE_DIR}/src
	${OPENCC_PATH}/src
	${QSCINT_PATH}/src
	${QSCINT_PATH}/src/Qsci
	${OPENCC_BUILD_PATH}/src
	)
	
#link libs
target_link_libraries (${PROJECT_NAME} libopencc  ${QTMODULES} qscint)



