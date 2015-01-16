# Creates C resources file from files in given directory
function(create_resources dir output)
    # Create empty output file
    file(WRITE ${output}.h "")
    file(WRITE ${output}.cpp "")
    # Collect input files
    file(GLOB bins ${dir}/*)
    
    file(APPEND ${output}.h "#pragma once\n\nnamespace Protean3D\n{\nstruct StandardFont\n{\n")
    file(APPEND ${output}.cpp "#include \"${output}.h\"\n\n")

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
        # Append data to output file
        file(APPEND ${output}.h "  static const unsigned char ${filename}[];\n  static const size_t ${filename}_size;\n")
        file(APPEND ${output}.cpp "const unsigned char Protean3D::StandardFont::${filename}[] = {${filedata}};\nconst size_t Protean3D::StandardFont::${filename}_size = sizeof(${filename});\n")
    endforeach()
    file(APPEND ${output}.h "};\n} // ns \n")
endfunction()