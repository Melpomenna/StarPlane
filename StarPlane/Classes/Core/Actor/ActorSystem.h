#pragma once

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

            ActorSystem() = default;
            ~ActorSystem();

            static ActorSystem *ResolveActorSystem();

            void Update(double);

            void RemoveActor(Actor *);
            void RegisterActor(Actor *);

			void RemoveDestroyedActors() noexcept;
            void CollisionDetection() noexcept;

        private:
            static void Destroy();
            static void Init();

            std::vector<Actor *> actors_;
        };
    } // namespace Core

} // namespace Game
