CMake_Minimum_Required ( VERSION 2.6 )
Project ( libopencif )
Add_Library ( opencif STATIC
                                 src/opencif.h
                                 src/command/command.h
                                 src/command/controlcommand/controlcommand.h
                                 src/command/controlcommand/callcommand/callcommand.h
                                 src/command/controlcommand/definitiondeletecommand/definitiondeletecommand.h
                                 src/command/controlcommand/definitionendcommand/definitionendcommand.h
                                 src/command/controlcommand/definitionstartcommand/definitionstartcommand.h
                                 src/command/fraction/fraction.h
                                 src/command/layercommand/layercommand.h
                                 src/command/point/point.h
                                 src/command/primitivecommand/primitivecommand.h
                                 src/command/primitivecommand/pathbasedcommand/pathbasedcommand.h
                                 src/command/primitivecommand/pathbasedcommand/polygoncommand/polygoncommand.h
                                 src/command/primitivecommand/pathbasedcommand/wirecommand/wirecommand.h
                                 src/command/primitivecommand/positionbasedcommand/positionbasedcommand.h
                                 src/command/primitivecommand/positionbasedcommand/boxcommand/boxcommand.h
                                 src/command/primitivecommand/positionbasedcommand/roundflashcommand.h
                                 src/command/rawcontentcommand/rawcontentcommand.h
                                 src/command/rawcontentcommand/commentcommand/commentcommand.h
                                 src/command/rawcontentcommand/userextensioncommand/userextensioncommand.h
                                 src/command/size/size.h
                                 src/command/transformation/transformation.h
                                 src/file/file.h
                                 src/finitestatemachine/finitestatemachine.h
                                 src/finitestatemachine/state.h
                                 src/finitestatemachine/ciffsm.h
                                 src/command/controlcommand/endcommand/endcommand.h
                                 src/command/command.cc
                                 src/command/controlcommand/controlcommand.cc
                                 src/command/controlcommand/callcommand/callcommand.cc
                                 src/command/controlcommand/definitiondeletecommand/definitiondeletecommand.cc
                                 src/command/controlcommand/definitionendcommand/definitionendcommand.cc
                                 src/command/controlcommand/definitionstartcommand/definitionstartcommand.cc
                                 src/command/fraction/fraction.cc
                                 src/command/layercommand/layercommand.cc
                                 src/command/point/point.cc
                                 src/command/primitivecommand/primitivecommand.cc
                                 src/command/primitivecommand/pathbasedcommand/pathbasedcommand.cc
                                 src/command/primitivecommand/pathbasedcommand/polygoncommand/polygoncommand.cc
                                 src/command/primitivecommand/pathbasedcommand/wirecommand/wirecommand.cc
                                 src/command/primitivecommand/positionbasedcommand/positionbasedcommand.cc
                                 src/command/primitivecommand/positionbasedcommand/boxcommand/boxcommand.cc
                                 src/command/primitivecommand/positionbasedcommand/roundflashcommand.cc
                                 src/command/rawcontentcommand/rawcontentcommand.cc
                                 src/command/rawcontentcommand/commentcommand/commentcommand.cc
                                 src/command/rawcontentcommand/userextensioncommand/userextensioncommand.cc
                                 src/command/size/size.cc
                                 src/command/transformation/transformation.cc
                                 src/file/file.cc
                                 src/finitestatemachine/finitestatemachine.cc
                                 src/finitestatemachine/state.cc
                                 src/finitestatemachine/ciffsm.cc
                                 src/command/controlcommand/endcommand/endcommand.cc
            )

Install ( TARGETS opencif
          DESTINATION lib
        )
Install ( DIRECTORY src/
          DESTINATION include/opencif
          FILES_MATCHING PATTERN "*.h"
        )

Set ( CPACK_PACKAGE_VERSION_MAJOR "1" )
Set ( CPACK_PACKAGE_VERSION_MINOR "2" )
Set ( CPACK_PACKAGE_VERSION_PATCH "0" )
Set ( CPACK_SOURCE_GENERATOR "TGZ" )
Set ( CPACK_SOURCE_PACKAGE_FILE_NAME
      "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}" )
Set ( CPACK_SOURCE_IGNORE_FILES
      "/build/;/.bzr/;/.git/;~$;${CPACK_SOURCE_IGNORE_FILES}" )
Add_Custom_Target ( dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source )
Include ( CPack )