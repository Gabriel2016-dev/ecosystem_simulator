// Structs.hpp 
#include <cstdint>
#include <string>
#include <cmath>

namespace Ecosystem {
namespace Core {
    // �  STRUCTS POUR LES DONNÉES SIMPLES struct Vector2D {
    float x;
    float y;
    
     // �  Constructeur avec valeurs par défaut
    Vector2D(float xValue = 0.0f, float yValue = 0.0f) : x(xValue), y(yValue) {}