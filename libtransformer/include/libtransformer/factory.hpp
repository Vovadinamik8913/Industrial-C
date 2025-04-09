#pragma once
#include <libtransformer/parser.hpp>
#include <libtransformer/serializer.hpp>
#include <memory>

namespace Factory {
    class ParserFactory {
    public:
        static std::unique_ptr<Parser::IParser> create(const std::string& format);
    };
    
    class SerializerFactory {
    public:
        static std::unique_ptr<Serializer::ISerializer> create(const std::string& format);
    };
}