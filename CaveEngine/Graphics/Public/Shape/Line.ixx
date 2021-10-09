module;

#include <cmath>
#include "GraphicsApiPch.h"

#include "CoreGlobals.h"


export module cave.Graphics.Shape.Line;
import cave.Core.Types.Float;
import cave.Core.Types.Vertex;
import Sprite;
import TextureManager;

namespace cave
{
	export class Line : public Sprite
	{
	public:
		Line() = delete;
		Line(Float2 point1, Float2 point2, uint16_t stroke);
		~Line();

	protected:
		void update();
		//void creatRenderCommand();
		//void makeRenderCommand();

	private:
		Float2 mPoint1;
		Float2 mPoint2;
		uint16_t mStroke;

	};
	
	Line::Line(Float2 point1, Float2 point2, uint16_t stroke)
		:Sprite(),
		mPoint1(point1),
		mPoint2(point2),
		mStroke(stroke)
	{	
		Float2 dis = { mPoint1.X - mPoint2.X,mPoint1.Y - mPoint2.Y };
		mWidth = sqrt(pow(dis.X, 2) +  pow(dis.Y,2));
		mHeight = mStroke;
		mPosition = { (mPoint1.X + mPoint2.X) / 2 ,(mPoint1.Y + mPoint2.Y) / 2,0 };
		mTexture = TextureManager::GetInstance().GetDefaultTexture();
		mAngle = atan2(dis.Y, dis.X) * 57.2958f;
	}

	Line::~Line()
	{

	}

	void Line::update()
	{

	}

}
