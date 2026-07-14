#include <openssl/hmac.h>
#include <iomanip>
#include <sstream>

#include "Hmac.h"

std::string Hmac::sha1(const std::string &key, const std::string &message)
{
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLength = 0;

    HMAC(
        EVP_sha1(),
        key.data(),
        static_cast<int>(key.size()),
        reinterpret_cast<const unsigned char *>(message.data()),
        message.size(),
        hash,
        &hashLength);

    std::stringstream ss;

    for (unsigned int i = 0; i < hashLength; ++i)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }

    return ss.str();
}