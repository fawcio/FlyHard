/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Sławomir Cielepak
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#pragma once

#include <string>
#include <map>
#include <memory>
#include <exception>
#include <cassert>
#include "ResourceID.hpp"
#include "utils/NonCopyable.hpp"

namespace SFGame
{

template <typename ResourceT, typename IdentifierT>
class ResourceHolder : NonCopyable
{
public:
    ResourceHolder() = default;
    virtual	~ResourceHolder() = default;

    void				load(IdentifierT id, const std::string& filename);

    template <typename ParameterT>
    void				load(IdentifierT id, const std::string& filename, const ParameterT& secondParam);

    ResourceT&	get(IdentifierT id) const;

private:
    std::map<IdentifierT, std::unique_ptr<ResourceT>> mResourceMap;
};

template <typename ResourceT, typename IdentifierT>
void ResourceHolder<ResourceT, IdentifierT>::load(IdentifierT id, const std::string& filename)
{
    std::unique_ptr<ResourceT> resource(new ResourceT);

    if (!resource->loadFromFile(filename))
        throw new std::runtime_error("ResourceHolder::load - Failed to load: " + filename);

    auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
    (void)inserted;
    assert(true == inserted.second);
}

template <typename ResourceT, typename IdentifierT>
template <typename ParameterT>
void ResourceHolder<ResourceT, IdentifierT>::load(IdentifierT id, const std::string& filename, const ParameterT& secondParam)
{
    std::unique_ptr<ResourceT> resource(new ResourceT);

    if (!resource->loadFromFile(filename, secondParam))
        throw new std::runtime_error("ResourceHolder::load - Failed to load: " + filename);

    auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(true == inserted.second);
}

template<typename ResourceT, typename IdentifierT>
ResourceT& ResourceHolder<ResourceT, IdentifierT>::get(IdentifierT id) const
{
    auto found = mResourceMap.find(id);
    assert(mResourceMap.end() != found);

    return *found->second;
}

using TextureHolder = ResourceHolder<sf::Texture, TextureID>;
using FontHolder    = ResourceHolder<sf::Font, FontID>;

} /* namespace sfml_playground */
