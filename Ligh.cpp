

#pragma once
#include "Light.h"
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <math.h>
#include <iostream>

namespace lightlib {

	const float Pi_L = 3.1415;
	
	float angle(sf::Vector2f v)
	{
		return std::atan2(v.y, v.x);
	}

	float signedAngleDifference(float a, float b)
	{
		return std::atan2(std::sin(b - a), std::cos(b - a));
	}

	float angleDifference(float a, float b)
	{
		return std::fabs(std::atan2(std::sin(b - a), std::cos(b - a))); //positive diff angle
	}

	float sgn(float x)
	{
		return static_cast <float>((x > 0.f) - (x < 0.f)); //It did not want to transform types, so i useed static cast
	}

	 sf::Vector2f perpendicular(sf::Vector2f v)
	{
		return sf::Vector2f(-v.y, v.x);
	}

	float length(sf::Vector2f v)
	{
		return std::sqrt(v.x * v.x + v.y * v.y);
	}

	sf::Vector2f normalize(sf::Vector2f v)
	{
		return v / length(v);
	}

	bool findLinesIntersection(sf::Vector2f a1, sf::Vector2f b1, sf::Vector2f a2, sf::Vector2f b2, sf::Vector2f& out)
	{
		if (((b2 - a2) == (b1 - a1)) || ((b2 - a2) == (a1 - b1))) //check if they parralel
			return false;											

		const float lead1x = b1.x - a1.x;
		const float lead1y = b1.y - a1.y;

		const float lead2x = b2.x - a2.x;
		const float lead2y = b2.y - a2.y;

		const float r = (lead1x*(a2.y - a1.y) + lead1y * (a1.x - a2.x)) / (lead2x * lead1y - lead2y * lead1x);
		const float s = (lead2x*(a1.y - a2.y) + lead2y * (a2.x - a1.x)) / (lead1x * lead2y - lead1y * lead2x);

		if ((0.f <= r) && (r <= 1.f) && (0.f <= s) && (s <= 1.f))
		{
			out = a1 + s * sf::Vector2f(lead1x, lead1y);
			return true;
		}
		return false;
	}

	 bool findStrictLinesIntersection(sf::Vector2f a1, sf::Vector2f b1, sf::Vector2f a2, sf::Vector2f b2, sf::Vector2f& out)
	{
		if (((b2 - a2) == (b1 - a1)) || ((b2 - a2) == (a1 - b1)))//parallel check
			return false; 

		const float lead1x = b1.x - a1.x;
		const float lead1y = b1.y - a1.y;

		const float lead2x = b2.x - a2.x;
		const float lead2y = b2.y - a2.y;

		const float r = (lead1x*(a2.y - a1.y) + lead1y * (a1.x - a2.x)) / (lead2x * lead1y - lead2y * lead1x);
		const float s = (lead2x*(a1.y - a2.y) + lead2y * (a2.x - a1.x)) / (lead1x * lead2y - lead1y * lead2x);

		if ((0.f < r) && (r < 1.f) && (0.f < s) && (s < 1.f))
		{
			out = a1 + s * sf::Vector2f(lead1x, lead1y);
			return true;
		}
		return false;
	}
	 
	sf::FloatRect LightParams::aabb() const
	{
		if (!cone)
		{
			const sf::Vector2f r2(radius, radius);
			return sf::FloatRect(position - r2, 2.f * r2);
		}//if not cone

		sf::Vector2f tripoints[3];
		tripoints[0] = sf::Vector2f(std::cos(coneAngle), std::sin(coneAngle));
		tripoints[1] = sf::Vector2f(std::cos(coneAngle + coneWidth / 2.f), std::sin(coneAngle + coneWidth / 2.f));
		tripoints[2] = sf::Vector2f(std::cos(coneAngle - coneWidth / 2.f), std::sin(coneAngle - coneWidth / 2.f));
		float minX = 0.f, minY = 0.f, maxX = 0.f, maxY = 0.f;
		for (sf::Vector2f v : tripoints)
		{
			minX = std::min(minX, v.x);
			minY = std::min(minY, v.y);
			maxX = std::max(maxX, v.x);
			maxY = std::max(maxY, v.y);
		}//for

		minX = sgn(minX);
		minY = sgn(minY);
		maxX = sgn(maxX);
		maxY = sgn(maxY);

		sf::FloatRect ret;
		ret.left = position.x + radius * minX;
		ret.top = position.y + radius * minY;
		ret.width = radius * (maxX - minX);
		ret.height = radius * (maxY - minY);
		return ret;
	}

	namespace {

