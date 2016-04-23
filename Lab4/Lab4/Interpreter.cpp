#include "Interpreter.h"

using namespace std;

void CInterpreter::CreateShape(std::string const & name)
{
	if (name == "cone")
	{
		shapes.push_back(make_shared<CBody *>(new CCone(GetDensity(), GetRadius(), GetHeight())));
	}
	else if (name == "cylinder")
	{
		shapes.push_back(make_shared<CBody *>(new CCylinder(GetDensity(), GetRadius(), GetHeight())));
	}
	else if (name == "sphere")
	{
		shapes.push_back(make_shared<CBody *>(new CSphere(GetDensity(), GetRadius())));
	}
	else if (name == "parallelepiped")
	{
		shapes.push_back(make_shared<CBody *>(new CParallelepiped(GetDensity(), GetHeight(), GetWidth(), GetDepth())));
	}
	else
	{
		cerr << "Unknown type of shape" << endl;
	}
}

double CInterpreter::GetRadius()
{
	double radius;
	cout << "radius = ";
	cin >> radius;
	return radius;
}

double CInterpreter::GetHeight()
{
	double height;
	cout << "height = ";
	cin >> height;
	return height;
}

double CInterpreter::GetDensity()
{
	double density;
	cout << "density = ";
	cin >> density;
	return density;
}

double CInterpreter::GetDepth()
{
	double depth;
	cout << "depth = ";
	cin >> depth;
	return depth;
}

double CInterpreter::GetWidth()
{
	double width;
	cout << "width = ";
	cin >> width;
	return width;
}

void CInterpreter::DisplaySummaryInfo()
{
	CBody *figureWithMaxMass = nullptr;
	CBody *lightFigure = nullptr;
	double maxMass = 0;
	double minWeight = std::numeric_limits<double>::infinity();
	for (auto it : shapes)
	{
		auto *shape = *it.get();
		if (maxMass < shape->GetMass())
		{
			maxMass = shape->GetMass();
			figureWithMaxMass = shape;
		}
		double weight = (shape->GetDensity() - 1000) * 10 * shape->GetVolume();
		if (minWeight > weight)
		{
			minWeight = weight;
			lightFigure = shape;
		}
	}
	if (figureWithMaxMass)
	{
		cout << "A figure which has the highest weight:\n" << figureWithMaxMass->ToString() << endl;
	}
	if (lightFigure)
	{
		// TODO: написать по другому
		cout << "A figure which can easily weigh in water:\n" << lightFigure->ToString() << endl;
	}
}
