#include <exception>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

#include "GoofyFiles.hpp"

bool GoofyFiles::create_file(const std::string& pathname, const std::string& content) {
    bool created = false;

    std::ofstream out(pathname);
    out << content;
    if (out.is_open()) {
        created = true;
        created_files.push_back(pathname);
    }
    out.close();

    return created;
}

bool GoofyFiles::delete_file(const std::string& pathname) {
    return std::filesystem::remove(pathname);
}

const std::string GoofyFiles::read_file(const std::string& pathname) {
    std::ifstream in(pathname);
    if (!in.is_open()) {
        throw std::exception();
    }

    std::stringstream sstream;
    sstream << in.rdbuf();

    return std::move(sstream.str());
}

bool GoofyFiles::rewrite_file(const std::string& pathname, const std::string& content) {
    bool success = false;

    std::ofstream out(pathname);
    out << content;
    if (out.is_open()) {
        success = true;
    }
    out.close();

    return success;
}

bool GoofyFiles::append_file(const std::string& pathname, const std::string& content) {
    bool success = false;

    std::ofstream out(pathname, std::ios_base::app);
    out << content;
    if (out.is_open()) {
        success = true;
    }
    out.close();

    return success;
}
