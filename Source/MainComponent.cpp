/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

template<class ButtonType>
auto makeButton(ButtonType* buttonToMakeUnique) -> std::unique_ptr<ButtonType>
{
	return std::unique_ptr<ButtonType>(buttonToMakeUnique);
}

//==============================================================================
MainComponent::MainComponent()
{
	heapButton.reset(new HeapButtonWrapper<TextButton>([]() { DBG("you clicked the heap"); },
														new TextButton("heapButton") 
														)
					);
	
	addAndMakeVisible(button);

	addAndMakeVisible( (*heapButton) );
	setSize(600, 400);
}

MainComponent::~MainComponent()
{
}

//struct Bar
//{
//	Bar() { doSomething(); }
//	Bar(int i_, float f_) : i(i_), f(f_) { doSomething(); }
//	Bar(const String& str_) : str(str_) { doSomething(); }
//
//	void doSomething() { DBG("i: " << i << " f: " << f << " str: " << str); }
//
//	int i{ 0 };
//	float f{ 0.f };
//	String str;
//};
//
//void barTest()
//{
//	Bar bar1;
//	Bar bar2(3, 4.5f);
//	Bar bar3("bar 3");
//}




//struct base
//{
//	base() { DBG("base ctor"); }
//	~base() { DBG("base dtor"); }
//};
//
//struct member
//{
//	member() { DBG("member ctor"); }
//	~member() { DBG("member dtor"); }
//};
//
//struct derived : base
//{
//	derived() { DBG("derived ctor"); }
//	~derived() { DBG("derived dtor"); }
//	member m;
//};

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setFont (Font (16.0f));
    g.setColour (Colours::red);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
	button->setBounds(498, 
						0,
						100, 30);
	(*heapButton)->setBounds(498, 
								368,
								100, 30);
}
