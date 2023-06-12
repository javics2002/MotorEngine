#include "UIText.h"
#include "Render/RenderUIText.h"
#include "EntityComponent/Entity.h"
#include "UITransform.h"

using namespace me;

Component* me::FactoryUIText::create(Parameters& params)
{
    if (params.empty())
    {
        return new UIText();
    }
    std::string name = Value(params, "name", std::string());
    std::string text = Value(params, "text", std::string());
    std::string fontName = Value(params, "fontname", std::string());
    Vector3 colour = Vector3(Value(params, "colour_x", 1.0f), Value(params, "colour_y", 1.0f), Value(params, "colour_z", 1.0f));
    Vector3 colourBottom = Vector3(Value(params, "colourbottom_x", 1.0f), Value(params, "colourbottom_y", 1.0f), Value(params, "colourbottom_z", 1.0f));
    Vector3 colourTop = Vector3(Value(params, "colourtop_x", 1.0f), Value(params, "colourtop_y", 1.0f), Value(params, "colourtop_z", 1.0f));
    Vector2 position = Vector2(Value(params, "position_x", 1.0f), Value(params, "position_y", 1.0f));
    Vector2 dimension = Vector2(Value(params, "dimension_x", 1.0f), Value(params, "dimension_y", 1.0f));
    int zOrder = Value(params, "zorder", 1);
    float charHeight = Value(params, "charheight", 0.1f);

    UIText* textRenderer = new UIText();
    textRenderer->setTextInfo(name, text, zOrder, fontName);
    textRenderer->setPosition(position.x, position.y);
    textRenderer->setSize(dimension.x, dimension.y);
    textRenderer->setCharHeight(charHeight);
    if (params.count("colourbottom_x")) {
        textRenderer->setColourTop(colourTop);
        textRenderer->setColourBottom(colourBottom);
    }
    else textRenderer->setColour(colour);

    textRenderer->setText(text);

    return textRenderer;
}

void me::FactoryUIText::destroy(Component* component)
{
    delete component;
}

UIText::UIText() : Component()
{
}

UIText::~UIText()
{
	delete mRenderUIText;
}

bool UIText::setTextInfo(std::string name, std::string text, int zOrder, std::string fontName)
{
	mName = name;
	mZOrder = zOrder;

	if (text.size() > 0) {
		mRenderUIText = new RenderUIText(mName, text, zOrder, fontName);
		return true;
	}

	return false;
 }

void UIText::start()
{
	mUITransform = getEntity()->getComponent<UITransform>("uitransform");
}

void UIText::setPosition(float x, float y)
{
	mRenderUIText->setPosition(Vector2( x,y ));
	
}

void UIText::setSize(float w, float h)
{
	mRenderUIText->setDimensions(Vector2( w,h ));
	
}

void UIText::setFont(std::string fontName)
{
	mRenderUIText->setFont(fontName);
	
}

void UIText::setText(std::string text)
{
	mRenderUIText->setText(text);
	
}

void UIText::setColour(Vector3 newColor)
{
	mRenderUIText->setColour(newColor);
	
}

void me::UIText::setColourBottom(Vector3 newColor)
{
	mRenderUIText->setColourBottom(newColor);
}

void me::UIText::setColourTop(Vector3 newColor)
{
	mRenderUIText->setColourTop(newColor);
}

void UIText::setCharHeight(double heightValue)
{
	mRenderUIText->setCharHeight(heightValue);
	
}

void UIText::setActive(bool active)
{
	// Show or hide the text area 
	mRenderUIText->setActive(active);
}

