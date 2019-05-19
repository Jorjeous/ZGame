#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#define M_PI 3.1415
namespace sf {
	class RenderTarget;
}//sf

namespace lightlib {

	class LightParams
	{
	public:
		sf::FloatRect aabb() const;

		sf::Vector2f position;
		float radius = 7.f;
		float coneAngle = 4.f;
		float coneWidth = 5.f;
		bool cone = false;
		int circlePointsPerRadian = 80;
	};

	class ShadowWorld
	{
	public:
		void addLine(sf::Vector2f a, sf::Vector2f b);
		void findLineSelfIntersections();
		void deduplicateLineEndPoints();
		void deduplicateLineSelfIntersectionsPoints();
		std::vector<sf::Vector2f> computeLightPoints(const LightParams& params);
		unsigned getLineCount() const;
		std::pair<sf::Vector2f, sf::Vector2f> getLineByIndex(unsigned idx) const;

	private:
		void findAndAddPoints(std::vector<sf::Vector2f>& out, sf::Vector2f p, sf::Vector2f a, float r, bool perpoffsettoo) const;
		sf::Vector2f findPoint(sf::Vector2f a, sf::Vector2f b) const;
		void catchLinesByLightAABB(const LightParams& params);

		std::vector<sf::Vector2f> m_linesa;
		std::vector<sf::Vector2f> m_linesb;
		std::vector<sf::Vector2f> m_uniquewallpoints;
		std::vector<sf::Vector2f> m_lineselfcrosspoints;

		std::vector<sf::Vector2f> m_caughtlinesa;
		std::vector<sf::Vector2f> m_caughtlinesb;
		std::vector<sf::Vector2f> m_allcaughtpoints;
	};

	void debugDrawLightPoints(sf::RenderTarget& target, const LightParams& params, const std::vector<sf::Vector2f>& points);// MAIN THING
	void debugDrawFloatRect(sf::RenderTarget& target, sf::FloatRect rect, unsigned color = 0xff0000ff);


	void RecPositioning(sf::RenderTarget &target, sf::Vector2f t, sf::Vector2f v, const LightParams& params);
	

}

