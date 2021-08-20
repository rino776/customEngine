#pragma once


class Component
{
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual int getID() = 0; //check ComponentIDs.txt for next num to implement
	
};

