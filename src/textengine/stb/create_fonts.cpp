#include <iostream>
#include <fstream>
#include <tclap/CmdLine.h>

int main(int argc, char** argv)
{
  try {

    // command line parsing

    TCLAP::CmdLine cmd("Font converter, ttf -> *.cpp/h", ' ', "");

    TCLAP::ValueArg<std::string> ifile("i", "input", "Input file", true, "", "");
    TCLAP::ValueArg<std::string> ofile("o", "output", "Base name for created cpp/h files", true, "", "");
    TCLAP::ValueArg<std::string> caption("t", "title", "Generated font title", true, "", "");

    cmd.add(ifile);
    cmd.add(ofile);
    cmd.add(caption);

    cmd.parse(argc, argv);

    // Get the value parsed by each arg. 
    std::string iname = ifile.getValue();
    std::string obasename = ofile.getValue();
    std::string captionname = caption.getValue();

    // body

    std::ifstream input_file;
    std::ofstream output_h_file, output_cpp_file;

    input_file.open(iname, std::ios::binary);
    output_h_file.open(obasename + ".h");
    output_cpp_file.open(obasename + ".cpp");

    output_h_file << "#pragma once\n";
    output_cpp_file << "//#include \"generated.h\"\n";
  }
  catch (TCLAP::ArgException &e)  // catch any exceptions
  {
    std::cerr << "command line error: " << e.error() << " for arg " << e.argId() << std::endl;
  }

  return 0;
}