		class VectorAngleComparator
		{
		public:
			VectorAngleComparator(sf::Vector2f c, float mid) : c(c), mid(mid) {}

			bool operator()(sf::Vector2f a, sf::Vector2f b) const
			{
				const float aa = signedAngleDifference(angle(a - c), mid);
				const float bb = signedAngleDifference(angle(b - c), mid);
				return aa < bb;
			}

		private:
			sf::Vector2f c;
			float mid;

		};

		class VectorAngleOutOfConeChecker
		{
		public:
			VectorAngleOutOfConeChecker(sf::Vector2f c, float conemid, float conesize) : c(c), conemid(conemid), conesize(conesize) {}

			bool operator()(sf::Vector2f a) const
			{
				return angleDifference(angle(a - c), conemid) > (0.001f + conesize / 2.f);
			}

		private:
			sf::Vector2f c;
			float conemid, conesize;

		};

	}//unnamed

	void ShadowWorld::addLine(sf::Vector2f a, sf::Vector2f b)
	{
		if (a == b)
			return;

		m_linesa.push_back(a);
		m_linesb.push_back(b);
	}

	void ShadowWorld::findLineSelfIntersections()
	{
		m_lineselfcrosspoints.clear();
		for (int i = 0; i < m_linesa.size(); ++i)
		{
			for (int j = i + 1; j < m_linesa.size(); ++j)
			{
				sf::Vector2f badp;
				const auto a1 = m_linesa[i];
				const auto b1 = m_linesb[i];
				const auto a2 = m_linesa[j];
				const auto b2 = m_linesb[j];
				if (findStrictLinesIntersection(a1, b1, a2, b2, badp))
					m_lineselfcrosspoints.push_back(badp);
			}//for j
		}//for i
	}

	inline bool compareXY(sf::Vector2f a, sf::Vector2f b)
	{
		if (a.x == b.x)
			return a.y < b.y;

		return a.x < b.x;
	}

	void ShadowWorld::deduplicateLineEndPoints()
	{
		m_uniquewallpoints.clear();
		m_uniquewallpoints = m_linesa;
		m_uniquewallpoints.insert(m_uniquewallpoints.end(), m_linesb.begin(), m_linesb.end());
		std::sort(m_uniquewallpoints.begin(), m_uniquewallpoints.end(), compareXY);
		auto newend = std::unique(m_uniquewallpoints.begin(), m_uniquewallpoints.end());
		m_uniquewallpoints.erase(newend, m_uniquewallpoints.end());
	}

	void ShadowWorld::deduplicateLineSelfIntersectionsPoints()
	{
		std::sort(m_lineselfcrosspoints.begin(), m_lineselfcrosspoints.end(), compareXY);
		auto newend = std::unique(m_lineselfcrosspoints.begin(), m_lineselfcrosspoints.end());
		m_lineselfcrosspoints.erase(newend, m_lineselfcrosspoints.end());
	}

	inline std::vector<sf::Vector2f> getCirclePoints(const LightParams& params)
	{
		std::vector<sf::Vector2f> ret;
		if (params.circlePointsPerRadian == 0u)
			return ret;

		const float baseangle = params.cone ? (params.coneAngle - params.coneWidth / 2.f) : 0.f;
		const float spreadangle = params.cone ? params.coneWidth : (2.f * Pi_L);
		const int pointscount = std::max<int>(params.circlePointsPerRadian * params.coneWidth, 3);
		for (int i = 0; i < pointscount; ++i)
		{
			const float angle = baseangle + (i * spreadangle) / (pointscount - 1);
			ret.push_back(params.position + sf::Vector2f(std::cos(angle), std::sin(angle)));
		}
		return ret;
	}

	std::vector<sf::Vector2f> ShadowWorld::computeLightPoints(const LightParams& params)
	{
		catchLinesByLightAABB(params);
		const sf::Vector2f p = params.position;
		const float r = params.radius;

		std::vector<sf::Vector2f> ret;

		for (const sf::Vector2f a : getCirclePoints(params))
			findAndAddPoints(ret, p, a, r, false);

		for (const sf::Vector2f a : m_allcaughtpoints)
			findAndAddPoints(ret, p, a, r, true);

		if (params.cone)
		{
			auto newend = std::remove_if(ret.begin(), ret.end(), VectorAngleOutOfConeChecker(p, params.coneAngle, params.coneWidth));
			ret.erase(newend, ret.end());
		}//if params cone

		std::sort(ret.begin(), ret.end(), VectorAngleComparator(p, params.cone ? params.coneAngle : 0.f));
		return ret;
	}

