#include <libtransformer/serializer.hpp>

void Serializer::XmlSerializer::serialize(
    std::ostream &output, std::vector<std::pair<std::string, AST::Node>>& nodes) {
    output << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
    output << "<application>" << std::endl;
    for (const auto& [key, value] : nodes)
    {
        serializeValue(key, value, output, 1);
        output << std::endl;
    }
    output << "</application>" << std::endl;
}

void Serializer::XmlSerializer::serializeValue(const std::string &name,
                                               const AST::Node &node,
                                               std::ostream &output,
                                               int indent) {
    std::visit([&](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, AST::Null>) {
            output << std::string(indent, ' ') << "<" << name << "/>";
        } else if constexpr (std::is_same_v<T, AST::Object>) {
            output << std::string(indent, ' ') << "<" << name << ">" << std::endl;
            for (const auto& [key, value] : arg) {
                serializeValue(key, value, output, indent + 2);
                output << std::endl;
            }
            output << std::string(indent, ' ') << "</" << name << ">";
        } else if constexpr (std::is_same_v<T, AST::Array>) {
            output << std::string(indent, ' ') << "<" << name << ">\n";
            for (const auto& node : arg) {
                serializeValue(name.substr(0, name.length() - 1), node, output, indent + 2);
                output << std::endl;
            }
            output << std::string(indent, ' ') << "</" << name << ">";
        }else if constexpr (std::is_same_v<T, AST::Bool>) {
            output << std::string(indent, ' ') << "<" << name << ">";
            output << (arg ? "true" : "false");
            output << "</" << name << ">";
        } else {
            output << std::string(indent, ' ') << "<" << name << ">";
            output << arg;
            output << "</" << name << ">";
        }
    }, node.value);
}

void Serializer::JsonSerializer::serialize(
    std::ostream &output,
    std::vector<std::pair<std::string, AST::Node>> &nodes) {
    output << '{' << std::endl;
    for (size_t i = 0; i < nodes.size() - 1; i++)
    {
        serializeValue(nodes[i].first, nodes[i].second, output, 1);
        output << "," << std::endl;
    }
    if (!nodes.empty())
    {
        serializeValue(nodes.back().first, nodes.back().second, output, 1);
    }
    output << std::endl << '}' << std::endl;
}

void Serializer::JsonSerializer::serializeValue(const std::string &name,
                                                const AST::Node &node,
                                                std::ostream &output,
                                                int indent) {
    std::visit([&](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if (!name.empty())
        {
            output << std::string(indent, ' ') << '"' << name << '"' << " : ";
        }
        if constexpr (std::is_same_v<T, AST::Null>) {
            output << "null";
        } else if constexpr (std::is_same_v<T, AST::Object>) {
            if (name.empty())
            {
                output << std::endl << std::string(indent, ' ');
            }
            output << '{' << std::endl;
            for (size_t i = 0; i < arg.size() - 1; i++)
            {
                serializeValue(arg[i].first, arg[i].second, output, indent + 2);
                output << "," << std::endl;
            }
            if (!arg.empty())
            {
                serializeValue(arg[arg.size() - 1].first, arg[arg.size() - 1].second, output, indent + 2);
            }
            output  << std::endl << std::string(indent, ' ') << '}';
        } else if constexpr (std::is_same_v<T, AST::Array>) {
            if (name.empty())
            {
                output << std::endl << std::string(indent, ' ');
            }
            output << '[';
            for (size_t i = 0; i < arg.size() - 1; i++)
            {
                serializeValue("", arg[i], output, indent + 2);
                output << ",";
            }
            if (!arg.empty())
            {
                serializeValue("", arg.back(), output, indent + 2);
                if (std::holds_alternative<AST::Object>(arg.back().value)
                || std::holds_alternative<AST::Array>(arg.back().value)) {
                    output << std::endl << std::string(indent, ' ');
                }
            }
            output << ']';
        } else if constexpr (std::is_same_v<T, AST::Bool>) {
            output << (arg ? "true" : "false");
        } else if constexpr (std::is_same_v<T, AST::String>) {
            output << '"' << arg << '"';
        } else {
            output << arg;
        }
    }, node.value);
}

void Serializer::TomlSerializer::serialize(
    std::ostream &output,
    std::vector<std::pair<std::string, AST::Node>> &nodes) {
    for (const auto& [key, value] : nodes)
    {
        serializeValue(key, value, output);
        output << std::endl;
    }
}

void Serializer::TomlSerializer::serializeValue(const std::string &name,
                                                const AST::Node &node,
                                                std::ostream &output,
                                                int indent) {
    std::visit([&](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, AST::Null>) {
            if (!name.empty())
            {
                output << name << " = ";
            }
            output << "null";
        } else if constexpr (std::is_same_v<T, AST::Object>) {
            if (!name.empty())
            {
                output << "[" << name << "]" << std::endl;
            }
            for (const auto& [key, value] : arg) {
                serializeValue(key, value, output, indent);
                output << std::endl;
            }
        } else if constexpr (std::is_same_v<T, AST::Array>) {
            if (!name.empty()) {
                output << name << " = ";
            }
            output << '[';
            for (size_t i = 0; i < arg.size(); i++) {
                serializeValue("", arg[i], output, indent);
                if (i < arg.size() - 1) {
                    output << ", ";
                }
            }
            output << ']';
        } else if constexpr (std::is_same_v<T, AST::Bool>) {
            if (!name.empty())
            {
                output << name << " = ";
            }
            output << (arg ? "true" : "false");
        } else if constexpr (std::is_same_v<T, AST::String>) {
            if (!name.empty())
            {
                output << name << " = ";
            }
            output << '"' << arg << '"';
        } else {
            if (!name.empty())
            {
                output << name << " = ";
            }
            output << arg;
        }
    }, node.value);
}
