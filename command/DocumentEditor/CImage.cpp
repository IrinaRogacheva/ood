#include "CImage.h"
#include "Commands.h"
#include <iostream>

CImage::CImage(CHistory& history, const Path& path, const int width, const int height)
    : m_history(history)
{
    if (width < 1 || width > 10000 || height < 1 || height > 10000)
    {
        throw std::invalid_argument("Wrong size argument. Width and height must be number greater than 1 and less than 10000");
    }
    m_width = width;
    m_height = height;

    if (!std::filesystem::exists(path))
    {
        throw std::invalid_argument("File does not exist");
    }

    std::string extension = std::filesystem::path(path).extension().string();
    if (SUPPORTED_EXTENSIONS.count(extension) == 0)
    {
        throw std::invalid_argument("This file is not image");
    }
    std::filesystem::create_directories(IMG_DIRECTORY_NAME);
    std::string generatedPath = IMG_DIRECTORY_NAME + GenerateRandomName() + extension;
    std::filesystem::copy_file(path, generatedPath, std::filesystem::copy_options::overwrite_existing);
    m_path = generatedPath;
}

Path CImage::GetPath() const
{
    return m_path;
}

int CImage::GetWidth() const
{
    return m_width;
}

int CImage::GetHeight() const
{
    return m_height;
}

void CImage::Resize(int width, int height)
{
    m_history.AddAndExecuteCommand(std::make_unique<CResizeImage>(m_width, width, m_height, height));
}

std::string CImage::GenerateRandomName() const
{
    auto randchar = []() -> char
    {
        const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        const size_t max_index = chars.size() - 1;
        return chars[rand() % max_index];
    };
    std::string str(IMG_NAME_LEN, 0);
    std::generate_n(str.begin(), IMG_NAME_LEN, randchar);
    return str;
}