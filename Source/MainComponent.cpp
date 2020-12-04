/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

OwnedArrayComponent::OwnedArrayComponent()
{
	for (int i = 0; i < 10; ++i)
	{
		auto* widget = buttons.add( new TextButton(String(i)));
		addAndMakeVisible(widget);
		widget->addListener(this);
	}
}

OwnedArrayComponent::~OwnedArrayComponent()
{
	for (auto* widget : buttons)
	{
		widget->removeListener(this);
	}
}

void OwnedArrayComponent::resized()
{
	auto width = getWidth() / static_cast<float>(buttons.size());
	int x = 0;
	auto h = getHeight();
	for (auto* widget : buttons)
	{
		widget->setBounds(x, 0, width, h);
		x += width;
	}
}

void OwnedArrayComponent::buttonClicked(Button *buttonThatWasClicked)
{
	if (buttonThatWasClicked == buttons.getFirst())
	{
		DBG("you clicked the first button");
	}
	else if (buttonThatWasClicked == buttons.getLast())
	{
		DBG("you clicked the last button");
	}
	else
	{
		DBG("you clicked some other button");
	}
}

//==============================================================================
MainComponent::MainComponent()
{
	addAndMakeVisible(comp);
	//comp.addMouseListener(this, false);

	addAndMakeVisible(ownedArrayComp);
	ownedArrayComp.addMouseListener(this, true);
	
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
	comp.removeMouseListener(this);
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

	comp.setBounds(30, 30, 100, 100);

	// Here is where we get it positioned
	// However big our MainComponent is, we will go from the right edge to 
	// where our set bounds exists, and we'll make this first start at the bottom.
	// And we want the width from our component's left edge to the rest of it.
	ownedArrayComp.setBounds(comp.getX(),
							comp.getBottom() + 5,
							getWidth() - comp.getX(),
							getHeight() - comp.getBottom());

}