	unsigned ShadowWorld::getLineCount() const
	{
		return m_linesa.size();
	}

	std::pair<sf::Vector2f, sf::Vector2f> ShadowWorld::getLineByIndex(unsigned i) const
	{
		return std::make_pair(m_linesa[i], m_linesb[i]);
	}

	void ShadowWorld::findAndAddPoints(std::vector<sf::Vector2f>& out, sf::Vector2f p, sf::Vector2f a, float r, bool perpoffsettoo) const
	{
		a = p + r * normalize(a - p);
		out.push_back(findPoint(p, a));
		if (perpoffsettoo)
		{
			const auto off = normalize(perpendicular(p - a));
			out.push_back(findPoint(p, a + off));
			out.push_back(findPoint(p, a - off));
		}//if perp offset too
	}

	sf::Vector2f ShadowWorld::findPoint(sf::Vector2f a, sf::Vector2f b) const
	{
		for (int i = 0; i < m_caughtlinesa.size(); ++i)
			findLinesIntersection(a, b, m_caughtlinesa[i], m_caughtlinesb[i], b);

		return b;
	}

	void sortXYInplace(sf::Vector2f& a, sf::Vector2f& b)
	{
		if (a.x < b.x)
			std::swap(a.x, a.x);

		if (a.y < b.y)
			std::swap(a.y, b.y);
	}

	void ShadowWorld::catchLinesByLightAABB(const LightParams& params)
	{
		const sf::FloatRect lightrect = params.aabb();
		m_caughtlinesa.clear();
		m_caughtlinesb.clear();
		m_allcaughtpoints.clear();
		for (int i = 0; i < m_linesa.size(); ++i)
		{
			sf::Vector2f a = m_linesa[i];
			sf::Vector2f b = m_linesb[i];
			sortXYInplace(a, b);
			const sf::FloatRect linerect(a, (b - a) + sf::Vector2f(1.f, 1.f));
			if (lightrect.intersects(linerect))
			{
				m_caughtlinesa.push_back(m_linesa[i]);
				m_caughtlinesb.push_back(m_linesb[i]);
			}//if
		}//for i

		//query all self intersections and wall points too
		for (const sf::Vector2f p : m_lineselfcrosspoints)
			if (lightrect.contains(p))
				m_allcaughtpoints.push_back(p);

		for (const sf::Vector2f p : m_uniquewallpoints)
			if (lightrect.contains(p))
				m_allcaughtpoints.push_back(p);
	}
	void RecPositioning(sf::RenderTarget &target, sf::Vector2f t,sf::Vector2f v, const LightParams& params) { //sorry for this part(
		sf::Vector2f Vect = v;
		sf::Vector2f deltaX(-15, 0);
		float dY, dX;
		dY = t.x;
		dX = t.y;
		sf::RectangleShape rec(sf::Vector2f(-30, -2000));
		/*if (t.x >= 0 && t.y >= 0) {   //down right 
			sf::RectangleShape rec(sf::Vector2f(-40, -500));
			rec.setFillColor(sf::Color(100, 200, 50));



			//std::cout << "hi";
			rec.setOrigin(sf::Vector2f(-20.f, 0.f));
			rec.setPosition(v);
			rec.setRotation((atan2f(-dY, dX)) * 180 / Pi_L);

			target.draw(rec);
		}
		if (t.x >= 0 && t.y <= 0) {
			sf::RectangleShape rec(sf::Vector2f(-40, -500));
			rec.setFillColor(sf::Color::Yellow); //
			

			rec.setOrigin(sf::Vector2f(-20.f, 0.f));
			rec.setPosition(v);
			rec.setRotation((atan2f(-dY, dX)) * 180 / Pi_L);
			
			target.draw(rec);
			 
			//rec.setPosition(v); //downl left
		}
		if (t.x <= 0 && t.y >= 0) {
			sf::RectangleShape rec(sf::Vector2f(-40, -500));
			rec.setFillColor(sf::Color::Black);



			
			rec.setOrigin(sf::Vector2f(-20.f, 0.f));
			rec.setPosition(v);
			rec.setRotation((atan2f(-dY, dX)) * 180 / Pi_L);

			target.draw(rec);
		}
		if (t.x <= 0 && t.y <= 0) {
			
			
			//target.draw(rec);
		}*/
		rec.setFillColor(sf::Color(0, 0, 10, 100));

		rec.setOrigin(deltaX);
		rec.setPosition(v);
		rec.setRotation((atan2f(-dY, dX)) * 180 / Pi_L);

		target.draw(rec);

		
	}


