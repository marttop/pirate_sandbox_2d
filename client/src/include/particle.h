#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "SFML/Graphics.hpp"

#define DEG_2_RAD(deg) (deg * M_PI / 180)
#define MIN_LIFE_TO_INTERPOLATE 15

struct SDL_Texture;

class Particle
{
	private:

	/*  This is the only variable we care about no matter if
	   the particle is alive or dead */
	unsigned int life = 0;

	union ParticleInfo
	{
		/* This struct holds the state of the particle when 
		   it's being update (it's still alive).*/
		struct ParticleState
		{
			unsigned int startLife;
			sf::Vector2f pos;
			float size;
			float speed;
			sf::Vector2f direction;
			sf::Vector2f randomDirection;
			sf::Color startColor;
			sf::Color endColor;
			sf::BlendMode blendMode;
			float t;

			ParticleState() {}

		} pLive;

		/* If the particle is dead, then the 'next' member comes 
		   into play and the struct it's not used. This pointer
		   called 'next' holds a pointer to the next available 
		   particle after this one. */
		Particle* next;

		ParticleInfo() {}
	} pState;

	public:

	Particle();

	// Initializes new generated particle
	void Init(sf::Vector2f pos, float speed, sf::Vector2f direction, sf::Vector2f randomDirection, float size, unsigned int life, sf::Color startColor, sf::Color endColor, sf::BlendMode blendMode);

	// Generic methods
	void Update();
	bool Draw(sf::RenderWindow *gWindow);
	bool IsAlive();

	// Particle pointer methods
	Particle* GetNext();
	void SetNext(Particle* next);

	// Given two colors interpolates linearly over time and returns the resulting color
	sf::Color RgbInterpolation(sf::Color startColor, float timeStep, sf::Color endColor);

	/* Calculates particle position considering its velocity
	   and if there's a vortex in the system */
	void CalculateParticlePos();
};

#endif