#include <SFML/Graphics.hpp>
#include <vector>
#include <cstddef>

using namespace sf;

template< typename P, typename T>
void drawTriangle(P& canvas,T first_vertex, T second_vertex, T third_vertex)
{
	Vertex fs[] = { first_vertex,second_vertex };//line between first and second vertex
	Vertex ft[] = { first_vertex, third_vertex };//...first third
	Vertex st[] = { second_vertex,third_vertex };//...second third
	
	canvas.draw(fs, 2, sf::Lines);
	canvas.draw(ft, 2, sf::Lines);
	canvas.draw(st, 2, sf::Lines);
}

template <typename T, typename Container, typename W>
void generateTriangle(T & triangle,Container & trojkaty, W & canvas)
{
	Vertex pierwszy = Vector2f((triangle[0].position.x + triangle[2].position.x) / 2, (triangle[0].position.y + triangle[2].position.y) / 2);
	Vertex drugi = Vector2f((triangle[0].position.x + triangle[1].position.x) / 2 ,(triangle[0].position.y + triangle[1].position.y) / 2) ;
	Vertex trzeci =Vector2f ((triangle[1].position.x + triangle[2].position.x) / 2 ,(triangle[1].position.y + triangle[2].position.y) / 2) ;

	std::vector<Vertex> trojk = { pierwszy,drugi,triangle[0] };
	std::vector<Vertex> trojk1 = { pierwszy,trzeci,triangle[2] };
	std::vector<Vertex> trojk2 = { drugi,trzeci,triangle[1] };
	
	trojkaty.push_back(trojk);
	trojkaty.push_back(trojk1);
	trojkaty.push_back(trojk2);
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
	const int window_width = 1240;
	const int window_height = 800;
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Sierpinski triangle!");

	std::vector<Vertex> first_triangle = {  Vector2f(window_width , window_height),Vector2f(window_width / 2, 0.f), Vector2f(0.f, window_height) };

	std::vector<std::vector<Vertex>> triangles;
	triangles.push_back(first_triangle);

	std::size_t deepth = sum_of_pow_three(8);
	for (std::size_t i = 0; i < deepth; i++)
	{
		generateTriangle(triangles[i], triangles, window);
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
			drawTriangle(window, triangles[j][0], triangles[j][1], triangles[j][2]);
		}
		window.display();
	}
	return 0;
}