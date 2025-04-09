#include <libtransformer/factory.hpp>
#include <memory>


std::unique_ptr<Parser::IParser>
Factory::ParserFactory::create(const std::string &format) {
    if (format == "json") return std::make_unique<Parser::JsonParser>();
    //if (format == "xml") return std::make_unique<XmlParser>();
    //if (format == "toml") return std::make_unique<TomlParser>();
    throw std::invalid_argument("Unsupported input format: " + format);
}
std::unique_ptr<Serializer::ISerializer>
Factory::SerializerFactory::create(const std::string &format) {
    if (format == "json") return std::make_unique<Serializer::JsonSerializer>();
    if (format == "xml") return std::make_unique<Serializer::XmlSerializer>();
    if (format == "toml") return std::make_unique<Serializer::TomlSerializer>();
    throw std::invalid_argument("Unsupported output format: " + format);
}