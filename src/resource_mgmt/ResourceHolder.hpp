/*
 * ResourceHolder.hpp
 *
 *  Created on: 2 sty 2015
 *      Author: marta
 */

#ifndef RESOURCE_MGMT_RESOURCEHOLDER_HPP_
#define RESOURCE_MGMT_RESOURCEHOLDER_HPP_

#include <string>
#include <map>
#include <memory>
#include <exception>
#include <cassert>
#include "ResourceID.hpp"

namespace sfml_playground
{

template <typename ResourceT, typename IdentifierT>
class ResourceHolder
{
public:
			 ResourceHolder() = default;
	virtual	~ResourceHolder() = default;

	void				load(IdentifierT id, std::string& filename);

	template <typename ParameterT>
	void				load(IdentifierT id, const std::string& filename, const ParameterT& secondParam);

	ResourceT&			get(IdentifierT id);

	const ResourceT&	get(IdentifierT id) const;

private:
	std::map<IdentifierT, std::unique_ptr<ResourceT>> mTextureMap;
};

template <typename ResourceT, typename IdentifierT>
void ResourceHolder<ResourceT, IdentifierT>::load(IdentifierT id, std::string& filename)
{
	std::unique_ptr<ResourceT> resource(new ResourceT);

	if (!resource->loadFromFile(filename))
		throw new std::runtime_error("ResourceHolder::load - Failed to load: " + filename);

	auto inserted = mTextureMap.insert(std::make_pair(id, std::move(resource)));
	assert(true == inserted.second);
}

template <typename ResourceT, typename IdentifierT>
template <typename ParameterT>
void ResourceHolder<ResourceT, IdentifierT>::load(IdentifierT id, const std::string& filename,
		const ParameterT& secondParam)
{
	std::unique_ptr<ResourceT> resource(new ResourceT);

	if (!resource->loadFromFile(filename, secondParam))
			throw new std::runtime_error("ResourceHolder::load - Failed to load: " + filename);

	auto inserted = mTextureMap.insert(std::make_pair(id, std::move(resource)));
		assert(true == inserted.second);
}

template<typename ResourceT, typename IdentifierT>
ResourceT& ResourceHolder<ResourceT, IdentifierT>::get(IdentifierT id)
{
	auto found = mTextureMap.find(id);
	assert(mTextureMap.end() != found);

	return *found->second;
}

template<typename ResourceT, typename IdentifierT>
const ResourceT& ResourceHolder<ResourceT, IdentifierT>::get(IdentifierT id) const
{
	auto found = mTextureMap.find(id);
	assert(mTextureMap.end() != found);

	return *found->second;
}

} /* namespace sfml_playground */

#endif /* RESOURCE_MGMT_RESOURCEHOLDER_HPP_ */
