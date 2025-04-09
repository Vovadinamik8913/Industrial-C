#include <libtransformer/parser.hpp>

void Parser::BaseParser::skipWhitespace(std::istream &input)  {
    while (isspace(input.peek())) {
        input.get();
    }
}

void Parser::BaseParser::isThrowParseError(std::istream &input) {
    if (input.eof()) {
        throw std::runtime_error("Unexpected end of input");
    } else if (!input.good()) {
        throw std::runtime_error("Input stream is not good");
    }
}

void Parser::BaseParser::throwParseError(const std::string &message, char c)  {
    throw std::runtime_error(message + ". Got: '" + std::string(1, c) + "'");
}

std::vector<std::pair<std::string, AST::Node>> Parser::JsonParser::parse(std::istream &input) {
    std::vector<std::pair<std::string, AST::Node>> nodes;
    skipWhitespace(input);
    char c = input.peek();
    if (c != '{') {
        throwParseError("Expected '{'", c);
    }
    input.get();
    
    skipWhitespace(input);
    c = input.peek();
    if (c == '}') {
        input.get();
        return nodes;
    }
    
    while (true) {
        skipWhitespace(input);
        isThrowParseError(input);
        
        std::string key = getName(input);
        skipWhitespace(input);
        c = input.peek();
        if (c != ':') {
            throwParseError("Expected ':'", c);
        }
        input.get();
        
        skipWhitespace(input);
        isThrowParseError(input);
        c = input.peek();
        if (c == '{') {
            auto nested = parse(input);
            nodes.push_back(std::make_pair(key, AST::Node(AST::Object(nested))));
        } else if (c == '[') {
            input.get();
            AST::Array arr;
            while (true) {
                skipWhitespace(input);
                c = input.peek();
                if (c == ']') {
                    input.get();
                    break;
                }
                if (c == '{')
                {
                    arr.push_back(parse(input));
                } else {
                    arr.push_back(parseBasic(input));
                }
                skipWhitespace(input);
                c = input.peek();
                if (c == ',') {
                    input.get();
                    continue;
                }
                if (c != ']') {
                    throwParseError("Expected ',' or ']'", c);
                }
            }
            nodes.push_back(std::make_pair(key, AST::Node(arr)));
        } else {
            nodes.push_back(std::make_pair(key, parseBasic(input)));
        }
        
        skipWhitespace(input);
        c = input.peek();
        if (c == ',') {
            input.get();
            continue;
        }
        if (c == '}') {
            input.get();
            break;
        }
        throwParseError("Expected ',' or '}'", c);
    }
    return nodes;
}

std::string Parser::JsonParser::getName(std::istream &input) {
    char c = input.get();
    if (c != '"') {
        throwParseError("Expected '\"'", c);
    }
    
    std::string key;
    while (!input.eof()) {
        c = input.get();
        if (c == '"') {
            break;
        }
        if (c == '\\') {
            c = input.get();
            if (c == 'n') c = '\n';
            else if (c == 't') c = '\t';
            else if (c == 'r') c = '\r';
        }
        key += c;
    }
    return key;
}

AST::Node Parser::JsonParser::parseBasic(std::istream &input) {
    char c = input.peek();
    if (c == '"') {
        return AST::Node(getName(input));
    } else if (isdigit(c) || c == '-') {
        std::string num;
        bool isFloat = false;
        while (!input.eof() && (isdigit(input.peek()) || input.peek() == '.' || input.peek() == '-')) {
            c = input.get();
            if (c == '.') isFloat = true;
            num += c;
        }
        if (isFloat) {
            return AST::Node(std::stod(num));
        } else {
            return AST::Node(static_cast<int64_t>(std::stoll(num)));
        }
    } else if (c == 't' || c == 'f') {
        std::string value;
        while (isalpha(input.peek())) {
            value += input.get();
        }
        return AST::Node(value == "true");
    } else {
        std::string value;
        while (isalpha(input.peek())) {
            value += input.get();
        }
        if (value == "null") {
            return AST::Node();
        } else {
            throw std::runtime_error("unknown type");
        }
    }
}
