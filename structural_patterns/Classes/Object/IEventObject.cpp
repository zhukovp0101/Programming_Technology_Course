#include "IEventObject.h"


IEventObject::InputHandler::InputHandler(IEventObject * event_object, sf::RenderWindow & window) : event_object_(event_object) {
	window.setKeyRepeatEnabled(false);
}

void
IEventObject::InputHandler::SetCommand(const sf::Event::EventType & name, shared_ptr<Command<sf::Event>> && command) {
	commands_[name] = command;
}

void IEventObject::InputHandler::Deactivate() {
	active_now_ = false;
}

void IEventObject::InputHandler::Activate() {
	active_now_ = true;
}

bool IEventObject::InputHandler::IsActiveNow() {
	return active_now_;
}

void IEventObject::InputHandler::operator ()(const sf::Event & event) {
	if (active_now_)
		Catch_(event);
}

void IEventObject::InputHandler::KeyPressed_(const shared_ptr<Command<sf::Event>> & command, const sf::Event & event) {
	(*command)(event);
}

void IEventObject::InputHandler::KeyReleased_(const shared_ptr<Command<sf::Event>> & command, const sf::Event & event) {
	(*command)(event);
}

void
IEventObject::InputHandler::MouseButtonPressed_(const shared_ptr<Command<sf::Event>> & command, const sf::Event & event) {
	(*command)(event);
}

void IEventObject::InputHandler::MouseButtonReleased_(const shared_ptr<Command<sf::Event>> & command,
                                                      const sf::Event & event) {
	(*command)(event);
}

void IEventObject::InputHandler::MouseMoved_(const shared_ptr<Command<sf::Event>> & command, const sf::Event & event) {
	(*command)(event);
}

void
IEventObject::InputHandler::MouseWheelScrolled_(const shared_ptr<Command<sf::Event>> & command, const sf::Event & event) {
	(*command)(event);
}

void IEventObject::InputHandler::Catch_(const sf::Event & event) {
	Handle_(event);
}

void IEventObject::InputHandler::Handle_(const sf::Event & event) {
	if (commands_[event.type])
		switch (event.type) {
			case sf::Event::KeyPressed:
				KeyPressed_(commands_[sf::Event::KeyPressed], event);
				break;
			case sf::Event::KeyReleased:
				KeyReleased_(commands_[sf::Event::KeyReleased], event);
				break;
			case sf::Event::MouseButtonPressed:
				MouseButtonPressed_(commands_[sf::Event::MouseButtonPressed], event);
				break;
			case sf::Event::MouseMoved:
				MouseMoved_(commands_[sf::Event::MouseMoved], event);
				break;
			case sf::Event::MouseButtonReleased:
				MouseButtonReleased_(commands_[sf::Event::MouseButtonReleased], event);
				break;
			case sf::Event::MouseWheelScrolled:
				MouseWheelScrolled_(commands_[sf::Event::MouseWheelScrolled], event);
				break;
		}
}

IEventObject::IEventObject(sf::RenderWindow & window) : input_handler_(make_shared<InputHandler>(this, window)) {

}

string IEventObject::GetInfo() const {
	return IObject::GetInfo() + ", IEventObject";
}

IEventObject::InputHandler & IEventObject::GetInputHandler() {
	return *input_handler_;
}
