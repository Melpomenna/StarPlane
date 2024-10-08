#pragma once

#ifndef RESERVE_ACTORS_SIZE
#define RESERVE_ACTORS_SIZE 100
#endif


#include <vector>

namespace Game
{

    namespace Core
    {
        class Actor;

        class ActorSystem final
        {
        public:
            friend class Application;

            ActorSystem();
            ~ActorSystem();

            static ActorSystem *ResolveActorSystem();

            void Update(double);

            void RemoveActor(Actor *);
            void RegisterActor(Actor *);

            void RemoveDestroyedActors() noexcept;
            void CollisionDetection() noexcept;
            void OnResize(size_t, size_t) noexcept;

			Actor *FindById(unsigned) const noexcept;

        private:
            static void Destroy();
            static void Init();

            std::vector<Actor *> actors_;
        };
    } // namespace Core

} // namespace Game
