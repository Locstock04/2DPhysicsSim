#pragma once
#include "Application.h"
#include "Lochiengine.h"

class LochiengineApplication : public Application
{
private:
	Lochiengine lochiengine;

public:
	LochiengineApplication();
	~LochiengineApplication();
	LochiengineApplication(const LochiengineApplication& other) = delete;
	LochiengineApplication& operator=(const LochiengineApplication& other) = delete;

	void Update(float delta) override;
	void OnLeftClick() override;
	void OnRightClick() override;
};

