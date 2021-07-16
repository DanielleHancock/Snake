// taken from https://www.sfml-dev.org/tutorials/2.0/graphics-shape.php

#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class EllipseShape : public sf::Shape
{
public:

    explicit EllipseShape(const sf::Vector2f& diameter = sf::Vector2f(0, 0))
    {
        m_radius = sf::Vector2f(diameter.x / 2.0, diameter.y / 2.0);
        update();
    }

    void setRadius(const sf::Vector2f& radius)
    {
        m_radius = radius;
        update();
    }

    const sf::Vector2f& getRadius() const
    {
        return m_radius;
    }

    virtual unsigned int getPointCount() const
    {
        return 30; // fixed, but could be an attribute of the class if needed
    }

    virtual sf::Vector2f getPoint(unsigned int index) const
    {
        static const float pi = 3.141592654f;

        float angle = index * 2 * pi / getPointCount() - pi / 2;
        float x = std::cos(angle) * m_radius.x;
        float y = std::sin(angle) * m_radius.y;

        return sf::Vector2f(m_radius.x + x, m_radius.y + y);
    }

private:

    sf::Vector2f m_radius;
};
