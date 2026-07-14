#include "HttpClient.h"

#include <curl/curl.h>
#include <stdexcept>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    auto *response = static_cast<std::string *>(userp);
    response->append(static_cast<char *>(contents), size * nmemb);
    return size * nmemb;
}

HttpClient::HttpClient(const std::string &baseUrl)
    : m_baseUrl(baseUrl)
{
}

std::string HttpClient::get(const std::string &path)
{
    return request("GET", path);
}

std::string HttpClient::post(const std::string &path, const std::string &body)
{
    return request("POST", path, body);
}

void HttpClient::setHeader(const std::string &key, const std::string &value)
{
    m_headers[key] = value;
}

void HttpClient::removeHeader(const std::string &key)
{
    m_headers.erase(key);
}

std::string HttpClient::request(const std::string &method, const std::string &path, const std::string &body)
{
    CURL *curl = curl_easy_init();

    if (!curl)
    {
        throw std::runtime_error("Unable to initialize CURL");
    }

    std::string response;

    curl_easy_setopt(curl, CURLOPT_URL, (m_baseUrl + path).c_str());
    // Ignorer les erreur de certifica SSL
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    // ------------------------------------------
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    struct curl_slist *headers = nullptr;

    headers = curl_slist_append(headers, "Content-Type: application/json");

    for (const auto &header : m_headers)
    {
        headers = curl_slist_append(
            headers,
            (header.first + ": " + header.second).c_str());
    }

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    if (method == "POST")
    {
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    }

    for (const auto &[key, value] : m_headers)
    {
        std::string header = key + ": " + value;
        headers = curl_slist_append(headers, header.c_str());
    }

    if (headers)
    {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    }

    CURLcode result = curl_easy_perform(curl);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (headers)
    {
        curl_slist_free_all(headers);
    }

    if (result != CURLE_OK)
    {
        throw std::runtime_error(curl_easy_strerror(result));
    }

    return response;
}