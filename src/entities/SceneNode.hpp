/*
 * SceneNode.hpp
 *
 *  Created on: 6 sty 2015
 *      Author: slawek
 */

#ifndef ENTITIES_SCENENODE_HPP_
#define ENTITIES_SCENENODE_HPP_

#include <memory>
#include <vector>

namespace sfml_playground
{

class SceneNode
{
public:
	using SceneNodePtr = std::unique_ptr<SceneNode>;

public:
			SceneNode();
	virtual ~SceneNode() = default;

	SceneNode*		getParent() const { return mParent; }

	void			attachChild(SceneNodePtr child);
	SceneNodePtr	detachChild(const SceneNode& node);

private:
	std::vector<SceneNodePtr>	mChildren;
	SceneNode*					mParent;
};

} /* namespace sfml_playground */

#endif /* ENTITIES_SCENENODE_HPP_ */
