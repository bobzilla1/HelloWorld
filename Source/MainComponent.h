/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
///*
//a car IS A vehicle
//a car IS A modern invention
//a car IS A status symbol
//a car IS A tool
//
//a car HAS A heater
//a car HAS A engine
//a car HAS A air conditioner
//a car HAS A battery
//*/
//
//struct Tool 
//{
//	Tool(const String& purpose_ = "to perform work") : purpose(purpose_) {}
//	String purpose;
//};
//
//struct TemperatureController { int currentTemp = 0; };
//
//struct PowerSupply 
//{ 
//	PowerSupply(int po) : powerOutput(po) {}
//	int powerOutput = 0; 
//};
//
//struct Heater : public TemperatureController {};
//struct Thermostat : public TemperatureController {};
//struct AirConditioner : public TemperatureController {};
//
//struct Engine : public PowerSupply 
//{
//	Engine(int power = 5) : PowerSupply(power) {}
//};
//
//struct Battery : public PowerSupply 
//{
//	Battery(int power = 3) : PowerSupply(power) {}
//};
//
//struct Vehicle : public Tool
//{
//	Vehicle(const String& purpose_, int enginePower, int batteryPower) : 
//		Tool(purpose_),
//		engine(enginePower),
//		battery(batteryPower)
//	{}
//
//	Heater heater;
//	AirConditioner airConditioner;
//	Engine engine;
//	Battery battery;
//};
//
//struct ModernInvention 
//{
//	int yearInvented = 1901;
//};
//
//struct StatusSymbol {};
//
//struct SemiTruck : public Vehicle
//{
//	SemiTruck() : Vehicle("to move cargo", 20, 10) {}
//};
//
//struct Car : public Vehicle, public ModernInvention, public StatusSymbol
//{
//	Car() : Vehicle("to move people", 5, 2) 
//	{
//		yearInvented = 1808;
//		this->ModernInvention::yearInvented = 1808;
//	}
//};
//
//struct MyButton
//{
//	struct Listener
//	{
//		virtual ~Listener(){}
//		virtual void buttonClicked(MyButton*) = 0;
//	};
//
//	Array<Listener*> listeners;
//	void addListener(Listener* listener) { listeners.addIfNotAlreadyThere(listener); }
//	void removeListener(Listener* listener) { listeners.removeFirstMatchingValue(listener); }
//	void click()
//	{
//		for(int i = listeners.size(); --i >= 0; )
//		{
//			listeners[i]->buttonClicked(this);
//		}
//	}
//};
//
//struct WidgetB : public MyButton::Listener
//{
//	MyButton button;
//	void buttonClicked(MyButton* b) override {};
//
//	WidgetB()
//	{
//		button.addListener(this);
//	}
//	~WidgetB()
//	{
//		button.removeListener(this);
//	}
//};
//
//struct Widget { Widget(void*) { } };
//
////struct Bar { virtual ~Bar() { } };
//
////struct Foo : public Bar
////{
////	Widget widgetA;
////	Foo() : widgetA(nullptr) { }
////};
////
////inline void test2()
////{
////	Foo foo;
////}

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
template<typename ButtonType>
struct ButtonWrapper : public Button::Listener
{
	template<typename ... Args>
	ButtonWrapper(std::function<void()> onClickHandler, 
					Args&& ... args ) : 
	onClick(std::move(onClickHandler)),
	button( std::forward<Args>(args) ... )
	{
		button.addListener(this);
	}
	~ButtonWrapper() { button.removeListener(this); }
	void buttonClicked(Button* b) override
	{
		if (onClick)
			onClick();
	}

	//operator Component*() { return &button; }
	operator Component&() { return button; }
	Button* operator->() { return &button; }
private:
	std::function<void()> onClick;
	ButtonType button;
};

template<typename ButtonType>
struct HeapButtonWrapper : public Button::Listener
{
	HeapButtonWrapper(std::function<void()> onClickHandler, 
		std::unique_ptr<ButtonType> heapButton) :
	onClick( std::move( onClickHandler ) ),
	button( std::move(heapButton) )
	{
		setupButton();
	}

	HeapButtonWrapper(std::function<void()> onClickHandler, 
						ButtonType* rawButtonPtr) :
	HeapButtonWrapper(onClickHandler, 
						std::unique_ptr<ButtonType>(rawButtonPtr) )
	{

	}

	~HeapButtonWrapper()
	{ 
		if( button.get() )
		button->removeListener(this); 
	}
	void buttonClicked(Button* b) override
	{
		if (onClick)
			onClick();
	}

	operator Component*()
	{ 
		if ( button.get() != nullptr )
			return button.get();
		return nullptr;
	}
	Button* operator->() { return button.get(); }
private:
	void setupButton()
	{
		jassert(button.get() != nullptr);
		if (button.get())
			button->addListener(this);
	}
	std::function<void()> onClick;
	std::unique_ptr<ButtonType> button;
};


class MainComponent   : public Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
	ButtonWrapper<TextButton> button{ []() { DBG("you clicked the button"); }, "textB" };
	std::unique_ptr<HeapButtonWrapper<TextButton>> heapButton;
    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
