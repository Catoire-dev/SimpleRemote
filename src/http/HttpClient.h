#pragma once

#include <map>
#include <string>

class HttpClient
{
public:
    explicit HttpClient(const std::string &baseUrl);

    std::string get(const std::string &path);
    std::string post(const std::string &path, const std::string &body);

    void setHeader(const std::string &key, const std::string &value);
    void removeHeader(const std::string &key);

private:
    std::string request(
        const std::string &method,
        const std::string &path,
        const std::string &body = "");

    std::string m_baseUrl;
    std::map<std::string, std::string> m_headers;
};