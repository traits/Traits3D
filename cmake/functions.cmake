# Creates C resources file from files in given directory
function(create_resources src_dir output_src_dir output_include_dir base_name include_prefix)
    # Create empty output files
    
    set (src_name ${output_src_dir}/${base_name}.cpp)
    set (inc_name ${output_include_dir}/${base_name}.h)
    set (inc_statement ${include_prefix}/${base_name}.h)
    
    file(WRITE ${inc_name} "")
    file(WRITE ${src_name} "")
    # Collect input files
    file(GLOB bins ${src_dir}/*)
    
    file(APPEND ${inc_name} "#pragma once\n\nnamespace Traits3D\n{\nstruct StandardFont\n{\n")
    file(APPEND ${src_name} "#include \"${inc_statement}\"\n\n")

    # Iterate through input files
    foreach(bin ${bins})
        # Get short filename
        get_filename_component(filename ${bin} NAME_WE)        
        #string(REGEX MATCH "([^/]+)$" filename ${bin})
        # Replace filename spaces & extension separator for C compatibility
        string(REGEX REPLACE "\\.| |-" "_" filename ${filename})
        # Read hex data from file
        file(READ ${bin} filedata HEX)
        # Convert hex data for C compatibility
        string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," filedata ${filedata})
        # remove redundant comma 
        string(REGEX REPLACE "(,$)" "" filedata ${filedata})
        # Append data to output file
        file(APPEND ${inc_name} "  static const unsigned char ${filename}[];\n  static const size_t ${filename}_size;\n")
        file(APPEND ${src_name} "const unsigned char Traits3D::StandardFont::${filename}[] = {${filedata}};\nconst size_t Traits3D::StandardFont::${filename}_size = sizeof(${filename});\n")
    endforeach()
    file(APPEND ${inc_name} "};\n} // ns \n")
endfunction()

function(example_creator subdirlist linklibrarylist ideproperty)
  foreach(subdir ${subdirlist})
    file(GLOB  ${subdir}_FILES ${subdir}/*.cpp ${subdir}/*.h ${subdir}/*.qml )
    file(GLOB  ${subdir}_QRC_FILES ${subdir}/*.qrc)
    
    if (NOT ("${${subdir}_QRC_FILES}" STREQUAL ""))
      qt5_add_resources(${subdir}_QRC_CREATED_FILES ${${subdir}_QRC_FILES})
      #message("Bummer: " ${${subdir}_QRC} " -> " ${QRC_FILES})
    endif()
    add_executable(${subdir}  ${${subdir}_FILES} ${${subdir}_QRC_CREATED_FILES})
    
    set_property(TARGET ${subdir} PROPERTY FOLDER ${ideproperty})
    target_link_libraries(${subdir} ${linklibrarylist})
    set_target_properties(${subdir} PROPERTIES WIN32_EXECUTABLE false)
    install(TARGETS ${subdir} 
    RUNTIME DESTINATION bin 
    LIBRARY DESTINATION bin 
    ARCHIVE DESTINATION lib
    )
  endforeach()
endfunction()