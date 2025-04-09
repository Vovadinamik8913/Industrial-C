#pragma once
#include <variant>
#include <string>
#include <vector>
#include <memory>

namespace AST {
    struct Node;
    
    using Null = std::monostate;
    using Bool = bool;
    using Int = int64_t;
    using Float = double;
    using String = std::string;
    using Array = std::vector<Node>;
    using Object = std::vector<std::pair<std::string, Node>>;
    
    struct Node {
        std::variant<
            Null,
            Bool,
            Int,
            Float,
            String,
            Array,
            Object
        > value;
        
        Node() : value(Null{}) {}
        Node(bool b) : value(b) {}
        Node(int64_t i) : value(i) {}
        Node(double f) : value(f) {}
        Node(const std::string& s) : value(s) {}
        Node(const char* s) : value(std::string(s)) {}
        Node(const Array& a) : value(a) {}
        Node(const Object& o) : value(o) {}
    };
}