/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================

ImageProcessingThread::ImageProcessingThread(int w_, int h_) : 
	Thread("ImageProcessingThread"), w(w_), h(h_)
{
	startThread();
}
ImageProcessingThread::~ImageProcessingThread()
{
	stopThread(500);
}
void ImageProcessingThread::run()
{
	while (true)
	{
		if (threadShouldExit())
			break;

		auto canvas = Image(Image::PixelFormat::RGB, w, h, true);

		if (threadShouldExit())
			break;

		DBG("[ImageProcessingThread] generating random image " << Time::getCurrentTime().toISO8601(true) );

		bool shouldBail = false;
		for (int x = 0; x < w; ++x)
		{
			if (threadShouldExit())
			{
				shouldBail = true;
				break;
			}

			for (int y = 0; y < h; ++y)
			{
				canvas.setPixelAt(x,
					y,
					Colour(r.nextFloat(),
						r.nextFloat(),
						r.nextFloat(),
						1.f));
			}
		}

		if (threadShouldExit() || shouldBail)  //this will kick us out of the while loop
			break;

		if (updateRenderer)  //checking to make sure not null pointer
			updateRenderer(std::move(canvas));  //o move image from  background thread to GUI thread

		wait(-1);
	}
}
void ImageProcessingThread::setUpdateRendererFunc(std::function<void(Image&&)> f) 
{ 
	updateRenderer = std::move(f); 
}

//==============================================================================

LambdaTimer::LambdaTimer(int ms, std::function<void()> f) : lambda(std::move(f))
{
	startTimer(ms);
}

LambdaTimer::~LambdaTimer()
{
	stopTimer();
}

void LambdaTimer::timerCallback()
{
	stopTimer();
	if (lambda)
		lambda();
}

//==============================================================================

Renderer::Renderer()
{
	lambdaTimer = std::make_unique<LambdaTimer>(10, [this]()
		{
			processingThread = std::make_unique<ImageProcessingThread>(getWidth(),
																		getHeight());
			processingThread->setUpdateRendererFunc([this](Image&& image)
			{
				int renderIndex = firstImage ? 0 : 1;
				firstImage = !firstImage;
				imageToRender[renderIndex] = std::move(image);

				triggerAsyncUpdate();

				lambdaTimer = std::make_unique<LambdaTimer>(1000, [this]()
					{
						processingThread->notify();
					});
			});
		});
}
Renderer::~Renderer()
{
	processingThread.reset();
	lambdaTimer.reset();
}
void Renderer::paint(Graphics& g)
{
	DBG("[Renderer] painting: " << Time::getCurrentTime().toISO8601(true) << "\n");
	g.drawImage(firstImage ? imageToRender[0] : imageToRender[1],
		getLocalBounds().toFloat());
}

void Renderer::handleAsyncUpdate()
{
	repaint();
}

//==============================================================================

DualButton::DualButton()
{
	addAndMakeVisible(button1);
	addAndMakeVisible(button2);

	/*
	button1.onClick = [this]()
	{
		DBG("Button1's size: " << this->button1.getBounds().toString());
		timerThing.startTimerHz(2);  //This one is 2 times a second
	};

	button2.onClick = [this]()
	{
		DBG("Button2's size: " << this->button2.getBounds().toString());
		timerThing.startTimerHz(4);  //This one is 4 times a second
	};
	*/
}

void DualButton::resized()
{
	auto bounds = getLocalBounds();
	button1.setBounds(bounds.removeFromLeft(30));
	button2.setBounds(bounds);
	//Say previously our local bounds was 100 pixels wide, now we 
	//have a rectangle who's bounds is 70 pixels wide and that 
	//30 pixel wide rectangle has been passed to button1.
}

void DualButton::setButton1Handler(std::function<void()> f)
{
	button1.onClick = f;
}

void DualButton::setButton2Handler(std::function<void()> f)
{
	button2.onClick = f;
}

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
	addAndMakeVisible(dualButton);

	dualButton.setButton1Handler([this]()
		{
			repeatingThing.startTimerHz(2);
		});
	
	dualButton.setButton2Handler([this]()
		{
			repeatingThing.startTimerHz(4);
		});

	addAndMakeVisible(repeatingThing);
	addAndMakeVisible(hiResGui);

//	addAndMakeVisible(renderer);

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

	dualButton.setBounds(comp.getBounds()
							.withX(comp.getRight() + 5));
	//It's actually NOT using chaining because
	//Rectangle<>::getBounds() returns a COPY, not a reference
	//The rectangle supplied to dualButton.setBounds() is a
	//temporary because of this.

	repeatingThing.setBounds(dualButton.getBounds().withX(dualButton.getRight() + 5));

	hiResGui.setBounds(repeatingThing.getBounds().withX(repeatingThing.getRight() + 5));

	//renderer.setBounds(hiResGui.getBounds().withX(hiResGui.getRight() + 5));
}
