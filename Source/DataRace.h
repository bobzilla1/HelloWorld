/*
  ==============================================================================

    DataRace.h
    Created: 14 Jan 2021 8:49:20pm
    Author:  bobby

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

struct Data
{
	uint64 a = 0;
	uint64 b = 0;

	bool operator==(const Data& other);
	bool operator!=(const Data& other);
};

const Data a = { 0xaaaaaaaa, 0xaaaaaaaa };
const Data b = { 0xffffffff, 0xffffffff };

struct A : Thread
{
	A(Data& _x) : Thread("A"), x(_x) { startThread(); }
	~A() { stopThread(100); }
	void run() override;
	Data& x;
};

struct B : Thread
{
	B(Data& _x) : Thread("B"), x(_x) { startThread(); }
	~B() { stopThread(100); }
	void run() override;
	Data& x;
};

struct Test
{
	Data data;
	A a {data};
	B b {data};
};