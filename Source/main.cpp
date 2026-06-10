#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

enum class TokenType {
    Identifier,
    Number,
    Equal,
    EqualEqual,
    NotEqual,
    Less,
    LessEqual,
    Greater,
    GreaterEqual,
    Star,
    LParam,
    RParam,
    EndOfLine,
    Unknown
};

struct Token {
    TokenType type;
    std::string value;
};

const char* TokenToString(TokenType type) {
    switch(type) {
        case TokenType::Identifier:   return "Identifier";
        case TokenType::Number:       return "Number";
        case TokenType::Equal:        return "Equal";
        case TokenType::EqualEqual:   return "EqualEqual";
        case TokenType::NotEqual:     return "NotEqual";
        case TokenType::Less:         return "Less";
        case TokenType::LessEqual:    return "LessEqual";
        case TokenType::Greater:      return "Greater";
        case TokenType::GreaterEqual: return "GreaterEqual";
        case TokenType::Star:         return "Star";
        case TokenType::LParam:       return "LParam";
        case TokenType::RParam:       return "RParam";
        case TokenType::EndOfLine:    return "EndOfLine";
        case TokenType::Unknown:      return "Unknown";
    }
    return "Unknown";
}

int main(int argc,char* argv[]) {

    if(argc < 2) {
        std::cerr << "wrong usage\n";
        return -1;
    }

    std::ifstream file(argv[1]);

    if(!file) {
        std::cerr << "File can't opened\n";
        return -1;
    }

    std::string Source;
    char ch;

    while(file.get(ch)) {
        Source += ch;
    }

    std::vector<Token> token;

    size_t i = 0;
    while(i < Source.size()) {
        char c = Source[i];

        if(std::isalpha(c)) {
            std::string value;
            while(i < Source.size() && std::isalnum(Source[i])) {
                value += Source[i];
                i++;
            }
            token.push_back({TokenType::Identifier, value});
            continue;
        }

        if(std::isdigit(c)) {
            std::string value;
            while(i < Source.size() && std::isdigit(Source[i])) {
                value += Source[i];
                i++;
            }
            token.push_back({TokenType::Number, value});
            continue;
        }

        switch(c) {
            case '=':
                if(i + 1 < Source.size() && Source[i + 1] == '=') {
                    token.push_back({TokenType::EqualEqual, "=="});
                    i += 2;
                    continue;
                }
                token.push_back({TokenType::Equal, "="});
                break;

            case '!':
                if(i + 1 < Source.size() && Source[i + 1] == '=') {
                    token.push_back({TokenType::NotEqual, "!="});
                    i += 2;
                    continue;
                }
                token.push_back({TokenType::Unknown, "!"});
                break;

            case '<':
                if(i + 1 < Source.size() && Source[i + 1] == '=') {
                    token.push_back({TokenType::LessEqual, "<="});
                    i += 2;
                    continue;
                }
                token.push_back({TokenType::Less, "<"});
                break;

            case '>':
                if(i + 1 < Source.size() && Source[i + 1] == '=') {
                    token.push_back({TokenType::GreaterEqual, ">="});
                    i += 2;
                    continue;
                }
                token.push_back({TokenType::Greater, ">"});
                break;

            case '*':
                token.push_back({TokenType::Star, "*"});
                break;

            case '(':
                token.push_back({TokenType::LParam, "("});
                break;

            case ')':
                token.push_back({TokenType::RParam, ")"});
                break;

            case '\n':
                token.push_back({TokenType::EndOfLine, "\\n"});
                break;

            case ' ':
            case '\t':
            case '\r':
                break;

            default:
                token.push_back({TokenType::Unknown, std::string(1, c)});
                break;
        }
        i++;    }

    for(const auto& t : token) {
        std::cout << TokenToString(t.type) << " : " << t.value << "\n";
    }

    return 0;
}
