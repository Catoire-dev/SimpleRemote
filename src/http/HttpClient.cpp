#include "HttpClient.h"

#include <curl/curl.h>
#include <stdexcept>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    auto *response = static_cast<std::string *>(userp);
    response->append(static_cast<char *>(contents), size * nmemb);
    return size * nmemb;
}

std::string HttpClient::get(const std::string &url)
{
    CURL *curl = curl_easy_init();

    if (!curl)
    {
        throw std::runtime_error("Unable to initialize CURL");
    }

    std::string response;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode result = curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    if (result != CURLE_OK)
    {
        throw std::runtime_error(curl_easy_strerror(result));
    }

    return response;
}