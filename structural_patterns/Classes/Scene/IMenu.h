#ifndef GAME_IMENU_H
#define GAME_IMENU_H


#include "MenuPage.h"
#include "IObject.h"
#include "BaseIncludes.h"
#include "Parser.h"


class IMenu: public IEventObject, public Scene { // Определяет интерфейс меню. Для создания меню необходимо отнаследоваться от данного класса и определить поведение для всех необходимых элементам команд.
public:
	class IMenuInputHandler: public InputHandler {
	public:
		explicit IMenuInputHandler(IMenu * menu_object);
	protected:
		void Catch_(const sf::Event & event) override;
	};
	IMenu() = delete;
	IMenu(sf::RenderWindow &window, const string &menu_name);;

	void Deactivate() override;

	void Activate() override;

	void Draw() override;;

	void Set(const string &filename);;

	void Move(int x, int y);

	map<string, shared_ptr<MenuPage>> & GetPages();;

	string GetInfo() const override;;

private:
	map<string, shared_ptr<MenuPage>> pages_;
	string active_page_ = "Main";
};


#endif //GAME_IMENU_H
