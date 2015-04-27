#include <Data\Mesh.hpp>

//void Mesh::updateInternal()
//{
//	internal.clear();
//	std::list <std::vector<sf::Vertex> > all = makeConvex(accessVertices);
//	for (auto poly : all)
//	{
//		sf::ConvexShape shape;
//		shape.setPointCount(poly.size());
//		for (int vertex = 0; vertex < poly.size(); vertex++)
//		{
//			shape.setPoint(vertex, poly[vertex].position);
//		}
//		internal.push_back(shape);
//	}
//}
std::list<std::vector<sf::Vertex> > Mesh::makeConvex(std::vector<sf::Vertex> _input)
{
	//check for polygon
	if (_input.size() < 2)
	{
		return std::list<std::vector<sf::Vertex> >();
	}

	//retrieve outmost point
	int startingPoint = 0;
	for (int i = 1; i < _input.size(); i++)
	{
		float max = _input[startingPoint].position.x
			+ _input[startingPoint].position.y;
		float cur = _input[i].position.x
			+ _input[i].position.y;
		if (cur > max)
		{
			startingPoint = i;
		}
	}
	//set default curvature
	int polyCurve = curvature(startingPoint);

	//global lists
	std::list<int> conflicting;
	for (int i = 0; i < _input.size(); i++)
	{
		if (curvature(i) != polyCurve)
		{
			conflicting.push_back(i);
			break;
		}
	}

	for (auto it : conflicting)
	{
		int currentChoice;
		int choiceRating = 6;
		for (int i = 0; i < _input.size(); i++)
		{
			int weight = 5;
			if (curvature(i) != polyCurve)
			{
				weight--;
			}
			if (curvature(prev(it), it, i) == polyCurve)
			{
				weight--;
			}
			if (curvature(i, it, next(it)) == polyCurve)
			{
				weight--;
			}
			if (curvature(prev(i), i, it) == polyCurve)
			{
				weight--;
			}
			if (curvature(it, i, next(i)) == polyCurve)
			{
				weight--;
			}
			if (weight < choiceRating)
			{
				//check possible
				bool possible = true;
				for (int hull = 0; hull < _input.size(); hull++)
				{
					if (intersect(it, i, hull, next(hull)))
					{
						possible = false;
						break;
					}
				}
				if (possible)
				{
					currentChoice = i;
					choiceRating = weight;
					if (!weight)
						break;
				}
			}
		}
		//make split
		std::list<std::vector<sf::Vertex> > output;

		std::vector<sf::Vertex> first;
		for (int start = it; start != currentChoice; first.push_back(_input[start = next(start)])){}
		for (auto half : makeConvex(first))
		{
			output.push_back(half);
		}

		std::vector<sf::Vertex> second;
		for (int start = currentChoice; start != it; first.push_back(_input[start = next(start)])){}
		for (auto half : makeConvex(second))
		{
			output.push_back(half);
		}

		return output;
	}
	std::list<std::vector<sf::Vertex> > output;
	output.push_back(_input);
	return output;
}
bool Mesh::intersect(int a1, int a2, int b1, int b2)
{
	int o1 = curvature(a1, a2, b1);
	int o2 = curvature(a1, a2, b2);
	int o3 = curvature(b1, b2, a1);
	int o4 = curvature(b1, b2, a2);

	if (o1*o2*o3*o4)
		return false;

	if (o1 != o2 && o3 != o4)
		return true;

	return false;
}
sf::Vector2f Mesh::intersect(sf::Vector2f a1, sf::Vector2f a2, sf::Vector2f b1, sf::Vector2f b2)
{
	float x1 = a1.x;
	float x2 = a2.x;
	float x3 = b1.x;
	float x4 = b2.x;
	float y1 = a1.y;
	float y2 = a2.y;
	float y3 = b1.y;
	float y4 = b2.y;
	sf::Vector2f result;
	
	float denominator = ((x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4));
	if (!denominator)
	{
		EXP::log("[Error]Deviding by ZERO(Line intersection test)");
		return sf::Vector2f(13, 37);
	}
	float prenominator = (x1*y2 - y1*x2);
	float postnominator = (x3*y4 - y3*x4);
	result.x = (prenominator*(x3 - x4) - (x1 - x2)*postnominator) / denominator;
	result.y = (prenominator*(y3 - y4) - (y1 - y2)*postnominator) / denominator;
	return result;
}
int Mesh::ccw(sf::Vector2f _a, sf::Vector2f _b, sf::Vector2f _c)
{
	int val = (_b.y - _a.y) * (_c.x - _b.x) -
		      (_b.x - _a.x) * (_c.y - _b.y);

	if (val == 0) return 0;
	return (val > 0) ? 1 : 2;
}
int Mesh::curvature(int _index)
{
	int prev = Mesh::prev(_index);
	int cur = _index;
	int next = Mesh::next(_index);
	return (ccw(accessVertices[prev].position, accessVertices[cur].position, accessVertices[next].position));
}
int Mesh::curvature(int _a, int _b, int _c)
{
	int prev = _a;
	int cur = _b;
	int next = _c;
	return (ccw(accessVertices[prev].position, accessVertices[cur].position, accessVertices[next].position));
}
int Mesh::prev(int _index)
{
	return ((accessVertices.size() - 1) + _index) % accessVertices.size();
}
int Mesh::next(int _index)
{
	return (_index + 1) % accessVertices.size();
}

Mesh::Mesh()
{
	EXP::log("Mesh has been constructed");
}
Mesh::~Mesh()
{
	EXP::log("Mesh has been destructed");
}

void Mesh::clear()
{
	accessVertices.clear();
	internal.clear();
}
//void Mesh::addVertex(sf::Vertex _vertex)
//{
//	accessVertices.push_back(_vertex);
//	updateInternal();
//}
//void Mesh::addVertex(int _pos, sf::Vertex _vertex)
//{
//	std::vector<sf::Vertex>::iterator it = accessVertices.begin();
//	for (; _pos > 0; it++, _pos--);
//	accessVertices.insert(it, _vertex);
//	updateInternal();
//}
//void Mesh::removeVertex(int _pos)
//{
//	std::vector<sf::Vertex>::iterator it = accessVertices.begin();
//	for (; _pos > 0; it++, _pos--);
//	accessVertices.erase(it);
//	updateInternal();
//}
//void Mesh::setVertex(int _pos, sf::Vertex _vertex)
//{
//	accessVertices[_pos] = _vertex;
//	updateInternal();
//}
//sf::Vertex Mesh::getVertex(int _pos)
//{
//	return accessVertices[_pos];
//}
//void Mesh::setVertices(std::vector<sf::Vertex> _vertices)
//{
//	accessVertices = _vertices;
//	updateInternal();
//}
//std::vector<sf::Vertex> Mesh::getVertices()
//{
//	return accessVertices;
//}
//
//sf::Vector2f Mesh::overlap(Mesh* _other)
//{
//	std::list<sf::Vector2f> centroids;
//	for (int a = 0; a < this->internal.size(); a++)
//	{
//		sf::ConvexShape& shapeA = this->internal[a];
//		for (int b = 0; b < _other->internal.size(); b++)
//		{
//			sf::ConvexShape& shapeB = _other->internal[b];
//			//WORK
//		}
//	}
//}
//
//void Mesh::draw(sf::RenderTarget* _target, sf::Color _color)
//{
//	for (auto it : internal)
//	{
//		it.setOutlineThickness(1.0f);
//		it.setOutlineColor(_color);
//		it.setFillColor(_color*sf::Color(255, 255, 255, 128));
//		_target->draw(it);
//	}
//}