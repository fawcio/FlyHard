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
#include <SFML/Graphics.hpp>
#include "utils/CommandCategory.hpp"
#include "utils/Command.hpp"

namespace sfml_playground
{

class Command;

class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public:
			SceneNode();
	virtual ~SceneNode() = default;

	SceneNode*					getParent() const { return mParent; }
	virtual CommandCategory		getCommandCategory() const { return CommandCategory {CommandCategory::eScene}; }

	void						attachChild(std::unique_ptr<SceneNode> child);
	std::unique_ptr<SceneNode>	detachChild(const SceneNode& node);

	void						update();

	sf::Transform				getWorldTransform() const;
	sf::Vector2f				getWorldPosition() const;

	void						onCommand(const Command& command, sf::Time dt);
	void						setForwardCommands(bool fwd) { mForwardCommands = fwd; }

private:
	virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const final override;
	virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void				drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void		updateCurrent();
	void				updateChildren();

private:
	std::vector<std::unique_ptr<SceneNode>>	mChildren;
	SceneNode*								mParent;
	bool									mForwardCommands;
};

} /* namespace sfml_playground */

#endif /* ENTITIES_SCENENODE_HPP_ */
