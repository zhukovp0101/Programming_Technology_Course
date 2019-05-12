#ifndef GAME_IEVENTOBJECT_H
#define GAME_IEVENTOBJECT_H


#include "IObject.h"
#include "BaseIncludes.h"
#include "Command.h"


class IEventObject: public IObject {
public:
	class InputHandler {
	public:
		explicit InputHandler(IEventObject * event_object, sf::RenderWindow & window);

		void SetCommand(const sf::Event::EventType & name, shared_ptr<Command<sf::Event>> && command);

		void Deactivate();

		void Activate();

		bool IsActiveNow();

		void operator ()(const sf::Event & event);

	protected:
		virtual void KeyPressed_(const shared_ptr<Command<sf::Event>> & command, const sf::Event & event);;
		virtual void KeyReleased_(const shared_ptr<Command<sf::Event>> & command, const sf::Event & event);;
		virtual void MouseButtonPressed_(const shared_ptr<Command<sf::Event>> & command, const sf::Event & event);;
		virtual void MouseButtonReleased_(const shared_ptr<Command<sf::Event>> & command, const sf::Event & event);;
		virtual void MouseMoved_(const shared_ptr<Command<sf::Event>> & command, const sf::Event & event);;
		virtual void MouseWheelScrolled_(const shared_ptr<Command<sf::Event>> & command, const sf::Event & event);

		virtual void Catch_(const sf::Event & event);

		IEventObject * event_object_;

	private:
		bool active_now_ = false;

		void Handle_(const sf::Event & event);;

		map<sf::Event::EventType, shared_ptr<Command<sf::Event>>> commands_;
	};

	explicit IEventObject(sf::RenderWindow & window);;
	IEventObject(const IEventObject & copy) = delete;
	virtual ~IEventObject() = default;
	virtual string GetInfo() const override;;

	InputHandler & GetInputHandler();

protected:
	shared_ptr<InputHandler> input_handler_;
};





#endif //GAME_IEVENTOBJECT_H
