#pragma once

#include "IBeverage.h"

class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string & description)
		:m_description(description)
	{}

	std::string GetDescription()const override final
	{
		return m_description;
	}
protected:
	std::string m_description;
};

enum class CoffeeServingSize
{
	Standard,
	Double,
};

class CCoffee : public CBeverage
{
public:
	CCoffee(CoffeeServingSize size = CoffeeServingSize::Standard, const std::string& description = " coffee")
		: CBeverage(description)
		, m_servingSize(size)
	{
		m_description = (size == CoffeeServingSize::Standard ? "Standard" : "Double") + description;
	}

	double GetCost() const override 
	{
		return 60; 
	}
private:
	CoffeeServingSize m_servingSize;
};

class CCappuccino : public CCoffee
{
public:
	CCappuccino(CoffeeServingSize servingSize = CoffeeServingSize::Standard, const std::string& description = " cappuccino")
		:CCoffee(servingSize, description)
		, m_servingSize(servingSize)
	{}

	double GetCost() const override 
	{
		return (m_servingSize == CoffeeServingSize::Standard ? 80 : 120);
	}
private:
	CoffeeServingSize m_servingSize;
};

class CLatte : public CCoffee
{
public:
	CLatte(CoffeeServingSize servingSize = CoffeeServingSize::Standard, const std::string& description = " latte")
		:CCoffee(servingSize, description)
		, m_servingSize(servingSize)
	{}

	double GetCost() const override 
	{
		return (m_servingSize == CoffeeServingSize::Standard ? 90 : 130);
	}
private:
	CoffeeServingSize m_servingSize;
};

enum class KindOfTea
{
	Black,
	Green,
	White,
	Assam,
};

class CTea : public CBeverage
{
public:
	CTea(KindOfTea kindOfTea = KindOfTea::Black, const std::string& description = " tea")
		:CBeverage(description)
	{
		switch (kindOfTea)
		{
		case KindOfTea::Black:
			m_description = "Black";
			break;
		case KindOfTea::Green:
			m_description = "Green";
			break;
		case KindOfTea::White:
			m_description = "White";
			break;
		case KindOfTea::Assam:
			m_description = "Assam";
			break;
		}
		m_description += description;
	}

	double GetCost() const override 
	{
		return 30; 
	}
};

enum class MilkshakeServingSize
{
	Small,
	Medium,
	Big,
};

class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakeServingSize servingSize = MilkshakeServingSize::Big, const std::string& description = " milkshake")
		:CBeverage(description)
		, m_servingSize(servingSize)
	{
		m_description = (servingSize == MilkshakeServingSize::Small ? "Small" : (servingSize == MilkshakeServingSize::Medium ? "Medium" : "Big")) + description;
	}

	double GetCost() const override 
	{ 
		return (m_servingSize == MilkshakeServingSize::Small ? 50 : (m_servingSize == MilkshakeServingSize::Medium ? 60 : 80));
	}
private:
	MilkshakeServingSize m_servingSize;
};
