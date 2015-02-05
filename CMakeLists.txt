CMake_Minimum_Required ( VERSION 2.6 )
Project ( libopencif )
Add_Library ( opencif STATIC
                                 src/opencif.hh
                                 src/command/command.hh
                                 src/command/controlcommand/controlcommand.hh
                                 src/command/controlcommand/callcommand/callcommand.hh
                                 src/command/controlcommand/definitiondeletecommand/definitiondeletecommand.hh
                                 src/command/controlcommand/definitionendcommand/definitionendcommand.hh
                                 src/command/controlcommand/definitionstartcommand/definitionstartcommand.hh
                                 src/command/fraction/fraction.hh
                                 src/command/layercommand/layercommand.hh
                                 src/command/point/point.hh
                                 src/command/primitivecommand/primitivecommand.hh
                                 src/command/primitivecommand/pathbasedcommand/pathbasedcommand.hh
                                 src/command/primitivecommand/pathbasedcommand/polygoncommand/polygoncommand.hh
                                 src/command/primitivecommand/pathbasedcommand/wirecommand/wirecommand.hh
                                 src/command/primitivecommand/positionbasedcommand/positionbasedcommand.hh
                                 src/command/primitivecommand/positionbasedcommand/boxcommand/boxcommand.hh
                                 src/command/primitivecommand/positionbasedcommand/roundflashcommand/roundflashcommand.hh
                                 src/command/rawcontentcommand/rawcontentcommand.hh
                                 src/command/rawcontentcommand/commentcommand/commentcommand.hh
                                 src/command/rawcontentcommand/userextensioncommand/userextensioncommand.hh
                                 src/command/size/size.hh
                                 src/command/transformation/transformation.hh
                                 src/file/file.hh
                                 src/finitestatemachine/finitestatemachine.hh
                                 src/finitestatemachine/state.hh
                                 src/finitestatemachine/ciffsm.hh
                                 src/command/controlcommand/endcommand/endcommand.hh
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
                                 src/command/primitivecommand/positionbasedcommand/roundflashcommand/roundflashcommand.cc
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
Install ( FILES src/opencif
          DESTINATION include
        )

Set ( CPACK_PACKAGE_VERSION_MAJOR "1" )
Set ( CPACK_PACKAGE_VERSION_MINOR "2" )
Set ( CPACK_PACKAGE_VERSION_PATCH "0" )
Set ( CPACK_SOURCE_GENERATOR "TGZ" )
Set ( CPACK_SOURCE_PACKAGE_FILE_NAME
      "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}" )
Set ( CPACK_SOURCE_IGNORE_FILES
      "/build/;/.deps/;/.bzr/;/.git/;~$;${CPACK_SOURCE_IGNORE_FILES}" )
Add_Custom_Target ( dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source )
Include ( CPack )