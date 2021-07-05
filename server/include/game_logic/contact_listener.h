#ifndef CONTACT_LISTENER_H
#define CONTACT_LISTENER_H

#include <Box2D/Box2D.h>

class ContactListener : public b2ContactListener {
public:
	virtual void BeginContact(b2Contact* contact) override;
};

#endif
