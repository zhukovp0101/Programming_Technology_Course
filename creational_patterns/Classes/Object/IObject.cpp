#include "IObject.h"

IObject::IObject(): id_(next_id_++) {
	IObject::all_.emplace(nullptr);
	all_.emplace(this);
	++count_;
}

IObject::IObject(const IObject & copy): id_(next_id_++) {
	all_.emplace(this);
	++count_;
}

IObject & IObject::operator = (const IObject & copy) {
	return *this;
}

IObject::~IObject() {
//	if (all_.find(this) != all_.end())
//		cout << IObject::GetCount() << ' ';
	all_.erase(this);
	--count_;
}

const set<IObject *> & IObject::GetAll() {
	return all_;
}

size_t IObject::GetCount() {
	return count_;
}

size_t IObject::GetId() const {
	return id_;
}

size_t IObject::count_(0);

size_t IObject::next_id_(0);

string IObject::GetInfo() const {
	return "IObject";
}

const vector<string> & IObject::GetErrors() {
	return errors_;
}

const string & IObject::GetLastError() {
	last_error_copy_ = last_error_;
	last_error_ = "";
	return last_error_copy_;
}

const bool IObject::Error() {
	if (error_) {
		error_ = false;
		return true;
	}
	return false;
}

void IObject::SetError(string str) {
	error_ = true;
	errors_.emplace_back(str);
	last_error_ = str;
	#ifdef DEBUG
		cout << last_error_ << endl;
	#endif
}

set<IObject *> IObject::all_ = set<IObject *>();

IDrawingObject::IDrawingObject(sf::RenderWindow & window): window_(window) {
}

sf::RenderWindow & IDrawingObject::GetWindow() const {
	return window_;
}

string IDrawingObject::GetInfo() const {
	return IObject::GetInfo() + ", IDrawingObject";
}
