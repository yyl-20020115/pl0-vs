#include "Evaluator.hpp"
#include "Parser.hpp"
//#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>

void load_string_file(std::string const& p, std::string& str)
{
    std::ifstream file;
    file.open(p, std::ios_base::binary);
    if (file) {
        file.seekg(0, std::ios_base::_Seekend);
    }
    //const boost::uintmax_t sz = filesystem::file_size(p);
    file.seekg(0, std::ios_base::end);

    // 获取当前文件指针位置，也就是获得文件大小
    std::streampos fileSize = file.tellg();

    // 文件指针移动到开头文件
    file.seekg(0, std::ios_base::beg);

    str.resize(static_cast<std::size_t>(fileSize), '\0');
    if (fileSize > 0u)
        file.read(&str[0], fileSize);
}


int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "usage: pl0 FILE\n";
        return 1;
    }

    try {
        std::string input;
        load_string_file(argv[1], input);
        auto program = PL0::Parser{input, std::cerr}();
        if (!program) return 1;
        PL0::Evaluator evaluator{std::cin, std::cout};
        program->accept(evaluator);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
