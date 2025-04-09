#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <libtransformer/ast.hpp>

namespace Parser {
    class IParser {
    public:
        virtual ~IParser() = default;
        virtual std::vector<std::pair<std::string, AST::Node>> parse(std::istream& input) = 0;    
    protected:
        virtual std::string getName(std::istream& input) = 0;
        virtual AST::Node parseBasic(std::istream& input) = 0;
    };

    class BaseParser : public IParser{
        public:
            virtual std::vector<std::pair<std::string, AST::Node>> parse(std::istream& input) override = 0; 
        protected:
            virtual std::string getName(std::istream& input) override = 0;
            virtual AST::Node parseBasic(std::istream& input) override = 0;
            void skipWhitespace(std::istream& input);
            void isThrowParseError(std::istream& input);
            [[noreturn]] void throwParseError(const std::string& message, char c);
    };

    class JsonParser : public BaseParser {
        public:
            std::vector<std::pair<std::string, AST::Node>> parse(std::istream& input) override;
        protected:
            std::string getName(std::istream& input) override;
            AST::Node parseBasic(std::istream& input) override;
    };
}