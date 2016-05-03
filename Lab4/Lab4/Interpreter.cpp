#include "Interpreter.h"

using namespace std;


std::shared_ptr<CBody> CBodyFactory::CreateBody(std::string const & name)
{
	std::shared_ptr<CBody> body;
	if (name == "cone")
	{
		body = make_shared<CCone>(CCone(GetData("density"), GetData("radius"), GetData("height")));
	}
	else if (name == "cylinder")
	{
		body = make_shared<CCylinder>(CCylinder(GetData("density"), GetData("radius"), GetData("height")));
	}
	else if (name == "sphere")
	{
		body = make_shared<CSphere>(CSphere(GetData("density"), GetData("radius")));
	}
	else if (name == "parallelepiped")
	{
		body = make_shared<CParallelepiped>(CParallelepiped(GetData("density"), GetData("height"), GetData("width"), GetData("depth")));
	}
	else if (name == "compound")
	{
		++nestingLevel;
		body = make_shared<CCompound>(CreateCompound());
	}
	else
	{
		throw::invalid_argument("Unknown type of shape");
	}
	return body;
}

CCompound CBodyFactory::CreateCompound()
{
	CCompound compound;
	string name;
	for (;;)
	{
		std::cout << "In compound " << nestingLevel << " > ";
		cin >> name;
		if (name == "exit")
		{
			break;
		}
		compound.AppendShape(CreateBody(name));
	}
	--nestingLevel;
	return compound;
}

double CBodyFactory::GetData(std::string const & type)
{
	double data;
	cout << type + "= ";
	cin >> data;
	return data;
}



void CInterpreter::SetBody(std::string const & name)
{
	bodies.push_back(m_bodyFactory.CreateBody(name));
}

void CInterpreter::DisplaySummaryInfo()
{
	CBody *figureWithMaxMass = nullptr;
	CBody *lightFigure = nullptr;
	double maxMass = 0;
	double minWeight = std::numeric_limits<double>::infinity();
	for (auto it : bodies)
	{
		auto shape = it.get();
		if (maxMass < shape->GetMass())
		{
			maxMass = shape->GetMass();
			figureWithMaxMass = shape;
		}
		double weight = abs((shape->GetDensity() - 1000)) * 10 * shape->GetVolume();
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

