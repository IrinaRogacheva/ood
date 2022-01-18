#pragma once
#include "IFillStyleEnumerator.h"
#include "IShape.h"

class CFillStyleEnumerator : public IFillStyleEnumerator
{
public:
	CFillStyleEnumerator(std::vector<std::shared_ptr<IShape>>& shapes);
	void EnumerateAll(Callback& callback) const override;
private:
	std::vector<std::shared_ptr<IShape>>& m_shapes;
};