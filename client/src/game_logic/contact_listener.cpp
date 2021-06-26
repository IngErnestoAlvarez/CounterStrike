#include "game_logic/contact_listener.h"
#include "game_logic/body.h"

void ContactListener::BeginContact(b2Contact* contact) {
	void* data_a = contact->GetFixtureA()->GetBody()->GetUserData();
	void* data_b = contact->GetFixtureB()->GetBody()->GetUserData();

	Body* body_a = static_cast<Body*>(data_a);
	Body* body_b = static_cast<Body*>(data_b);

	body_a->handleCollision(body_b);
}
