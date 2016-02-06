#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

namespace SFGame
{

/**
 * Forward declarations
 */
struct Command;
struct CommandCategory;

class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public:
    SceneNode();
    virtual ~SceneNode() = default;

    SceneNode*					getParent() const { return mParent; }
    virtual CommandCategory		getCommandCategory() const;

    void						attachChild(std::unique_ptr<SceneNode> child);
    std::unique_ptr<SceneNode>	detachChild(const SceneNode& node);

    void						update();

    sf::Transform				getWorldTransform() const;
    sf::Vector2f				getWorldPosition() const;

    void						onCommand(const Command& command);

private:
    virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const final override;
    virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    void				drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

    virtual void		updateCurrent();
    void				updateChildren();

private:
    std::vector<std::unique_ptr<SceneNode>>	mChildren;
    SceneNode*								mParent;
};

} /* namespace sfml_playground */
