#pragma once
#include "Entity.h"
#include "Structs.h"
#include <memory>
#include <random>
#include <string>
#include <vector>
void AddEntity(EntityType type, constVector2D &pos)
{
    if (mEntities.size() >= mMaxentities)
    {
        return;
    }
    std::string name;
    switch (type)
    {
        caseEntityType::HERBIVORE : name = "Herbivore_" + std::to_string(mStats.totalHerbivores);
        break;
        caseEntityType::CARNIVORE : name = "Carnivore_" + std::to_string(mStats.totalCarnivores);
        break;
        caseEntityType::PLANT : name = "Plant_" + std::to_string(mStats.totalPlants);
        break;
    }
    mEntities.push_back(std::make_unique<Entiy>(type, pos, name));
}
void AddFood(const Vector2D &pos, 25.0f)
{
    if (mFoodsources.size() < 500) // limite
    {
        mFoodsources.emplace_back(pos, 35.0f);
    }
}
namespace Ecosystem
{
    namespace Core
    {
        class Ecosystem
        {
        private:
            // 🔒 ÉTAT INTERNE
            std::vector<std::unique_ptr<Entity>> mEntities;
            std::vector<Food> mFoodSources;

            float mWorldWidth;
            float mWorldHeight;
            int mMaxEntities;
            int mDayCycle;

            // 🎲 Générateur aléatoire

            std::mt19937 mRandomGenerator;

            // 📊 STATISTIQUES
            struct Statistics
            {
                int totalHerbivores;
                int totalCarnivores;
                int totalPlants;
                int totalFood;
                int deathsToday;
                int birthsToday;
            } mStats;

        public:
            // CONSTRUCTEUR/DESTRUCTEUR
            Ecosystem(float width, float height, int maxEntities = 500);
            ~Ecosystem();
            // ⚙️ MÉTHODES PUBLIQUES
            void Initialize(int initialHerbivores, int initialCarnivores, int initialPlants);
            void Update(float deltaTime);
            void SpawnFood(int count);
            void RemoveDeadEntities();
            void HandleReproduction();
            void HandleEating();

            // 📊 GETTERS
            size_t GetEntityCount() const
            {
                return mEntities.size();
            }
            // Implémentation de la Classe Ecosystem
            int GetFoodCount() const
            {
                return mFoodSources.size();
            }
            Statistics GetStatistics() const
            {
                return mStats;
            }
            float GetWorldWidth() const
            {
                return mWorldWidth;
            }
            float GetWorldHeight() const
            {
                return mWorldHeight;
            }

            // 🎯 MÉTHODES DE GESTION
            void AddEntity(std::unique_ptr<Entity> entity);
            void AddFood(Vector2D position, float energy = 25.0f);

            // 🎨 RENDU
            void Render(SDL_Renderer *renderer) const;

        private:
            // 🔐 MÉTHODES PRIVÉES
            void UpdateStatistics();
            void SpawnRandomEntity(EntityType type);
            Vector2D GetRandomPosition();
            void HandlePlantGrowth(float deltaTime);
        };
    } // namespace Core
} // namespace Ecosystem