/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

struct Widget : public Component
{
	Widget(int i) : num(i) {}
	void paint(Graphics& g) override
	{
		g.fillAll(Colours::red);
		g.setColour(Colours::black);
		g.drawRect(getLocalBounds().reduced(2));

		//feel free to experiment with that text placement
		g.drawFittedText(String(num), 
			getLocalBounds(),
			Justification::centred, 
			1);  
	}
	int num = 0;
};

struct OwnedArrayComponent : Component
{
	OwnedArrayComponent()
	{
		for ( int i = 0; i < 10; ++i )
		{
			auto* widget = widgets.add( new Widget(i) );
			addAndMakeVisible(widget);
		}
	}

	void resized() override
	{
		//We are going to divide our window size by the number of widgets that we have.
		//We'll make widget.size a float incase we have a weird size that's not a division of 10.  
		//That's going to force our width size to be a float.
		auto width = getWidth() / static_cast<float>(widgets.size());
		int x = 0;  //x is going to be where these guys go
		auto h = getHeight();

		//This is going to iterate through each of our widgets in the OwnedArray.
		//A range based for loop is the equivalent of this, it would look like this:
		//	for (int i = 0; i < widgets.size(); ++i)
		//	{
		//		auto* widget = widgets[i];
		//	}
		for (auto* widget : widgets)
		{
			widget->setBounds(x, 0, width, h);
			x += width;
		}
	}

	OwnedArray<Widget> widgets;

};

struct MyComp : Component
{
	void resized() override { }
	void paint(Graphics& g) override 
		{ g.fillAll(Colours::green); }

	void mouseEnter(const MouseEvent& e) override 
	{
		DBG( "MyComp mouseEnter" << counter);
		++counter;
	}
	void mouseExit(const MouseEvent& e) override
	{
		DBG( "MyComp mouseExit" << counter);
		++counter;
	}
	void mouseMove(const MouseEvent& e) override
	{
		DBG("MyComp mouseMove" << counter);
		++counter;
	}
private:
	int counter = 0;
};

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	void mouseEnter(const MouseEvent& e) override 
	{
		DBG( "MainComponent mouseEnter " << counter );
		++counter;
	}
	void mouseExit(const MouseEvent& e) override
	{
		DBG( "MainComponent mouseExit " << counter );
		++counter;
	}
	void mouseMove(const MouseEvent& e) override
	{
		DBG("MainComponent mouseMove " << counter );
		++counter;
	}
private:
	int counter = 0;
	MyComp comp;
	OwnedArrayComponent ownedArrayComp;
    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
