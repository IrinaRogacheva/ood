#pragma once
#include "ILineStyleEnumerator.h"
#include "IShape.h"

class CLineStyleEnumerator : public ILineStyleEnumerator
{
public:
	CLineStyleEnumerator(std::vector<std::shared_ptr<IShape>>& shapes);
	void EnumerateAll(Callback& callback) const override;
private:
	std::vector<std::shared_ptr<IShape>>& m_shapes;
};