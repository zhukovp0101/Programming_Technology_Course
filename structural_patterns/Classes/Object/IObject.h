#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H


#include "BaseIncludes.h"


class IObject {
public:
	IObject();
	IObject(const IObject & copy);
	IObject & operator = (const IObject & copy);
	virtual ~IObject();

	size_t GetId() const;
	static size_t GetCount();
	virtual string GetInfo() const;

	static const set<IObject *> & GetAll();
	static const vector<string> & GetErrors();
	static const string & GetLastError();
	static const bool Error();

private:
	static set<IObject *> all_;
	static size_t count_;
	static size_t next_id_;
	size_t id_ = 0;

protected:
	static void SetError(string str);
	static vector<string> errors_;
	static string last_error_;
	static string last_error_copy_;
	static bool error_;
};

class IDrawingObject: public IObject {
public:
	explicit IDrawingObject(sf::RenderWindow & window);
	virtual ~IDrawingObject() = default;
	virtual void Draw() = 0;
	virtual string GetInfo() const override;

	sf::RenderWindow & GetWindow() const;

private:
	sf::RenderWindow & window_;
};

#endif //GAME_OBJECT_H
