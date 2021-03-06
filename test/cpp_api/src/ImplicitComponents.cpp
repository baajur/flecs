#include <cpp_api.h>

struct Trait {
    int value;
};

void ImplicitComponents_add() {
    flecs::world world;

    auto e = flecs::entity(world).add<Position>();

    test_str(e.type().str().c_str(), "Position");
    test_assert(e.has<Position>());

    auto position = world.lookup("Position");
    test_assert(position.id() != 0);
}

void ImplicitComponents_remove() {
    flecs::world world;

    auto e = flecs::entity(world).remove<Position>();

    test_assert(!e.has<Position>());

    auto position = world.lookup("Position");
    test_assert(position.id() != 0);
}

void ImplicitComponents_has() {
    flecs::world world;

    auto e = flecs::entity(world);
    test_assert(!e.has<Position>());

    auto position = world.lookup("Position");
    test_assert(position.id() != 0);
}

void ImplicitComponents_set() {
    flecs::world world;

    auto e = flecs::entity(world).set<Position>({10, 20});

    test_str(e.type().str().c_str(), "Position");
    test_assert(e.has<Position>());
    auto *p = e.get<Position>();
    test_int(p->x, 10);
    test_int(p->y, 20);

    auto position = world.lookup("Position");
    test_assert(position.id() != 0);
}

void ImplicitComponents_get() {
    flecs::world world;

    auto e = flecs::entity(world);

    auto *p = e.get<Position>();
    test_assert(p == nullptr);

    auto position = world.lookup("Position");
    test_assert(position.id() != 0);
}

void ImplicitComponents_add_trait() {
    flecs::world world;

    auto e = flecs::entity(world).add_trait<Trait, Position>();

    test_str(e.type().str().c_str(), "TRAIT|Trait>Position");
    test_assert((e.has_trait<Trait, Position>()));

    auto position = world.lookup("Position");
    test_assert(position.id() != 0);

    auto trait = world.lookup("Trait");
    test_assert(trait.id() != 0);    
}

void ImplicitComponents_remove_trait() {
    flecs::world world;

    auto e = flecs::entity(world).remove_trait<Position, Trait>();

    test_assert((!e.has_trait<Position, Trait>()));

    auto position = world.lookup("Position");
    test_assert(position.id() != 0);

    auto trait = world.lookup("Trait");
    test_assert(trait.id() != 0);   
}

void ImplicitComponents_module() {
    flecs::world world;

    flecs::module<Position>(world);

    auto position = world.lookup("Position");
    test_assert(position.id() != 0);
}

void ImplicitComponents_system() {
    flecs::world world;

    flecs::system<Position, Velocity>(world)
        .each([](flecs::entity e, Position& p, Velocity& v) {
        });

    auto position = world.lookup("Position");
    test_assert(position.id() != 0);

    auto velocity = world.lookup("Velocity");
    test_assert(velocity.id() != 0);    
}

void ImplicitComponents_system_optional() {
    flecs::world world;

    flecs::system<Position*, Velocity*>(world)
        .each([](flecs::entity e, Position* p, Velocity* v) {
        });

    auto position = world.lookup("Position");
    test_assert(position.id() != 0);

    auto velocity = world.lookup("Velocity");
    test_assert(velocity.id() != 0);  

    auto pcomp = flecs::component<Position>(world);
    test_assert(pcomp == position);

    auto vcomp = flecs::component<Velocity>(world);
    test_assert(vcomp == velocity);    
}

void ImplicitComponents_query() {
    flecs::world world;

    auto q = flecs::query<Position, Velocity>(world);

    q.each([](flecs::entity e, Position& p, Velocity &v) { });

    auto position = world.lookup("Position");
    test_assert(position.id() != 0);

    auto velocity = world.lookup("Velocity");
    test_assert(velocity.id() != 0);  
}

void ImplicitComponents_implicit_name() {
    flecs::world world;

    auto pcomp = flecs::component<Position>(world);

    auto position = world.lookup("Position");
    test_assert(position.id() != 0);

    test_assert(pcomp == position);
}
