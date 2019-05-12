#ifndef GAME_COMMAND_H
#define GAME_COMMAND_H


#include "IUpdateObject.h"


template <class ... T_Object>
class Command {
public:
	virtual const void operator()(const T_Object & ...);; // Возможность воздейстовать на другой объект, поддающийся изменениям;
};

template<class... T_Object>
const void Command<T_Object...>::operator ()(const T_Object & ...) {}


#endif //GAME_COMMAND_H
