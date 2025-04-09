#include <iostream>
#include <libtransformer/factory.hpp>
#include <libtransformer/ast.hpp>

int main(int argc, char* argv[]) {
    try {
        if (argc != 3) {
            std::cerr << "Usage: " << argv[0] << " <input-format> <output-format>\n";
            return 1;
        }
        
        std::string inputFormat = argv[1];
        std::string outputFormat = argv[2];
        auto parser = Factory::ParserFactory::create(inputFormat);
        auto serializer = Factory::SerializerFactory::create(outputFormat);
        std::vector<std::pair<std::string, AST::Node>> ast = parser->parse(std::cin);
        serializer->serialize(std::cout, ast);
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}