	void debugDrawLightPoints(sf::RenderTarget& target, const LightParams& params, const std::vector<sf::Vector2f>& points)
	{
		if (points.empty()){
			return;
		}
		sf::Vector2f player = params.position;

		/*int I_counter = 0;
		int II_counter = 0;
		int III_counter = 0;
		int IV_counter = 0;

		sf::ConvexShape I; //first quater	//down right
		sf::ConvexShape II;					//up right
		sf::ConvexShape III;				//left down
		sf::ConvexShape IV;					//up left
		sf::ConvexShape V;
		*/


		sf::CircleShape sha;
		sha.setRadius(5.f);
		sha.setOrigin(sha.getRadius(), sha.getRadius());
		int sizePoints = points.size();
		
		//for (const sf::Vector2f v : points)
		for(int i = 0; i < sizePoints; i++)
		{
			
			sf::Vector2f v = points[i]; 	
			sf::Vector2f tmp = player - v; //vector from player to point

			//tmp = sf::Vector2f(normalize(tmp).x*1000, normalize(tmp).y*1000);
			
			
			//rec.setPosition(v+deltaX);
			//rec.setOrigin(v);

			
			//rec.setFillColor(sf::Color(200, 0, 31, 200));
			
			
			//rec.setPosition(v);
			RecPositioning(target, tmp, v, params); //ROTATION
			sha.setPosition(v);
			target.draw(sha);
			
		}	
		/*I.setPoint(I_counter, sf::Vector2f(200 * 20, 200 * 20));
		II.setPoint(II_counter, sf::Vector2f(0, 200 * 20));
		III.setPoint(III_counter, sf::Vector2f(200 * 20, 0));
		IV.setPoint(IV_counter, sf::Vector2f(0, 0));
		I.setFillColor(sf::Color(0, 0, 31, 100));
		V.setFillColor(sf::Color(0, 0, 31, 100));


			
			I.setPointCount(sizePoints/4 );
			II.setPointCount(sizePoints / 4);
			III.setPointCount(sizePoints / 4);
			IV.setPointCount(sizePoints / 4);
			I.setFillColor(sf::Color(0, 0, 31, 100));
			I.setPoint(0, sf::Vector2f(0, 0));
			if (tmp.x <= 0 && tmp.y <= 0) {
				I.setPoint(I_counter, v);   //down right
				I_counter++;
											//rec.setPosition(v);
			}
			if (tmp.x >= 0 && tmp.y <= 0) {
				II.setPoint(II_counter, v);
				II_counter++;
				//rec.setPosition(v); //up right
			}
			if (tmp.x <= 0 && tmp.y >= 0) {
				III.setPoint(III_counter, v);
				III_counter++;
				//rec.setPosition(v); //left down
			}
			if (tmp.x <= 0 && tmp.y <= 0) {
				IV.setPoint(IV_counter, v);
				IV_counter++;
				//rec.setPosition(v); //up left
			}
			
		target.draw(I);
		target.draw(II);
		target.draw(III);
		target.draw(IV);

		target.draw(V);
		*/
		sf::VertexArray arr(sf::LinesStrip);
		for (const sf::Vector2f v : points)
			arr.append(sf::Vertex(v));

		if (params.cone)
			arr.append(sf::Vertex(params.position));

		arr.append(sf::Vertex(points[0]));
		target.draw(arr);

		arr.clear();
		arr.setPrimitiveType(sf::TrianglesFan);
		arr.append(sf::Vertex(params.position));
		for (const sf::Vector2f v : points)
			arr.append(sf::Vertex(v));

		if (!params.cone)
			arr.append(sf::Vertex(points[0]));

		for (int i = 0; i < arr.getVertexCount(); ++i)
			arr[i].color = sf::Color(50, 230, 31, 20);  //Color of circle 

		target.draw(arr);
	}

	void debugDrawFloatRect(sf::RenderTarget& target, sf::FloatRect rect, unsigned color)
	{
		sf::VertexArray arr(sf::LinesStrip);
		const float x1 = rect.left;
		const float x2 = rect.left + rect.width;
		const float y1 = rect.top;
		const float y2 = rect.top + rect.height;
		const sf::Color c(color);

		arr.append(sf::Vertex(sf::Vector2f(x1, y1), c));
		arr.append(sf::Vertex(sf::Vector2f(x1, y2), c));
		arr.append(sf::Vertex(sf::Vector2f(x2, y2), c));
		arr.append(sf::Vertex(sf::Vector2f(x2, y1), c));
		arr.append(sf::Vertex(sf::Vector2f(x1, y1), c));
		target.draw(arr);
	}

}//lightlib
