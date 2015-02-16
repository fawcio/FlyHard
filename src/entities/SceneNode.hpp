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

namespace sfml_playground
{

class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public:
	using SceneNodePtr = std::unique_ptr<SceneNode>;

public:
					SceneNode();
	virtual 		~SceneNode() = default;

	SceneNode*		getParent() const { return mParent; }

	void			attachChild(SceneNodePtr child);
	SceneNodePtr	detachChild(const SceneNode& node);

	void			update();

	sf::Transform	getWorldTransform() const;
	sf::Vector2f	getWorldPosition() const;

private:
	virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const final override;
	virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void			drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void	updateCurrent();
	void			updateChildren();

private:
	std::vector<SceneNodePtr>	mChildren;
	SceneNode*					mParent;
};

} /* namespace sfml_playground */

#endif /* ENTITIES_SCENENODE_HPP_ */
