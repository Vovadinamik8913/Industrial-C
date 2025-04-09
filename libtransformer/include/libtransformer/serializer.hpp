#pragma once
#include <ostream>
#include <unordered_map>
#include <string>
#include <variant>
#include <libtransformer/ast.hpp>


namespace Serializer {
    class ISerializer {
    public:
        virtual ~ISerializer() = default;
        virtual void serialize(std::ostream& output, std::vector<std::pair<std::string, AST::Node>>& nodes) = 0;
    protected:
        virtual void serializeValue(const std::string& name, const AST::Node& node, 
        std::ostream& output, int indent = 0) = 0;  
    };

    class JsonSerializer : public ISerializer {
    public:
        void serialize(std::ostream &output,
            std::vector<std::pair<std::string, AST::Node>>& nodes) override;
    protected:
      void serializeValue(const std::string &name, const AST::Node &node,
                          std::ostream &output, int indent = 0) override;
    };

    class TomlSerializer : public ISerializer {
    public:
        void serialize(std::ostream &output,
            std::vector<std::pair<std::string, AST::Node>>& nodes) override;
    protected:
      void serializeValue(const std::string &name, const AST::Node &node,
                          std::ostream &output, int indent = 0) override;
    };
    class XmlSerializer : public ISerializer {
    public:
        void serialize(std::ostream &output,
            std::vector<std::pair<std::string, AST::Node>>& nodes) override;
    protected:
      void serializeValue(const std::string &name, const AST::Node &node,
                          std::ostream &output, int indent = 0) override;
    };
}