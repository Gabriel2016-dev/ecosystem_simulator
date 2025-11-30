// Entity.hpp
#pragma once
#include "Structs.h"
#include <SDL3/SDL.h>
#include <memory>
#include <random>
#include <string>
#include <vector>
Vector2D seekfood(std::vector<foodsource> &foods) const
{
    if (foods.empty())
    {
        return vector2D(0, 0);
    }
    foodsource *closest = nullptr;
    float DIstancemin = 999999.0f;
    for (const auto &food : foods)
    {
        float d = posiiton.Distance(food.position);
        if (d < Distancemin)
        {
            Distancemin = d;
            closest = &food;
        }
    }
    if (!closest)
    {
        return vector2D(0, 0);
    }
    //direction vers la nourriture
    Vector2D desired = (closest-position - posiiton).Normalized() * mMaxspeed;
    return (desired -mVelocity).Clamped(mMacforce);
}
Vector2D AvoidPredator(std::vector<Entity> entities) const
{
    Vector2D force(0, 0);
    float dangerR = 80.0f;
    for (const auto &e : entities)
    {
        if (e->GetType() != EntityType::CARNIVORE)
        {
            continue;
        }
        if (e->get() == this)
        {
            continue;
        }
        float d1 = posiiton.Distance(e->position);
        if (d1 < dangerR)
        {
            Vector2D flee = (position - e->position).Normalized();
            force = force + flee * (1.0f - d / dangerR);
        }
    }
    return force.Clamped(mMaxforce);
}
Vector2D StayInBounds(float width, float height) const
{
    float margin = 30.0f;
    Vector2D correction(0, 0);
    if (position.x < margin)
    {
        correction.x = mMaxspeed;
    }
    else if (position.x > (width - margin))
    {
        correction.x = -mMaxspeed;
    }
    if (position.y < margin)
    {
        correction.y = mMaxspeed;
    }
    else if (position.y > (height - margin))
    {
        correction.y = -mMaxspeed;
    }
    return correction.Clamped(mMaxforce);
}
void ApplyForce(Vector2D& force){
     mAccelereation = mAcceleration + force;
}
namespace Ecosystem
{
    namespace Core
    {
        // 🎯 ÉNUMÉRATION DES TYPES D'ENTITÉS
        enum class EntityType
        {
            HERBIVORE,
            CARNIVORE,
            PLANT
        };
        class Entity
        {
        private:
            // 🔒 DONNÉES PRIVÉES - État interne protégé
            float mEnergy;
            float mMaxEnergy;
            int mAge;
            int mMaxAge;
            bool mIsAlive;
            Vector2D mVelocity;
            EntityType mType;

            // 🎲 Générateur aléatoire
            mutable std::mt19937 mRandomGenerator;

        public:
            // 🔓 DONNÉES PUBLIQUES - Accès direct sécurisé
            Vector2D position;
            Color color;
            float size;
            std::string name;
            // CONSTRUCTEURS
            Entity(EntityType type, Vector2D pos, std::string entityName = "Unnamed");
            Entity(const Entity &other); // Constructeur de copie

            // DESTRUCTEUR
            ~Entity();
            // ⚙️ MÉTHODES PUBLIQUES
            void Update(float deltaTime);
            void Move(float deltaTime);
            void Eat(float energy);
            bool CanReproduce() const;
            std::unique_ptr<Entity> Reproduce();
            void ApplyForce(Vector2D force);

            // 📊 GETTERS - Accès contrôlé aux données privées
            float GetEnergy() const { return mEnergy; }
            float GetEnergyPercentage() const { return mEnergy / mMaxEnergy; }
            int GetAge() const { return mAge; }
            bool IsAlive() const { return mIsAlive; }
            EntityType GetType() const { return mType; }
            Vector2D GetVelocity() const { return mVelocity; }

            // 🎯 MÉTHODES DE COMPORTEMENT
            Vector2D SeekFood(const std::vector<Food> &foodSources) const;
            Vector2D AvoidPredators(const std::vector<Entity *> &predators) const;
            Vector2D StayInBounds(float worldWidth, float worldHeight) const;

            // 🎨 MÉTHODE DE RENDU
            void Render(SDL_Renderer *renderer) const;

        private:
            // 🔐 MÉTHODES PRIVÉES - Logique interne
            void ConsumeEnergy(float deltaTime);
            void Age(float deltaTime);
            void CheckVitality();
            Vector2D GenerateRandomDirection();
            Color CalculateColorBasedOnState() const;
        };
    } // namespace Core
} // namespace Ecosystem