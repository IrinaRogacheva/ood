#include "Beverages.h"
#include "Condiments.h"

#include <iostream>
#include <string>
#include <functional>

using namespace std;

struct MakeLemon
{
	MakeLemon(unsigned quantity)
		:m_quantity(quantity)
	{}

	auto operator()(IBeveragePtr && beverage)const
	{
		return make_unique<CLemon>(move(beverage), m_quantity); 
	}
private:
	unsigned m_quantity;
};

function<IBeveragePtr(IBeveragePtr &&)> MakeCinnamon()
{
	return [] (IBeveragePtr && b) {
		return make_unique<CCinnamon>(move(b));
	};
}

template <typename Condiment, typename... Args>
auto MakeCondiment(const Args&...args)
{
	return [=](auto && b) {
		return make_unique<Condiment>(forward<decltype(b)>(b), args...);
	};
}

template <typename Component, typename Decorator>
auto operator << (Component && component, const Decorator & decorate)
{
	return decorate(forward<Component>(component));
}

void DialogWithUser()
{
	cout << "Type 1 for coffee or 2 for tea\n";
	int beverageChoice;
	cin >> beverageChoice;

	unique_ptr<IBeverage> beverage;

	if (beverageChoice == 1)
	{
		beverage = make_unique<CCoffee>();
	}
	else if (beverageChoice == 2)
	{
		beverage = make_unique<CTea>();
	}
	else
	{
		return;
	}

	int condimentChoice;
	for (;;)
	{
		cout << "1 - Lemon, 2 - Cinnamon, 0 - Checkout" << endl;
		cin >> condimentChoice;

		if (condimentChoice == 1)
		{
			beverage = move(beverage) << MakeCondiment<CLemon>(2);
		}
		else if (condimentChoice == 2)
		{
			beverage = move(beverage) << MakeCondiment<CCinnamon>();
		}
		else if (condimentChoice == 0)
		{
			break;
		}
		else
		{
			return;
		}
	}

	cout << beverage->GetDescription() << ", cost: " << beverage->GetCost() << endl;
}

int main()
{
	auto latte = make_unique<CLatte>(CoffeeServingSize::Double);
	auto cinnamon = make_unique<CCinnamon>(move(latte));
	auto lemon = make_unique<CLemon>(move(cinnamon), 2);
	auto iceCubes = make_unique<CIceCubes>(move(lemon), 2, IceCubeType::Dry);
	auto cream = make_unique<CCream>(move(iceCubes));
	auto chocolate = make_unique<CChocolate>(move(cream), 6);
	auto liquor = make_unique<CLiquor>(move(chocolate), LiquorType::Nutty);
	auto beverage = make_unique<CChocolateCrumbs>(move(liquor), 2);

	auto cappuccino = make_unique<CCappuccino>(CoffeeServingSize::Double);

	auto tea = make_unique<CTea>(KindOfTea::Assam);

	auto milkshake = make_unique<CMilkshake>(MilkshakeServingSize::Small);

	cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	cout << cappuccino->GetDescription() << " costs " << cappuccino->GetCost() << endl;
	cout << tea->GetDescription() << " costs " << tea->GetCost() << endl;
	cout << milkshake->GetDescription() << " costs " << milkshake->GetCost() << endl;
}
