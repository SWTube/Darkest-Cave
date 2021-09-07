module;

#include "GraphicsApiPch.h"
#include "Containers/Vertex.h"

export module Line;
import Renderable;

namespace cave
{
	class Line : public Renderable
	{
	public:
		Line() = delete;
		Line(Float2 point1, Float2 point2, float stroke);
		~Line();

	protected:
		void update();
		void creatRenderCommand();
		void makeRenderCommand();

	private:
		Float2 mPoint1;
		Float2 mPoint2;
		float mStroke;

	};
	Line::Line(Float2 point1, Float2 point2, float stroke)
		:mPoint1(point1),
		mPoint2(point2),
		mStroke(stroke)
	{	
	}
	Line::~Line()
	{

	}

	void Line::update()
	{
	}
	void Line::creatRenderCommand()
	{

	}
	void Line::makeRenderCommand()
	{
	}
}
