#include <SFML/Graphics.hpp>
#include <vector>
#include <cstddef>

template< typename P, typename T>
void draw_triangle(P& canvas,T first_vertex, T second_vertex, T third_vertex)
{
	sf::Vertex fs[] = { first_vertex,second_vertex };//line between first and second vertex
	sf::Vertex ft[] = { first_vertex, third_vertex };//...first third
	sf::Vertex st[] = { second_vertex,third_vertex };//...second third
	
	canvas.draw(fs, 2, sf::Lines);
	canvas.draw(ft, 2, sf::Lines);
	canvas.draw(st, 2, sf::Lines);
}

template <typename T, typename Container>
void generate_triangle(T & triangle, Container & c_triangles)
{
	sf::Vertex f_vertex = sf::Vector2f((triangle[0].position.x + triangle[2].position.x) / 2, (triangle[0].position.y + triangle[2].position.y) / 2);
	sf::Vertex s_vertex = sf::Vector2f((triangle[0].position.x + triangle[1].position.x) / 2 ,(triangle[0].position.y + triangle[1].position.y) / 2) ;
	sf::Vertex t_vertex =sf::Vector2f ((triangle[1].position.x + triangle[2].position.x) / 2 ,(triangle[1].position.y + triangle[2].position.y) / 2) ;

	std::vector<sf::Vertex> f_triangle = { f_vertex,s_vertex,triangle[0] };
	std::vector<sf::Vertex> s_triangle = { f_vertex,t_vertex,triangle[2] };
	std::vector<sf::Vertex> t_triangle = { s_vertex,t_vertex,triangle[1] };
	
	c_triangles.push_back(f_triangle);
	c_triangles.push_back(s_triangle);
	c_triangles.push_back(t_triangle);
}

std::size_t power_three(std::size_t n)
{
	std::size_t score = 1;
	for (std::size_t i = 0; i < n; i++)
	{
		score *= 3;
	}
	return score;
}
std::size_t sum_of_pow_three(std::size_t n)
{
	std::size_t result = 0;
	for (std::size_t i = 0; i < n; i++)
	{
		result += power_three(i);
	}
	return result;
}
int main()
{
	const std::size_t window_width = 900;
	const std::size_t window_height = 900;
	std::size_t fractal_deepth = 9;

	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Sierpinski triangle!");

	std::vector<sf::Vertex> first_triangle = {  sf::Vector2f(window_width , window_height),sf::Vector2f(window_width / 2, 0.f), sf::Vector2f(0.f, window_height) };

	std::vector<std::vector<sf::Vertex>> triangles;
	triangles.push_back(first_triangle);

	for (std::size_t i = 0; i < sum_of_pow_three(fractal_deepth); i++)
	{
		generate_triangle(triangles[i], triangles);
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		for (std::size_t j = 0; j < triangles.size(); j++)
		{
			draw_triangle(window, triangles[j][0], triangles[j][1], triangles[j][2]);
		}
		window.display();
	}

	return 0;
}