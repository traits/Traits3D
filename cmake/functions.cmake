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
    
    file(APPEND ${inc_name} "#pragma once\n\nnamespace Protean3D\n{\nstruct StandardFont\n{\n")
    file(APPEND ${src_name} "#include \"${inc_statement}\"\n\n")

    # Iterate through input files
    foreach(bin ${bins})
        # Get short filename
        string(REGEX MATCH "([^/]+)$" filename ${bin})
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
        file(APPEND ${src_name} "const unsigned char Protean3D::StandardFont::${filename}[] = {${filedata}};\nconst size_t Protean3D::StandardFont::${filename}_size = sizeof(${filename});\n")
    endforeach()
    file(APPEND ${inc_name} "};\n} // ns \n")
endfunction()

function(protean3d_example_creator subdirlist linklibrarylist ideproperty)
  foreach(subdir ${subdirlist})
    file(GLOB  ${subdir}_SOURCES ${subdir}/*.c*)
    file(GLOB  ${subdir}_HEADERS ${subdir}/*.h)

    add_executable(${subdir}  ${${subdir}_SOURCES} ${${subdir}_HEADERS})
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