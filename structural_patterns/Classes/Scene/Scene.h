#ifndef GAME_SCENE_H
#define GAME_SCENE_H


#include <IUpdateObject.h>
#include "IObject.h"
#include "BaseIncludes.h"


class Scene: public IDrawingObject {
public:
	explicit Scene(sf::RenderWindow & window);;
	virtual ~Scene() = default;
	virtual void Draw() override = 0;
	void SetBackGround(string resource);;

	virtual void Deactivate();;

	virtual void Activate();;

	bool IsActiveNow();

	const sf::Sprite & GetBackGround();;

	virtual string GetInfo() const override;;

	virtual sf::Vector2u GetSize() const;;

protected:
	bool active_now_ = false;

private:
	sf::Sprite background_;
	sf::Texture background_texture_;
};


#endif //GAME_SCENE_H
